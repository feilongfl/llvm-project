add_llvm_component_group(G3KH)

set(LLVM_TARGET_DEFINITIONS G3KH.td)

tablegen(LLVM G3KHGenAsmMatcher.inc -gen-asm-matcher)
tablegen(LLVM G3KHGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM G3KHGenCallingConv.inc -gen-callingconv)
tablegen(LLVM G3KHGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM G3KHGenDisassemblerTables.inc -gen-disassembler)
tablegen(LLVM G3KHGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM G3KHGenMCCodeEmitter.inc -gen-emitter)
tablegen(LLVM G3KHGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM G3KHGenSubtargetInfo.inc -gen-subtarget)

add_public_tablegen_target(G3KHCommonTableGen)

add_llvm_target(G3KHCodeGen
  G3KHBranchSelector.cpp
  G3KHISelDAGToDAG.cpp
  G3KHISelLowering.cpp
  G3KHInstrInfo.cpp
  G3KHFrameLowering.cpp
  G3KHMachineFunctionInfo.cpp
  G3KHRegisterInfo.cpp
  G3KHSubtarget.cpp
  G3KHTargetMachine.cpp
  G3KHAsmPrinter.cpp
  G3KHMCInstLower.cpp

  LINK_COMPONENTS
  AsmPrinter
  CodeGen
  Core
  MC
  G3KHDesc
  G3KHInfo
  SelectionDAG
  Support
  Target

  ADD_TO_COMPONENT
  G3KH
  )

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
add_subdirectory(AsmParser)
add_subdirectory(Disassembler)
