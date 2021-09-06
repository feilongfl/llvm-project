add_llvm_component_library(LLVMG3KHDesc
  G3KHAsmBackend.cpp
  G3KHELFObjectWriter.cpp
  G3KHELFStreamer.cpp
  G3KHInstPrinter.cpp
  G3KHMCAsmInfo.cpp
  G3KHMCCodeEmitter.cpp
  G3KHMCTargetDesc.cpp

  LINK_COMPONENTS
  MC
  G3KHInfo
  Support

  ADD_TO_COMPONENT
  G3KH
  )
