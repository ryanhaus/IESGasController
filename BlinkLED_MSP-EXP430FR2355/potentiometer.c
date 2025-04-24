#include "potentiometer.h"
#include "adc.h"
#include <msp430fr2355.h>

void potent_Init()
{
    adc_Init();

    // Configure 1.5 to be ADC pin (A5)
    P1SEL0 |= BIT5;
    P1SEL1 |= BIT5;
}

uint16_t potent_Read()
{
    ADC_SOURCE = ADC_POTENTIOMETER;
    ADCMCTL0 &= ~ADCINCH;
    ADCMCTL0 |= ADCINCH_5;                                   // A5 ADC input select; Vref=AVCC

    adc_StartRead();

    return ADC_RESULT_POTENTIOMETER;
}
