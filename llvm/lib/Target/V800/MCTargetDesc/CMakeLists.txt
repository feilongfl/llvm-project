add_llvm_component_library(LLVMV800Desc
  V800MCTargetDesc.cpp
  V800MCAsmInfo.cpp

  LINK_COMPONENTS
  MC
  V800Info
  Support

  ADD_TO_COMPONENT
  V800
)
