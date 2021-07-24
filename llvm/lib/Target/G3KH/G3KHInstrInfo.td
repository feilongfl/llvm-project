//===-- G3KHInstrInfo.td - G3KH Instruction defs -------*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file describes the G3KH instructions in TableGen format.
//
//===----------------------------------------------------------------------===//

include "G3KHInstrFormats.td"

//===----------------------------------------------------------------------===//
// Type Constraints.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Type Profiles.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// G3KH Specific Node Definitions.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// G3KH Operand Definitions.
//===----------------------------------------------------------------------===//

// Short jump targets have OtherVT type and are printed as pcrel imm values.
def jmptarget : Operand<OtherVT> {
  let PrintMethod = "printPCRelImmOperand";
  let EncoderMethod = "getPCRelImmOpValue";
}

//===----------------------------------------------------------------------===//
//  Control Flow Instructions...
//

let isBranch = 1, isTerminator = 1 in {

// Direct branch
let isBarrier = 1 in {
  // Short branch
  def JMPI : IForm<0b000011, (outs), (ins jmptarget:$dst),
                   "jmp\t$dst",
                   []> {
    // let reg1 = 0b00000;
    let reg2 = 0b00000;
  }
  def JMPVI : IForm<0b110111, (outs), (ins jmptarget:$dst),
                   "jmp\t$dst",
                   []> {
    // let reg1 = 0b00000;
    let reg2 = 0b00000;
  }
}

} // isBranch, isTerminator

//===----------------------------------------------------------------------===//
// Non-Instruction Patterns
