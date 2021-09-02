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
def G3KHretflag  : SDNode<"G3KHISD::RET_FLAG", SDTNone,
                       [SDNPHasChain, SDNPOptInGlue, SDNPVariadic]>;


//===----------------------------------------------------------------------===//
// G3KH Operand Definitions.
//===----------------------------------------------------------------------===//

// Short jump targets have OtherVT type and are printed as pcrel imm values.
def jmptarget : Operand<OtherVT> {
  let PrintMethod = "printPCRelImmOperand";
  let EncoderMethod = "getPCRelImmOpValue";
}

//===----------------------------------------------------------------------===//
//  G3KH Instructions
//  ref: Renesas R01US0165EJ0120 Rev. 1.20
//===--------------------7.2 BASIC  instructions---------------------------===//
//===--------------------7.2.1(1) Load instructions------------------------===//
class LDST_VIIForm<bits<6> opcode, string asmstr>
  : VIIForm<opcode, 
            (outs), (ins i16imm:$disp16, GR32:$reg1, GR32:$reg2), asmstr#"\t$disp16[$reg1],$reg2", []> ;
class LDST_VIIForm2<bits<6> opcode,bit sub_opcode1, string asmstr>
  : VIIForm2<opcode,
            (outs), (ins i16imm:$disp16, GR32:$reg1, GR32:$reg2), asmstr#"\t$disp16[$reg1],$reg2", []> {
    let sub_opcode = sub_opcode1;
}
class LDST_XIVForm<bits<6> opcode,bits<5> sub_opcode1,bits<4> sub_opcode2, string asmstr>
  : XIVForm<opcode, 
            (outs), (ins i32imm:$disp23, GR32:$reg1, GR32:$reg3), asmstr#"\t$disp23[$reg1],$reg3", []> {
  let sub_opcode{4-0} = sub_opcode1{4-0};
  let sub_opcode{8-5} = sub_opcode2{3-0};
}
class LDST_XIVForm2<bits<6> opcode,bits<5> sub_opcode1,bits<4> sub_opcode2, string asmstr>
  : XIVForm2<opcode, 
            (outs), (ins i32imm:$disp23, GR32:$reg1, GR32:$reg3), asmstr#"\t$disp23[$reg1],$reg3", []> {
  let sub_opcode{4-0} = sub_opcode1{4-0};
  let sub_opcode{8-5} = sub_opcode2{3-0};
}
class SLDST_IVForm<bits<4> opcode, string asmstr>
  : IVForm<opcode, 
            (outs), (ins i32imm:$disp7, GR32:$reg2), asmstr#"\t$disp7[EP],$reg2", []> {
}
class SLDST_IVForm2<bits<4> opcode, bit sub_opcode1, string asmstr>
  : IVForm2<opcode, 
            (outs), (ins i32imm:$disp7, GR32:$reg2), asmstr#"\t$disp7[EP],$reg2", []> {
  let sub_opcode = sub_opcode1;
}
class SLDST_IVForm3<bits<7> opcode, string asmstr>
  : IVForm3<opcode, 
            (outs), (ins i32imm:$disp7, GR32:$reg2), asmstr#"\t$disp7[EP],$reg2", []> {
}

