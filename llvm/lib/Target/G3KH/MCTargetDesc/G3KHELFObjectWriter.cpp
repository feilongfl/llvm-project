//===-- G3KHELFObjectWriter.cpp - G3KH ELF Writer ---------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/G3KHFixupKinds.h"
#include "MCTargetDesc/G3KHMCTargetDesc.h"

#include "MCTargetDesc/G3KHMCTargetDesc.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCFixup.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCValue.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

namespace {
class G3KHELFObjectWriter : public MCELFObjectTargetWriter {
public:
  G3KHELFObjectWriter(uint8_t OSABI)
    : MCELFObjectTargetWriter(false, OSABI, ELF::EM_G3KH,
                              /*HasRelocationAddend*/ true) {}

  ~G3KHELFObjectWriter() override {}

protected:
  unsigned getRelocType(MCContext &Ctx, const MCValue &Target,
                        const MCFixup &Fixup, bool IsPCRel) const override {
    // Translate fixup kind to ELF relocation type.
    switch (Fixup.getTargetKind()) {
    case FK_Data_1:                   return ELF::R_G3KH_8;
    case FK_Data_2:                   return ELF::R_G3KH_16_BYTE;
    case FK_Data_4:                   return ELF::R_G3KH_32;
    case G3KH::fixup_32:            return ELF::R_G3KH_32;
    case G3KH::fixup_10_pcrel:      return ELF::R_G3KH_10_PCREL;
    case G3KH::fixup_16:            return ELF::R_G3KH_16;
    case G3KH::fixup_16_pcrel:      return ELF::R_G3KH_16_PCREL;
    case G3KH::fixup_16_byte:       return ELF::R_G3KH_16_BYTE;
    case G3KH::fixup_16_pcrel_byte: return ELF::R_G3KH_16_PCREL_BYTE;
    case G3KH::fixup_2x_pcrel:      return ELF::R_G3KH_2X_PCREL;
    case G3KH::fixup_rl_pcrel:      return ELF::R_G3KH_RL_PCREL;
    case G3KH::fixup_8:             return ELF::R_G3KH_8;
    case G3KH::fixup_sym_diff:      return ELF::R_G3KH_SYM_DIFF;
    default:
      llvm_unreachable("Invalid fixup kind");
    }
  }
};
} // end of anonymous namespace

std::unique_ptr<MCObjectTargetWriter>
llvm::createG3KHELFObjectWriter(uint8_t OSABI) {
  return std::make_unique<G3KHELFObjectWriter>(OSABI);
}
