//===--- V800.h - Declare V800 target feature support ---------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares V800 TargetInfo objects.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_LIB_BASIC_TARGETS_V800_H
#define LLVM_CLANG_LIB_BASIC_TARGETS_V800_H

#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/TargetOptions.h"
#include "llvm/ADT/Triple.h"
#include "llvm/Support/Compiler.h"

namespace clang {
namespace targets {

class LLVM_LIBRARY_VISIBILITY V800TargetInfo : public TargetInfo {
  static const Builtin::Info BuiltinInfo[];

public:
  V800TargetInfo(const llvm::Triple &Triple, const TargetOptions &)
      : TargetInfo(Triple) {
    NoAsmVariants = true;
    LongLongAlign = 32;
    SuitableAlign = 32;
    DoubleAlign = LongDoubleAlign = 32;
    SizeType = UnsignedInt;
    PtrDiffType = SignedInt;
    IntPtrType = SignedInt;
    WCharType = UnsignedChar;
    WIntType = UnsignedInt;
    UseZeroLengthBitfieldAlignment = true;
    resetDataLayout("e-m:e-p:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64"
                    "-f32:32:32-f64:32:64-a:0:32-n32");
  }

  void getTargetDefines(const LangOptions &Opts,
                        MacroBuilder &Builder) const override;

  ArrayRef<Builtin::Info> getTargetBuiltins() const override;

  BuiltinVaListKind getBuiltinVaListKind() const override {
    return TargetInfo::VoidPtrBuiltinVaList;
  }

  const char *getClobbers() const override { return ""; }

  ArrayRef<const char *> getGCCRegNames() const override {
    static const char *const GCCRegNames[] = {
        "r0", "r1", "r2",  "r3",  "r4", "r5", "r6", "r7",
        "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15",
        "r16", "r17", "r18", "r19", "r20", "r21", "r22", "r23",
        "r24", "r25", "r26", "r27", "r28", "r29", "r30", "r31",
    };
    return llvm::makeArrayRef(GCCRegNames);
  }

  ArrayRef<TargetInfo::GCCRegAlias> getGCCRegAliases() const override {
    static const TargetInfo::GCCRegAlias GCCRegAliases[] = {
        {{"sp"}, "r3"},
        {{"gp"}, "r4"},
        {{"tp"}, "r5"},
        {{"ep"}, "r30"},
        {{"lp"}, "r31"},
    };

    return llvm::makeArrayRef(GCCRegAliases);
  }

  bool validateAsmConstraint(const char *&Name,
                             TargetInfo::ConstraintInfo &Info) const override {
    return false;
  }

  int getEHDataRegisterNumber(unsigned RegNo) const override {
    // R0=ExceptionPointerRegister R1=ExceptionSelectorRegister
    return (RegNo < 2) ? RegNo : -1;
  }

  bool allowsLargerPreferedTypeAlignment() const override { return false; }

  bool hasBitIntType() const override { return true; }
};
} // namespace targets
} // namespace clang
#endif // LLVM_CLANG_LIB_BASIC_TARGETS_V800_H
