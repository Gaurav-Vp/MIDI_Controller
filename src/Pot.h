#ifndef POT_H
#define POT_H

#include <Arduino.h>
#include "ShiftRegister.h"
#include "config.h"

#ifdef ATMEGA32U4
#include "MiDiLib.h"
#endif

extern int potVar; // Signal variation

void initPots();
void potentiometers();

#endif // POT_H