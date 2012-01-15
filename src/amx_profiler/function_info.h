// AMX profiler for SA-MP server: http://sa-mp.com
//
// Copyright (C) 2011-2012 Sergey Zolotarev
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

#ifndef AMX_PROFILER_FUNCTION_INFO_H
#define AMX_PROFILER_FUNCTION_INFO_H

#include <memory>
#include "performance_counter.h"

namespace amx_profiler {

class Function;

class FunctionInfo {
public:
	friend class Function;

	explicit FunctionInfo(std::shared_ptr<Function> f);

	std::shared_ptr<Function> function() const;

	long &num_calls();
	const long &num_calls() const;

	TimeInterval &total_time();
	const TimeInterval &total_time() const;

	TimeInterval &child_time();
	const TimeInterval &child_time() const;

private:
	std::shared_ptr<Function> func_;

	long num_calls_;
	TimeInterval total_time_;
	TimeInterval child_time_;
};

} // namespace amx_profiler

#endif // !AMX_PROFILER_FUNCTION_INFO_H