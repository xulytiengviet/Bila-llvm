---
layout: default
title: Bila-LLVM Lite
---
# Bila-LLVM Lite v0.3

Trình biên dịch thử nghiệm Base27/Trit và bộ sinh IR hằng số, không yêu cầu MLIR SDK tại runtime.

[README và hướng dẫn cài đặt trên GitHub](https://github.com/xulytiengviet/Bila-llvm/blob/main/README.md) · [CI và tải artifact](https://github.com/xulytiengviet/Bila-llvm/actions/workflows/bila-cvnss-ci.yml) · [Mã nguồn Lite](https://github.com/xulytiengviet/Bila-llvm/tree/main/mlir/examples/cvnss/lite)

## Sử dụng nhanh

```sh
./bila-lite pack 1 0 -1
# 21
./bila-lite unpack 21
# 1 0 -1
./bila-lite emit-mlir 1 0 -1
./bila-lite emit-llvm 1 0 -1
```

Bản Lite không phải compiler BilaScript hoàn chỉnh hay codec CVNSS4.0 chính thức. Native MLIR SDK là cấu hình phát triển riêng, chưa nghiệm thu.

[Kiểm thử Lite đã đạt trên commit 00376ca](https://github.com/xulytiengviet/Bila-llvm/actions/runs/45577729669): 27 Base27 round trips, 54 IR outputs, 4 bridge tests. Artifact ZIP: 11,059 bytes.

[Giấy phép Apache-2.0 WITH LLVM-exception](https://github.com/xulytiengviet/Bila-llvm/blob/main/LICENSE.TXT)
