/* Write an ARM C program for the LPC1768 microcontroller to initialize UART0
for serial communication at 9600 baud rate and send a string repeatedly in an infinite
loop with a simple software delay between transmissions. */

#include <LPC17xx.h>

#define UART0_BAUDRATE 9600

void UART0_Init(void)
{
    uint32_t Fdiv;

    LPC_SC->PCONP |= (1 << 3);
    LPC_PINCON->PINSEL0 &= ~((3 << 4) | (3 << 6));
    LPC_PINCON->PINSEL0 |= (1 << 4) | (1 << 6);

    Fdiv = (25000000 / (16 * UART0_BAUDRATE));

    LPC_UART0->LCR = 0x83;
    LPC_UART0->DLM = Fdiv / 256;
    LPC_UART0->DLL = Fdiv % 256;
    LPC_UART0->LCR = 0x03;

    LPC_UART0->FCR = 0x07;
}

void UART0_SendChar(char c)
{
    while (!(LPC_UART0->LSR & (1 << 5)));
    LPC_UART0->THR = c;
}

void UART0_SendString(const char* str)
{
    while (*str)
        UART0_SendChar(*str++);
}

int main(void)
{
    int i;

    UART0_Init();

    while (1)
    {
        UART0_SendString("INTERSTELLAR\r\n");
        for (i = 0; i < 1000000; i++);
    }
}
