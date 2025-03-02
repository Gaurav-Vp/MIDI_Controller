/////////////////////////////////////////////
// BOARD SELECTION
// Define the microcontroller or debugging mode
// Enter "ATMEGA32U4 1" for ATmega32U4 or "DEBUG 1" for debugging
// inside config.h file

/////////////////////////////////////////////
// LIBRARIES
#include "src/Button.h"
#include "src/LED_lights.h"
#include "src/LCD.h"
#include "src/Pot.h"

/////////////////////////////////////////////
// SETUP
void setup()
{
    init_BTN_ENC_LCDstatus();
    initPots();
    initMicrophone_LEDlights(); // Run calibration for LED panel

    // Baud Rate
    // Use this for ATmega328 boards (Uno, Mega, Nano...)
    // 31250 for MIDI class compliant | 115200 for Hairless MIDI
    Serial.begin(115200); //*
}

/////////////////////////////////////////////
// LOOP
void loop()
{
    iterate_BTN_ENC_LCD();
    HandleLCD();
    potentiometers();

    runLEDEffects(); // Run LED panel effects
}