/*  Write and ALP to demonstrate LOAD-STORE ARCHITECTURE  */

AREA    LOAD_STORE_DEMO, CODE, READONLY
EXPORT  __main

__main
    LDR     R0, =SRC_AREA
    LDR     R1, =DST_AREA

    LDR     R2, =0x12345678
    STR     R2, [R1]
    LDR     R3, [R1]

    LDR     R4, =0xABCDEF10
    STRB    R4, [R1, #4]
    LDRB    R5, [R1, #4]

    LDR     R6, =0xCDEFABCD
    STRH    R6, [R1, #8]
    LDRH    R7, [R1, #8]

    LDR     R8, =0xAAAA1111
    LDR     R9, =0xBBBB2222
    LDR     R10, =0xCCCC3333

    STMIA   R1!, {R8-R10}
    SUB     R1, R1, #12

    MOV     R8, #0
    MOV     R9, #0
    MOV     R10, #0

    LDMIA   R1!, {R8-R10}

STOP    B       STOP

AREA    DATA, DATA, READWRITE
SRC_AREA    DCD     0x11223344
DST_AREA    DCD     0x0, 0x0, 0x0, 0x0

END
