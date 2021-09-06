//===-- TOYSubtarget.cpp - TOY Subtarget Information ------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the TOY specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#include "TOYSubtarget.h"
#include "TOY.h"
#include "llvm/Support/TargetRegistry.h"

#define DEBUG_TYPE "toy-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "TOYGenSubtargetInfo.inc"

using namespace llvm;

void TOYSubtarget::anchor() {}

TOYSubtarget::TOYSubtarget(const std::string &TT, const std::string &CPU,
                           const std::string &FS, TOYTargetMachine &TM)
    : TOYGenSubtargetInfo(TT, CPU, FS),
      DL("e-m:e-p:32:32-i1:8:32-i8:8:32-i16:16:32-i64:32-f64:32-a:0:32-n32"),
      InstrInfo(), TLInfo(TM), TSInfo(DL), FrameLowering() {}
