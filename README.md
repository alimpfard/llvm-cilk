# Cilk-compiler
Cilk to LLVM / citron compiler

# Configure Environment

1. get yourself a build of llvm (7 is tested)
2. proceed to the next step

# Compile
To compile the compiler source code  

1. ```make clean```
2. ```make```

# Run code

- ```./compiler [-vfph] <c_code/your_code.c>```

- -v: display generated back-end code in the terminal.
- -f: output generated back-end code to ```<c_code/your_code.[(ll)/(ctr)]>```.
- -p: alternatively generate citron code.
- -h: help

# Test code

- using ```lli c_code/your_code.ll``` to test llvm back-end code.
- using ```ctr c_code/your_code.ctr``` to test citron back-end code.
