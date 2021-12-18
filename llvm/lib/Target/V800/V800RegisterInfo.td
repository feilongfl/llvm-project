//===-- V800RegisterInfo.td - V800 Register defs -------*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Declarations that describe the V800 register file
//===----------------------------------------------------------------------===//

class V800Reg<bits<5> num, string n, list<string> alt = []> : Register<n> {
  field bits<5> Num = num;
  let Namespace = "V800";
  let HWEncoding{4-0} = num;
  let AltNames = alt;
  let DwarfNumbers = [num];
}

class V800RegWithSubregs<bits<5> num, string n, list<Register> subregs,
                           list<string> alt = []> 
  : RegisterWithSubRegs<n, subregs> {
  field bits<5> Num = num;
  let Namespace = "V800";
  let HWEncoding{4-0} = num;
  let AltNames = alt;
  let DwarfNumbers = [num];
}

//===----------------------------------------------------------------------===//
//  Program counter
//===----------------------------------------------------------------------===//
def PC : Register<"pc"> {
   let Namespace = "V800";
}

//===----------------------------------------------------------------------===//
//  General purpose Registers
//===----------------------------------------------------------------------===//
def R0B  : V800Reg<0,  "r0", ["zero"]>;
def R1B  : V800Reg<1,  "r1">;
def R2B  : V800Reg<2,  "r2">;
def SPB  : V800Reg<3,  "r3", ["sp"]>;
def GPB  : V800Reg<4,  "r4", ["gp"]>;
def TPB  : V800Reg<5,  "r5", ["tp"]>;
def R6B  : V800Reg<6,  "r6">;
def R7B  : V800Reg<7,  "r7">;
def R8B  : V800Reg<8,  "r8">;
def R9B  : V800Reg<9,  "r9">;
def R10B : V800Reg<10, "r10">;
def R11B : V800Reg<11, "r11">;
def R12B : V800Reg<12, "r12">;
def R13B : V800Reg<13, "r13">;
def R14B : V800Reg<14, "r14">;
def R15B : V800Reg<15, "r15">;
def R16B : V800Reg<16, "r16">;
def R17B : V800Reg<17, "r17">;
def R18B : V800Reg<18, "r18">;
def R19B : V800Reg<19, "r19">;
def R20B : V800Reg<20, "r20">;
def R21B : V800Reg<21, "r21">;
def R22B : V800Reg<22, "r22">;
def R23B : V800Reg<23, "r23">;
def R24B : V800Reg<24, "r24">;
def R25B : V800Reg<25, "r25">;
def R26B : V800Reg<26, "r26">;
def R27B : V800Reg<27, "r27">;
def R28B : V800Reg<28, "r28">;
def R29B : V800Reg<29, "r29">;
def EPB : V800Reg<30, "r30", ["ep"]>;
def LPB : V800Reg<31, "r31", ["lp"]>;

def R0H  : V800Reg<0,  "r0", ["zero"]>;
def R1H  : V800Reg<1,  "r1">;
def R2H  : V800Reg<2,  "r2">;
def SPH  : V800Reg<3,  "r3", ["sp"]>;
def GPH  : V800Reg<4,  "r4", ["gp"]>;
def TPH  : V800Reg<5,  "r5", ["tp"]>;
def R6H  : V800Reg<6,  "r6">;
def R7H  : V800Reg<7,  "r7">;
def R8H  : V800Reg<8,  "r8">;
def R9H  : V800Reg<9,  "r9">;
def R10H : V800Reg<10, "r10">;
def R11H : V800Reg<11, "r11">;
def R12H : V800Reg<12, "r12">;
def R13H : V800Reg<13, "r13">;
def R14H : V800Reg<14, "r14">;
def R15H : V800Reg<15, "r15">;
def R16H : V800Reg<16, "r16">;
def R17H : V800Reg<17, "r17">;
def R18H : V800Reg<18, "r18">;
def R19H : V800Reg<19, "r19">;
def R20H : V800Reg<20, "r20">;
def R21H : V800Reg<21, "r21">;
def R22H : V800Reg<22, "r22">;
def R23H : V800Reg<23, "r23">;
def R24H : V800Reg<24, "r24">;
def R25H : V800Reg<25, "r25">;
def R26H : V800Reg<26, "r26">;
def R27H : V800Reg<27, "r27">;
def R28H : V800Reg<28, "r28">;
def R29H : V800Reg<29, "r29">;
def EPH : V800Reg<30, "r30", ["ep"]>;
def LPH : V800Reg<31, "r31", ["lp"]>;

