# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
import itertools
import subprocess
import sys
from pathlib import Path
exe = sys.argv[1]
def run(*args, ok=True):
    p = subprocess.run([exe, *map(str,args)], capture_output=True, text=True)
    assert (p.returncode == 0) == ok, (args,p.returncode,p.stderr)
    if not ok:
        assert not p.stdout
    return p.stdout.strip()
for h,m,l in itertools.product(range(-1,2),repeat=3):
    n=13+9*h+3*m+l
    assert run("pack",h,m,l)==str(n)
    assert run("unpack",n)==f"{h} {m} {l}"
    assert run("emit-mlir",h,m,l)==f"module {{\n  func.func @pack() -> i32 {{\n    %id = arith.constant {n} : i32\n    return %id : i32\n  }}\n}}"
    assert run("emit-llvm",h,m,l)==f"define i32 @pack() {{\n  ret i32 {n}\n}}"
for args in [("pack",2,0,0),("pack",0,0,-2),("unpack",27),("unpack",-1),("unpack","1x"),("pack","999999999999999",0,0),("pack",0,0),("bad",0,0,0),("unpack","+-1")]:
    run(*args,ok=False)
assert run("pack","+1",0,-1)=="21"
assert Path(exe).stat().st_size < 30_000_000
print("PASS: 27 Base27 round trips, 54 IR outputs, invalid inputs, executable size")
