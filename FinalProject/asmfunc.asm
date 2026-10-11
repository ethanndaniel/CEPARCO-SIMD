section .data
msg db "ASM Test",13,10,0

section .text
bits 64
default rel

global asmkernel
extern printf

asmkernel:
	sub rsp, 8*5 ; caller
	lea rcx, [msg]
	call printf
	add rsp, 8*5
	ret