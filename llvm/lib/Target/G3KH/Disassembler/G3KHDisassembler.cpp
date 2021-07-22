//===-- G3KHDisassembler.cpp - Disassembler for G3KH ------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements the G3KHDisassembler class.
//
//===----------------------------------------------------------------------===//

#include "G3KH.h"
#include "MCTargetDesc/G3KHMCTargetDesc.h"
#include "TargetInfo/G3KHTargetInfo.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCDisassembler/MCDisassembler.h"
#include "llvm/MC/MCFixedLenDisassembler.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/Endian.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "g3kh-disassembler"

typedef MCDisassembler::DecodeStatus DecodeStatus;

namespace {
class G3KHDisassembler : public MCDisassembler {
  DecodeStatus getInstructionI(MCInst &MI, uint64_t &Size,
                               ArrayRef<uint8_t> Bytes, uint64_t Address,
                               raw_ostream &CStream) const;

  DecodeStatus getInstructionII(MCInst &MI, uint64_t &Size,
                                ArrayRef<uint8_t> Bytes, uint64_t Address,
                                raw_ostream &CStream) const;

  DecodeStatus getInstructionCJ(MCInst &MI, uint64_t &Size,
                                ArrayRef<uint8_t> Bytes, uint64_t Address,
                                raw_ostream &CStream) const;

public:
  G3KHDisassembler(const MCSubtargetInfo &STI, MCContext &Ctx)
      : MCDisassembler(STI, Ctx) {}

  DecodeStatus getInstruction(MCInst &MI, uint64_t &Size,
                              ArrayRef<uint8_t> Bytes, uint64_t Address,
                              raw_ostream &CStream) const override;
};
} // end anonymous namespace

