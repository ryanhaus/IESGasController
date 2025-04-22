#include "thermistor.h"
#include <msp430fr2355.h>
#include "adc.h"

void therm_Init()
{
    adc_Init();

    // Configure 1.6 to be ADC pin (A6)
    P1SEL0 |= BIT6;
    P1SEL1 |= BIT6;
}

uint16_t therm_Read()
{
    ADC_SOURCE = ADC_THERMISTOR;
    ADCMCTL0 &= ~ADCINCH;
    ADCMCTL0 |= ADCINCH_6;                                   // A6 ADC input select; Vref=AVCC

    adc_StartRead();

    return ADC_RESULT_THERMISTOR;
}