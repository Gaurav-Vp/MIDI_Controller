#ifndef MIDI_H
#define MIDI_H

#include "MIDIUSB.h"
#include <Arduino.h>

// MIDI
extern byte midiCh; // MIDI channel to be used
extern byte note;   // Lowest note to be used
extern byte cc;     // Lowest MIDI CC to be used

void noteOn(byte channel, byte pitch, byte velocity);
void noteOff(byte channel, byte pitch, byte velocity);
void controlChange(byte channel, byte control, byte value);

#endif // MIDI_H