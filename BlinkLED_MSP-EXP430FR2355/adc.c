#include "adc.h"
#include <msp430fr2355.h>

void adc_Init()
{
    ADCCTL0 |= ADCSHT_2 | ADCON;                             // ADCON, S&H=16 ADC clks
    ADCCTL1 |= ADCSHP;                                       // ADCCLK = MODOSC; sampling timer
    ADCCTL2 &= ~ADCRES;                                      // clear ADCRES in ADCCTL
    ADCCTL2 |= ADCRES_2;                                     // 12-bit conversion results
    ADCIE |= ADCIE0;                                         // Enable ADC conv complete interrupt
}

void adc_StartRead()
{
    ADCCTL0 |= ADCENC | ADCSC;                           // Sampling and conversion start
    __bis_SR_register(LPM0_bits | GIE);                  // LPM0, ADC_ISR will force exit

    __delay_cycles(20);
}

// declared in adc.h
volatile int ADC_RESULT_THERMISTOR = 0;
volatile int ADC_RESULT_THERMOCOUPLE = 0;
volatile int ADC_RESULT_POTENTIOMETER = 0;
volatile adc_source_t ADC_SOURCE = ADC_NONE;

// updates the proper result variable based on the set source and ADC result
void handle_adc_value_update()
{
    switch (ADC_SOURCE)
    {
        case ADC_NONE:
            break;

        case ADC_THERMISTOR:
            ADC_RESULT_THERMISTOR = ADCMEM0;
            break;

        case ADC_THERMOCOUPLE:
            ADC_RESULT_THERMOCOUPLE = ADCMEM0;
            break;

        case ADC_POTENTIOMETER:
            ADC_RESULT_POTENTIOMETER = ADCMEM0;
            break;
    }

    ADC_SOURCE = ADC_NONE;
}

// ADC interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(ADC_VECTOR))) ADC_ISR (void)
#else
#error Compiler not supported!
#endif
{
    switch(__even_in_range(ADCIV,ADCIV_ADCIFG))
    {
        case ADCIV_NONE:
            break;
        case ADCIV_ADCOVIFG:
            break;
        case ADCIV_ADCTOVIFG:
            break;
        case ADCIV_ADCHIIFG:
            break;
        case ADCIV_ADCLOIFG:
            break;
        case ADCIV_ADCINIFG:
            break;
        case ADCIV_ADCIFG:
            handle_adc_value_update();
            ADCCTL0 &= ~(ADCENC | ADCSC);
            ADC_SOURCE = ADC_NONE;
            __bic_SR_register_on_exit(LPM0_bits);            // Clear CPUOFF bit from LPM0
            break;
        default:
            break;
    }
}
