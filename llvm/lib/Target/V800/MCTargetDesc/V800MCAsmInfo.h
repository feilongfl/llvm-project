//===-- V800MCAsmInfo.h - V800 asm properties --------------*- C++ -*--===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the V800MCAsmInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_V800_MCTARGETDESC_V800MCASMINFO_H
#define LLVM_LIB_TARGET_V800_MCTARGETDESC_V800MCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {
class Triple;

class V800MCAsmInfo : public MCAsmInfoELF {
  void anchor() override;

public:
  explicit V800MCAsmInfo(const Triple &TT, const MCTargetOptions &Options);
};

} // namespace llvm

#endif
