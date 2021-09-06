//===-- G3KHMCAsmInfo.h - G3KH asm properties --------------*- C++ -*--===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the G3KHMCAsmInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_G3KH_MCTARGETDESC_G3KHMCASMINFO_H
#define LLVM_LIB_TARGET_G3KH_MCTARGETDESC_G3KHMCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {
class Triple;

class G3KHMCAsmInfo : public MCAsmInfoELF {
  void anchor() override;

public:
  explicit G3KHMCAsmInfo(const Triple &TT, const MCTargetOptions &Options);
};

} // namespace llvm

#endif
