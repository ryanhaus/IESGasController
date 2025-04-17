#include "igniter_led.h"

void igniter_Init() {

    //Set P5 to output

    P5OUT &= ~BIT0;

    P5DIR |= BIT0;
    P5SEL0 &= BIT0;
    P5SEL1 &= BIT0;
    
}

void  igniter_Control(bool state) {
// state = true : Turn IGNITER LED on
// state = false : Turn IGNITE LED off

    (state == true) ? (P5OUT |= BIT0) : (P5OUT &= ~BIT0);

}