//  7.2.1(1)(a) LD instructions
def LDB_VII : LDST_VIIForm<0b111000, "LD.B">;
def LDB_XIV : LDST_XIVForm<0b111100, 0b00000, 0b0101, "LD.B">;
def LDBU_VII : LDST_VIIForm2<0b111000, 1, "LD.BU">;
def LDBU_XIV : LDST_XIVForm<0b111101, 0b00000, 0b0101, "LD.BU">;
def LDDW_XIV : LDST_XIVForm2<0b111101, 0b00000, 0b1001, "LD.DW">;
def LDH_VII : LDST_VIIForm2<0b111001, 0, "LD.H">;
def LDH_XIV : LDST_XIVForm2<0b111100, 0b00000, 0b0111, "LD.H">;
def LDHU_VII : LDST_VIIForm2<0b111111, 1, "LD.HU">;
def LDHU_XIV : LDST_XIVForm2<0b111101, 0b00000, 0b0111, "LD.HU">;
def LDW_VII : LDST_VIIForm2<0b111001, 1, "LD.W">;
def LDW_XIV : LDST_XIVForm2<0b111100, 0b00000, 0b1001, "LD.W">;
//  7.2.1(1)(b) SLD instructions
def SLDB_VII : SLDST_IVForm<0b0110, "SLD.B">;
def SLDBU_VII : SLDST_IVForm3<0b0000110, "SLD.BU">;
def SLDH_VII : SLDST_IVForm<0b1000, "SLD.H">;
def SLDHU_VII : SLDST_IVForm3<0b0000111, "SLD.HU">;
def SLDW_VII : SLDST_IVForm2<0b1010, 0, "SLD.W">;
//===--------------------7.2.1(2) Store instructions-----------------------===//
//  7.2.1(2)(a) ST instructions
def STB_VII : LDST_VIIForm<0b111010, "ST.B">;
def STB_XIV : LDST_XIVForm<0b111100, 0b00000, 0b1101, "ST.B">;
def STDW_XIV : LDST_XIVForm2<0b111101, 0b00000, 0b1111, "ST.DW">;
def STH_VII : LDST_VIIForm2<0b111011, 0, "ST.H">;
def STH_XIV : LDST_XIVForm2<0b111101, 0b00000, 0b1101, "ST.H">;
def STW_VII : LDST_VIIForm2<0b111011, 1, "ST.W">;
def STW_XIV : LDST_XIVForm2<0b111100, 0b00000, 0b1111, "ST.W">;
//  7.2.1(2)(b) SST instructions
def SSTB_VII : SLDST_IVForm<0b0111, "SLD.B">;
def SSTH_VII : SLDST_IVForm<0b1001, "SLD.H">;
def SSTW_VII : SLDST_IVForm2<0b1010, 1, "SLD.W">;
//===--------------------7.2.1(3) Multiply instructions--------------------===//
//===--------------------7.2.1(4) Multiply-accumulate instructions---------===//
//===--------------------7.2.1(5) Arithmetic instructions------------------===//
//===--------------------7.2.1(6) Conditional arithmetic instructions------===//
//===--------------------7.2.1(7) Saturated operation instructions---------===//
//===--------------------7.2.1(8) Logical instructions---------------------===//
//===--------------------7.2.1(9) Data manipulation instructions-----------===//
//===--------------------7.2.1(10) Bit search instructions-----------------===//
//===--------------------7.2.1(11) Divide instructions---------------------===//
//===--------------------7.2.1(12) High-speed divide instructions----------===//
//===--------------------7.2.1(13) Branch instructions---------------------===//
let isBranch = 1, isTerminator = 1 in {

// Direct branch
let isBarrier = 1 in {
  // Short branch
  def JMP_I : IForm<0b000011, (outs), (ins GR32:$reg1),
                   "jmp\t$reg1",
                   []> {
    let reg2 = 0b00000;
  }
  def JMP_VI : VIForm6<0b110111, (outs), (ins GR32:$reg1, i32imm:$disp32),
                   "jmp\t$reg1,\t$disp32",
                   []> {
    let reg2 = 0b00000;
  }
}

} // isBranch, isTerminator

//  Call Instructions...
//
// All calls clobber the non-callee saved registers. SPW is marked as
// a use to prevent stack-pointer assignments that appear immediately
// before calls from potentially appearing dead. Uses for argument
// registers are added manually.
let isCall = 1,
    Defs = [R11, R12, R13, R14, R15, SP],
    Uses = [SP] in {
  def JARL_V : VForm<0b11110, (outs), (ins i22imm:$disp22, GR32:$reg2),
                    "jarl\t$disp22,\t$reg2",
                    []>{
    // let reg2 = 0b00000;
  }
  def JARL_VI : VIForm6<0b010111, (outs), (ins i32imm:$disp32, GR32:$reg1),
                    "jarl32\t$disp32",
                    []>{
    let reg2 = 0b00000;
  }
  def JARL_XI : XIForm<0b111111, (outs), (ins GR32:$reg1, GR32:$reg3),
                    "jarl32\t$reg1,\t$reg3",
                    []>{
    let reg2 = 0b11000;
    let sub_opcode = 0b0010110000;
  }
}

//===--------------------7.2.1(14) Loop instructions-----------------------===//
//===--------------------7.2.1(15) Bit manipulation instructions-----------===//
//===--------------------7.2.1(16) Special instructions--------------------===//
let Defs = [SP], Uses = [SP], hasSideEffects = 0 in {
let mayLoad = 1 in {
def POPSP_XI   : XIForm<0b111111, (outs GR32:$reg1, GR32:$reg3), (ins), 
                "popsp\t$reg1,\t$reg3", []> {
    let reg2 = 0b01100;
    let sub_opcode = 0b0010110000;
}
// todo: dispose
}

let mayStore = 1 in{
def PUSHSP_XI : XIForm<0b111111, (outs), (ins GR32:$reg1, GR32:$reg3),
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
