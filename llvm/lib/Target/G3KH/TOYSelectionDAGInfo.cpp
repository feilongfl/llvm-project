//===-- TOYSelectionDAGInfo.cpp - TOY SelectionDAG Info ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the TOYSelectionDAGInfo class.
//
//===----------------------------------------------------------------------===//

#include "TOYSelectionDAGInfo.h"
using namespace llvm;

#define DEBUG_TYPE "toy-selectiondag-info"

TOYSelectionDAGInfo::TOYSelectionDAGInfo(const DataLayout &DL)
    : TargetSelectionDAGInfo(&DL) {}

TOYSelectionDAGInfo::~TOYSelectionDAGInfo() {}
