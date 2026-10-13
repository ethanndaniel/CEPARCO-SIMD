# CEPARCO SIMD Project
### 1st Term AY 2026-2027 | S01 Group 2
---
 
### Members
| Name | GitHub |
| :--- | :--- |
| Dabuit, Daniel Jedrick C. | [@danueli](https://github.com/danueli) |
| Magbatoc, Ethan Daniel | [@ethanndaniel](https://github.com/ethanndaniel) |
| Perez, Jose Bryan | [@JoseBryanPerez](https://github.com/JoseBryanPerez) |
| Uy, Tara Ysabel P. | [@tartar121](https://github.com/tartar121) |
 
---
 
## 1. Project Overview
 
This project implements the **sum of absolute values (ASUM)** kernel of a double-precision vector `A` in four ways and compares their performance and correctness.
 
```
asum = Σ |A[i]|   for i = 0 .. n-1
```
 
| # | Version | File | Registers |
| :-: | :--- | :--- | :--- |
| 1 | C | `main.c` (`ckernel`) | compiler-generated |
| 2 | x86-64 (non-SIMD) | `asmfunc.asm` (`asmkernel`) | scalar XMM (`movsd`, `addsd`) |
| 3 | x86-64 SIMD AVX2 | `xmm.asm` (`xmmkernel`) | XMM (128-bit, 2 doubles) |
| 4 | x86-64 SIMD AVX2 | `ymm.asm` (`ymmkernel`) | YMM (256-bit, 4 doubles) |
 
**Kernel signature (all versions):** `double kernel(const double* A, int n)`, with the result returned in `XMM0` (Windows x64 calling convention: `RCX = A`, `EDX = n`).
 
---
 
## 2. How to Build and Run
 _TODO: CORRECT THIS PART ONCE FINISHED_
 
**Requirements:** Visual Studio _(version: TODO)_, NASM _(version: TODO)_, x64 platform, a CPU with AVX2.
 
1. Clone the repo and open `FinalProject.sln`.
2. Select the **x64** platform and either **Debug** or **Release**.
3. Build and run (`Ctrl+F5`).
_TODO: note any NASM custom-build setup needed in Visual Studio._
 
**Test machine:**
 
| Item | Value |
| :--- | :--- |
| CPU | TODO |
| RAM | TODO |
| OS | TODO |
| Compiler / flags | TODO (Debug: `/Od`, Release: `/O2`) |
 
---
 
## 3. Methodology
 
- **Input values:** TODO. Currently `srand(67)` and `A[i] = (rand() / RAND_MAX) * 100.0 - 50.0`, i.e. random doubles in [-50, 50].
- **Vector sizes (n):** TODO (2^20, 2^26, 2^30, or the fallback size actually used, and why).
- **Timing:** only the kernel call is timed, using `QueryPerformanceCounter`. Each kernel runs **30 times** and the average is reported. One untimed warm-up call is made first.
- **Correctness:** the C version is the answer key. Because SIMD adds in a different order than scalar code, floating-point sums can differ in the last digits, so a result counts as correct if the relative error is ≤ `1e-9`.
- **Boundary handling:** TODO. The XMM kernel handles 8 elements per iteration and the YMM kernel 16, and the remaining `n mod 8` / `n mod 16` elements are processed by a scalar tail loop. Tested sizes: TODO (e.g. 1, 3, 7, 15, 17, 1003, 2^20 + 3).
---
 
## 4. Report
 
### i. Program output with execution time (all cases)
 
#### Debug
<!-- ![Debug timing](screenshots/debug_timing.png) -->
_TODO: screenshot_
 
#### Release
<!-- ![Release timing](screenshots/release_timing.png) -->
_TODO: screenshot_
 
### ii. Comparative table of execution time
 
Average of 30 runs, in seconds.
 
#### Debug
| n | C | x86-64 | SIMD XMM | SIMD YMM |
| :--- | :-: | :-: | :-: | :-: |
| 2^20 | TODO | TODO | TODO | TODO |
| 2^26 | TODO | TODO | TODO | TODO |
| 2^30 (or fallback) | TODO | TODO | TODO | TODO |
 
#### Release
| n | C | x86-64 | SIMD XMM | SIMD YMM |
| :--- | :-: | :-: | :-: | :-: |
| 2^20 | TODO | TODO | TODO | TODO |
| 2^26 | TODO | TODO | TODO | TODO |
| 2^30 (or fallback) | TODO | TODO | TODO | TODO |
 
#### Speedup relative to C (Release)
| n | x86-64 | SIMD XMM | SIMD YMM |
| :--- | :-: | :-: | :-: |
| 2^20 | TODO× | TODO× | TODO× |
| 2^26 | TODO× | TODO× | TODO× |
| 2^30 (or fallback) | TODO× | TODO× | TODO× |
 
_TODO: short analysis of how many times faster each kernel is and why._
 
### iii. Correctness check: C version
<!-- ![C output](screenshots/c_output.png) -->
_TODO: screenshot_
 
### iv. Correctness check: x86-64
<!-- ![x86-64 output](screenshots/asm_output.png) -->
_TODO: screenshot_
 
### v. Correctness check: SIMD XMM
<!-- ![XMM output](screenshots/xmm_output.png) -->
_TODO: screenshot_
 
### vi. Correctness check: SIMD YMM
<!-- ![YMM output](screenshots/ymm_output.png) -->
_TODO: screenshot_
 
### vii. Boundary check: SIMD XMM and YMM
<!-- ![Boundary check](screenshots/boundary.png) -->
_TODO: screenshot (e.g. n = 1003 and other sizes that are not multiples of the SIMD width)_
 
### viii. Analysis of results
 
_TODO. Points to cover:_
- Which kernel is fastest, and why?
- Is the kernel memory-bound or compute-bound? Is YMM faster than optimized C? (Estimate bandwidth as `n × 8 bytes ÷ time` and compare it to the machine's memory bandwidth.)
- Why the speedup is or isn't close to the theoretical one (2× for XMM, 4× for YMM): memory bandwidth limit, cache effects at different n, loop and add latency (multiple accumulators), tail loop overhead.
- Debug vs Release differences.
- Why the x86-64 scalar version performs the way it does (e.g. a branch on the sign of each element vs a branchless bitmask).
### ix. Problems encountered, solutions, unique methodology, AHA moments
 
_TODO. Ideas to document:_
- Problems encountered and how they were solved.
- Unique methodology used (e.g. sign-bit masking for `|x|`, 4 independent accumulators, `vzeroupper` before returning from the YMM kernel, `movsxd` for the `int n` argument).
- AHA moments.
---
 
## 5. Repository Contents
 
```
CEPARCO-SIMD/
├── FinalProject/
│   ├── FinalProject.vcxproj          # Visual Studio project file
│   ├── FinalProject.vcxproj.filters
│   ├── main.c                        # C kernel, driver, timing, correctness check
│   ├── asmfunc.asm                   # x86-64 non-SIMD kernel
│   ├── xmm.asm                       # SIMD AVX2 kernel (XMM)
│   └── ymm.asm                       # SIMD AVX2 kernel (YMM)
├── screenshots/                      # images used in this report (to be added)
├── .gitattributes
├── .gitignore
├── FinalProject.sln                  # open this in Visual Studio
└── README.md
```
