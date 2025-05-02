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
    // reset IFG
    P3IFG &= ~BIT0;
    __bic_SR_register_on_exit(LPM3_bits); // exit
}
