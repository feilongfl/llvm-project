//===-- V800MCTargetDesc.h - V800 Target Descriptions -------*- C++ -*-===//
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

#ifndef LLVM_LIB_TARGET_V800_MCTARGETDESC_V800MCTARGETDESC_H
#define LLVM_LIB_TARGET_V800_MCTARGETDESC_V800MCTARGETDESC_H

#include "llvm/Support/DataTypes.h"
#include <memory>

namespace llvm {
class Target;
class MCAsmBackend;
class MCCodeEmitter;
class MCInstrInfo;
class MCSubtargetInfo;
class MCRegisterInfo;
class MCContext;
class MCTargetOptions;
class MCObjectTargetWriter;
class MCStreamer;
class MCTargetStreamer;

/// Creates a machine code emitter for V800.
MCCodeEmitter *createV800MCCodeEmitter(const MCInstrInfo &MCII,
                                         const MCRegisterInfo &MRI,
                                         MCContext &Ctx);
} // End llvm namespace

#define GET_REGINFO_ENUM
#include "V800GenRegisterInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "V800GenSubtargetInfo.inc"

#endif
