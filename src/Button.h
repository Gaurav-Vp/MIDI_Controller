#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>
#include "ShiftRegister.h"
#include "MENU_.h"
#include "config.h"

#ifdef ATMEGA32U4
#include "MiDiLib.h"
#endif

/////////////////////////////////////////////
// Rotary encoder
#define CLOCKWISE true // Define rotation directions
#define COUNTER_CLOCKWISE false

/////////////////////////////////////////////
// LCD
extern bool backlightPState; // Previous backlight state
extern bool backlightCState; // Backlight state

void init_BTN_ENC_LCDstatus();
void buttons();
void HandleEncoder();
void LCD_status();
void iterate_BTN_ENC_LCD();

#endif // BUTTONS_H