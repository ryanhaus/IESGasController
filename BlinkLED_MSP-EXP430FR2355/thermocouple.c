#include "thermocouple.h"
#include <msp430fr2355.h>
#include "adc.h"
#include "sac.h"

const int FLAME_THRESHOLD = 68;

void flame_Init()
{
    adc_Init();

    // op amp
    /*// 1. Enable and configure SAC0 for non-inverting PGA at max gain (33×)
    SAC0OA = SACEN          // turn on the SAC module
        | OAEN           // power up the op amp
        | PMUXEN         // enable positive-input multiplexer
        | NMUXEN         // enable negative-input multiplexer
        | (0b00 << 0)   // PSEL = 00 → external OAx+ pin
        | (0b01 << 4);  // NSEL = 01 → PGA feedback network

    SAC0PGA = (0b00 << 0)  // MSEL = 10 → non-inverting PGA mode
            | (0b111 << 4); // GAIN = 111 → 33× gain :contentReference[oaicite:0]{index=0}
*/
    // 2. Map P1.3 into the SAC input path  
    //    (on FR2355, OAx+ pad is on P1.3 itself when SACEN + PMUXEN)
    /*P1SEL1 |= BIT3;  // P1.3 tertiary function
    P1SEL0 |=  BIT3;  // → route P1.3 to OAx+ :contentReference[oaicite:1]{index=1}&#8203;:contentReference[oaicite:2]{index=2}
    P1DIR  &= ~BIT3;  // input*/ 
    P1SEL1 |= BIT2;  // P1.2 tertiary function
    P1SEL0 |=  BIT2;  // → route P1.2 to OAx- :contentReference[oaicite:1]{index=1}&#8203;:contentReference[oaicite:2]{index=2}
    P1DIR  &= ~BIT2;  // input

    // 3. Route the SAC output (OAxO) to P1.1:
    P1SEL1 |= BIT1;  // P1.1 tertiary function
    P1SEL0 |= BIT1;  // → route OAxO to P1.1 :contentReference[oaicite:3]{index=3}&#8203;:contentReference[oaicite:4]{index=4}
    P1DIR  |=  BIT1;  // output
    SAC_DAC_selectRefVoltage(SAC0_BASE, SAC_DAC_PRIMARY_REFERENCE);
    SAC_DAC_selectLoad(SAC0_BASE, SAC_DAC_LOAD_DACDAT_WRITTEN);
    SAC_DAC_setData(SAC0_BASE, 0);
    SAC_DAC_enable(SAC0_BASE);
    SAC_OA_init(SAC0_BASE, SAC_OA_POSITIVE_INPUT_SOURCE_DAC, SAC_OA_NEGATIVE_INPUT_SOURCE_PGA);
    SAC_PGA_setMode(SAC0_BASE, SAC_PGA_MODE_INVERTING);
    SAC_PGA_setGain(SAC0_BASE, SAC_PGA_GAIN_BIT0 | SAC_PGA_GAIN_BIT1 | SAC_PGA_GAIN_BIT2);
    SAC_OA_enable(SAC0_BASE);
    SAC_enable(SAC0_BASE);
}

bool flame_Detect()
{
    ADC_SOURCE = ADC_THERMOCOUPLE;
    ADCMCTL0 &= ~ADCINCH;
    ADCMCTL0 |= ADCINCH_1;                                   // A1 ADC input select; Vref=AVCC

    adc_StartRead();

    return ADC_RESULT_THERMOCOUPLE > FLAME_THRESHOLD;
}
