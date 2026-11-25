# Bila-LLVM Lite 0.3 (experimental)
Standalone C++17 constant Base27 compiler, no LLVM/MLIR SDK at runtime.
Commands: bila-lite pack 1 0 -1; bila-lite unpack 21; bila-lite emit-mlir 1 0 -1; bila-lite emit-llvm 1 0 -1.
Emits a restricted, constant-only func/arith MLIR or LLVM IR module. It is not
a general MLIR parser, optimizer, BilaScript compiler or official CVNSS codec.
The bundled hub.py supports Python AST metadata and explicit manifests for
other languages; Python 3 is needed only for this optional utility.
Linux binary requires compatible system C/C++ runtime. No SDK is distributed.
CI checks all 27 states and output text, compiles one LLVM IR fixture with
system Clang and enforces a package budget of strictly less than 30,000,000 bytes.
Native MLIR validation remains separate: see ../README.md in source checkout.
Build locally: g++ -std=c++17 -Os -s main.cpp -o bila-lite
