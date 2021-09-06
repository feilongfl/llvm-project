add_llvm_component_library(LLVMG3KHAsmParser
  G3KHAsmParser.cpp

  LINK_COMPONENTS
  MC
  MCParser
  G3KHDesc
  G3KHInfo
  Support

  ADD_TO_COMPONENT
  G3KH
)
