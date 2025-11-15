/*  Write a C program to demonstrate the use of the SysTick timer interrupt managed by Nested Vector Interrupt Controller(NVIC). */

#include "LPC17xx.h"

void SysTick_Handler(void)
{
    LPC_GPIO0->FIOPIN ^= (1 << 22);
}

void init_GPIO(void)
{
    LPC_PINCON->PINSEL1 &= ~(3 << 12);
    LPC_GPIO0->FIODIR   |=  (1 << 22);
}

void init_SysTick(void)
{
    SysTick->LOAD  = (SystemCoreClock / 2) - 1;
    SysTick->VAL   = 0;
    SysTick->CTRL  = SysTick_CTRL_TICKINT_Msk |
                     SysTick_CTRL_ENABLE_Msk;
}

int main(void)
{
    SystemInit();
    SystemCoreClockUpdate();

    init_GPIO();
    init_SysTick();

    while(1)
    {
        __WFI();
    }
}
