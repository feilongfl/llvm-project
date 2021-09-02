#!/usr/bin/env fish

# ../../build/bin/clang -help
# ../../build/bin/clang --print-multiarch
# ../../build/bin/clang -print-targets
# ../../build/bin/clang -print-supported-cpus 
killall xdot
../../build/bin/clang --target=g3kh main.c -O0 -g -emit-llvm -S -c -o ../../build/test/01_simple_c.ll
../../build/bin/llc --view-dag-combine1-dags ../../build/test/01_simple_c.ll
# code ../../build/test/01_simple_c.ll
