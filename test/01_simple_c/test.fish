#!/usr/bin/env fish

# ../../build/bin/clang -help
# ../../build/bin/clang --print-multiarch
# ../../build/bin/clang -print-targets
# ../../build/bin/clang -print-supported-cpus 
killall xdot
../../build/bin/clang --target=g3kh main.c -O1 -g -emit-llvm -S -c -o ../../build/test/01_simple_c_g3kh.ll
../../build/bin/clang --target=msp430 main.c -O1 -g -emit-llvm -S -c -o ../../build/test/01_simple_c_430.ll
../../build/bin/clang main.c -O1 -g -emit-llvm -S -c -o ../../build/test/01_simple_c_x86.ll
# echo build ll x86
# ../../build/bin/llc --view-dag-combine1-dags ../../build/test/01_simple_c_x86.ll
echo build ll msp430
../../build/bin/llc --view-dag-combine1-dags ../../build/test/01_simple_c_430.ll
echo build ll g3kh
../../build/bin/llc --view-dag-combine1-dags ../../build/test/01_simple_c_g3kh.ll
# code ../../build/test/01_simple_c.ll
