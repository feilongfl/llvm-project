//===-- V800TargetInfo.cpp - V800 Target Implementation ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "TargetInfo/V800TargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
using namespace llvm;

Target &llvm::getTheV800Target() {
  static Target TheV800Target;
  return TheV800Target;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeV800TargetInfo() {
  RegisterTarget<Triple::v800> X(getTheV800Target(), "V800",
                                   "V800 [experimental]", "V800");
}
