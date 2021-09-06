//===-- TOYFixupKinds.h - TOY-Specific Fixup Entries ------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_TOYFIXUPKINDS_H
#define LLVM_TOYFIXUPKINDS_H

#include "llvm/MC/MCFixup.h"

namespace llvm {
namespace TOY {
enum Fixups {
  fixup_toy_mov_hi16_pcrel = FirstTargetFixupKind,
  fixup_toy_mov_lo16_pcrel,

  // Marker
  LastTargetFixupKind,
  NumTargetFixupKinds = LastTargetFixupKind - FirstTargetFixupKind
};
}
}

#endif

