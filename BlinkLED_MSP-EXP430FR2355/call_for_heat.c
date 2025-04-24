#include "call_for_heat.h"
#include <msp430fr2355.h>

void callForHeat_Init()
{
    // pin 3.0 input w/ pulldown
    P3DIR &= ~BIT0;
    P3REN |= BIT0;
    P3OUT &= ~BIT0;

    // rising edge interrupt
    P3IE |= BIT0;
    P3IES |= BIT0;
    P3IFG &= ~BIT0;
}

bool callForHeat_Detect()
{
    return (P4IN & BIT0) > 0;
}

#pragma vector=PORT3_VECTOR
__interrupt void port3_ISR()
{
    printf("Port 3 interrupt");
    P3IFG &= ~BIT0;
}