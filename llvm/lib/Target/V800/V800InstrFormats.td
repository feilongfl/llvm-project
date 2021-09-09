


// class SourceMode<bits<2> val> {
//   bits<2> Value = val;
// }

// def SrcReg      : SourceMode<0>; // r
// def SrcMem      : SourceMode<1>; // m
// def SrcIndReg   : SourceMode<2>; // n
// def SrcPostInc  : SourceMode<3>; // p
// def SrcImm      : SourceMode<3>; // i
//  SrcCGImm    : SourceMode< >; // c

// class DestMode<bit val> {
//   bit Value = val;
// }

// def DstReg      : DestMode<0>;   // r
// def DstMem      : DestMode<1>;   // m

// Generic V800 Format
class V800Inst<dag outs, dag ins, int size, string asmstr> : Instruction {
  field bits<48> Inst;
  field bits<48> SoftFail = 0;

  let Namespace = "V800";

  dag OutOperandList = outs;
  dag InOperandList  = ins;

  let AsmString = asmstr;
  let Size = size;
}

// class InstV800<dag outs, dag ins, string asmstr,
//             list<dag> pattern, InstrItinClass itin = NoItinerary>
//         : Instruction {
//     field bits<32> Inst;
//     field bits<32> SoftFail = 0;
//     let Namespace = "V800";
//     let Size = 4;
//     dag OutOperandList = outs;
//     dag InOperandList = ins;
//     let AsmString = asmstr;
//     let Pattern = pattern;
//     let DecoderNamespace = "V800";
//     let Itinerary = itin;
// }


//===----------------------------------------------------------------------===//
//  V800 Instructions Format
//  ref: Renesas R01US0165EJ0120 Rev. 1.20 Section 7.1.1

// V800 reg-reg instruction (Format I)
class IForm<bits<6> opcode, 
            dag outs, dag ins, string asmstr, list<dag> pattern>
  : V800Inst<outs, ins, 2, asmstr> {
  let Pattern = pattern;

  bits<5> reg1;
  bits<5> reg2;


  let Inst{15-11}  = reg2;
  let Inst{10-5} = opcode;
  let Inst{4-0}   = reg1;
}

// V800 reg-imm instruction (Format II)
class IIForm<bits<6> opcode, 
            dag outs, dag ins, string asmstr, list<dag> pattern>
  : V800Inst<outs, ins, 2, asmstr> {
  let Pattern = pattern;

  bits<5> imm;
  bits<5> reg2;

  let Inst{15-11}  = reg2;
  let Inst{10-5} = opcode;
  let Inst{4-0}   = imm;
}

// V800 conditional branch instruction (Format III)
class IIIForm<bits<4> opcode,
            dag outs, dag ins, string asmstr, list<dag> pattern>
  : V800Inst<outs, ins, 2, asmstr> {
  let Pattern = pattern;

  bits<8> disp;
  bits<4> cond;

  let Inst{15-11}  = disp{7-3};
  let Inst{10-7} = opcode;
  let Inst{6-4} = disp{2-0};
  let Inst{3-0}   = cond;
}

// V800 16-bit load/store instruction (Format IV)
class IVForm<bits<4> opcode,
            dag outs, dag ins, string asmstr, list<dag> pattern>
  : V800Inst<outs, ins, 2, asmstr> {
  let Pattern = pattern;

  bits<7> disp;
  bits<5> reg2;

  let Inst{15-11}  = reg2{4-0};
  let Inst{10-7} = opcode;
  let Inst{6-0} = disp{6-0};
}
class IVForm2<bits<4> opcode,
            dag outs, dag ins, string asmstr, list<dag> pattern>
  : V800Inst<outs, ins, 2, asmstr> {
  let Pattern = pattern;

  bits<7> disp;
  bit sub_opcode;
  bits<5> reg2;

  let Inst{15-11}  = reg2{4-0};
  let Inst{10-7} = opcode;
  let Inst{6-1} = disp{6-1};
  let Inst{0}   = sub_opcode;
}
class IVForm3<bits<7> opcode,
            dag outs, dag ins, string asmstr, list<dag> pattern>
  : V800Inst<outs, ins, 2, asmstr> {
  let Pattern = pattern;

  bits<4> disp;
  bits<5> reg2;

  let Inst{15-11}  = reg2{4-0};
  let Inst{10-4} = opcode;
  let Inst{3-0} = disp{3-0};
}

// V800 Jump instruction (Format V)
class VForm<bits<5> opcode,
            dag outs, dag ins, string asmstr, list<dag> pattern>
  : V800Inst<outs, ins, 4, asmstr> {
  let Pattern = pattern;

  bits<5> reg2;
  bits<22> disp22;

  let Inst{15-11}  = reg2;
  let Inst{10-6} = opcode;
  let Inst{5-0} = disp22{21-16};
  let Inst{31-17} = disp22{15-1};
  let Inst{16} = 0;
}

