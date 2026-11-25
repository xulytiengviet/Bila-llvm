// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#include <charconv>
#include <iostream>
#include <string_view>
#include <system_error>
static bool integer(std::string_view s, int &v) {
  if (s.empty()) return false;
  if (s.front() == '+') { s.remove_prefix(1); if (s.empty() || s.front() == '-') return false; }
  auto r = std::from_chars(s.data(), s.data()+s.size(), v);
  return r.ec == std::errc{} && r.ptr == s.data()+s.size();
}
static int fail() { std::cerr << "invalid arguments or out-of-range value\n"; return 2; }
int main(int argc, char **argv) {
  if (argc == 2 && std::string_view(argv[1]) == "--version") {
    std::cout << "Bila-LLVM Lite 0.3 experimental\n"; return 0;
  }
  if (argc == 2 && std::string_view(argv[1]) == "--help") {
    std::cout << "bila-lite pack H M L | unpack ID | emit-mlir H M L | emit-llvm H M L\n"; return 0;
  }
  if (argc < 2) return fail();
  std::string_view op(argv[1]);
  int h=0,m=0,l=0,n=0;
  if (op == "unpack") {
    if (argc != 3 || !integer(argv[2],n) || n<0 || n>26) return fail();
    std::cout << n/9-1 << ' ' << (n/3)%3-1 << ' ' << n%3-1 << '\n'; return 0;
  }
  if (op != "pack" && op != "emit-mlir" && op != "emit-llvm") return fail();
  if (argc != 5 || !integer(argv[2],h) || !integer(argv[3],m) || !integer(argv[4],l)
      || h < -1 || h > 1 || m < -1 || m > 1 || l < -1 || l > 1) return fail();
  n=13+9*h+3*m+l;
  if (op=="pack") std::cout << n << '\n';
  else if (op=="emit-mlir")
    std::cout << "module {\n  func.func @pack() -> i32 {\n    %id = arith.constant "
              << n << " : i32\n    return %id : i32\n  }\n}\n";
  else std::cout << "define i32 @pack() {\n  ret i32 " << n << "\n}\n";
  return 0;
}
