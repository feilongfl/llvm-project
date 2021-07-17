//===--- G3KH.cpp - Implement G3KH target feature support -------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements G3KH TargetInfo objects.
//
//===----------------------------------------------------------------------===//

#include "G3KH.h"
#include "clang/Basic/MacroBuilder.h"

using namespace clang;
using namespace clang::targets;

const char *const G3KHTargetInfo::GCCRegNames[] = {
    "r0", "r1", "r2",  "r3",  "r4",  "r5",  "r6",  "r7",
    "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15",
    "r16", "r17", "r18", "r19", "r20", "r21", "r22", "r23",
    "r24", "r25", "r26", "r27", "r28", "r29", "r30", "r31",
};

ArrayRef<const char *> G3KHTargetInfo::getGCCRegNames() const {
  return llvm::makeArrayRef(GCCRegNames);
}

void G3KHTargetInfo::getTargetDefines(const LangOptions &Opts,
                                        MacroBuilder &Builder) const {
  Builder.defineMacro("G3KH");
  Builder.defineMacro("__G3KH__");
  Builder.defineMacro("__ELF__");
  // FIXME: defines for different 'flavours' of MCU
}
