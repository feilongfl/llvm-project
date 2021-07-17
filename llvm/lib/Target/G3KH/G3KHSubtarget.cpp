//===-- G3KHSubtarget.cpp - G3KH Subtarget Information ----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements the G3KH specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#include "G3KHSubtarget.h"
#include "G3KH.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "g3kh-subtarget"

static cl::opt<G3KHSubtarget::HWMultEnum>
HWMultModeOption("mhwmult", cl::Hidden,
           cl::desc("Hardware multiplier use mode for G3KH"),
           cl::init(G3KHSubtarget::NoHWMult),
           cl::values(
             clEnumValN(G3KHSubtarget::NoHWMult, "none",
                "Do not use hardware multiplier"),
             clEnumValN(G3KHSubtarget::HWMult16, "16bit",
                "Use 16-bit hardware multiplier"),
             clEnumValN(G3KHSubtarget::HWMult32, "32bit",
                "Use 32-bit hardware multiplier"),
             clEnumValN(G3KHSubtarget::HWMultF5, "f5series",
                "Use F5 series hardware multiplier")));

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "G3KHGenSubtargetInfo.inc"

void G3KHSubtarget::anchor() { }

G3KHSubtarget &
G3KHSubtarget::initializeSubtargetDependencies(StringRef CPU, StringRef FS) {
  ExtendedInsts = false;
  HWMultMode = NoHWMult;

  StringRef CPUName = CPU;
  if (CPUName.empty())
    CPUName = "g3kh";

  ParseSubtargetFeatures(CPUName, /*TuneCPU*/ CPUName, FS);

  if (HWMultModeOption != NoHWMult)
    HWMultMode = HWMultModeOption;

  return *this;
}

G3KHSubtarget::G3KHSubtarget(const Triple &TT, const std::string &CPU,
                                 const std::string &FS, const TargetMachine &TM)
    : G3KHGenSubtargetInfo(TT, CPU, /*TuneCPU*/ CPU, FS), FrameLowering(),
      InstrInfo(initializeSubtargetDependencies(CPU, FS)), TLInfo(TM, *this) {}
