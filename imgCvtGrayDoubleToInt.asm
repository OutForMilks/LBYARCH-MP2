section .data
    val dq 255.0
section .text
global imgCvtGrayDoubleToInt ; C can call this

imgCvtGrayDoubleToInt:

loop:
    MOVSD XMM1, qword [RCX] ; copy double (current index)
    MULSD XMM1, qword [rel val]; rel is used to get the value relative to the instruction (inside this )
    CVTSD2SI R11, XMM1
    MOV [RDX], R11D ; paste double (current index)
    
    ADD RCX, 8 ; move to next index
    ADD RDX, 4 ; move to next index

    DEC R8 ; decrement counter  
    JNZ loop ; restart until 0

    xor rax, rax
    ret
