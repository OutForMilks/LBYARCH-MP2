section .text
global imgCvtGrayDoubleToInt ; C can call this

imgCvtGrayDoubleToInt:

	CVTSI2SD XMM15, R9
loop:
    MOVSD XMM1, [RCX] ; copy double (current index)
    MULSD XMM1, XMM15
    CVTSD2SI R11, XMM1
    MOV [RDX], R11D ; paste double (current index)
    
    ADD RCX, 8 ; move to next index
    ADD RDX, 4 ; move to next index

    DEC R8 ; decrement counter  
    JNZ loop ; restart until 0

    xor rax, rax
    ret
