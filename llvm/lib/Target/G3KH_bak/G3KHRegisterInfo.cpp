//===-- G3KHRegisterInfo.cpp - G3KH Register Information --------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the G3KH implementation of the TargetRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#include "G3KHRegisterInfo.h"
#include "G3KH.h"
#include "G3KHMachineFunctionInfo.h"
#include "G3KHTargetMachine.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"

using namespace llvm;

#define DEBUG_TYPE "g3kh-reg-info"

#define GET_REGINFO_TARGET_DESC
#include "G3KHGenRegisterInfo.inc"

// FIXME: Provide proper call frame setup / destroy opcodes.
G3KHRegisterInfo::G3KHRegisterInfo()
  : G3KHGenRegisterInfo(G3KH::PC) {}

const MCPhysReg*
G3KHRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  // const G3KHFrameLowering *TFI = getFrameLowering(*MF);
  const Function* F = &MF->getFunction();
  static const MCPhysReg CalleeSavedRegs[] = {
    G3KH::R6, G3KH::R7, G3KH::R8, G3KH::R9,
    G3KH::R10, G3KH::R11, G3KH::R12,G3KH::R13,
    G3KH::R14, G3KH::R15, G3KH::R16,G3KH::R17,
    G3KH::R18, G3KH::R19, G3KH::R20,G3KH::R21,
    G3KH::R22, G3KH::R23, G3KH::R24,G3KH::R25,
    G3KH::R26, G3KH::R27, G3KH::R28,G3KH::R29,
    0
  };
  // static const MCPhysReg CalleeSavedRegsFP[] = {
  //   G3KH::R6, G3KH::R7, G3KH::R8, G3KH::R9,
  //   G3KH::R10, G3KH::R11, G3KH::R12,G3KH::R13,
  //   G3KH::R14, G3KH::R15, G3KH::R16,G3KH::R17,
  //   G3KH::R18, G3KH::R19, G3KH::R20,G3KH::R21,
  //   G3KH::R22, G3KH::R23, G3KH::R24,G3KH::R25,
  //   G3KH::R26, G3KH::R27, G3KH::R28,G3KH::R29,
  //   0
  // };
  static const MCPhysReg CalleeSavedRegsIntr[] = {
    G3KH::R6, G3KH::R7, G3KH::R8, G3KH::R9,
    G3KH::R10, G3KH::R11, G3KH::R12,G3KH::R13,
    G3KH::R14, G3KH::R15, G3KH::R16,G3KH::R17,
    G3KH::R18, G3KH::R19, G3KH::R20,G3KH::R21,
    G3KH::R22, G3KH::R23, G3KH::R24,G3KH::R25,
    G3KH::R26, G3KH::R27, G3KH::R28,G3KH::R29,
    0
  };
  // static const MCPhysReg CalleeSavedRegsIntrFP[] = {
  //   G3KH::R6, G3KH::R7, G3KH::R8, G3KH::R9,
  //   G3KH::R10, G3KH::R11, G3KH::R12,G3KH::R13,
  //   G3KH::R14, G3KH::R15, G3KH::R16,G3KH::R17,
  //   G3KH::R18, G3KH::R19, G3KH::R20,G3KH::R21,
  //   G3KH::R22, G3KH::R23, G3KH::R24,G3KH::R25,
  //   G3KH::R26, G3KH::R27, G3KH::R28,G3KH::R29,
  //   0
  // };

  // if (TFI->hasFP(*MF))
    // return (F->getCallingConv() == CallingConv::G3KH_INTR ?
            // CalleeSavedRegsIntrFP : CalleeSavedRegsFP);
  // else
    return (F->getCallingConv() == CallingConv::G3KH_INTR ?
            CalleeSavedRegsIntr : CalleeSavedRegs);

}

BitVector G3KHRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());
  // const G3KHFrameLowering *TFI = getFrameLowering(MF);

  // Mark 4 special registers with subregisters as reserved.
  Reserved.set(G3KH::R0B);
  Reserved.set(G3KH::R1B);
  Reserved.set(G3KH::R2B);
  Reserved.set(G3KH::SPB);
  Reserved.set(G3KH::GPB);
  Reserved.set(G3KH::TPB);
  Reserved.set(G3KH::EPB);
  Reserved.set(G3KH::LPB);
  Reserved.set(G3KH::R0);
  Reserved.set(G3KH::R1);
  Reserved.set(G3KH::R2);
  Reserved.set(G3KH::SP);
  Reserved.set(G3KH::GP);
  Reserved.set(G3KH::TP);
  Reserved.set(G3KH::EP);
  Reserved.set(G3KH::LP);
  Reserved.set(G3KH::PC);

  // Mark frame pointer as reserved if needed.
  // if (TFI->hasFP(MF)) {
  //   Reserved.set(G3KH::R1B);
  //   Reserved.set(G3KH::R1);
  // }

  return Reserved;
}

const TargetRegisterClass *
G3KHRegisterInfo::getPointerRegClass(const MachineFunction &MF, unsigned Kind)
                                                                         const {
  return &G3KH::GR32RegClass;
}

void
G3KHRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                        int SPAdj, unsigned FIOperandNum,
                                        RegScavenger *RS) const {
  assert(SPAdj == 0 && "Unexpected");

  MachineInstr &MI = *II;
  MachineBasicBlock &MBB = *MI.getParent();
  MachineFunction &MF = *MBB.getParent();
  const G3KHFrameLowering *TFI = getFrameLowering(MF);
  DebugLoc dl = MI.getDebugLoc();
  int FrameIndex = MI.getOperand(FIOperandNum).getIndex();

  unsigned BasePtr = (TFI->hasFP(MF) ? G3KH::R1 : G3KH::SP);
  int Offset = MF.getFrameInfo().getObjectOffset(FrameIndex);

  // Skip the saved PC
  Offset += 2;

  if (!TFI->hasFP(MF))
    Offset += MF.getFrameInfo().getStackSize();
  else
    Offset += 2; // Skip the saved FP

  // Fold imm into offset
  Offset += MI.getOperand(FIOperandNum + 1).getImm();

  // if (MI.getOpcode() == G3KH::ADDframe) {
  //   // This is actually "load effective address" of the stack slot
  //   // instruction. We have only two-address instructions, thus we need to
  //   // expand it into mov + add
  //   const TargetInstrInfo &TII = *MF.getSubtarget().getInstrInfo();

  //   MI.setDesc(TII.get(G3KH::MOV16rr));
  //   MI.getOperand(FIOperandNum).ChangeToRegister(BasePtr, false);

  //   if (Offset == 0)
  //     return;

  //   // We need to materialize the offset via add instruction.
  //   Register DstReg = MI.getOperand(0).getReg();
  //   if (Offset < 0)
  //     BuildMI(MBB, std::next(II), dl, TII.get(G3KH::SUB16ri), DstReg)
  //       .addReg(DstReg).addImm(-Offset);
  //   else
  //     BuildMI(MBB, std::next(II), dl, TII.get(G3KH::ADD16ri), DstReg)
  //       .addReg(DstReg).addImm(Offset);

  //   return;
  // }

  MI.getOperand(FIOperandNum).ChangeToRegister(BasePtr, false);
  MI.getOperand(FIOperandNum + 1).ChangeToImmediate(Offset);
}

Register G3KHRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  const G3KHFrameLowering *TFI = getFrameLowering(MF);
  return TFI->hasFP(MF) ? G3KH::R1 : G3KH::SP;
}
