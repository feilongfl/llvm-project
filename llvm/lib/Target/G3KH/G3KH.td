//===-- G3KH.td - Describe the G3KH Target Machine -----*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
// This is the top level entry point for the G3KH target.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Target-independent interfaces
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// Subtarget Features. 
//===----------------------------------------------------------------------===//
def FeatureX
 : SubtargetFeature<"ext", "ExtendedInsts", "true",
                    "Enable G3KH-X extensions">;

def FeatureHWMult16
 : SubtargetFeature<"hwmult16", "HWMultMode", "HWMult16",
                    "Enable 16-bit hardware multiplier">;

def FeatureHWMult32
 : SubtargetFeature<"hwmult32", "HWMultMode", "HWMult32",
                    "Enable 32-bit hardware multiplier">;

def FeatureHWMultF5
 : SubtargetFeature<"hwmultf5", "HWMultMode", "HWMultF5",
                    "Enable F5 series hardware multiplier">;

//===----------------------------------------------------------------------===//
// G3KH supported processors.
//===----------------------------------------------------------------------===//
class Proc<string Name, list<SubtargetFeature> Features>
 : Processor<Name, NoItineraries, Features>;

def : Proc<"generic",         []>;
def : Proc<"g3kh",          []>;
def : Proc<"g3khx",         [FeatureX]>;

//===----------------------------------------------------------------------===//
// Register File Description
//===----------------------------------------------------------------------===//

include "G3KHRegisterInfo.td"

//===----------------------------------------------------------------------===//
// Calling Convention Description
//===----------------------------------------------------------------------===//

include "G3KHCallingConv.td"

//===----------------------------------------------------------------------===//
// Instruction Descriptions
//===----------------------------------------------------------------------===//

include "G3KHInstrInfo.td"

def G3KHInstrInfo : InstrInfo;

//===---------------------------------------------------------------------===//
// Assembly Printers
//===---------------------------------------------------------------------===//

def G3KHAsmWriter : AsmWriter {
  string AsmWriterClassName = "InstPrinter";
}

//===---------------------------------------------------------------------===//
// Assembly Parsers
//===---------------------------------------------------------------------===//

def G3KHAsmParser : AsmParser {
  let AllowDuplicateRegisterNames = 1;
  let ShouldEmitMatchRegisterAltName = 1;
}

//===----------------------------------------------------------------------===//
// Target Declaration
//===----------------------------------------------------------------------===//

def G3KH : Target {
  let InstructionSet = G3KHInstrInfo;
  let AssemblyParsers = [G3KHAsmParser];
}

