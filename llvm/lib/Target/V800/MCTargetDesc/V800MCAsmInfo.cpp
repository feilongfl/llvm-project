//===-- V800MCAsmInfo.cpp - V800 asm properties -----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the declarations of the V800MCAsmInfo properties.
//
//===----------------------------------------------------------------------===//

#include "V800MCAsmInfo.h"
using namespace llvm;

void V800MCAsmInfo::anchor() { }

V800MCAsmInfo::V800MCAsmInfo(const Triple &TT,
                                 const MCTargetOptions &Options) {
  CodePointerSize = CalleeSaveStackSlotSize = 2;

  CommentString = ";";

  UsesELFSectionDirectiveForBSS = true;

  SupportsDebugInformation = true;
}
