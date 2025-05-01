#include "rgb_led.h"


void rgbLed_Init() {
    P6DIR   |= BIT0 | BIT1 | BIT2;      // P6.0 to P6.2 output
    P6SEL0  |= BIT0 | BIT1 | BIT2;      
    P6SEL1  &= ~(BIT0 | BIT1 | BIT2);

    TB3CCR0 = 1024-1;                   // PWM Period
    TB3CCTL1 = OUTMOD_3;                // CCR1 reset/set
    TB3CCR1 = 750;                      // CCR1 PWM duty cycle
    TB3CCTL2 = OUTMOD_3;                // CCR2 reset/set
    TB3CCR2 = 250;                      // CCR2 PWM duty cycle
    TB3CCTL3 = OUTMOD_3;                // CCR3 reset/set
    TB3CCR3 = 500;                      // CCR3 PWM duty cycle

    TB3CTL = TBSSEL__SMCLK | MC__UP | TBCLR;  // SMCLK, up mode, clear TBR
}


/* setRGBLED (Red, Green, Blue) sets the RGB LED to a specific color.
    -
*/
void rgbLed_SetPWM(char Red, char Green, char Blue) 
{
    TB3CCR3 = Blue << 2;
    TB3CCR2 = Green << 2;
    TB3CCR1 = Red << 2;
}

