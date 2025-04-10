#include "servo.h"
#include <msp430fr2355.h>

void servo_init()
{
    TB3CCR0 = 20000 - 1;               // PWM period (20 ms)
    TB3CCTL1 = OUTMOD_7;              // CCR1 reset/set (PWM)
    TB3CCR1 = 1500;                   // 1.5 ms pulse width (neutral position)
    TB3CTL = TBSSEL__SMCLK | MC__UP | TBCLR; // SMCLK, up mode, clear TAR

    P6DIR |= BIT0;                   // Set P1.6 as output
    P6SEL0 |= BIT0;                  // Select TB0.1 function
    P6SEL1 &= ~BIT0;
}


void servo_setPosition(uint8_t pos)
{
    // 500 us - 2500 us range
    TB3CCR1 = 500 + (2000 * pos) / 256;
}