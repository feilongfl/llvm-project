//===-- G3KHTargetInfo.cpp - G3KH Target Implementation ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "TargetInfo/G3KHTargetInfo.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

Target &llvm::getTheG3KHTarget() {
  static Target TheG3KHTarget;
  return TheG3KHTarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeG3KHTargetInfo() {
  RegisterTarget<Triple::g3kh> X(getTheG3KHTarget(), "g3kh",
                                   "G3KH [experimental]", "G3KH");
}
