//===-- G3KHRegisterInfo.td - G3KH Register defs -------*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Declarations that describe the G3KH register file
//===----------------------------------------------------------------------===//

class G3KHReg<bits<4> num, string n, list<string> alt = []> : Register<n> {
  field bits<4> Num = num;
  let Namespace = "G3KH";
  let HWEncoding{3-0} = num;
  let AltNames = alt;
  let DwarfNumbers = [num];
}

class G3KHRegWithSubregs<bits<4> num, string n, list<Register> subregs,
                           list<string> alt = []> 
  : RegisterWithSubRegs<n, subregs> {
  field bits<4> Num = num;
  let Namespace = "G3KH";
  let HWEncoding{3-0} = num;
  let AltNames = alt;
  let DwarfNumbers = [num];
}

//===----------------------------------------------------------------------===//
//  Registers
//===----------------------------------------------------------------------===//

def PCB  : G3KHReg<0,  "r0", ["pc"]>;
def SPB  : G3KHReg<1,  "r1", ["sp"]>;
def SRB  : G3KHReg<2,  "r2", ["sr"]>;
def CGB  : G3KHReg<3,  "r3", ["cg"]>;
def R4B  : G3KHReg<4,  "r4", ["fp"]>;
def R5B  : G3KHReg<5,  "r5">;
def R6B  : G3KHReg<6,  "r6">;
def R7B  : G3KHReg<7,  "r7">;
def R8B  : G3KHReg<8,  "r8">;
def R9B  : G3KHReg<9,  "r9">;
def R10B : G3KHReg<10, "r10">;
def R11B : G3KHReg<11, "r11">;
def R12B : G3KHReg<12, "r12">;
def R13B : G3KHReg<13, "r13">;
def R14B : G3KHReg<14, "r14">;
def R15B : G3KHReg<15, "r15">;

def subreg_8bit : SubRegIndex<8> { let Namespace = "G3KH"; }

let SubRegIndices = [subreg_8bit] in {
def PC  : G3KHRegWithSubregs<0,  "r0",  [PCB], ["pc"]>;
def SP  : G3KHRegWithSubregs<1,  "r1",  [SPB], ["sp"]>;
def SR  : G3KHRegWithSubregs<2,  "r2",  [SRB], ["sr"]>;
def CG  : G3KHRegWithSubregs<3,  "r3",  [CGB], ["cg"]>;
def R4  : G3KHRegWithSubregs<4,  "r4",  [R4B], ["fp"]>;
def R5  : G3KHRegWithSubregs<5,  "r5",  [R5B]>;
def R6  : G3KHRegWithSubregs<6,  "r6",  [R6B]>;
def R7  : G3KHRegWithSubregs<7,  "r7",  [R7B]>;
def R8  : G3KHRegWithSubregs<8,  "r8",  [R8B]>;
def R9  : G3KHRegWithSubregs<9,  "r9",  [R9B]>;
def R10 : G3KHRegWithSubregs<10, "r10", [R10B]>;
def R11 : G3KHRegWithSubregs<11, "r11", [R11B]>;
def R12 : G3KHRegWithSubregs<12, "r12", [R12B]>;
def R13 : G3KHRegWithSubregs<13, "r13", [R13B]>;
def R14 : G3KHRegWithSubregs<14, "r14", [R14B]>;
def R15 : G3KHRegWithSubregs<15, "r15", [R15B]>;
}

def GR8 : RegisterClass<"G3KH", [i8], 8,
   // Volatile registers
  (add R12B, R13B, R14B, R15B, R11B, R10B, R9B, R8B, R7B, R6B, R5B,
   // Frame pointer, sometimes allocable
   R4B,
   // Volatile, but not allocable
   PCB, SPB, SRB, CGB)>;

def GR16 : RegisterClass<"G3KH", [i16], 16,
   // Volatile registers
  (add R12, R13, R14, R15, R11, R10, R9, R8, R7, R6, R5,
   // Frame pointer, sometimes allocable
   R4,
   // Volatile, but not allocable
   PC, SP, SR, CG)>;
