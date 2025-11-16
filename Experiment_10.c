/*  Write a C program for the ARM Cortex-M3 (LPC1768) microcontroller to demonstrate the working of special interrupt mask registers — PRIMASK, BASEPRI, and FAULTMASK. */

#include <LPC17xx.h>
#include <core_cm3.h>

#define LED_PIN (1 << 22)

void LED_Init(void)
{
    LPC_GPIO0->FIODIR |= LED_PIN;
}

void LED_Toggle(void)
{
    LPC_GPIO0->FIOPIN ^= LED_PIN;
}

void delay(void)
{
    volatile int i;
    for (i = 0; i < 500000; i++);
}

void SysTick_Handler(void)
{
    LED_Toggle();
}

int main(void)
{
    SystemInit();
    LED_Init();
    SysTick_Config(SystemCoreClock / 100);

    while (1)
    {
        __set_PRIMASK(1);
        delay();
        __set_PRIMASK(0);
        delay();

        __set_BASEPRI(0x40);
        delay();
        __set_BASEPRI(0x00);
        delay();

        __set_FAULTMASK(1);
        delay();
        __set_FAULTMASK(0);
        delay();
    }
}