def subreg_8bit : SubRegIndex<8> { let Namespace = "V800"; }
def subreg_16bit : SubRegIndex<16> { let Namespace = "V800"; }

let SubRegIndices = [subreg_8bit, subreg_16bit] in {
def R0  : V800RegWithSubregs<0,  "r0",  [R0B, R0H], ["zero"]>;
def R1  : V800RegWithSubregs<1,  "r1",  [R1B, R1H]>;
def R2  : V800RegWithSubregs<2,  "r2",  [R2B, R2H]>;
def SP  : V800RegWithSubregs<3,  "r3",  [SPB, SPH], ["sp"]>;
def GP  : V800RegWithSubregs<4,  "r4",  [GPB, GPH], ["gp"]>;
def TP  : V800RegWithSubregs<5,  "r5",  [TPB, TPH], ["tp"]>;
def R6  : V800RegWithSubregs<6,  "r6",  [R6B, R6H]>;
def R7  : V800RegWithSubregs<7,  "r7",  [R7B, R7H]>;
def R8  : V800RegWithSubregs<8,  "r8",  [R8B, R8H]>;
def R9  : V800RegWithSubregs<9,  "r9",  [R9B, R9H]>;
def R10 : V800RegWithSubregs<10, "r10", [R10B, R10H]>;
def R11 : V800RegWithSubregs<11, "r11", [R11B, R11H]>;
def R12 : V800RegWithSubregs<12, "r12", [R12B, R12H]>;
def R13 : V800RegWithSubregs<13, "r13", [R13B, R13H]>;
def R14 : V800RegWithSubregs<14, "r14", [R14B, R14H]>;
def R15 : V800RegWithSubregs<15, "r15", [R15B, R15H]>;
def R16 : V800RegWithSubregs<16, "r16", [R16B, R16H]>;
def R17 : V800RegWithSubregs<17, "r17", [R17B, R17H]>;
def R18 : V800RegWithSubregs<18, "r18", [R18B, R18H]>;
def R19 : V800RegWithSubregs<19, "r19", [R19B, R19H]>;
def R20 : V800RegWithSubregs<20, "r20", [R20B, R20H]>;
def R21 : V800RegWithSubregs<21, "r21", [R21B, R21H]>;
def R22 : V800RegWithSubregs<22, "r22", [R22B, R22H]>;
def R23 : V800RegWithSubregs<23, "r23", [R23B, R23H]>;
def R24 : V800RegWithSubregs<24, "r24", [R24B, R24H]>;
def R25 : V800RegWithSubregs<25, "r25", [R25B, R25H]>;
def R26 : V800RegWithSubregs<26, "r26", [R26B, R26H]>;
def R27 : V800RegWithSubregs<27, "r27", [R27B, R27H]>;
def R28 : V800RegWithSubregs<28, "r28", [R28B, R28H]>;
def R29 : V800RegWithSubregs<29, "r29", [R29B, R29H]>;
def EP : V800RegWithSubregs<30, "r30", [EPB, EPH], ["ep"]>;
def LP : V800RegWithSubregs<31, "r31", [LPB, LPH], ["lp"]>;
}

def GR8 : RegisterClass<"V800", [i8], 8,
   // Volatile registers
  (add R24B, R25B, R26B, R27B, R20B, R21B, R22B, R23B, R28B, R29B,
  R16B, R17B, R18B, R19B, 
  R12B, R13B, R14B, R15B, R11B, R10B, R9B, R8B, R7B, R6B,
   // asm usage
   R1B, 
   // rtos usage
   R2B,
   // Volatile, but not allocable
   SPB, GPB, TPB, EPB, LPB )>;

def GR16 : RegisterClass<"V800", [i16], 16,
   // Volatile registers
  (add R24H, R25H, R26H, R27H, R20H, R21H, R22H, R23H, R28H, R29H,
  R16H, R17H, R18H, R19H, 
  R12H, R13H, R14H, R15H, R11H, R10H, R9H, R8H, R7H, R6H,
   // asm usage
   R1H, 
   // rtos usage
   R2H,
   // Volatile, Hut not allocaHle
   SPH, GPH, TPH, EPH, LPH )>;

def GR32 : RegisterClass<"V800", [i32], 32,
   // Volatile registers
  (add R24, R25, R26, R27, R20, R21, R22, R23, R28, R29, 
  R16, R17, R18, R19, 
  R12, R13, R14, R15, R11, R10, R9, R8, R7, R6,
   // asm usage
   R1, 
   // rtos usage
   R2,
   // Volatile, but not allocable
   SP, GP, TP, EP, LP )>;
