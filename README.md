# LBYARCH-MP2

**Overview:**
- **Project:** x86-64 assembly <-> C interface to convert a grayscale image represented as doubles (0.0–1.0) into 8-bit integers (0–255).
- **Function implemented in assembly:** `imgCvtGrayDoubleToInt`
- **Language / tools:** C (GCC), x86-64 assembly (NASM), Windows build instructions shown (object `.obj` linking).

**Files:**
- `main.c`: C driver that generates data, times the assembly function, runs correctness checks, and prints results.
- `imgCvtGrayDoubleToInt.asm`: Assembly implementation of the conversion function using scalar SIMD (XMM) floating-point instructions.
- `imgCvtGrayDoubleToInt.obj`: Assembled object (not included here — build with NASM).

**Build & Run (Windows, GCC + NASM):**
- Assemble the assembly file with NASM:
```powershell
nasm -f win64 imgCvtGrayDoubleToInt.asm -o imgCvtGrayDoubleToInt.obj
```
- Compile & link with GCC:
```powershell
gcc main.c imgCvtGrayDoubleToInt.obj -o test.exe
```
- Run the executable:
```powershell
.\test.exe
```

**Example Output (what to expect):**
- The program runs three sizes: `10x10`, `100x100`, and `1000x1000` (or a reduced maximum if your machine cannot allocate `1000x1000`).
- It prints an average assembly time (over `RUNS`) and whether the assembly output matches the C reference.
- Example printed lines:
```
=====================================
Image Size: 10 x 10
Average ASM Time (30 runs): 0.000000 seconds
Correctness Check: FAILED
```

**Timing notes & recommended changes (why you saw tiny times):**
- The example uses `clock()` which returns CPU ticks with relatively low resolution on some Windows toolchains; for very quick calls (small images) the measured `(end-start)` may be zero and print `0.000000` seconds.
- For reliable timing results:
	- Increase `RUNS` (e.g. 1000 or 10000) so each measured call accumulates measurable time, or
	- Call the assembly routine many times within a single measurement loop, or
	- Replace `clock()` with a high-resolution timer such as `QueryPerformanceCounter` / `QueryPerformanceFrequency`.

Example high-resolution timer snippet (Windows C):
```c
#include <windows.h>
LARGE_INTEGER freq, t0, t1;
QueryPerformanceFrequency(&freq);
QueryPerformanceCounter(&t0);
// call measured code here
QueryPerformanceCounter(&t1);
double seconds = (double)(t1.QuadPart - t0.QuadPart) / (double)freq.QuadPart;
```

**Correctness notes (why ASM differed by ±1):**
- The C code originally used casts like `(int)(x * 255)` which truncate toward zero.
- The SSE instruction `CVTSD2SI` rounds according to the current SSE rounding mode (often round-to-nearest) and can produce off-by-one results compared to truncation. That explains observed mismatches (ASM larger by 1 in some entries).
- Fix: use the truncating conversion instruction `CVTTSD2SI` in the assembly implementation to match C-style truncation. Example replacement in the ASM loop:
```asm
		; before
		CVTSD2SI R11, XMM1
		; after
		CVTTSD2SI R11, XMM1
```

**Assembly best-practices & hints:**
- Use a volatile XMM register (e.g. `XMM2`) or a memory constant for the multiplication factor `255.0` to avoid clobbering callee-saved registers.
- `imgCvtGrayDoubleToInt` calling convention (Windows x86-64):
	- Arguments arrive in `RCX`, `RDX`, `R8`, `R9` — match your implementation. Common layout used here is:
		- `RCX` = `double *input`
		- `RDX` = `int *output`
		- `R8`  = `size` (number of elements)
		- `R9`  = (optional) not required if loading `255.0` from memory; if passing factor via register, convert it to double once with `CVTSI2SD` and use an XMM register.
- Loop outline:
	- Load input double into `XMM1` with `MOVSD [RCX]`.
	- Multiply by the factor `255.0` with `MULSD`.
	- Convert to integer with `CVTTSD2SI` to `R11`.
	- Store `R11D` into `[RDX]`.
	- Advance `RCX += 8`, `RDX += 4`, decrement `R8` and loop.

**What I tested / Observed (notes to include in your report):**
- During development you may observe `Correctness Check: FAILED` when using `CVTSD2SI` due to rounding differences. Switching to `CVTTSD2SI` resolves off-by-one mismatches.
- Timing values for small images (10x10, 100x100) may print `0.000000` seconds when measured with `clock()` due to low resolution; `1000x1000` produced a nonzero average in one run but use high-resolution timing for credible performance analysis.

**Deliverables to include on GitHub (as required by the assignment):**
- Source files: `main.c`, `imgCvtGrayDoubleToInt.asm` (and the assembled object if you prefer), any build scripts.
- `README.md` (this file) with the required sections:
	- Execution time and short analysis of performance (include how you measured and note any limitations),
	- A screenshot of the program output that shows correctness checking and timings,
	- A short screen-capture video (5–10 mins) walking through source code, compilation, and execution,
	- List of group members in the repo's README or a separate `AUTHORS` file,
	- Any additional notes about machine/platform used (OS, CPU) and any deviations from the spec.

**How to reproduce (concise):**
1. Assemble: `nasm -f win64 imgCvtGrayDoubleToInt.asm -o imgCvtGrayDoubleToInt.obj`
2. Compile & link: `gcc main.c imgCvtGrayDoubleToInt.obj -o test.exe`
3. Run: `.\test.exe`

**Notes & next steps you may want me to apply:**
- (A) Replace `CVTSD2SI` with `CVTTSD2SI` in `imgCvtGrayDoubleToInt.asm` to match C truncation exactly.
- (B) Replace `clock()` timing with `QueryPerformanceCounter` for higher resolution measurements.
- (C) Increase `RUNS` to a larger number (e.g. 1000) for more stable averages.

If you want, I can apply changes (A) and (B) to your repository and run a build to show updated correctness and timing results.

---
_Prepared to accompany the course assignment: x86-to-C interface programming project._