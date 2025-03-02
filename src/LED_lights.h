#ifndef LED_LIGHTS_H
#define LED_LIGHTS_H

#include <Arduino.h>
#include "ShiftRegister.h"

extern int patternMode;

void initMicrophone_LEDlights();
int getFilteredMicValue();
void updateLEDLevel();
void persistencePattern();
void breathingEffect();
void vuMeter();
void knightRiderEffect();
void randomSparkles();
void waveEffect();
void runLEDEffects();

#endif // LED_LIGHTS_H