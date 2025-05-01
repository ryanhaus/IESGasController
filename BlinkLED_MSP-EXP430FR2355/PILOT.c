#include "pilot.h"
#include <msp430fr2355.h>

void pilot_Init() {

    //Set P5.4 to output

    P5OUT &= ~BIT4;

    P5DIR |= BIT4;
    P5SEL0 &= BIT4;
    P5SEL1 &= BIT4;
    
}

void pilot_Control(bool state) {
// state = true : Turn Solenoid on
// state = false : Turn Solenoid off

    (state == true) ? (P5OUT |= BIT4) : (P5OUT &= ~BIT4);

}

bool pilot_Status() {
    
    if ( (P5OUT &= BIT4) == BIT4) {
        return true;
    }

    else {
        return false;
    }

}
