//===-- G3KHMCTargetDesc.cpp - G3KH Target Descriptions ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides G3KH specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "G3KHMCTargetDesc.h"
#include "G3KHInstPrinter.h"
#include "G3KHMCAsmInfo.h"
#include "TargetInfo/G3KHTargetInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define GET_INSTRINFO_MC_DESC
#include "G3KHGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "G3KHGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "G3KHGenRegisterInfo.inc"

static MCInstrInfo *createG3KHMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitG3KHMCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createG3KHMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitG3KHMCRegisterInfo(X, G3KH::PC);
  return X;
}

static MCSubtargetInfo *
createG3KHMCSubtargetInfo(const Triple &TT, StringRef CPU, StringRef FS) {
  return createG3KHMCSubtargetInfoImpl(TT, CPU, /*TuneCPU*/ CPU, FS);
}

static MCInstPrinter *createG3KHMCInstPrinter(const Triple &T,
                                                unsigned SyntaxVariant,
                                                const MCAsmInfo &MAI,
                                                const MCInstrInfo &MII,
                                                const MCRegisterInfo &MRI) {
  if (SyntaxVariant == 0)
    return new G3KHInstPrinter(MAI, MII, MRI);
  return nullptr;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeG3KHTargetMC() {
  Target &T = getTheG3KHTarget();

  RegisterMCAsmInfo<G3KHMCAsmInfo> X(T);
  TargetRegistry::RegisterMCInstrInfo(T, createG3KHMCInstrInfo);
  TargetRegistry::RegisterMCRegInfo(T, createG3KHMCRegisterInfo);
  TargetRegistry::RegisterMCSubtargetInfo(T, createG3KHMCSubtargetInfo);
  TargetRegistry::RegisterMCInstPrinter(T, createG3KHMCInstPrinter);
  TargetRegistry::RegisterMCCodeEmitter(T, createG3KHMCCodeEmitter);
  TargetRegistry::RegisterMCAsmBackend(T, createG3KHMCAsmBackend);
  TargetRegistry::RegisterObjectTargetStreamer(
      T, createG3KHObjectTargetStreamer);
}
