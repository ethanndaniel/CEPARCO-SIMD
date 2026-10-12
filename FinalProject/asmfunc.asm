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
		add_loop:
		cmp r9, rdx
		JE fin
		movsd xmm1, [rcx+r9*8]
		ucomisd xmm1, xmm2    ; if less than 0  CF = 1
		JNC adding   ; If CF != 1 or 0 (meaning positive), go straight to adding
		vmulsd xmm1, [negate] ; will turn negative into positive
		adding:
		addsd xmm0, xmm1
		inc r9
		JMP add_loop
		fin:
		ret