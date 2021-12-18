//===-- V800.td - Describe the V800 Target Machine -----*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
// This is the top level entry point for the V800 target.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Target-independent interfaces
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// Subtarget Features. 
//===----------------------------------------------------------------------===//
def FeatureFPU
 : SubtargetFeature<"fpu", "FPUInsts", "true",
                    "Enable V800 FPU">;

def FeatureCache
 : SubtargetFeature<"cache", "CacheInsts", "true",
                    "Enable V800 cache">;

//===----------------------------------------------------------------------===//
// V800 supported processors.
//===----------------------------------------------------------------------===//
class Proc<string Name, list<SubtargetFeature> Features>
 : Processor<Name, NoItineraries, Features>;

def : Proc<"generic",         []>;
def : Proc<"g3k",             []>;
def : Proc<"g3kh",            [FeatureFPU]>;

def V800 : Target {
}
