// AMX profiler for SA-MP server: http://sa-mp.com
//
// Copyright (C) 2011 Sergey Zolotarev
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

#include <fstream>
#include <string>

#include <boost/date_time.hpp>

#include "function.h"
#include "function_profile.h"
#include "html_printer.h"
#include "timer.h"

namespace samp_profiler {

void HtmlPrinter::Print(const std::string &script_name, std::ostream &stream, 
		const std::vector<FunctionProfile> &stats) 
{
	stream << 
	"<html>\n"
	"<head>\n"
	"	<title>" << "Profile of '" << script_name << "'</title>\n"
	"</head>\n\n"
	"<body>"
	"	<h1>" << 
	"		Profile of '" << script_name << "'"
	"	</h1>\n"
	"	<h2>Generated on " << boost::posix_time::second_clock::local_time() << 
	"	</h2>"
	"	<table id=\"stats\" class=\"tablesorter\" border=\"1\" width=\"100%\">\n"
	"		<thead>\n"
	"			<tr>\n"
	"				<th>Type</th>\n"
	"				<th>Name</th>\n"
	"				<th>Calls</th>\n"
	"				<th>Self Time</th>\n"
	"				<th>Total Time</th>\n"
	"			</tr>\n"
	"		</thead>\n"
	"		<tbody>\n"
	;

	Timer::TimeType time_all = 0;
	for (std::vector<FunctionProfile>::const_iterator it = stats.begin(); it != stats.end(); ++it) {
		time_all += it->total_time() - it->child_time();
	}    

	Timer::TimeType total_time_all = 0;
	for (std::vector<FunctionProfile>::const_iterator it = stats.begin(); it != stats.end(); ++it) {
		total_time_all += it->total_time();
	}

	for (std::vector<FunctionProfile>::const_iterator it = stats.begin(); it != stats.end(); ++it) {
		stream 
		<< "		<tr>\n"
		<< "			<td>" << it->function()->type() << "</td>\n"
		<< "			<td>" << it->function()->name() << "</td>\n"
		<< "			<td>" << it->num_calls() << "</td>\n"
		<< "			<td>" << std::fixed << std::setprecision(2) 
			<< static_cast<double>((it->total_time() - it->child_time()) * 100) / time_all << "</td>\n"
		<< "			<td>" << std::fixed << std::setprecision(2) 
			<< static_cast<double>(it->total_time() * 100) / total_time_all << "</td>\n"
		<< "		</tr>\n";
	}

	stream << 
	"		</tbody>\n"
	"	</table>\n"
	;

	stream <<
	"	<script type=\"text/javascript\"\n"
	"		src=\"http://code.jquery.com/jquery-latest.min.js\"></script>\n"
	"	<script type=\"text/javascript\"\n"
	"		src=\"http://autobahn.tablesorter.com/jquery.tablesorter.min.js\"></script>\n"
	"	<script type=\"text/javascript\">\n"
	"	$(document).ready(function() {\n"
	"		$(\"#stats\").tablesorter();\n"
	"	});\n"
	"	</script>\n"
	"</body>\n"
	"</html>\n"
	;
}

} // namespace samp_profiler
