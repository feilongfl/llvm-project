//===-- G3KHInstrFormats.td - G3KH Instruction Formats -*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Describe G3KH instructions format here
//

class SourceMode<bits<2> val> {
  bits<2> Value = val;
}

def SrcReg      : SourceMode<0>; // r
def SrcMem      : SourceMode<1>; // m
def SrcIndReg   : SourceMode<2>; // n
def SrcPostInc  : SourceMode<3>; // p
def SrcImm      : SourceMode<3>; // i
//  SrcCGImm    : SourceMode< >; // c

class DestMode<bit val> {
  bit Value = val;
}

def DstReg      : DestMode<0>;   // r
def DstMem      : DestMode<1>;   // m

// Generic G3KH Format
class G3KHInst<dag outs, dag ins, int size, string asmstr> : Instruction {
  field bits<48> Inst;
  field bits<48> SoftFail = 0;

  let Namespace = "G3KH";

  dag OutOperandList = outs;
  dag InOperandList  = ins;

  let AsmString = asmstr;
  let Size = size;
}

//===----------------------------------------------------------------------===//
//  G3KH Instructions Format
//  ref: Renesas R01US0165EJ0120 Rev. 1.20 Section 7.1.1

// G3KH reg-reg instruction (Format I)
class IForm<bits<6> opcode, 
            dag outs, dag ins, string asmstr, list<dag> pattern>
  : G3KHInst<outs, ins, 2, asmstr> {
  let Pattern = pattern;

  bits<5> reg1;
  bits<5> reg2;


  let Inst{15-11}  = reg2;
  let Inst{10-5} = opcode;
  let Inst{4-0}   = reg1;
}

// G3KH reg-imm instruction (Format II)
class IIForm<bits<6> opcode, 
            dag outs, dag ins, string asmstr, list<dag> pattern>
  : G3KHInst<outs, ins, 2, asmstr> {
  let Pattern = pattern;

  bits<5> imm;
  bits<5> reg2;

  let Inst{15-11}  = reg2;
  let Inst{10-5} = opcode;
  let Inst{4-0}   = imm;
}

// G3KH conditional branch instruction (Format III)
class IIIForm<bits<4> opcode, int size,
            dag outs, dag ins, string asmstr, list<dag> pattern>
  : G3KHInst<outs, ins, 2, asmstr> {
  let Pattern = pattern;

  bits<8> disp;
  bits<4> cond;

  let Inst{15-11}  = disp{7-3};
  let Inst{10-7} = opcode;
  let Inst{6-4} = disp{2-0};
  let Inst{3-0}   = cond;
}

// todo: G3KH 16-bit load/store instruction (Format IV)
// G3KH Jump instruction (Format V)
class VForm<bits<5> opcode,
            dag outs, dag ins, string asmstr, list<dag> pattern>
  : G3KHInst<outs, ins, 4, asmstr> {
  let Pattern = pattern;

  bits<5> reg2;
  bits<22> disp;

  let Inst{15-11}  = reg2;
  let Inst{10-6} = opcode;
  let Inst{5-0} = disp{21-16};
  let Inst{31-17} = disp{15-1};
  let Inst{16} = 0;
}

// G3KH 3-Operand instruction (Format VI)
class VIForm<bits<6> opcode, 
            dag outs, dag ins, string asmstr, list<dag> pattern>
  : G3KHInst<outs, ins, 4, asmstr> {
  let Pattern = pattern;

  bits<5> reg1;
  bits<5> reg2;
  bits<16> imm;


  let Inst{15-11}  = reg2;
  let Inst{10-5} = opcode;
  let Inst{4-0} = reg1;
  let Inst{31-16} = imm;
}

// todo: G3KH 32-bit load/store instruction (Format VII)
// todo: G3KH Bit manipulation instruction (Format VIII)
// todo: G3KH Extended-1 instruction (Format IX)
// todo: G3KH Extended-2 instruction (Format X)
// G3KH Extended-3 instruction (Format XI)
class XIForm<bits<6> opcode, int size,
            dag outs, dag ins, string asmstr, list<dag> pattern>
  : G3KHInst<outs, ins, 4, asmstr> {
  let Pattern = pattern;

  bits<5> reg1;
  bits<5> reg2;
  bits<5> reg3;
  bits<10> sub_opcode;

  let Inst{15-11}  = reg2;
  let Inst{10-5} = opcode;
  let Inst{4-0} = reg1;
  let Inst{31-27} = reg3;
  let Inst{26-17} = sub_opcode;
  let Inst{16} = 0;
}

// todo: G3KH Extended-4 instruction (Format XII)
// todo: G3KH Stack manipulation instruction (Format XIII)
// todo: G3KH 48-bit load/store instruction (Format XIV)

// Pseudo instructions
class Pseudo<dag outs, dag ins, string asmstr, list<dag> pattern>
  : G3KHInst<outs, ins, 0, asmstr> {
  let Pattern = pattern;
}
