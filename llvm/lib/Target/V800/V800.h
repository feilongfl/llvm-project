//===-- V800.h - Top-level interface for V800 representation --*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in the LLVM
// V800 back-end.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_V800_V800_H
#define LLVM_LIB_TARGET_V800_V800_H

#include "MCTargetDesc/V800MCTargetDesc.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
  class FunctionPass;
  class V800TargetMachine;
  class AsmPrinter;
  class MCInst;
  class MachineInstr;

  FunctionPass *createV800ISelDag(V800TargetMachine &TM);
  FunctionPass *createV800DelaySlotFillerPass();

  void LowerV800MachineInstrToMCInst(const MachineInstr *MI,
                                      MCInst &OutMI,
                                      AsmPrinter &AP);
} // end namespace llvm;

namespace llvm {
  // Enums corresponding to V800 condition codes, both icc's and fcc's.  These
  // values must be kept in sync with the ones in the .td file.
  namespace V800 {
    enum CondCodes {
      BGE = 0b1110; // Greater than or equal to signed
      // todo: add more
    };
  }

  inline static const char *V800CondCodeToString(SPCC::CondCodes CC) {
    switch (CC) {
    case SPCC::BGE:   return "BGE";
    }
    llvm_unreachable("Invalid cond code");
  }

  inline static unsigned HI22(int64_t imm) {
    return (unsigned)((imm >> 10) & ((1 << 22)-1));
  }

  inline static unsigned LO10(int64_t imm) {
    return (unsigned)(imm & 0x3FF);
  }

  inline static unsigned HIX22(int64_t imm) {
    return HI22(~imm);
  }

  inline static unsigned LOX10(int64_t imm) {
    return ~LO10(~imm);
  }

}  // end namespace llvm
#endif
