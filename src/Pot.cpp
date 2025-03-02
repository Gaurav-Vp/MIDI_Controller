#include "Pot.h"

/////////////////////////////////////////////
// Potentiometers
#define S0_add 5
#define S1_add 6
#define S2_add 7
#define MUXdataPin1 A5
#define MUXdataPin2 A4
#define N_POTS 16            // Number of potentiometers
const int TIMEOUT = 300;     // Time period during which the potentiometer will be read
const int varThreshold = 16; // Threshold for signal variation

/////////////////////////////////////////////
// Potentiometers
int potCState[N_POTS] = {0};       // Current analog states
int potPState[N_POTS] = {0};       // Previous analog states
int midiCState[N_POTS] = {0};      // Current MIDI values
int midiPState[N_POTS] = {0};      // Previous MIDI values
unsigned long PTime[N_POTS] = {0}; // Last active time for each pot
unsigned long timer[N_POTS] = {0}; // Elapsed time since last active

int potVar = 0;        // Signal variation
bool potMoving = true; // Whether the pot is moving

void initPots()
{
    //////////////////////////////////////////////////////////////////////////////////////////
    // POTENTIOMETERS
    // Setup 74HC4051 connections
    // both multiplexers are connected to the same pins
    // i.e. S0, S1 and S2 are common for both the multiplexers
    // and enable pins are connected to GND by default
    pinMode(S0_add, OUTPUT);
    pinMode(S1_add, OUTPUT);
    pinMode(S2_add, OUTPUT);
    pinMode(MUXdataPin1, INPUT);
    pinMode(MUXdataPin2, INPUT);
}

/////////////////////////////////////////////
// POTENTIOMETERS
void potentiometers()
{
    /* This function reads potentiometer values using two 74HC4051 multiplexers,
       maps the values to MIDI ranges, and sends MIDI control changes if any
       potentiometer moves beyond a threshold.
    */

    for (int i = 0; i < (N_POTS / 2); i++)
    {
        // Set multiplexer addresses for selecting channels on both multiplexers
        digitalWrite(S2_add, bitRead(i, 2));
        digitalWrite(S1_add, bitRead(i, 1));
        digitalWrite(S0_add, bitRead(i, 0));

        // Read potentiometer values from both multiplexers
        int pot1Value = analogRead(MUXdataPin1);
        int pot2Value = analogRead(MUXdataPin2);

        // Store current potentiometer states
        potCState[i] = pot1Value;
        potCState[i + (N_POTS / 2)] = pot2Value;

        // Map potentiometer readings to MIDI values (0 to 127)
        midiCState[i] = map(pot1Value, 0, 1023, 0, 127);
        midiCState[i + (N_POTS / 2)] = map(pot2Value, 0, 1023, 0, 127);

        // Check if the current pot reading has changed significantly from the previous state
        potVar = abs(pot1Value - potPState[i]);
        if (potVar > varThreshold)
        {
            PTime[i] = millis(); // Reset the timer for MUX1 potentiometers
        }

        potVar = abs(pot2Value - potPState[i + (N_POTS / 2)]);
        if (potVar > varThreshold)
        {
            PTime[i + (N_POTS / 2)] = millis(); // Reset the timer for MUX2 potentiometers
        }

        // Calculate elapsed time and determine if potentiometers are still moving
        timer[i] = millis() - PTime[i];
        timer[i + (N_POTS / 2)] = millis() - PTime[i + (N_POTS / 2)];

        potMoving = (timer[i] < TIMEOUT) || (timer[i + (N_POTS / 2)] < TIMEOUT);

        // Send MIDI control changes for MUX1 and MUX2 if potentiometers are moving
        if (potMoving)
        {
            if (midiPState[i] != midiCState[i])
            {
                // MIDI FUNCTIONS (for ATmega32U4)
#ifdef ATMEGA32U4
                controlChange(midiCh, cc + i, midiCState[i]);
                MidiUSB.flush();
#elif DEBUG
                Serial.print("Sent MIDI CC for Mux1 Channel ");
                Serial.print(i);
                Serial.print(" Value: ");
                Serial.println(midiCState[i]);
#endif
                potPState[i] = pot1Value;
                midiPState[i] = midiCState[i];
            }

            if (midiPState[i + (N_POTS / 2)] != midiCState[i + (N_POTS / 2)])
            {
#ifdef ATMEGA32U4
                controlChange(midiCh, cc + i + (N_POTS / 2), midiCState[i + (N_POTS / 2)]);
                MidiUSB.flush();
#elif DEBUG
                Serial.print("Sent MIDI CC for Mux2 Channel ");
                Serial.print(i);
                Serial.print(" Value: ");
                Serial.println(midiCState[i + (N_POTS / 2)]);
#endif
                potPState[i + (N_POTS / 2)] = pot2Value;
                midiPState[i + (N_POTS / 2)] = midiCState[i + (N_POTS / 2)];
            }
        }
    }
}
