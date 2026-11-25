# Bila-LLVM Lite — CVNSS-CIR Research Toolchain

**Phiên bản thử nghiệm 0.3 / Experimental v0.3**

Bila-LLVM là nhánh nghiên cứu độc lập dựa trên LLVM/MLIR, hướng tới biểu diễn ký hiệu tiếng Việt CVNSS4.0, Base27, tam phân cân bằng và khả năng tương tác ngữ nghĩa đa ngôn ngữ.

[![Bila CVNSS CI](https://github.com/xulytiengviet/Bila-llvm/actions/workflows/bila-cvnss-ci.yml/badge.svg?branch=main)](https://github.com/xulytiengviet/Bila-llvm/actions/workflows/bila-cvnss-ci.yml)

[CI / Downloads](https://github.com/xulytiengviet/Bila-llvm/actions/workflows/bila-cvnss-ci.yml) · [Lite source](mlir/examples/cvnss/lite/) · [Developer SDK](mlir/examples/cvnss/README.md) · [Compatibility](mlir/examples/cvnss/specification/compatibility.md)

## 1. Cài đặt nhanh / Quick start

Bản Lite không yêu cầu cài LLVM/MLIR SDK. Gói CI hiện dành cho Linux x86-64 (Ubuntu 24.04 runner); trên Windows 10 nên dùng WSL2 Ubuntu hoặc build từ mã nguồn bằng compiler C++17.

### A. Tải bản đã biên dịch / Download

1. Mở [Bila CVNSS CI](https://github.com/xulytiengviet/Bila-llvm/actions/workflows/bila-cvnss-ci.yml), chọn lần chạy thành công mới nhất trên main (hoặc [lần chạy PR đã kiểm chứng](https://github.com/xulytiengviet/Bila-llvm/actions/runs/45577729669)).
2. Trong Artifacts tải `bila-llvm-lite-linux-x86_64`. Đăng nhập GitHub nếu cần. Artifact chỉ lưu 7 ngày, không phải GitHub Release lâu dài.
3. Giải nén ZIP rồi giải nén tar.gz:

```bash
mkdir -p bila-lite-dist
tar -xzf bila-llvm-lite-linux-x86_64.tar.gz -C bila-lite-dist
cd bila-lite-dist
sha256sum -c SHA256SUMS
chmod +x bila-lite
./bila-lite --version
```

### B. Build từ mã nguồn / Build from source

Ubuntu/WSL:

```bash
sudo apt update
sudo apt install -y git g++ python3
git clone --depth 1 --filter=blob:none --sparse https://github.com/xulytiengviet/Bila-llvm.git
cd Bila-llvm
git sparse-checkout set mlir/examples/cvnss
mkdir -p dist
g++ -std=c++17 -Os -flto -ffunction-sections -fdata-sections -Wl,--gc-sections -s mlir/examples/cvnss/lite/main.cpp -o dist/bila-lite
python3 mlir/examples/cvnss/lite/test_lite.py dist/bila-lite
python3 mlir/examples/cvnss/test/test_bridge.py
```

## 2. Sử dụng / Usage

```bash
./bila-lite --help
./bila-lite pack 1 0 -1
# 21
./bila-lite unpack 21
# 1 0 -1
./bila-lite emit-mlir 1 0 -1 > sample.mlir
./bila-lite emit-llvm 1 0 -1 > sample.ll
```

Nếu sử dụng bản tự build từ mã nguồn, thay `./bila-lite` bằng `./dist/bila-lite`.

Công thức: ID = 13 + 9h + 3m + l, mỗi trit thuộc {-1, 0, +1}; ID thuộc [0, 26]. Dữ liệu không hợp lệ bị từ chối.

Muốn biên dịch LLVM IR thành object file (tùy chọn, cần Clang):

```bash
clang -c sample.ll -o sample.o
```

## 3. Cầu ngữ nghĩa / Semantic bridge

Python 3 chỉ cần cho tiện ích hub.py. Ví dụ từ thư mục mã nguồn:

```bash
printf 'def process(x):\n    return x * 2\n' > example.py
python3 mlir/examples/cvnss/bridges/hub.py python example.py --format mlir > example.mlir
```

Đối với C/C++, JavaScript, Rust, BilaScript, dùng manifest symbol JSON rõ ràng, ví dụ `[{"symbol":"process","kind":"function"}]` lưu vào symbols.json:

```bash
python3 mlir/examples/cvnss/bridges/hub.py cpp example.cpp --symbols symbols.json --format json
```

Bridge không thực thi chương trình nhập, không tự suy luận tương đương ngữ nghĩa và chưa tích hợp native ClangIR, JSIR, MIR hay xDSL.

## 4. Kết quả kiểm thử / Validation

[CI run 45577729669](https://github.com/xulytiengviet/Bila-llvm/actions/runs/45577729669) trên commit `00376ca`: Lite build PASS, 27 Base27 round trips, 54 IR outputs, 4 Python bridge tests, mẫu LLVM IR thực thi thành công qua Clang; package trước manifest 33,997 bytes, artifact ZIP 11,059 bytes. Ngưỡng CI: dưới 30,000,000 bytes.

Đây là số đo của bản Lite thử nghiệm trên Linux, không phải dung lượng toàn bộ LLVM SDK. CI main cần được kiểm tra riêng. Native MLIR build/CTest chưa được xác nhận; GitHub Pages build có lỗi Jekyll riêng, không phải lỗi Lite.

## 5. Kiến trúc / Architecture

| Profile | Scope |
| --- | --- |
| Lite | Standalone constant Base27 compiler / IR emitter, C++17 |
| Developer | Native MLIR dialect, ODS, verification, lowering; matching SDK required |
| Future | Official CVNSS4.0 codec, BilaScript AST, domain dialects, cross-language native bridges |

Lite chỉ sinh tập con IR hằng số; không phải compiler BilaScript đầy đủ, general MLIR optimizer hay codec CVNSS4.0 chính thức. Không tuyên bố tương đương ngữ nghĩa hoặc hiệu năng AI khi chưa có benchmark.

[Developer build instructions](mlir/examples/cvnss/README.md) · [Bridge specification](mlir/examples/cvnss/bridges/README.md) · [Quality gates](mlir/examples/cvnss/specification/quality-gates.md)

## 6. Đóng góp / Contributions

Báo lỗi và đề xuất tại [Issues](https://github.com/xulytiengviet/Bila-llvm/issues). Mã nguồn nghiên cứu có AI hỗ trợ đáng kể; cần human review trước phát hành ổn định. Đây là dự án độc lập, không hàm ý LLVM upstream chấp thuận. Giấy phép: [Apache-2.0 WITH LLVM-exception](LICENSE.TXT).

---

# The LLVM Compiler Infrastructure

[![OpenSSF Scorecard](https://api.securityscorecards.dev/projects/github.com/llvm/llvm-project/badge)](https://securityscorecards.dev/viewer/?uri=github.com/llvm/llvm-project)
[![OpenSSF Best Practices](https://www.bestpractices.dev/projects/8273/badge)](https://www.bestpractices.dev/projects/8273)
[![libc++](https://github.com/llvm/llvm-project/actions/workflows/libcxx-pr-conformance-tests.yaml/badge.svg?branch=main&event=schedule)](https://github.com/llvm/llvm-project/actions/workflows/libcxx-pr-conformance-tests.yaml?query=event%3Aschedule)

Welcome to the LLVM project!

This repository contains the source code for LLVM, a toolkit for the
construction of highly optimized compilers, optimizers, and run-time
environments.

The LLVM project has multiple components. The core of the project is
itself called "LLVM". This contains all of the tools, libraries, and header
files needed to process intermediate representations and convert them into
object files. Tools include an assembler, disassembler, bitcode analyzer, and
bitcode optimizer.

C-like languages use the [Clang](https://clang.llvm.org/) frontend. This
component compiles C, C++, Objective-C, and Objective-C++ code into LLVM bitcode
-- and from there into object files, using LLVM.

Other components include:
the [libc++ C++ standard library](https://libcxx.llvm.org),
the [LLD linker](https://lld.llvm.org), and more.

## Getting the Source Code and Building LLVM

Consult the
[Getting Started with LLVM](https://llvm.org/docs/GettingStarted.html#getting-the-source-code-and-building-llvm)
page for information on building and running LLVM.

For information on how to contribute to the LLVM project, please take a look at
the [Contributing to LLVM](https://llvm.org/docs/Contributing.html) guide.

## Getting in touch

Join the [LLVM Discourse forums](https://discourse.llvm.org/), [Discord
chat](https://discord.gg/xS7Z362),
[LLVM Office Hours](https://llvm.org/docs/GettingInvolved.html#office-hours) or
[Regular sync-ups](https://llvm.org/docs/GettingInvolved.html#online-sync-ups).

The LLVM project has adopted a [code of conduct](https://llvm.org/docs/CodeOfConduct.html) for
participants to all modes of communication within the project.
