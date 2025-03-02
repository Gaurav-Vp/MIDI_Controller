#include "ShiftRegister.h"

/////////////////////////////////////////////
// Shift registers
// BTN: Buttons, LCD: LCD Display, UNI: Universal
#define latchPin_BTN_LCD 8 // PL pin 5
#define latchPin_LEDlights 3
#define clockPin_UNI 9         // CP pin 4
#define clockEnablePin_BTN 10  // CE pin 3
#define SERdataIn_BTN 11       // Q7 pin 2
#define SERdataOut_LCD 12      // SER pin
#define SERdataOut_LEDlights 2 // SER pin
#define BYTE_count_LCD 1       // Number of bytes for shifting (8 bits per byte)
bool shiftRegistersInitialized = false;

uint16_t pin_state = 0; // Initial state of the pins

// For Shift In Data
uint32_t prevCombinedValue = 0xFFFFFF; // 24-bit to store previous button states
uint32_t combinedValue = 0xFFFFFF;     // 24-bit to store current button states

void initShiftRegisters()
{
    if (shiftRegistersInitialized)
        return;                       // Prevent re-initialization
    shiftRegistersInitialized = true; // Mark initialization as done

    //////////////////////////////////////////////////////////////////////////////////////////
    // Shift registers
    // Setup 74HC595 connections
    pinMode(latchPin_LEDlights, OUTPUT);   // RCLK pin 12   // LED panel
    pinMode(SERdataOut_LEDlights, OUTPUT); // SER pin       // LED panel
    // BUTTONS
    // clockPin_UNI is common for both the ICs          // SER pin
    // Setup 74HC165 connections
    // and also for 74HC595
    // clockPin_UNI and latchPin_BTN_LCD are common for both the ICs
    //                                    74HC165 and 74HC595
    pinMode(latchPin_BTN_LCD, OUTPUT);   // PL pin 5 and RCLK pin 12
    pinMode(clockEnablePin_BTN, OUTPUT); // CE pin 3
    pinMode(clockPin_UNI, OUTPUT);       // CP pin 4 and SRCLK pin 11
    pinMode(SERdataIn_BTN, INPUT);       // Q7 pin 2
    pinMode(SERdataOut_LCD, OUTPUT);     // SER pin
}

/////////////////////////////////////////////
// Shift register function for LCD
void set_pin(int pin, bool set_reset)
{
    if (pin < 1 || pin > BYTE_count_LCD * 8)
    {
        return;
    }
    if (set_reset == HIGH)
    {
        pin_state |= (1 << (pin - 1));
    }
    else if (set_reset == LOW)
    {
        pin_state &= ~(1 << (pin - 1));
    }
    return;
}

void shiftOutData()
{
    // Shift the bits out
    digitalWrite(latchPin_BTN_LCD, LOW);
    for (int i = 0; i < BYTE_count_LCD; ++i)
    {
        shiftOut(SERdataOut_LCD, clockPin_UNI, MSBFIRST, (pin_state >> (8 * i)) & 0xFF);
    }
    digitalWrite(latchPin_BTN_LCD, HIGH);
}

// Function to send data to shift register
void updateShiftRegister(uint8_t ledState)
{
    digitalWrite(latchPin_LEDlights, LOW);
    shiftOut(SERdataOut_LEDlights, clockPin_UNI, MSBFIRST, ledState);
    digitalWrite(latchPin_LEDlights, HIGH);
}

void ShiftInData()
{
    // Write pulse to latchPin_BTN_LCD pin
    digitalWrite(latchPin_BTN_LCD, LOW);
    delayMicroseconds(5);
    digitalWrite(latchPin_BTN_LCD, HIGH);
    delayMicroseconds(5);

    // Get data from 3 shift registers (24 bits)
    digitalWrite(clockPin_UNI, HIGH);
    digitalWrite(clockEnablePin_BTN, LOW);

    byte incoming3 = shiftIn(SERdataIn_BTN, clockPin_UNI, LSBFIRST); // Third shift register
    byte incoming2 = shiftIn(SERdataIn_BTN, clockPin_UNI, LSBFIRST); // Second shift register
    byte incoming1 = shiftIn(SERdataIn_BTN, clockPin_UNI, LSBFIRST); // First shift register

    digitalWrite(clockEnablePin_BTN, HIGH);

    // Combine the three bytes into a 24-bit value
    combinedValue = ((uint32_t)incoming1 << 16) | ((uint32_t)incoming2 << 8) | incoming3;
}
