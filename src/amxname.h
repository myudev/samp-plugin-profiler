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

#ifndef AMXNAME_H
#define AMXNAME_H

#include <ctime>
#include <list>
#include <map>
#include <string>

#ifdef _WIN32
	#include <memory>
#else
	#include <tr/memory>
#endif

#include "amx/amx.h"

std::string GetAmxName(AMX_HEADER *amxhdr);
std::string GetAmxName(AMX *amx);

class AmxFile {
public:
	static void FreeAmx(AMX *amx);

	explicit AmxFile(const std::string &name);

	bool IsLoaded() const { return amxPtr_.get() != 0; }

	const AMX *GetAmx() const { return amxPtr_.get(); }
	const std::string &GetName() const { return name_; }
	std::time_t GetModified() const { return modified_; }

private:
	std::tr1::shared_ptr<AMX> amxPtr_;
	std::string name_;
	std::time_t modified_;
};

#endif