static MCDisassembler *createG3KHDisassembler(const Target &T,
                                                const MCSubtargetInfo &STI,
                                                MCContext &Ctx) {
  return new G3KHDisassembler(STI, Ctx);
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeG3KHDisassembler() {
  TargetRegistry::RegisterMCDisassembler(getTheG3KHTarget(),
                                         createG3KHDisassembler);
}

static const unsigned GR8DecoderTable[] = {
  G3KH::SPB,  G3KH::TPB,  G3KH::EPB,
  G3KH::R1B,  G3KH::R2B,  G3KH::R6B,  G3KH::R7B,
  G3KH::R8B,  G3KH::R9B,  G3KH::R10B, G3KH::R11B,
  G3KH::R12B, G3KH::R13B, G3KH::R14B, G3KH::R15B
};

static DecodeStatus DecodeGR8RegisterClass(MCInst &MI, uint64_t RegNo,
                                           uint64_t Address,
                                           const void *Decoder) {
  if (RegNo > 15)
    return MCDisassembler::Fail;

  unsigned Reg = GR8DecoderTable[RegNo];
  MI.addOperand(MCOperand::createReg(Reg));
  return MCDisassembler::Success;
}

static const unsigned GR16DecoderTable[] = {
  G3KH::PC,  G3KH::SP,  G3KH::TP,  G3KH::EP,
  G3KH::R1,  G3KH::R2,  G3KH::R6,  G3KH::R7,
  G3KH::R8,  G3KH::R9,  G3KH::R10, G3KH::R11,
  G3KH::R12, G3KH::R13, G3KH::R14, G3KH::R15
};

static DecodeStatus DecodeGR16RegisterClass(MCInst &MI, uint64_t RegNo,
                                            uint64_t Address,
                                            const void *Decoder) {
  if (RegNo > 15)
    return MCDisassembler::Fail;

  unsigned Reg = GR16DecoderTable[RegNo];
  MI.addOperand(MCOperand::createReg(Reg));
  return MCDisassembler::Success;
}

static DecodeStatus DecodeEPImm(MCInst &MI, uint64_t Bits, uint64_t Address,
                                const void *Decoder);

static DecodeStatus DecodeMemOperand(MCInst &MI, uint64_t Bits,
                                     uint64_t Address,
                                     const void *Decoder);

#include "G3KHGenDisassemblerTables.inc"

static DecodeStatus DecodeEPImm(MCInst &MI, uint64_t Bits, uint64_t Address,
                                const void *Decoder) {
  int64_t Imm;
  switch (Bits) {
  default:
    llvm_unreachable("Invalid immediate value");
  case 0x22: Imm =  4; break;
  case 0x32: Imm =  8; break;
  case 0x03: Imm =  0; break;
  case 0x13: Imm =  1; break;
  case 0x23: Imm =  2; break;
  case 0x33: Imm = -1; break;
  }
  MI.addOperand(MCOperand::createImm(Imm));
  return MCDisassembler::Success;
}

static DecodeStatus DecodeMemOperand(MCInst &MI, uint64_t Bits,
                                     uint64_t Address,
                                     const void *Decoder) {
  unsigned Reg = Bits & 15;
  unsigned Imm = Bits >> 4;

  if (DecodeGR16RegisterClass(MI, Reg, Address, Decoder) !=
      MCDisassembler::Success)
    return MCDisassembler::Fail;
  
  MI.addOperand(MCOperand::createImm((int16_t)Imm));
  return MCDisassembler::Success;
}

enum AddrMode {
  amInvalid = 0,
  amRegister,
  amIndexed,
  amIndirect,
  amIndirectPost,
  amSymbolic,
  amImmediate,
  amAbsolute,
  amConstant
};

static AddrMode DecodeSrcAddrMode(unsigned Rs, unsigned As) {
  switch (Rs) {
  case 0:
    if (As == 1) return amSymbolic;
    if (As == 2) return amInvalid;
    if (As == 3) return amImmediate;
    break;
  case 2:
    if (As == 1) return amAbsolute;
    if (As == 2) return amConstant;
    if (As == 3) return amConstant;
    break;
  case 3:
    return amConstant;
  default:
    break;
  }
  switch (As) {
  case 0: return amRegister;
  case 1: return amIndexed;
  case 2: return amIndirect;
  case 3: return amIndirectPost;
  default:
    llvm_unreachable("As out of range");
  }
}

static AddrMode DecodeSrcAddrModeI(unsigned Insn) {
  unsigned Rs = fieldFromInstruction(Insn, 8, 4);
  unsigned As = fieldFromInstruction(Insn, 4, 2);
  return DecodeSrcAddrMode(Rs, As);
}

static AddrMode DecodeSrcAddrModeII(unsigned Insn) {
  unsigned Rs = fieldFromInstruction(Insn, 0, 4);
  unsigned As = fieldFromInstruction(Insn, 4, 2);
  return DecodeSrcAddrMode(Rs, As);
}

static AddrMode DecodeDstAddrMode(unsigned Insn) {
  unsigned Rd = fieldFromInstruction(Insn, 0, 4);
  unsigned Ad = fieldFromInstruction(Insn, 7, 1);
  switch (Rd) {
  case 0: return Ad ? amSymbolic : amRegister;
  case 2: return Ad ? amAbsolute : amRegister;
  default:
    break;
  }
  return Ad ? amIndexed : amRegister;
}

static const uint8_t *getDecoderTable(AddrMode SrcAM, unsigned Words) {
  assert(0 < Words && Words < 4 && "Incorrect number of words");
  switch (SrcAM) {
  default:
    llvm_unreachable("Invalid addressing mode");
  case amRegister:
    assert(Words < 3 && "Incorrect number of words");
    return Words == 2 ? DecoderTableAlpha32 : DecoderTableAlpha16;
  case amConstant:
    assert(Words < 3 && "Incorrect number of words");
    return Words == 2 ? DecoderTableBeta32 : DecoderTableBeta16;
  case amIndexed:
  case amSymbolic:
  case amImmediate:
  case amAbsolute:
    assert(Words > 1 && "Incorrect number of words");
    return Words == 2 ? DecoderTableGamma32 : DecoderTableGamma48;
  case amIndirect:
  case amIndirectPost:
    assert(Words < 3 && "Incorrect number of words");
    return Words == 2 ? DecoderTableDelta32 : DecoderTableDelta16;
  }
}

DecodeStatus G3KHDisassembler::getInstructionI(MCInst &MI, uint64_t &Size,
                                                 ArrayRef<uint8_t> Bytes,
                                                 uint64_t Address,
                                                 raw_ostream &CStream) const {
  uint64_t Insn = support::endian::read16le(Bytes.data());
  AddrMode SrcAM = DecodeSrcAddrModeI(Insn);
  AddrMode DstAM = DecodeDstAddrMode(Insn);
  if (SrcAM == amInvalid || DstAM == amInvalid) {
    Size = 2; // skip one word and let disassembler to try further
    return MCDisassembler::Fail;
  }

  unsigned Words = 1;
  switch (SrcAM) {
  case amIndexed:
  case amSymbolic:
  case amImmediate:
  case amAbsolute:
    if (Bytes.size() < (Words + 1) * 2) {
      Size = 2;
      return DecodeStatus::Fail;
    }
    Insn |= (uint64_t)support::endian::read16le(Bytes.data() + 2) << 16;
    ++Words;
    break;
  default:
    break;
  }
  switch (DstAM) {
  case amIndexed:
  case amSymbolic:
  case amAbsolute:
    if (Bytes.size() < (Words + 1) * 2) {
      Size = 2;
      return DecodeStatus::Fail;
    }
    Insn |= (uint64_t)support::endian::read16le(Bytes.data() + Words * 2)
        << (Words * 16);
    ++Words;
    break;
  default:
    break;
  }

  DecodeStatus Result = decodeInstruction(getDecoderTable(SrcAM, Words), MI,
                                          Insn, Address, this, STI);
  if (Result != MCDisassembler::Fail) {
    Size = Words * 2;
    return Result;
  }

  Size = 2;
  return DecodeStatus::Fail;
}

DecodeStatus G3KHDisassembler::getInstructionII(MCInst &MI, uint64_t &Size,
                                                  ArrayRef<uint8_t> Bytes,
                                                  uint64_t Address,
                                                  raw_ostream &CStream) const {
  uint64_t Insn = support::endian::read16le(Bytes.data());
  AddrMode SrcAM = DecodeSrcAddrModeII(Insn);
  if (SrcAM == amInvalid) {
    Size = 2; // skip one word and let disassembler to try further
    return MCDisassembler::Fail;
  }

  unsigned Words = 1;
  switch (SrcAM) {
  case amIndexed:
  case amSymbolic:
  case amImmediate:
  case amAbsolute:
    if (Bytes.size() < (Words + 1) * 2) {
      Size = 2;
      return DecodeStatus::Fail;
    }
    Insn |= (uint64_t)support::endian::read16le(Bytes.data() + 2) << 16;
    ++Words;
    break;
  default:
    break;
  }

  const uint8_t *DecoderTable = Words == 2 ? DecoderTable32 : DecoderTable16;
  DecodeStatus Result = decodeInstruction(DecoderTable, MI, Insn, Address,
                                          this, STI);
  if (Result != MCDisassembler::Fail) {
    Size = Words * 2;
    return Result;
  }

  Size = 2;
  return DecodeStatus::Fail;
}

static G3KHCC::CondCodes getCondCode(unsigned Cond) {
  switch (Cond) {
  case 0: return G3KHCC::COND_NE;
  case 1: return G3KHCC::COND_E;
  case 2: return G3KHCC::COND_LO;
  case 3: return G3KHCC::COND_HS;
  case 4: return G3KHCC::COND_N;
  case 5: return G3KHCC::COND_GE;
  case 6: return G3KHCC::COND_L;
  case 7: return G3KHCC::COND_NONE;
  default:
    llvm_unreachable("Cond out of range");
  }
}

DecodeStatus G3KHDisassembler::getInstructionCJ(MCInst &MI, uint64_t &Size,
                                                  ArrayRef<uint8_t> Bytes,
                                                  uint64_t Address,
                                                  raw_ostream &CStream) const {
  uint64_t Insn = support::endian::read16le(Bytes.data());
  unsigned Cond = fieldFromInstruction(Insn, 10, 3);
  unsigned Offset = fieldFromInstruction(Insn, 0, 10);

  MI.addOperand(MCOperand::createImm(SignExtend32(Offset, 10)));

  if (Cond == 7)
    MI.setOpcode(G3KH::JMP);
  else {
    MI.setOpcode(G3KH::JCC);
    MI.addOperand(MCOperand::createImm(getCondCode(Cond)));
  }

  Size = 2;
  return DecodeStatus::Success;
}

DecodeStatus G3KHDisassembler::getInstruction(MCInst &MI, uint64_t &Size,
                                                ArrayRef<uint8_t> Bytes,
                                                uint64_t Address,
                                                raw_ostream &CStream) const {
  if (Bytes.size() < 2) {
    Size = 0;
    return MCDisassembler::Fail;
  }

  uint64_t Insn = support::endian::read16le(Bytes.data());
  unsigned Opc = fieldFromInstruction(Insn, 13, 3);
  switch (Opc) {
  case 0:
    return getInstructionII(MI, Size, Bytes, Address, CStream);
  case 1:
    return getInstructionCJ(MI, Size, Bytes, Address, CStream);
  default:
    return getInstructionI(MI, Size, Bytes, Address, CStream);
  }
}
