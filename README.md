# LBYARCH-MP2
***Lab Group 4***
- Borja, Stephen
- Ching, Justin

**Overview:**
- **Project:** x86-64 assembly <-> C interface to convert a grayscale image represented as doubles (0.0–1.0) into 8-bit integers (0–255).
- **Function implemented in assembly:** `imgCvtGrayDoubleToInt`
- **Language / tools:** C (GCC), x86-64 assembly (NASM), Windows build instructions shown (object `.obj` linking).

**Files:**
- `main.c`: C driver that takes inputs then prints the outputs from the ASM function.
- `performance_tests.c`: C driver that generates data, times the assembly function, runs correctness checks, and prints results.
- `imgCvtGrayDoubleToInt.asm`: Assembly implementation of the conversion function using scalar SIMD (XMM) floating-point instructions.
- `imgCvtGrayDoubleToInt.obj`: Assembled object (not included here — build with NASM).

**Build & Run (Windows, GCC + NASM):**
- Assemble the assembly file with NASM:
```powershell
nasm -f win64 imgCvtGrayDoubleToInt.asm -o imgCvtGrayDoubleToInt.obj
```
- Compile & link with GCC:
```powershell
gcc main.c imgCvtGrayDoubleToInt.obj -o main.exe
```

- For performance tests:
```
gcc performance_tests.c imgCvtGrayDoubleToInt.obj -o tests.exe
```

- Run the executable:
```powershell
.\main.exe
```
