//===-- G3KHTargetMachine.cpp - Define TargetMachine for G3KH ---------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Top-level implementation for the G3KH target.
//
//===----------------------------------------------------------------------===//

#include "G3KHTargetMachine.h"
#include "G3KH.h"
#include "TargetInfo/G3KHTargetInfo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeG3KHTarget() {
  // Register the target.
  RegisterTargetMachine<G3KHTargetMachine> X(getTheG3KHTarget());
}

static Reloc::Model getEffectiveRelocModel(Optional<Reloc::Model> RM) {
  if (!RM.hasValue())
    return Reloc::Static;
  return *RM;
}

static std::string computeDataLayout(const Triple &TT, StringRef CPU,
                                     const TargetOptions &Options) {
  return "e-m:e-p:16:16-i32:16-i64:16-f32:16-f64:16-a:8-n8:16-S16";
}

G3KHTargetMachine::G3KHTargetMachine(const Target &T, const Triple &TT,
                                         StringRef CPU, StringRef FS,
                                         const TargetOptions &Options,
                                         Optional<Reloc::Model> RM,
                                         Optional<CodeModel::Model> CM,
                                         CodeGenOpt::Level OL, bool JIT)
    : LLVMTargetMachine(T, computeDataLayout(TT, CPU, Options), TT, CPU, FS,
                        Options, getEffectiveRelocModel(RM),
                        getEffectiveCodeModel(CM, CodeModel::Small), OL),
      TLOF(std::make_unique<TargetLoweringObjectFileELF>()),
      Subtarget(TT, std::string(CPU), std::string(FS), *this) {
  initAsmInfo();
}

G3KHTargetMachine::~G3KHTargetMachine() {}

namespace {
/// G3KH Code Generator Pass Configuration Options.
class G3KHPassConfig : public TargetPassConfig {
public:
  G3KHPassConfig(G3KHTargetMachine &TM, PassManagerBase &PM)
    : TargetPassConfig(TM, PM) {}

  G3KHTargetMachine &getG3KHTargetMachine() const {
    return getTM<G3KHTargetMachine>();
  }

  bool addInstSelector() override;
  void addPreEmitPass() override;
};
} // namespace

TargetPassConfig *G3KHTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new G3KHPassConfig(*this, PM);
}

bool G3KHPassConfig::addInstSelector() {
  // Install an instruction selector.
  addPass(createG3KHISelDag(getG3KHTargetMachine(), getOptLevel()));
  return false;
}

void G3KHPassConfig::addPreEmitPass() {
  // Must run branch selection immediately preceding the asm printer.
  addPass(createG3KHBranchSelectionPass(), false);
}
