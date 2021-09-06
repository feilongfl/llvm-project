add_llvm_component_library(LLVMG3KHDisassembler
  G3KHDisassembler.cpp

  LINK_COMPONENTS
  MCDisassembler
  G3KHInfo
  Support

  ADD_TO_COMPONENT
  G3KH
  )
