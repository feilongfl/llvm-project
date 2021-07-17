//===-- G3KHELFStreamer.cpp - G3KH ELF Target Streamer Methods --------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides G3KH specific target streamer methods.
//
//===----------------------------------------------------------------------===//

#include "G3KHMCTargetDesc.h"
#include "llvm/BinaryFormat/ELF.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCELFStreamer.h"
#include "llvm/MC/MCSectionELF.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"

using namespace llvm;

namespace llvm {

class G3KHTargetELFStreamer : public MCTargetStreamer {
public:
  MCELFStreamer &getStreamer();
  G3KHTargetELFStreamer(MCStreamer &S, const MCSubtargetInfo &STI);
};

// This part is for ELF object output.
G3KHTargetELFStreamer::G3KHTargetELFStreamer(MCStreamer &S,
                                                 const MCSubtargetInfo &STI)
    : MCTargetStreamer(S) {
  MCAssembler &MCA = getStreamer().getAssembler();
  unsigned EFlags = MCA.getELFHeaderEFlags();
  MCA.setELFHeaderEFlags(EFlags);

  // Emit build attributes section according to
  // G3KH EABI (slaa534.pdf, part 13).
  MCSection *AttributeSection = getStreamer().getContext().getELFSection(
      ".G3KH.attributes", ELF::SHT_G3KH_ATTRIBUTES, 0);
  Streamer.SwitchSection(AttributeSection);

  // Format version.
  Streamer.emitInt8(0x41);
  // Subsection length.
  Streamer.emitInt32(22);
  // Vendor name string, zero-terminated.
  Streamer.emitBytes("mspabi");
  Streamer.emitInt8(0);

  // Attribute vector scope tag. 1 stands for the entire file.
  Streamer.emitInt8(1);
  // Attribute vector length.
  Streamer.emitInt32(11);
  // OFBA_MSPABI_Tag_ISA(4) = 1, G3KH
  Streamer.emitInt8(4);
  Streamer.emitInt8(1);
  // OFBA_MSPABI_Tag_Code_Model(6) = 1, Small
  Streamer.emitInt8(6);
  Streamer.emitInt8(1);
  // OFBA_MSPABI_Tag_Data_Model(8) = 1, Small
  Streamer.emitInt8(8);
  Streamer.emitInt8(1);
}

MCELFStreamer &G3KHTargetELFStreamer::getStreamer() {
  return static_cast<MCELFStreamer &>(Streamer);
}

MCTargetStreamer *
createG3KHObjectTargetStreamer(MCStreamer &S, const MCSubtargetInfo &STI) {
  const Triple &TT = STI.getTargetTriple();
  if (TT.isOSBinFormatELF())
    return new G3KHTargetELFStreamer(S, STI);
  return nullptr;
}

} // namespace llvm