// V800 3-Operand instruction (Format VI)
class VIForm4<bits<6> opcode, 
            dag outs, dag ins, string asmstr, list<dag> pattern>
  : V800Inst<outs, ins, 4, asmstr> {
  let Pattern = pattern;

  bits<5> reg1;
  bits<5> reg2;
  bits<16> imm;


  let Inst{15-11}  = reg2;
  let Inst{10-5} = opcode;
  let Inst{4-0} = reg1;
  let Inst{31-16} = imm;
}

// Maybe manual have a miss that VI format not include `disp32` which used
// by JMP/JR/JARL
class VIForm6<bits<6> opcode, 
            dag outs, dag ins, string asmstr, list<dag> pattern>
  : V800Inst<outs, ins, 6, asmstr> {
  let Pattern = pattern;

  bits<5> reg1;
  bits<5> reg2;
  bits<32> disp32;

  let Inst{15-11}  = reg2;
  let Inst{10-5} = opcode;
  let Inst{4-0} = reg1;
  let Inst{31-17} = disp32{15-1};
  let Inst{16} = 0;
  let Inst{47-32} = disp32{31-16};
}

// todo: V800 32-bit load/store instruction (Format VII)
class VIIForm<bits<6> opcode, 
            dag outs, dag ins, string asmstr, list<dag> pattern>
  : V800Inst<outs, ins, 4, asmstr> {
  let Pattern = pattern;

  bits<5> reg1;
  bits<5> reg2;
  bits<16> disp16;

  let Inst{15-11}  = reg2;
  let Inst{10-5} = opcode;
  let Inst{4-0} = reg1;
  let Inst{31-17} = disp16{15-1};
  let Inst{16} = disp16{0};
}
class VIIForm2<bits<6> opcode, 
            dag outs, dag ins, string asmstr, list<dag> pattern>
  : V800Inst<outs, ins, 4, asmstr> {
  let Pattern = pattern;

  bits<5> reg1;
  bits<5> reg2;
  bits<16> disp16;
  bit sub_opcode;

  let Inst{15-11}  = reg2;
  let Inst{10-5} = opcode;
  let Inst{4-0} = reg1;
  let Inst{31-17} = disp16{15-1};
  let Inst{16} = sub_opcode;
}

// todo: V800 Bit manipulation instruction (Format VIII)
// todo: V800 Extended-1 instruction (Format IX)
// todo: V800 Extended-2 instruction (Format X)
// V800 Extended-3 instruction (Format XI)
class XIForm<bits<6> opcode,
            dag outs, dag ins, string asmstr, list<dag> pattern>
  : V800Inst<outs, ins, 4, asmstr> {
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

// todo: V800 Extended-4 instruction (Format XII)
// todo: V800 Stack manipulation instruction (Format XIII)
// todo: V800 48-bit load/store instruction (Format XIV)
class XIVForm<bits<6> opcode, 
            dag outs, dag ins, string asmstr, list<dag> pattern>
  : V800Inst<outs, ins, 6, asmstr> {
  let Pattern = pattern;

  bits<5> reg1;
  bits<5> reg3;
  bits<23> disp23;
  bits<9> sub_opcode;

  let Inst{15-11}  = sub_opcode{4-0};
  let Inst{10-5} = opcode;
  let Inst{4-0} = reg1;
  let Inst{31-27} = reg3;
  let Inst{26-20} = disp23{6-0};
  let Inst{19-16} = sub_opcode{8-5};
  let Inst{47-32} = disp23{22-7};
}
class XIVForm2<bits<6> opcode, 
            dag outs, dag ins, string asmstr, list<dag> pattern>
  : V800Inst<outs, ins, 6, asmstr> {
  let Pattern = pattern;

  bits<5> reg1;
  bits<5> reg3;
  bits<23> disp23;
  bits<9> sub_opcode;

  let Inst{15-11}  = sub_opcode{4-0};
  let Inst{10-5} = opcode;
  let Inst{4-0} = reg1;
  let Inst{31-27} = reg3;
  let Inst{26-21} = disp23{6-1};
  let Inst{20} = 0;
  let Inst{19-16} = sub_opcode{8-5};
  let Inst{47-32} = disp23{22-7};
}

// Pseudo instructions
class Pseudo<dag outs, dag ins, string asmstr, list<dag> pattern>
  : V800Inst<outs, ins, 0, asmstr> {
  let Pattern = pattern;
}
