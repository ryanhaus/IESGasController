#include "call_for_heat.h"
#include "intrinsics.h"
#include "pilot.h"
#include <iso646.h>
#include <msp430fr2355.h>
#include <stdio.h>

void callForHeat_Init()
{
    // pin 3.0 input w/ pulldown

    // p3.0 as input
    P3OUT &= ~BIT0;
    P3SEL0 &= ~BIT0;
    P3SEL1 &= ~BIT1;

    // pull down
    P3DIR &= ~BIT0;
    P3REN |= BIT0;


    // rising edge interrupt
    P3IE |= BIT0;
    P3IES &= ~BIT0; // interupt edge select set to 0 initially to look for low-high transistion
    P3IFG &= ~BIT0; // set interupt flag
}

bool callForHeat_Detect()
{
    // if pin 3.0 is high return true 
    return (P3IN & BIT0) > 0;
}

#pragma vector=PORT3_VECTOR
__interrupt void port3_ISR()
{
    // toggle IES to look for the start or end of  "call for heat" signal
    P3IES ^= BIT0;

    if ( (P3IES &= BIT0) == BIT0) { 

        __bis_SR_register(CPUOFF); // if IES is 0 enter LPM0

    }

    else {

        __bis_SR_register(~CPUOFF); // if IES is 1 exit LPM0

    }

    // reset IFG
    P3IFG &= ~BIT0;
}
