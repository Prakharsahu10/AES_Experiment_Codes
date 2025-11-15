/* Write an embedded C program to interface a simple switch and display its status through LED. */

#include <LPC17xx.h>

int main(void)
{
    SystemInit();
    SystemCoreClockUpdate();

    LPC_PINCON->PINSEL1 = 0x00000000;         // Configure P0.16 – P0.31 as GPIO
    LPC_GPIO0->FIODIR  |= 0x03000000;         // Configure P0.24 and P0.25 as output (LEDs)
    LPC_GPIO2->FIODIR  &= ~(0x00000800);      // Configure P2.11 as input (Switch)

    while(1)
    {
        if(!(LPC_GPIO2->FIOPIN & 0x00000800)) // Switch pressed (active low)
        {
            LPC_GPIO0->FIOSET = 0x03000000;   // Turn ON LEDs (P0.24 & P0.25)
        }
        else
        {
            LPC_GPIO0->FIOCLR = 0x03000000;   // Turn OFF LEDs
        }
    }
}
