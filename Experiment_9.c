/* Write an embedded C program to demonstrate the working of Inter Integrated Circuit (𝑰𝟐C) using LPC1768 and verify the same in Keil simulator */

#include <LPC17xx.h>

#define I2C_CLK        100000
#define I2C_SLAVE_ADDR 0x50

void I2C_Init(void)
{
    LPC_PINCON->PINSEL1 |= (1 << 22) | (1 << 24);
    LPC_I2C1->I2SCLH = 125;
    LPC_I2C1->I2SCLL = 125;
    LPC_I2C1->I2CONSET = (1 << 6);
}

void I2C_Start(void)
{
    LPC_I2C1->I2CONSET = (1 << 5);
    LPC_I2C1->I2CONCLR = (1 << 3);
    while (!(LPC_I2C1->I2CONSET & (1 << 3)));
}

void I2C_Stop(void)
{
    LPC_I2C1->I2CONSET = (1 << 4);
    LPC_I2C1->I2CONCLR = (1 << 3);
}

void I2C_WriteByte(uint8_t data)
{
    LPC_I2C1->I2DAT = data;
    LPC_I2C1->I2CONCLR = (1 << 3);
    while (!(LPC_I2C1->I2CONSET & (1 << 3)));
}

int main(void)
{
    volatile int i;

    SystemInit();
    I2C_Init();

    while (1)
    {
        I2C_Start();
        I2C_WriteByte((I2C_SLAVE_ADDR << 1) | 0);
        I2C_WriteByte(0xCD);
        I2C_Stop();

        for (i = 0; i < 1000000; i++);
    }

    return 0;
}
