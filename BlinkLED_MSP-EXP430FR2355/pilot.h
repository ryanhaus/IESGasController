#ifndef PILOT_H
#define PILOT_H

#include <stdbool.h>

void pilot_Init();
void pilot_Control(bool state);
bool pilot_Status();

#endif
