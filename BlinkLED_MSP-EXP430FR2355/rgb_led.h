 #ifndef RGB_LED_H
 #define RGB_LED_H

#include <msp430.h>

void rgbLed_Init();
void rgbLed_SetPWM(char Red, char Green, char Blue);

#endif
