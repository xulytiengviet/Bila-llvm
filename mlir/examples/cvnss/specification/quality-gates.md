# Bila-LLVM quality gates
Independent development, not an attempt to override LLVM upstream approvals.
Required evidence for release: native build, CTest (27 Base27 cases, verifier,
lowering and semantic bridge), human review and reproducible toolchain.
Do not report pending/skipped checks as success. The Python-only test does
not establish native correctness. Record actual CI links for every release.
Keep upstream contributions separate and follow LLVM's AI tool policy.

Lite gates are separate: compile standalone C++17, test all 27 states and emitted text, execute an LLVM IR fixture compiled by Clang, test metadata bridge and enforce package size <30 MB. Native MLIR gates remain required for native SDK releases, not claimed by Lite CI.
