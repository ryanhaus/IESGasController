#ifndef ADC_H
#define ADC_H

void adc_Init();
void adc_StartRead();

// different ADC result sources
typedef enum {
    ADC_NONE,
    ADC_THERMISTOR,
    ADC_THERMOCOUPLE,
    ADC_POTENTIOMETER
} adc_source_t;

// stores the most recent result of various adc sources (defined in adc.c)
extern volatile int ADC_RESULT_THERMISTOR;
extern volatile int ADC_RESULT_THERMOCOUPLE;
extern volatile int ADC_RESULT_POTENTIOMETER;
extern volatile adc_source_t ADC_SOURCE;

#endif