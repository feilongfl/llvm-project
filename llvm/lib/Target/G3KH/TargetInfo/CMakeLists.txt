add_llvm_component_library(LLVMG3KHInfo
  G3KHTargetInfo.cpp

  LINK_COMPONENTS
  Support

  ADD_TO_COMPONENT
  G3KH
  )
