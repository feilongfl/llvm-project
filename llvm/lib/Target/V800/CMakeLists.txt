add_llvm_component_group(V800)

set(LLVM_TARGET_DEFINITIONS V800.td)

tablegen(LLVM V800GenSubtargetInfo.inc -gen-subtarget)

add_public_tablegen_target(V800CommonTableGen)

add_llvm_target(V800CodeGen
  V800TargetMachine.cpp

  LINK_COMPONENTS
  AsmPrinter
  CodeGen
  Core
  MC
  V800Desc
  V800Info
  SelectionDAG
  Support
  Target

  ADD_TO_COMPONENT
  V800
)

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
# add_subdirectory(AsmParser)
# add_subdirectory(Disassembler)
