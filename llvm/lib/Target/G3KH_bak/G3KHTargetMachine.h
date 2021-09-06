//===-- G3KHTargetMachine.h - Define TargetMachine for G3KH -*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares the G3KH specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//


#ifndef LLVM_LIB_TARGET_G3KH_G3KHTARGETMACHINE_H
#define LLVM_LIB_TARGET_G3KH_G3KHTARGETMACHINE_H

#include "G3KHSubtarget.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
class StringRef;

/// G3KHTargetMachine
///
class G3KHTargetMachine : public LLVMTargetMachine {
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
  G3KHSubtarget        Subtarget;

public:
  G3KHTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                      StringRef FS, const TargetOptions &Options,
                      Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM,
                      CodeGenOpt::Level OL, bool JIT);
  ~G3KHTargetMachine() override;

  const G3KHSubtarget *getSubtargetImpl(const Function &F) const override {
    return &Subtarget;
  }
  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;

  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }
}; // G3KHTargetMachine.

} // end namespace llvm

#endif
