//===-- TOYRegisterInfo.cpp - TOY Register Information ----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the TOY implementation of the MRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#include "TOYRegisterInfo.h"
#include "TOY.h"
#include "TOYInstrInfo.h"
#include "TOYMachineFunctionInfo.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/MathExtras.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetFrameLowering.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"

#define GET_REGINFO_TARGET_DESC
#include "TOYGenRegisterInfo.inc"

using namespace llvm;

TOYRegisterInfo::TOYRegisterInfo() : TOYGenRegisterInfo(TOY::LR) {}

const uint16_t *
TOYRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  static const uint16_t CalleeSavedRegs[] = { TOY::R4, TOY::R5, TOY::R6,
                                              TOY::R7, TOY::R8, TOY::R9,
                                              0 };
  return CalleeSavedRegs;
}

BitVector TOYRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());

  Reserved.set(TOY::SP);
  Reserved.set(TOY::LR);
  return Reserved;
}

const uint32_t *TOYRegisterInfo::getCallPreservedMask(CallingConv::ID) const {
  return CC_Save_RegMask;
}

bool
TOYRegisterInfo::requiresRegisterScavenging(const MachineFunction &MF) const {
  return true;
}

bool
TOYRegisterInfo::trackLivenessAfterRegAlloc(const MachineFunction &MF) const {
  return true;
}

bool TOYRegisterInfo::useFPForScavengingIndex(const MachineFunction &MF) const {
  return false;
}

void TOYRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                          int SPAdj, unsigned FIOperandNum,
                                          RegScavenger *RS) const {
  MachineInstr &MI = *II;
  const MachineFunction &MF = *MI.getParent()->getParent();
  const MachineFrameInfo *MFI = MF.getFrameInfo();
  MachineOperand &FIOp = MI.getOperand(FIOperandNum);
  unsigned FI = FIOp.getIndex();

  // Determine if we can eliminate the index from this kind of instruction.
  unsigned ImmOpIdx = 0;
  switch (MI.getOpcode()) {
  default:
    // Not supported yet.
    return;
  case TOY::LDR:
  case TOY::STR:
    ImmOpIdx = FIOperandNum + 1;
    break;
  }

  // FIXME: check the size of offset.
  MachineOperand &ImmOp = MI.getOperand(ImmOpIdx);
  int Offset = MFI->getObjectOffset(FI) + MFI->getStackSize() + ImmOp.getImm();
  FIOp.ChangeToRegister(TOY::SP, false);
  ImmOp.setImm(Offset);
}

unsigned TOYRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  return TOY::SP;
}
