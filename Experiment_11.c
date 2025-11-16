/* Write an embedded C program to demonstrate the working of two-stack model in ARM- LPC1768. */

#include <LPC17xx.h>
#include <core_cm3.h>

uint32_t processStack[128];
uint32_t *psp_top;

uint32_t msp_before, psp_before, control_before;
uint32_t control_after, current_psp, current_msp;

void delay(void)
{
    volatile int i;
    for (i = 0; i < 200000; i++);
}

int main(void)
{
    LPC_GPIO0->FIODIR |= (1 << 22);

    msp_before     = __get_MSP();
    psp_before     = __get_PSP();
    control_before = __get_CONTROL();

    psp_top = processStack + 128;
    __set_PSP((uint32_t)psp_top);
    __set_CONTROL(0x02);
    __ISB();

    control_after = __get_CONTROL();
    current_psp   = __get_PSP();
    current_msp   = __get_MSP();

    while (1)
    {
        LPC_GPIO0->FIOPIN ^= (1 << 22);
        delay();
    }
}
