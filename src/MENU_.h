#ifndef MENU_H
#define MENU_H

#include "LCD.h"
#include "Button.h"
#include "LED_lights.h"
#include <Arduino.h>

void initializeMenu();
void updateMenuDisplay();
void handleMenuRotation(uint8_t rotationDirection);
void handleMenuPress(bool selectPressed);
void updateAboutMenuDisplay();
void HandleLCD();

#endif // MENU_H