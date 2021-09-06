//===-- G3KHMCAsmInfo.cpp - G3KH asm properties -----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the declarations of the G3KHMCAsmInfo properties.
//
//===----------------------------------------------------------------------===//

#include "G3KHMCAsmInfo.h"
using namespace llvm;

void G3KHMCAsmInfo::anchor() { }

G3KHMCAsmInfo::G3KHMCAsmInfo(const Triple &TT,
                                 const MCTargetOptions &Options) {
  CodePointerSize = CalleeSaveStackSlotSize = 2;

  CommentString = ";";
  SeparatorString = "{";

  AlignmentIsInBytes = false;
  UsesELFSectionDirectiveForBSS = true;

  SupportsDebugInformation = true;
}
