#ifndef LLVM_LIB_TARGET_V800_V800SUBTARGET_H
#define LLVM_LIB_TARGET_V800_V800SUBTARGET_H

#define GET_SUBTARGETINFO_HEADER
#include "V800GenSubtargetInfo.inc"

namespace llvm {
    class V800Subtarget : public V800GenSubtargetInfo {
        Triple TargetTriple;
        virtual void anchor();

        V800InstrInfo InstrInfo;
        V800TargetLowing TLInfo;
        V800FrameLowering FrameLowering;
    }
}

#endif