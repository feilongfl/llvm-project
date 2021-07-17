//===-- G3KHMCTargetDesc.h - G3KH Target Descriptions -------*- C++ -*-===//
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

#ifndef LLVM_LIB_TARGET_G3KH_MCTARGETDESC_G3KHMCTARGETDESC_H
#define LLVM_LIB_TARGET_G3KH_MCTARGETDESC_G3KHMCTARGETDESC_H

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

/// Creates a machine code emitter for G3KH.
MCCodeEmitter *createG3KHMCCodeEmitter(const MCInstrInfo &MCII,
                                         const MCRegisterInfo &MRI,
                                         MCContext &Ctx);

MCAsmBackend *createG3KHMCAsmBackend(const Target &T,
                                       const MCSubtargetInfo &STI,
                                       const MCRegisterInfo &MRI,
                                       const MCTargetOptions &Options);

MCTargetStreamer *
createG3KHObjectTargetStreamer(MCStreamer &S, const MCSubtargetInfo &STI);

std::unique_ptr<MCObjectTargetWriter>
createG3KHELFObjectWriter(uint8_t OSABI);

} // End llvm namespace

// Defines symbolic names for G3KH registers.
// This defines a mapping from register name to register number.
#define GET_REGINFO_ENUM
#include "G3KHGenRegisterInfo.inc"

// Defines symbolic names for the G3KH instructions.
#define GET_INSTRINFO_ENUM
#include "G3KHGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "G3KHGenSubtargetInfo.inc"

#endif
