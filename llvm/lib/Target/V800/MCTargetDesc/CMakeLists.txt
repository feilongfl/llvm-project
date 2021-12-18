add_llvm_component_library(LLVMV800Desc
  V800MCTargetDesc.cpp
  V800InstPrinter.cpp
  V800MCAsmInfo.cpp
  V800AsmBackend.cpp
  V800MCCodeEmitter.cpp
  V800ELFObjectWriter.cpp

  LINK_COMPONENTS
  MC
  V800Info
  Support

  ADD_TO_COMPONENT
  V800
)
