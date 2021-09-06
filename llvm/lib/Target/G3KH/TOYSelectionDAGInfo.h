//===-- TOYSelectionDAGInfo.h - TOY SelectionDAG Info -------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines the TOY subclass for TargetSelectionDAGInfo.
//
//===----------------------------------------------------------------------===//

#ifndef TOYSELECTIONDAGINFO_H
#define TOYSELECTIONDAGINFO_H

#include "llvm/Target/TargetSelectionDAGInfo.h"

namespace llvm {

class TOYSelectionDAGInfo : public TargetSelectionDAGInfo {
public:
  explicit TOYSelectionDAGInfo(const DataLayout &DL);
  ~TOYSelectionDAGInfo();
};
}

#endif
