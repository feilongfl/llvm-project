add_llvm_component_library(LLVMV800Info
  V800TargetInfo.cpp

  LINK_COMPONENTS
  MC
  Support

  ADD_TO_COMPONENT
  V800
  )
