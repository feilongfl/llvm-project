//===-- V800MCTargetDesc.cpp - V800 Target Descriptions ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides V800 specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "V800MCTargetDesc.h"
#include "V800MCAsmInfo.h"
#include "TargetInfo/V800TargetInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define GET_REGINFO_MC_DESC
#include "V800GenRegisterInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "V800GenSubtargetInfo.inc"

static MCInstrInfo *createV800MCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  return X;
}

static MCRegisterInfo *createV800MCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitV800MCRegisterInfo(X, V800::PC);
  return X;
}

static MCSubtargetInfo *
createV800MCSubtargetInfo(const Triple &TT, StringRef CPU, StringRef FS) {
  return createV800MCSubtargetInfoImpl(TT, CPU, CPU, FS);
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeV800TargetMC() {
  Target &T = getTheV800Target();

  RegisterMCAsmInfo<V800MCAsmInfo> X(T);
  TargetRegistry::RegisterMCInstrInfo(T, createV800MCInstrInfo);
  TargetRegistry::RegisterMCRegInfo(T, createV800MCRegisterInfo);
  TargetRegistry::RegisterMCSubtargetInfo(T, createV800MCSubtargetInfo);
}
