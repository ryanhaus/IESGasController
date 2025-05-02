//***************************************************************************************
//  Title
//
//  Description;
//  Authours: 
//  Rowan University
//  IES S1
//  Date:
//  Built with Code Composer Studio ______
//***************************************************************************************

#include "igniter_led.h"
#include "intrinsics.h"
#include "msp430fr2355.h"
#include "adc.h"
#include "call_for_heat.h"
#include "main_valve.h"
#include "pilot.h"
#include "potentiometer.h"
#include "rgb_led.h"
#include "thermistor.h"
#include "thermocouple.h"


int main(void) {
    // red LED -> pilot light check failed
    // green led -> pilot light check passed

    WDTCTL = WDTPW | WDTHOLD;                 // Stop WDT

    adc_Init();
    callForHeat_Init();
    mainValve_Init();
    pilot_Init();
    igniter_Init();
    potent_Init();
    rgbLed_Init();
    therm_Init();
    flame_Init();

    // arbitrary values as of now

    const char valve_OPEN = 255;  // Set to ocnst for tuning               // Make valve_SP a output of a function for PID implementation
    const char valve_CLOSE = 0; // Set to const for tuning

    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings

    PM5CTL0 &= ~LOCKLPM5; // disable high-impedance mode

    while(1)
    {
        pilot_Control(false);
        igniter_Control(false);
        mainValve_SetPosition(valve_CLOSE);
        rgbLed_SetPWM(0, 0, 0);

        if (callForHeat_Detect()) {

            pilot_Control(true); // enable pilot light
            igniter_Control(true); // enable igniter (the led)

            __delay_cycles(250000);

            while (!flame_Detect() && callForHeat_Detect()) {}

            if (flame_Detect()) {  // thermocouple check

                rgbLed_SetPWM(0, 255, 0);               // green led -> pilot light check passed

                mainValve_SetPosition(valve_OPEN);        // open pilot valve to start heating

                __delay_cycles(500000);

                while (therm_Read() <= potent_Read()) {    // check if heat is past set point

                    pilot_Control(false);               // close valve and turn off pilot light
                    mainValve_SetPosition(valve_OPEN); // open valve
                    
                    igniter_Control(false);             // disable igniter

                    rgbLed_SetPWM(0, 0, 255);             // blue led -> temp reached

                    //low power mode should be handled by interupt
                    //__bis_SR_register(CPUOFF);
                }

            }
            
            else { // thermocouple check failed

                rgbLed_SetPWM(255, 0, 0);               // red led -> pilot light check failed

                pilot_Control(false);                   // close pilot light to stop gas from leaking

            }
        }
        else {
            // low power mode should be handled by interupt either way
            //__bis_SR_register(LPM3_bits);
        }

        __delay_cycles(250000);

    }

}
