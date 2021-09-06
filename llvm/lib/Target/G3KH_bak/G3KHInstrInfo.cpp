//===-- G3KHInstrInfo.cpp - G3KH Instruction Information --------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the G3KH implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#include "G3KHInstrInfo.h"
#include "G3KH.h"
#include "G3KHMachineFunctionInfo.h"
#include "G3KHTargetMachine.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define GET_INSTRINFO_CTOR_DTOR
#include "G3KHGenInstrInfo.inc"

// Pin the vtable to this file.
void G3KHInstrInfo::anchor() {}

G3KHInstrInfo::G3KHInstrInfo(G3KHSubtarget &STI)
  : G3KHGenInstrInfo(),
    RI() {}

void G3KHInstrInfo::storeRegToStackSlot(MachineBasicBlock &MBB,
                                          MachineBasicBlock::iterator MI,
                                    Register SrcReg, bool isKill, int FrameIdx,
                                          const TargetRegisterClass *RC,
                                          const TargetRegisterInfo *TRI) const {
  DebugLoc DL;
  if (MI != MBB.end()) DL = MI->getDebugLoc();
  MachineFunction &MF = *MBB.getParent();
  MachineFrameInfo &MFI = MF.getFrameInfo();

  MachineMemOperand *MMO = MF.getMachineMemOperand(
      MachinePointerInfo::getFixedStack(MF, FrameIdx),
      MachineMemOperand::MOStore, MFI.getObjectSize(FrameIdx),
      MFI.getObjectAlign(FrameIdx));

  // if (RC == &G3KH::GR16RegClass)
  //   BuildMI(MBB, MI, DL, get(G3KH::MOV16mr))
  //     .addFrameIndex(FrameIdx).addImm(0)
  //     .addReg(SrcReg, getKillRegState(isKill)).addMemOperand(MMO);
  // else if (RC == &G3KH::GR8RegClass)
  //   BuildMI(MBB, MI, DL, get(G3KH::MOV8mr))
  //     .addFrameIndex(FrameIdx).addImm(0)
  //     .addReg(SrcReg, getKillRegState(isKill)).addMemOperand(MMO);
  // else
    llvm_unreachable("Cannot store this register to stack slot!");
}

void G3KHInstrInfo::loadRegFromStackSlot(MachineBasicBlock &MBB,
                                           MachineBasicBlock::iterator MI,
                                           Register DestReg, int FrameIdx,
                                           const TargetRegisterClass *RC,
                                           const TargetRegisterInfo *TRI) const{
  DebugLoc DL;
  if (MI != MBB.end()) DL = MI->getDebugLoc();
  MachineFunction &MF = *MBB.getParent();
  MachineFrameInfo &MFI = MF.getFrameInfo();

  MachineMemOperand *MMO = MF.getMachineMemOperand(
      MachinePointerInfo::getFixedStack(MF, FrameIdx),
      MachineMemOperand::MOLoad, MFI.getObjectSize(FrameIdx),
      MFI.getObjectAlign(FrameIdx));

  // if (RC == &G3KH::GR16RegClass)
  //   BuildMI(MBB, MI, DL, get(G3KH::MOV16rm))
  //     .addReg(DestReg, getDefRegState(true)).addFrameIndex(FrameIdx)
  //     .addImm(0).addMemOperand(MMO);
  // else if (RC == &G3KH::GR8RegClass)
  //   BuildMI(MBB, MI, DL, get(G3KH::MOV8rm))
  //     .addReg(DestReg, getDefRegState(true)).addFrameIndex(FrameIdx)
  //     .addImm(0).addMemOperand(MMO);
  // else
    llvm_unreachable("Cannot store this register to stack slot!");
}

void G3KHInstrInfo::copyPhysReg(MachineBasicBlock &MBB,
                                  MachineBasicBlock::iterator I,
                                  const DebugLoc &DL, MCRegister DestReg,
                                  MCRegister SrcReg, bool KillSrc) const {
  unsigned Opc;
  // if (G3KH::GR16RegClass.contains(DestReg, SrcReg))
  //   Opc = G3KH::MOV16rr;
  // else if (G3KH::GR8RegClass.contains(DestReg, SrcReg))
  //   Opc = G3KH::MOV8rr;
  // else
    llvm_unreachable("Impossible reg-to-reg copy");

  BuildMI(MBB, I, DL, get(Opc), DestReg)
    .addReg(SrcReg, getKillRegState(KillSrc));
}

unsigned G3KHInstrInfo::removeBranch(MachineBasicBlock &MBB,
                                       int *BytesRemoved) const {
  assert(!BytesRemoved && "code size not handled");

  MachineBasicBlock::iterator I = MBB.end();
  unsigned Count = 0;

  while (I != MBB.begin()) {
    --I;
    if (I->isDebugInstr())
      continue;
    // if (I->getOpcode() != G3KH::JMP &&
    //     I->getOpcode() != G3KH::JCC &&
    //     I->getOpcode() != G3KH::Br &&
    //     I->getOpcode() != G3KH::Bm)
    //   break;
    // Remove the branch.
    I->eraseFromParent();
    I = MBB.end();
    ++Count;
  }

  return Count;
}

bool G3KHInstrInfo::
reverseBranchCondition(SmallVectorImpl<MachineOperand> &Cond) const {
  assert(Cond.size() == 1 && "Invalid Xbranch condition!");

  G3KHCC::CondCodes CC = static_cast<G3KHCC::CondCodes>(Cond[0].getImm());

  switch (CC) {
  default: llvm_unreachable("Invalid branch condition!");
  case G3KHCC::COND_E:
    CC = G3KHCC::COND_NE;
    break;
  case G3KHCC::COND_NE:
    CC = G3KHCC::COND_E;
    break;
  case G3KHCC::COND_L:
    CC = G3KHCC::COND_GE;
    break;
  case G3KHCC::COND_GE:
    CC = G3KHCC::COND_L;
    break;
  case G3KHCC::COND_HS:
    CC = G3KHCC::COND_LO;
    break;
  case G3KHCC::COND_LO:
    CC = G3KHCC::COND_HS;
    break;
  }

  Cond[0].setImm(CC);
  return false;
}

