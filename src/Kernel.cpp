// Copyright 2015 Alessio Sclocco <a.sclocco@vu.nl>
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

#include <Kernel.hpp>

namespace isa {
namespace OpenCL {

KernelConf::KernelConf() : nrThreadsD0(1), nrThreadsD1(1), nrThreadsD2(1), nrItemsD0(1), nrItemsD1(1), nrItemsD2(1) {}

KernelConf::~KernelConf() {}

std::string KernelConf::print() const {
  return isa::utils::toString(nrThreadsD0) + " " + isa::utils::toString(nrThreadsD1) + " " + isa::utils::toString(nrThreadsD2) + " " + isa::utils::toString(nrItemsD0) + " " + isa::utils::toString(nrItemsD1) + " " + isa::utils::toString(nrItemsD2);
}

cl::Kernel * compile(const std::string & name, const std::string & code, const std::string & flags, cl::Context & clContext, cl::Device & clDevice) {
  cl::Program * program = 0;
  cl::Kernel * kernel = 0;
  try {
    cl::Program::Sources sources(1, std::make_pair(code.c_str(), code.length()));
    program = new cl::Program(clContext, sources, NULL);
    program->build(std::vector<cl::Device>(1, clDevice), flags.c_str(), NULL, NULL);
  } catch ( cl::Error & err ) {
    throw isa::OpenCL::OpenCLError("ERROR: OpenCL build error \"" + program->getBuildInfo<CL_PROGRAM_BUILD_LOG>(clDevice) + "\"");
  }
  try {
    kernel = new cl::Kernel(*program, name.c_str(), NULL);
    delete program;
  } catch ( cl::Error &err ) {
    throw isa::OpenCL::OpenCLError("ERROR: OpenCL kernel error \"" + isa::utils::toString<cl_int>(err.err()) + "\"");
  }

  return kernel;
}

} // OpenCL
} // isa

