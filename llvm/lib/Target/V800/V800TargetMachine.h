//===-- V800TargetMachine.h - Define TargetMachine for V800 ---*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares the V800 specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_V800_V800TARGETMACHINE_H
#define LLVM_LIB_TARGET_V800_V800TARGETMACHINE_H

// #include "V800InstrInfo.h"
#include "V800Subtarget.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class V800TargetMachine : public LLVMTargetMachine {
  // std::unique_ptr<TargetLoweringObjectFile> TLOF;
  // V800Subtarget Subtarget;
  // bool is64Bit;
  // mutable StringMap<std::unique_ptr<V800Subtarget>> SubtargetMap;
public:
  V800TargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                     StringRef FS, const TargetOptions &Options,
                     Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM,
                     CodeGenOpt::Level OL, bool JIT, bool is64bit);
  ~V800TargetMachine() override;

  const V800Subtarget *getSubtargetImpl() const { return &Subtarget; }
  const V800Subtarget *getSubtargetImpl(const Function &) const = delete;

  // Pass Pipeline Configuration
  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;
  // TargetLoweringObjectFile *getObjFileLowering() const override {
    // return TLOF.get();
  // }
};

/// G3KH 32-bit target machine
///
class G3KHTargetMachine : public V800TargetMachine {
  virtual void anchor();
public:
  G3KHTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                       StringRef FS, const TargetOptions &Options,
                       Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM,
                       CodeGenOpt::Level OL, bool JIT);
};
} // end namespace llvm

#endif