bool G3KHInstrInfo::analyzeBranch(MachineBasicBlock &MBB,
                                    MachineBasicBlock *&TBB,
                                    MachineBasicBlock *&FBB,
                                    SmallVectorImpl<MachineOperand> &Cond,
                                    bool AllowModify) const {
  // Start from the bottom of the block and work up, examining the
  // terminator instructions.
  MachineBasicBlock::iterator I = MBB.end();
  while (I != MBB.begin()) {
    --I;
    if (I->isDebugInstr())
      continue;

    // Working from the bottom, when we see a non-terminator
    // instruction, we're done.
    if (!isUnpredicatedTerminator(*I))
      break;

    // A terminator that isn't a branch can't easily be handled
    // by this analysis.
    if (!I->isBranch())
      return true;

    // Cannot handle indirect branches.
    // if (I->getOpcode() == G3KH::Br ||
    //     I->getOpcode() == G3KH::Bm)
    //   return true;

    // // Handle unconditional branches.
    // if (I->getOpcode() == G3KH::JMP) {
    //   if (!AllowModify) {
    //     TBB = I->getOperand(0).getMBB();
    //     continue;
    //   }

    //   // If the block has any instructions after a JMP, delete them.
    //   while (std::next(I) != MBB.end())
    //     std::next(I)->eraseFromParent();
    //   Cond.clear();
    //   FBB = nullptr;

    //   // Delete the JMP if it's equivalent to a fall-through.
    //   if (MBB.isLayoutSuccessor(I->getOperand(0).getMBB())) {
    //     TBB = nullptr;
    //     I->eraseFromParent();
    //     I = MBB.end();
    //     continue;
    //   }

    //   // TBB is used to indicate the unconditinal destination.
    //   TBB = I->getOperand(0).getMBB();
    //   continue;
    // }

    // Handle conditional branches.
    // assert(I->getOpcode() == G3KH::JCC && "Invalid conditional branch");
    G3KHCC::CondCodes BranchCode =
      static_cast<G3KHCC::CondCodes>(I->getOperand(1).getImm());
    if (BranchCode == G3KHCC::COND_INVALID)
      return true;  // Can't handle weird stuff.

    // Working from the bottom, handle the first conditional branch.
    if (Cond.empty()) {
      FBB = TBB;
      TBB = I->getOperand(0).getMBB();
      Cond.push_back(MachineOperand::CreateImm(BranchCode));
      continue;
    }

    // Handle subsequent conditional branches. Only handle the case where all
    // conditional branches branch to the same destination.
    assert(Cond.size() == 1);
    assert(TBB);

    // Only handle the case where all conditional branches branch to
    // the same destination.
    if (TBB != I->getOperand(0).getMBB())
      return true;

    G3KHCC::CondCodes OldBranchCode = (G3KHCC::CondCodes)Cond[0].getImm();
    // If the conditions are the same, we can leave them alone.
    if (OldBranchCode == BranchCode)
      continue;

    return true;
  }

  return false;
}

unsigned G3KHInstrInfo::insertBranch(MachineBasicBlock &MBB,
                                       MachineBasicBlock *TBB,
                                       MachineBasicBlock *FBB,
                                       ArrayRef<MachineOperand> Cond,
                                       const DebugLoc &DL,
                                       int *BytesAdded) const {
  // Shouldn't be a fall through.
  assert(TBB && "insertBranch must not be told to insert a fallthrough");
  assert((Cond.size() == 1 || Cond.size() == 0) &&
         "G3KH branch conditions have one component!");
  assert(!BytesAdded && "code size not handled");

  // if (Cond.empty()) {
  //   // Unconditional branch?
  //   assert(!FBB && "Unconditional branch with multiple successors!");
  //   BuildMI(&MBB, DL, get(G3KH::JMP)).addMBB(TBB);
  //   return 1;
  // }

  // // Conditional branch.
  unsigned Count = 0;
  // BuildMI(&MBB, DL, get(G3KH::JCC)).addMBB(TBB).addImm(Cond[0].getImm());
  // ++Count;

  // if (FBB) {
  //   // Two-way Conditional branch. Insert the second branch.
  //   BuildMI(&MBB, DL, get(G3KH::JMP)).addMBB(FBB);
  //   ++Count;
  // }
  return Count;
}

/// GetInstSize - Return the number of bytes of code the specified
/// instruction may be.  This returns the maximum number of bytes.
///
unsigned G3KHInstrInfo::getInstSizeInBytes(const MachineInstr &MI) const {
  const MCInstrDesc &Desc = MI.getDesc();

  switch (Desc.getOpcode()) {
  case TargetOpcode::CFI_INSTRUCTION:
  case TargetOpcode::EH_LABEL:
  case TargetOpcode::IMPLICIT_DEF:
  case TargetOpcode::KILL:
  case TargetOpcode::DBG_VALUE:
    return 0;
  case TargetOpcode::INLINEASM:
  case TargetOpcode::INLINEASM_BR: {
    const MachineFunction *MF = MI.getParent()->getParent();
    const TargetInstrInfo &TII = *MF->getSubtarget().getInstrInfo();
    return TII.getInlineAsmLength(MI.getOperand(0).getSymbolName(),
                                  *MF->getTarget().getMCAsmInfo());
  }
  }

  return Desc.getSize();
}
