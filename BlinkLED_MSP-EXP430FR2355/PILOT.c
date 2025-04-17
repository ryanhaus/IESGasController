#include "pilot.h"

void pilot_Init() {

    //Set P5 to output

    P5OUT &= ~BIT4;

    P5DIR |= BIT4;
    P5SEL0 &= BIT4;
    P5SEL1 &= BIT4;
    
}

void pilot_Control(bool state) {
// state = true : Turn IGNITER LED on
// state = false : Turn IGNITE LED off

    (state == true) ? (P5OUT |= BIT4) : (P5OUT &= ~BIT4);

}

