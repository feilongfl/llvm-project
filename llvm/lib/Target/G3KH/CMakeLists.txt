add_llvm_component_group(G3KH)

set(LLVM_TARGET_DEFINITIONS TOY.td)

tablegen(LLVM TOYGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM TOYGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM TOYGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM TOYGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM TOYGenCallingConv.inc -gen-callingconv)
tablegen(LLVM TOYGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM TOYGenMCCodeEmitter.inc -gen-emitter)
add_public_tablegen_target(TOYCommonTableGen)

add_llvm_target(G3KHCodeGen
  TOYSubtarget.cpp
  TOYTargetMachine.cpp
  TOYRegisterInfo.cpp
  TOYInstrInfo.cpp
  TOYFrameLowering.cpp
  TOYISelLowering.cpp
  TOYSelectionDAGInfo.cpp
  TOYISelDAGToDAG.cpp
  TOYAsmPrinter.cpp
  TOYMCInstLower.cpp

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

add_subdirectory(InstPrinter)
add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
