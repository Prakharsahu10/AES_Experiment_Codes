/* Write an ALP to perform 32-bit addition, subtraction, multiplication, and division on operands stored in RAM locations */ 

AREA PROGRAM, CODE, READONLY
EXPORT __main

__main
    LDR     R1, =0x10000000
    LDR     R2, [R1]
    LDR     R3, [R1, #4]
    LDR     R4, [R1, #8]

    CMP     R2, #1
    BNE     CHK_SUB
    ADDS    R7, R3, R4
    B       LAST

CHK_SUB
    CMP     R2, #2
    BNE     CHK_MUL
    SUBS    R7, R3, R4
    B       LAST

CHK_MUL
    CMP     R2, #3
    BNE     CHK_DIV
    UMULL   R7, R8, R3, R4
    B       LAST

CHK_DIV
    CMP     R2, #4
    BNE     LAST
    UDIV    R7, R3, R4

LAST
    STR     R7, [R1, #20]
    STR     R8, [R1, #24]

STOP
    B       STOP

END
