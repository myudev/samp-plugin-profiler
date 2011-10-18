// SA:MP Profiler plugin
//
// Copyright (c) 2011 Zeex
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <algorithm>
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iterator>
#include <list>
#include <map>
#include <string>

#include "amxname.h"
#include "debuginfo.h"
#include "jump.h"
#include "logprintf.h"
#include "plugin.h"
#include "profiler.h"
#include "version.h"

#include "amx/amx.h"

extern void *pAMXFunctions; 

// Symbolic info, used for getting function names
static std::map<AMX*, DebugInfo> debugInfos;

// Both x86 and x86-64 are Little Endian...
static void *AMXAPI DummyAmxAlign(void *v) { return v; }

static uint32_t amx_Exec_addr;
static unsigned char amx_Exec_code[5];

static int AMXAPI Exec(AMX *amx, cell *retval, int index) {
	memcpy(reinterpret_cast<void*>(::amx_Exec_addr), ::amx_Exec_code, 5);

	int error = AMX_ERR_NONE;

	// Check if this script has a profiler attached to it
	Profiler *prof = Profiler::Get(amx);
	if (prof != 0) {
		error =  prof->Exec(retval, index);
	} else {
		error = amx_Exec(amx, retval, index);
	}

	SetJump(reinterpret_cast<void*>(::amx_Exec_addr), (void*)::Exec, ::amx_Exec_code);

	return error;
}

// Replaces back slashes with forward slashes
static std::string ToPortablePath(const std::string &path) {
	std::string fsPath = path;
	std::replace(fsPath.begin(), fsPath.end(), '\\', '/');   
	return fsPath;
}

// Returns true if the .amx should be profiled
static bool WantsProfiler(const std::string &amxName) {
	std::ifstream config("plugins/profiler.cfg");    

	std::istream_iterator<std::string> begin(config);
	std::istream_iterator<std::string> end;

	if (std::find(begin, end, ToPortablePath(amxName)) != end) {
		return true;
	}

	return false;
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData) {
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

	// The server does not export amx_Align* for some reason.
	// They are used in amxdbg.c and amxaux.c, so they must be callable.
	((void**)pAMXFunctions)[PLUGIN_AMX_EXPORT_Align16] = (void*)DummyAmxAlign; // amx_Align16
	((void**)pAMXFunctions)[PLUGIN_AMX_EXPORT_Align32] = (void*)DummyAmxAlign; // amx_Align32
	((void**)pAMXFunctions)[PLUGIN_AMX_EXPORT_Align64] = (void*)DummyAmxAlign; // amx_Align64

	// Hook amx_Exec
	::amx_Exec_addr = reinterpret_cast<uint32_t>(((void**)pAMXFunctions)[PLUGIN_AMX_EXPORT_Exec]);
	SetJump(reinterpret_cast<void*>(::amx_Exec_addr), (void*)::Exec, ::amx_Exec_code);

	logprintf("  Profiler plugin v" VERSION " is OK.");

	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
	return;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx) {
	std::string filename = GetAmxName(amx);
	if (filename.empty()) {
		logprintf("Profiler: Failed to detect .amx name");
		return AMX_ERR_NONE;
	}

	if (!Profiler::IsScriptProfilable(amx)) {
		logprintf("Profiler: %s can't be profiled (are you using -d0?)", filename.c_str());
		return AMX_ERR_NONE;
	}
	 
	if (WantsProfiler(filename)) {
		logprintf("Profiler: Will profile %s", filename.c_str());
		if (DebugInfo::HasDebugInfo(amx)) {
			DebugInfo debugInfo;
			debugInfo.Load(filename);
			if (debugInfo.IsLoaded()) {
				logprintf("Profiler: Loaded debug info from %s", filename.c_str());
				::debugInfos[amx] = debugInfo;
				Profiler::Attach(amx, debugInfo); 
				return AMX_ERR_NONE;
			} else {
				logprintf("Profiler: Error loading debug info from %s", filename.c_str());
			}
		}
		Profiler::Attach(amx);
	} 

	return AMX_ERR_NONE;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx) {
	// Get an instance of Profiler attached to the unloading AMX
	Profiler *prof = Profiler::Get(amx);

	// Detach profiler
	if (prof != 0) {
		// Before doing that, print stats to <amx_file_path>.prof
		std::string name = GetAmxName(amx);
		if (!name.empty()) {
			std::string outfile = name + std::string(".prof");
			logprintf("Profiler: Writing profile to %s", outfile.c_str());
			prof->PrintStats(outfile);
		}
		Profiler::Detach(amx);
	}

	// Free debug info
	std::map<AMX*, DebugInfo>::iterator it = ::debugInfos.find(amx);
	if (it != ::debugInfos.end()) {
		it->second.Free();
		::debugInfos.erase(it);
	}

	return AMX_ERR_NONE;
}
