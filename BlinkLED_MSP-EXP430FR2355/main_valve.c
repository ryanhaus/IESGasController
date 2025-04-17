#include "main_valve.h"
#include <msp430fr2355.h>

void mainValve_Init()
{
    TB1CCR0 = 20000 - 1;               // PWM period (20 ms)
    TB1CCTL2 = OUTMOD_7;              // CCR1 reset/set (PWM)
    TB1CCR2 = 1500;                   // 1.5 ms pulse width (neutral position)
    TB1CTL = TBSSEL__SMCLK | MC__UP | TBCLR; // SMCLK, up mode, clear TAR

    P2DIR |= BIT1;                   // Set P2.1 as output
    P2SEL0 |= BIT1;                  // Select TB1.2 function
    P2SEL1 &= ~BIT1;
}


void mainValve_SetPosition(uint8_t pos)
{
    // 500 us - 2500 us range
    TB3CCR1 = 500 + (2000 * pos) / 256;
}