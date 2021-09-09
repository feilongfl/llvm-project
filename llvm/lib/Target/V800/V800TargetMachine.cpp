//===-- V800TargetMachine.cpp - Define TargetMachine for V800 -----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
//
//===----------------------------------------------------------------------===//

#include "V800TargetMachine.h"
#include "LeonPasses.h"
// #include "V800.h"
// #include "V800TargetObjectFile.h"
// #include "TargetInfo/V800TargetInfo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeV800Target() {
  // Register the target.
  RegisterTargetMachine<G3KHTargetMachine> X(getTheV800Target());
}

static std::string computeDataLayout(const Triple &T, bool is64Bit) {
  if (T.getArch() == Triple::g3kh) 
    return "e-m:e-p:32:32:32-f32-32-32-n8-16-32";

  return "";
}

// static Reloc::Model getEffectiveRelocModel(Optional<Reloc::Model> RM) {
//   return RM.getValueOr(Reloc::Static);
// }

// // Code models. Some only make sense for 64-bit code.
// //
// // SunCC  Reloc   CodeModel  Constraints
// // abs32  Static  Small      text+data+bss linked below 2^32 bytes
// // abs44  Static  Medium     text+data+bss linked below 2^44 bytes
// // abs64  Static  Large      text smaller than 2^31 bytes
// // pic13  PIC_    Small      GOT < 2^13 bytes
// // pic32  PIC_    Medium     GOT < 2^32 bytes
// //
// // All code models require that the text segment is smaller than 2GB.
// static CodeModel::Model
// getEffectiveV800CodeModel(Optional<CodeModel::Model> CM, Reloc::Model RM,
//                            bool Is64Bit, bool JIT) {
//   if (CM) {
//     if (*CM == CodeModel::Tiny)
//       report_fatal_error("Target does not support the tiny CodeModel", false);
//     if (*CM == CodeModel::Kernel)
//       report_fatal_error("Target does not support the kernel CodeModel", false);
//     return *CM;
//   }
//   if (Is64Bit) {
//     if (JIT)
//       return CodeModel::Large;
//     return RM == Reloc::PIC_ ? CodeModel::Small : CodeModel::Medium;
//   }
//   return CodeModel::Small;
// }

// /// Create an ILP32 architecture model
// V800TargetMachine::V800TargetMachine(
//     const Target &T, const Triple &TT, StringRef CPU, StringRef FS,
//     const TargetOptions &Options, Optional<Reloc::Model> RM,
//     Optional<CodeModel::Model> CM, CodeGenOpt::Level OL, bool JIT, bool is64bit)
//     : LLVMTargetMachine(T, computeDataLayout(TT, is64bit), TT, CPU, FS, Options,
//                         getEffectiveRelocModel(RM),
//                         getEffectiveV800CodeModel(
//                             CM, getEffectiveRelocModel(RM), is64bit, JIT),
//                         OL),
//       TLOF(std::make_unique<V800ELFTargetObjectFile>()),
//       Subtarget(TT, std::string(CPU), std::string(FS), *this, is64bit),
//       is64Bit(is64bit) {
//   initAsmInfo();
// }

// V800TargetMachine::~V800TargetMachine() {}

// const V800Subtarget *
// V800TargetMachine::getSubtargetImpl(const Function &F) const {
//   Attribute CPUAttr = F.getFnAttribute("target-cpu");
//   Attribute FSAttr = F.getFnAttribute("target-features");

//   std::string CPU =
//       CPUAttr.isValid() ? CPUAttr.getValueAsString().str() : TargetCPU;
//   std::string FS =
//       FSAttr.isValid() ? FSAttr.getValueAsString().str() : TargetFS;

//   // FIXME: This is related to the code below to reset the target options,
//   // we need to know whether or not the soft float flag is set on the
//   // function, so we can enable it as a subtarget feature.
//   bool softFloat = F.getFnAttribute("use-soft-float").getValueAsBool();

//   if (softFloat)
//     FS += FS.empty() ? "+soft-float" : ",+soft-float";

//   auto &I = SubtargetMap[CPU + FS];
//   if (!I) {
//     // This needs to be done before we create a new subtarget since any
//     // creation will depend on the TM and the code generation flags on the
//     // function that reside in TargetOptions.
//     resetTargetOptions(F);
//     I = std::make_unique<V800Subtarget>(TargetTriple, CPU, FS, *this,
//                                           this->is64Bit);
//   }
//   return I.get();
// }

namespace {
/// V800 Code Generator Pass Configuration Options.
class V800PassConfig : public TargetPassConfig {
public:
  V800PassConfig(V800TargetMachine &TM, PassManagerBase &PM)
    : TargetPassConfig(TM, PM) {}

  V800TargetMachine &getV800TargetMachine() const {
    return getTM<V800TargetMachine>();
  }

  // void addIRPasses() override;
  bool addInstSelector() override;
  // void addPreEmitPass() override;
};
} // namespace

TargetPassConfig *V800TargetMachine::createPassConfig(PassManagerBase &PM) {
  return new V800PassConfig(*this, PM);
}

// void V800PassConfig::addIRPasses() {
//   addPass(createAtomicExpandPass());

//   TargetPassConfig::addIRPasses();
// }

bool V800PassConfig::addInstSelector() {
  addPass(createV800ISelDag(getV800TargetMachine()));
  return false;
}

// void V800PassConfig::addPreEmitPass(){
//   addPass(createV800DelaySlotFillerPass());

//   if (this->getV800TargetMachine().getSubtargetImpl()->insertNOPLoad())
//   {
//     addPass(new InsertNOPLoad());
//   }
//   if (this->getV800TargetMachine().getSubtargetImpl()->detectRoundChange()) {
//     addPass(new DetectRoundChange());
//   }
//   if (this->getV800TargetMachine().getSubtargetImpl()->fixAllFDIVSQRT())
//   {
//     addPass(new FixAllFDIVSQRT());
//   }
// }

void V800V8TargetMachine::anchor() { }

V800V8TargetMachine::V800V8TargetMachine(const Target &T, const Triple &TT,
                                           StringRef CPU, StringRef FS,
                                           const TargetOptions &Options,
                                           Optional<Reloc::Model> RM,
                                           Optional<CodeModel::Model> CM,
                                           CodeGenOpt::Level OL, bool JIT)
    : V800TargetMachine(T, TT, CPU, FS, Options, RM, CM, OL, JIT, false) {}

// void V800V9TargetMachine::anchor() { }

// V800V9TargetMachine::V800V9TargetMachine(const Target &T, const Triple &TT,
//                                            StringRef CPU, StringRef FS,
//                                            const TargetOptions &Options,
//                                            Optional<Reloc::Model> RM,
//                                            Optional<CodeModel::Model> CM,
//                                            CodeGenOpt::Level OL, bool JIT)
//     : V800TargetMachine(T, TT, CPU, FS, Options, RM, CM, OL, JIT, true) {}

// void V800elTargetMachine::anchor() {}

// V800elTargetMachine::V800elTargetMachine(const Target &T, const Triple &TT,
//                                            StringRef CPU, StringRef FS,
//                                            const TargetOptions &Options,
//                                            Optional<Reloc::Model> RM,
//                                            Optional<CodeModel::Model> CM,
//                                            CodeGenOpt::Level OL, bool JIT)
//     : V800TargetMachine(T, TT, CPU, FS, Options, RM, CM, OL, JIT, false) {}
