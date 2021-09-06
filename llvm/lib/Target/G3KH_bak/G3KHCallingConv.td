//==- G3KHCallingConv.td - Calling Conventions for G3KH -*- tablegen -*-==//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
// This describes the calling conventions for G3KH architecture.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// G3KH Return Value Calling Convention
//===----------------------------------------------------------------------===//
def RetCC_G3KH : CallingConv<[
  // i8 are returned in registers R12B, R13B, R14B, R15B
  // CCIfType<[i8], CCAssignToReg<[R12B, R13B, R14B, R15B]>>,

  // i16 are returned in registers R12, R13, R14, R15
  // CCIfType<[i16], CCAssignToReg<[R12H, R13H, R14H, R15H]>>,

  // i32 are returned in registers R12, R13, R14, R15
  CCIfType<[i32], CCAssignToReg<[R12, R13, R14, R15]>>
]>;

//===----------------------------------------------------------------------===//
// G3KH Argument Calling Conventions
//===----------------------------------------------------------------------===//
def CC_G3KH_AssignStack : CallingConv<[
  // Pass by value if the byval attribute is given
  CCIfByVal<CCPassByVal<4, 4>>,

  // Integer values get stored in stack slots that are 2 bytes in
  // size and 2-byte aligned.
  CCIfType<[i8, i16], CCPromoteToType<i32>>,

  CCIfType<[i32], CCAssignToStack<4, 4>>
]>;

