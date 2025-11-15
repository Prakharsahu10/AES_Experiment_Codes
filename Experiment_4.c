/*  Write a C program to demonstrate the working of Memory Protection Unit (MPU). */

#include "LPC17xx.h"

#define PROT_BASE 0x2007E000UL

void MemManage_Handler(void)
{
    volatile uint32_t cfsr  = SCB->CFSR;
    volatile uint32_t mmfar = SCB->MMFAR;
    while(1);
}

int main(void)
{
    SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA_Msk;
    SCB->CFSR = 0xFFFFFFFF;

    MPU->RNR  = 0;
    MPU->RBAR = PROT_BASE;
    MPU->RASR = ((8 - 1) << MPU_RASR_SIZE_Pos) |
                (0U << MPU_RASR_AP_Pos) |
                MPU_RASR_ENABLE_Msk;

    MPU->CTRL = MPU_CTRL_ENABLE_Msk | MPU_CTRL_PRIVDEFENA_Msk;

    __DSB();
    __ISB();

    *((volatile uint32_t *)PROT_BASE) = 0xABCDABCD;

    while(1);
}
