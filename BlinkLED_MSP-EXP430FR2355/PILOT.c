#include "msp430fr2355.h"
#include <driverlib.h>

void ConfigurePILOT() {

    //Set P5 to output

    P5OUT &= ~BIT4;

    P5DIR |= BIT4;
    P5SEL0 &= BIT4;
    P5SEL1 &= BIT4;
    
}

void SetPILOT(bool state) {
// state = true : Turn IGNITER LED on
// state = false : Turn IGNITE LED off

    (state == true) ? (P5OUT |= BIT4) : (P5OUT &= ~BIT4);

}

