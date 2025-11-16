/* Write a C program for ARM Cortex-M3 (LPC1768) to demonstrate the working of low power modes: Idle, Sleep, Deep Sleep, and Power Down.
*/

#include <LPC17xx.h>

void EINT0_IRQHandler(void);
void toggleLED(uint32_t pin);

static uint32_t led_state = 0;

void init_GPIO(void)
{
    LPC_PINCON->PINSEL1 &= ~((3 << 12) | (3 << 14) | (3 << 16) | (3 << 18));
    LPC_GPIO0->FIODIR   |= (0x0F << 22);
}

void init_EINT0(void)
{
    LPC_PINCON->PINSEL4 &= ~(3 << 20);
    LPC_PINCON->PINSEL4 |=  (1 << 20);
    LPC_SC->EXTMODE     |=  (1 << 0);
    LPC_SC->EXTPOLAR    &= ~(1 << 0);
    NVIC_EnableIRQ(EINT0_IRQn);
}

int main(void)
{
    SystemInit();
    init_GPIO();
    init_EINT0();

    while (1)
    {
        LPC_SC->PCON = 0x01;
        __WFI();
        toggleLED(22);

        LPC_SC->PCON = 0x02;
        __WFI();
        toggleLED(23);

        LPC_SC->PCON = 0x03;
        __WFI();
        toggleLED(24);

        LPC_SC->PCON = 0x07;
        __WFI();
        toggleLED(25);
    }
}

void EINT0_IRQHandler(void)
{
    LPC_SC->EXTINT = (1 << 0);
}

void toggleLED(uint32_t pin)
{
    led_state ^= (1 << pin);
    if (led_state & (1 << pin))
        LPC_GPIO0->FIOSET = (1 << pin);
    else
        LPC_GPIO0->FIOCLR = (1 << pin);
}
