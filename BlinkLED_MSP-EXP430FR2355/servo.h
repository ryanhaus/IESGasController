#ifndef SERVO_H
#define SERVO_H

#include <stdint.h>

void servo_init();
void servo_setPosition(uint8_t pos);

#endif