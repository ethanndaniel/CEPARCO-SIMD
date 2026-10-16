; asmfunc.asm
; ASUM using scalar x86-64 assembly
; computes asum = sum of |A[i]|
; Input: rcx = pointer to A, edx = number of elements n
; Output: xmm0 = sum of absolute values
section .data
	clear dq 0.0
	negate dq -1.0 

section .text
bits 64
default rel
global asmkernel

asmkernel:
	xor r9, r9
	movsd xmm0, [clear]
	movsd xmm2, [clear]

	cmp edx, 0 ; handle zero or negative length
    jle fin

	movsxd rdx, edx ; convert the 32-bit integer n to 64 bits

add_loop:
	cmp r9, rdx
    jae fin

    movsd xmm1, [rcx + r9*8] ; load A[i]

    ; compare A[i] with zero
    ucomisd xmm1, xmm2
    jnc adding

    mulsd xmm1, [negate] ; if negative, multiply by -1.0

adding:
	addsd xmm0, xmm1 ; add |A[i]| to the running sum
	inc r9
	JMP add_loop

fin:
	ret