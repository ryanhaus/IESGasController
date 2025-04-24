#include "thermocouple.h"
#include <msp430fr2355.h>
#include "adc.h"

const int FLAME_THRESHOLD = 250;

void flame_Init()
{
    adc_Init();

    // Configure 1.3 to be ADC pin (A3)
    P1SEL0 |= BIT3;
    P1SEL1 |= BIT3;
}

bool flame_Detect()
{
    ADC_SOURCE = ADC_THERMOCOUPLE;
    ADCMCTL0 &= ~ADCINCH;
    ADCMCTL0 |= ADCINCH_3;                                   // A3 ADC input select; Vref=AVCC

    adc_StartRead();

    return ADC_RESULT_THERMOCOUPLE > FLAME_THRESHOLD;
}
