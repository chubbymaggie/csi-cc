//===----------------------- LocalCoveragePass.h --------------------------===//
//
// Superclass for all program coverage passes that gather stack-local coverage
// data.  Shared functionality includes: declaration of local arrays, and
// storage of boolean data.
//
//===----------------------------------------------------------------------===//
//
// Copyright (c) 2016 Peter J. Ohmann and Benjamin R. Liblit
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
//===----------------------------------------------------------------------===//
#ifndef CSI_LOCAL_COVERAGE_PASS_H
#define CSI_LOCAL_COVERAGE_PASS_H

#include "CoveragePass.h"
#include "SilentInternalOption.h"

#include "llvm_proxy/BasicBlock.h"
#include "llvm_proxy/IRBuilder.h"

namespace llvm
{
  class AllocaInst;
  class Instruction;
}


namespace csi_inst
{
  class LocalCoveragePass : public CoveragePass
  {
  private:
    const std::string &lowerShortName;

  protected:
    struct Options : public CoveragePass::Options
    {
      SilentInternalOption silentInternal;
      Options(const CoveragePassNames &);
    };

    LocalCoveragePass(char &, const CoveragePassNames &);

    struct CoverageArrays
    {
      llvm::GlobalVariable &global;
      llvm::AllocaInst &local;
    };

    CoverageArrays prepareFunction(llvm::Function &, unsigned, const SilentInternalOption &);
    void insertArrayStoreInsts(const CoverageArrays &, unsigned, llvm::IRBuilder<> &) const;

  public:
    void getAnalysisUsage(llvm::AnalysisUsage &) const;
  };
}


#endif	// !CSI_LOCAL_COVERAGE_PASS_H
