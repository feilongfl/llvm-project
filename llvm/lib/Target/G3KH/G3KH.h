//==-- G3KH.h - Top-level interface for G3KH representation --*- C++ -*-==//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in
// the LLVM G3KH backend.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_G3KH_G3KH_H
#define LLVM_LIB_TARGET_G3KH_G3KH_H

#include "MCTargetDesc/G3KHMCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace G3KHCC {
  // G3KH specific condition code.
  enum CondCodes {
    COND_E  = 0,  // aka COND_Z
    COND_NE = 1,  // aka COND_NZ
    COND_HS = 2,  // aka COND_C
    COND_LO = 3,  // aka COND_NC
    COND_GE = 4,
    COND_L  = 5,
    COND_N  = 6,  // jump if negative
    COND_NONE,    // unconditional

    COND_INVALID = -1
  };
}

namespace llvm {
  class G3KHTargetMachine;
  class FunctionPass;

  FunctionPass *createG3KHISelDag(G3KHTargetMachine &TM,
                                    CodeGenOpt::Level OptLevel);

  FunctionPass *createG3KHBranchSelectionPass();

} // end namespace llvm;

#endif
