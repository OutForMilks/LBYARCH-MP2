section .text
global imgCvtGrayDoubleToInt ; C can call this

imgCvtGrayDoubleToInt:

loop:
    MOVSD XMM1, [RCX] ; copy double (current index)
    MOVSD [RDX], XMM1 ; paste double (current index)
    
    ADD RCX, 8 ; move to next index
    ADD RDX, 8 ; move to next index

    DEC R8 ; decrement counter  
    JNZ loop ; restart until 0

    xor rax, rax
    ret