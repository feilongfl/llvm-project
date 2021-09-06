//===-- TOYMachineFuctionInfo.h - TOY machine function info -*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares TOY-specific per-machine-function information.
//
//===----------------------------------------------------------------------===//

#ifndef TOYMACHINEFUNCTIONINFO_H
#define TOYMACHINEFUNCTIONINFO_H

#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"

namespace llvm {

// Forward declarations
class Function;

/// TOYFunctionInfo - This class is derived from MachineFunction private
/// TOY target-specific information for each MachineFunction.
class TOYFunctionInfo : public MachineFunctionInfo {
public:
  TOYFunctionInfo() {}

  ~TOYFunctionInfo() {}
};
} // End llvm namespace

#endif // TOYMACHINEFUNCTIONINFO_H

