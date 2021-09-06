//===-- TOYTargetMachine.h - Define TargetMachine for TOY ---*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the TOY specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#ifndef TOYTARGETMACHINE_H
#define TOYTARGETMACHINE_H

#include "TOY.h"
#include "TOYFrameLowering.h"
#include "TOYISelLowering.h"
#include "TOYInstrInfo.h"
#include "TOYSelectionDAGInfo.h"
#include "TOYSubtarget.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class TOYTargetMachine : public LLVMTargetMachine {
  TOYSubtarget Subtarget;

public:
  TOYTargetMachine(const Target &T, StringRef TT, StringRef CPU, StringRef FS,
                   const TargetOptions &Options, Reloc::Model RM,
                   CodeModel::Model CM, CodeGenOpt::Level OL);

  virtual const TOYSubtarget *getSubtargetImpl() const { return &Subtarget; }

  // Pass Pipeline Configuration
  virtual TargetPassConfig *createPassConfig(PassManagerBase &PM);

  virtual void addAnalysisPasses(PassManagerBase &PM);
};

} // end namespace llvm

#endif
