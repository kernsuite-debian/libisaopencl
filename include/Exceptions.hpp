// Copyright 2014 Alessio Sclocco <a.sclocco@vu.nl>
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

#include <string>
#include <exception>
#include <typeinfo>

#pragma once

namespace isa {
namespace OpenCL {

// Generic OpenCL exception to incapsulate the error message
class OpenCLError : public std::exception {
public:
	explicit OpenCLError(const std::string & message);
	~OpenCLError();

	const char *what() const noexcept;

private:
  std::string message;
};

} // OpenCL
} // isa

