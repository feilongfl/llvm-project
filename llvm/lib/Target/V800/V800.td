//===-- CSKY.td - Describe the CSKY Target Machine ---------*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

include "V800RegisterInfo.td"
include "V800CallingConv.td"
include "V800Schedule.td"
include "V800InstrFormats.td"
include "V800InstrInfo.td"

// not use
def : ProcessorModel<"generic", NoSchedModel, []>;
// at this time I don't prepare for othre v800 serial cpu.
def : ProcessorModel<"g3kh", G3KHSchedModel, []>;

def V800InstrInfo : InstrInfo;

def V800AsmParser : AsmParser;

def V800AsmWriter : AsmWriter;

def V800 : Target {
  let InstructionSet = V800InstrInfo;
  let AssemblyParsers = [V800AsmParser];
  let AssemblyWriters = [V800AsmWriter];
  let AllowRegisterRenaming = 1;
}
