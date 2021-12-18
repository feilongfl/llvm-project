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

static MCInstrInfo *createV800MCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  return X;
}

static MCRegisterInfo *createV800MCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  return X;
}

static MCSubtargetInfo *
createV800MCSubtargetInfo(const Triple &TT, StringRef CPU, StringRef FS) {
  const llvm::MCSchedModel NoSchedModel = {};

  const llvm::SubtargetSubTypeKV PD[] = {
    { "temp_subtype", { { { 0x0ULL, 0x0ULL, 0x0ULL, 0x0ULL, } } }, { { { 0x0ULL, 0x0ULL, 0x0ULL, 0x0ULL, } } }, &NoSchedModel },
  };

  llvm::SubtargetFeatureKV PF[] = {
    { "temp_feature", "feature placehold", 0x0ULL, { { { 0x0ULL, 0x0ULL, 0x0ULL, 0x0ULL, } } } },
  };

  const llvm::MCWriteProcResEntry WriteProcResTable[] = {{}};
  const llvm::MCWriteLatencyEntry WriteLatencyTable[] = {{}};
  const llvm::MCReadAdvanceEntry ReadAdvanceTable[] = {{}};

  MCSubtargetInfo *X = new MCSubtargetInfo(TT, CPU, CPU, FS,
                  PF, PD,
                  WriteProcResTable, WriteLatencyTable,
                  ReadAdvanceTable, nullptr,
                  nullptr, nullptr );

  return X;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeV800TargetMC() {
  Target &T = getTheV800Target();

  RegisterMCAsmInfo<V800MCAsmInfo> X(T);
  TargetRegistry::RegisterMCInstrInfo(T, createV800MCInstrInfo);
  TargetRegistry::RegisterMCRegInfo(T, createV800MCRegisterInfo);
  TargetRegistry::RegisterMCSubtargetInfo(T, createV800MCSubtargetInfo);
}
