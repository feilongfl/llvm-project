//===-- TOYRegisterInfo.td - TOY Register defs ---------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Declarations that describe the TOY register file 
//===----------------------------------------------------------------------===//

class TOYReg<bits<16> Enc, string n> : Register<n> {
  let HWEncoding = Enc;
  let Namespace = "TOY";
}

// CPU registers
def R0  : TOYReg< 0, "r0">;
def R1  : TOYReg< 1, "r1">;
def R2  : TOYReg< 2, "r2">;
def R3  : TOYReg< 3, "r3">;
def R4  : TOYReg< 4, "r4">;
def R5  : TOYReg< 5, "r5">;
def R6  : TOYReg< 6, "r6">;
def R7  : TOYReg< 7, "r7">;
def R8  : TOYReg< 8, "r8">;
def R9  : TOYReg< 9, "r9">;

def SP  : TOYReg<13, "sp">;
def LR  : TOYReg<14, "lr">;

// Register classes.
//
def GRRegs : RegisterClass<"TOY", [i32], 32,
  // Return values and arguments
  (add R0, R1, R2, R3,
       R4, R5, R6, R7, R8, R9, SP)>;
