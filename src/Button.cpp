#include "Button.h"

/////////////////////////////////////////////
// Rotary encoder
#define ENCODER_DT 20  // Data pin
#define ENCODER_CLK 21 // Clock pin
#define ENCODER_SW 22  // Switch pin
int lastEncoderState = HIGH;
int lastButtonState = HIGH;
unsigned long lastDebounceTimeOfEncoder = 0;

/////////////////////////////////////////////
// LCD
bool backlightPState = 0; // Previous backlight state
bool backlightCState = 0; // Backlight state

/////////////////////////////////////////////
// Buttons
#define DEBOUNCE_DELAY_BTN_ENCBTN 50 // 50 ms debounce delay
#define ttlBTN 20                    // Total number of buttons
// Buttons are connecter to pin 0 to 19
// Arrays to store debounce states
uint32_t lastDebounceTime[ttlBTN] = {0}; // Tracks the last time each button state changed
bool lastStableState[ttlBTN] = {0};      // Stores the last stable state of each button

/////////////////////////////////////////////
// LCD
#define LCDstatePin 23 // To read backlight state on 74HC165

void init_BTN_ENC_LCDstatus()
{
    initShiftRegisters();
}

void buttons()
{
    // Iterate through each bit (button)
    for (int i = 0; i < ttlBTN; i++)
    {
        bool currentState = bitRead(combinedValue, i); // Current state of the button
        bool previousStableState = lastStableState[i]; // Last stable state
        uint32_t currentTime = millis();               // Get current time

        // Check if the button state has changed
        if (currentState != previousStableState)
        {
            // If debounce time has passed, consider it a valid state change
            if (currentTime - lastDebounceTime[i] > DEBOUNCE_DELAY_BTN_ENCBTN)
            {
                lastDebounceTime[i] = currentTime; // Update last debounce time
                lastStableState[i] = currentState; // Update stable state

                // Handle button press/release events
                if (currentState == 0)
                {
#ifdef ATMEGA32U4
                    // Send MIDI note ON
                    noteOn(midiCh, note + i, 127); // channel, note, velocity
                    MidiUSB.flush();
#elif DEBUG
                    Serial.print("Button ");
                    Serial.print(i);
                    Serial.println(" pressed");
#endif
                }
                else
                {
#ifdef ATMEGA32U4
                    // Send MIDI note OFF
                    noteOff(midiCh, note + i, 0); // channel, note, velocity
                    MidiUSB.flush();
#elif DEBUG
                    Serial.print("Button ");
                    Serial.print(i);
                    Serial.println(" released");
#endif
                }
            }
        }
    }
}

void HandleEncoder()
{
    //////////////////////////////////////////////////////////////////////////////////////////
    // Handle Encoder
    bool clkState = bitRead(combinedValue, ENCODER_CLK);
    bool dtState = bitRead(combinedValue, ENCODER_DT);
    bool buttonState = bitRead(combinedValue, ENCODER_SW);
    bool ENC_BTN_Pressed_Cstate;
    bool rotationDirection;

    // Handle rotation
    if (clkState != lastEncoderState)
    {
        if (clkState == LOW)
        {
            if (dtState == HIGH)
            {
#ifdef DEBUG
                Serial.println("Encoder rotated: CLOCKWISE");
#endif
                rotationDirection = CLOCKWISE;
            }
            else
            {
#ifdef DEBUG
                Serial.println("Encoder rotated: COUNTER-CLOCKWISE");
#endif
                rotationDirection = COUNTER_CLOCKWISE;
            }
            handleMenuRotation(rotationDirection);
        }
    }
    lastEncoderState = clkState;

    // Handle button press for select/edit toggle
    if (buttonState != lastButtonState)
    {
        if (buttonState == LOW)
        {
            if (millis() - lastDebounceTimeOfEncoder > DEBOUNCE_DELAY_BTN_ENCBTN)
            {
#ifdef DEBUG
                Serial.println("Encoder button pressed");
#endif
                ENC_BTN_Pressed_Cstate = true;
                lastDebounceTimeOfEncoder = millis();
            }
            else
            {
#ifdef DEBUG
                Serial.println("Encoder button released");
#endif
                ENC_BTN_Pressed_Cstate = false;
            }
            handleMenuPress(ENC_BTN_Pressed_Cstate);
        }
        lastButtonState = buttonState;
    }
}

void LCD_status()
{
    /////////////////////////////////////////////
    // LCD
    backlightCState = bitRead(combinedValue, LCDstatePin);
    return;
}

void iterate_BTN_ENC_LCD()
{
    ShiftInData();
    buttons();
    HandleEncoder();
    LCD_status();
}
