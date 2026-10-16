section .data
    ;mask to clear sign bit for abs val (0 = sign bit, 1 = rest)
    mask dq 0x7FFFFFFFFFFFFFFF
    clear    dq 0.0

section .text
bits 64
default rel
global asmkernel

asmkernel:
    ;rcx = array A, rdx = int n
    xor r9, r9           ;i
    movsd xmm0, [clear]  ;sum

    test rdx, rdx
    jle done

asm_loop:
    cmp r9, rdx
    jge done

    movsd xmm1, [rcx+r9*8] ;A[i] to xmm (8 bytes for double)
    pand xmm1, [mask]      ;clear sign bit, turns negative to positive
    addsd xmm0, xmm1       ;sum += abs value (A[i])

    inc r9
    jmp asm_loop

done:
    ret
