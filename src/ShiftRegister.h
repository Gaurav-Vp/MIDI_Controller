#ifndef SHIFTREGISTER_H
#define SHIFTREGISTER_H

#include <Arduino.h>

extern bool shiftRegistersInitialized; // Global flag

/////////////////////////////////////////////
// Shift registers
// For Shift Out Data
extern uint16_t pin_state; // Initial state of the pins

// For Shift In Data
extern uint32_t prevCombinedValue; // 24-bit to store previous button states
extern uint32_t combinedValue;     // 24-bit to store current button states

void initShiftRegisters();
void set_pin(int pin, bool set_reset);
void ShiftInData();
void shiftOutData();
void updateShiftRegister(uint8_t ledState);

#endif // SHIFTREGISTER_H