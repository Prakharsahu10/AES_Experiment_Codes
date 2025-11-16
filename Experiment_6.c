/* Write an embedded C program to generate a sine wave using SysTick timer in LPC1768. */

#include <LPC17xx.h>
#include <math.h>

#define PI 3.14159265
#define SAMPLES 100

uint16_t sine_table[SAMPLES];

void generate_sine_table(void)
{
    int i;
    for (i = 0; i < SAMPLES; i++)
        sine_table[i] = (uint16_t)(512 + 511 * sin(2 * PI * i / SAMPLES));
}

void init_DAC(void)
{
    LPC_PINCON->PINSEL1 &= ~(3 << 20);
    LPC_PINCON->PINSEL1 |=  (2 << 20);
}

void DAC_Output(uint16_t value)
{
    LPC_DAC->DACR = (value << 6);
}

volatile uint32_t index = 0;

void SysTick_Handler(void)
{
    DAC_Output(sine_table[index++]);
    if (index >= SAMPLES)
        index = 0;
}

int main(void)
{
    generate_sine_table();
    init_DAC();
    SysTick_Config(SystemCoreClock / (1000 * SAMPLES));

    while(1)
    {
    }
}
