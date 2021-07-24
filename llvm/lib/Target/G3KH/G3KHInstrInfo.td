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
  def JMPI : IForm<0b000011, (outs), (ins GR32:$reg1),
                   "jmp\t$reg1",
                   []> {
    let reg2 = 0b00000;
  }
  def JMPVI : VIForm6<0b110111, (outs), (ins GR32:$reg1, i32imm:$disp32),
                   "jmp\t$reg1,\t$disp32",
                   []> {
    let reg2 = 0b00000;
  }
}

} // isBranch, isTerminator

//===----------------------------------------------------------------------===//
//  Call Instructions...
//
// All calls clobber the non-callee saved registers. SPW is marked as
// a use to prevent stack-pointer assignments that appear immediately
// before calls from potentially appearing dead. Uses for argument
// registers are added manually.
let isCall = 1,
    Defs = [R11, R12, R13, R14, R15, SP],
    Uses = [SP] in {
  def JARLV : VForm<0b11110, (outs), (ins i22imm:$disp22, GR32:$reg2),
                    "jarl\t$disp22,\t$reg2",
                    []>{
    // let reg2 = 0b00000;
  }
  def JARLVI : VIForm6<0b010111, (outs), (ins i32imm:$disp32, GR32:$reg1),
                    "jarl32\t$disp32",
                    []>{
    let reg2 = 0b00000;
  }
  def JARLXI : XIForm<0b111111, (outs), (ins GR32:$reg1, GR32:$reg3),
                    "jarl32\t$reg1,\t$reg3",
                    []>{
    let reg2 = 0b11000;
    let sub_opcode = 0b0010110000;
  }
}

//===----------------------------------------------------------------------===//
//  Miscellaneous Instructions...
//
let Defs = [SP], Uses = [SP], hasSideEffects = 0 in {
let mayLoad = 1 in {
def POPSPXI   : XIForm<0b111111, (outs GR32:$reg1, GR32:$reg3), (ins), 
                "popsp\t$reg1,\t$reg3", []> {
    let reg2 = 0b01100;
    let sub_opcode = 0b0010110000;
}
// todo: dispose
}

let mayStore = 1 in{
def PUSHSPXI : XIForm<0b111111, (outs), (ins GR32:$reg1, GR32:$reg3),
                      "pushsp\t$reg1,\t$reg3",
                      []>{
    let reg2 = 0b01000;
    let sub_opcode = 0b0010110000;
}
// todo: prepare
}
}

//===----------------------------------------------------------------------===//
// Non-Instruction Patterns
