/* Write an embedded C program to implement Type-II Linear FIR Filter using ARM LPC1768. */

#include <LPC17xx.h>

#define N 4

float h[N] = {0.25, 0.25, 0.25, 0.25};
float x[N] = {0};

volatile float output = 0;
volatile int i;

float input_samples[] = {100, 120, 80, 60, 200, 100, 150, 90, 50, 0};
int sample_index = 0;
int num_samples = sizeof(input_samples) / sizeof(float);

float fir_filter(float new_sample)
{
    float result = 0;
    int i;

    for (i = N - 1; i > 0; i--)
        x[i] = x[i - 1];

    x[0] = new_sample;

    for (i = 0; i < N; i++)
        result += h[i] * x[i];

    return result;
}

int main(void)
{
    float input;

    SystemInit();
    SystemCoreClockUpdate();

    LPC_PINCON->PINSEL1 &= ~(0xF << 16);
    LPC_GPIO0->FIODIR   |= (1 << 24) | (1 << 25);

    while (1)
    {
        if (sample_index < num_samples)
            input = input_samples[sample_index++];
        else
            input = 0;

        output = fir_filter(input);

        if (output > 100.0)
            LPC_GPIO0->FIOSET = (1 << 24) | (1 << 25);
        else
            LPC_GPIO0->FIOCLR = (1 << 24) | (1 << 25);

        for (i = 0; i < 500000; i++);
    }
}
