#include "MiDiLib.h"

// MIDI
byte midiCh = 2; // MIDI channel to be used
byte note = 36;  // Lowest note to be used
byte cc = 11;    // Lowest MIDI CC to be used

void noteOn(byte channel, byte pitch, byte velocity)
{
    midiEventPacket_t noteOn = {0x09, (uint8_t)(0x90 | channel), pitch, velocity};
    MidiUSB.sendMIDI(noteOn);
}
void noteOff(byte channel, byte pitch, byte velocity)
{
    midiEventPacket_t noteOff = {0x08, (uint8_t)(0x80 | channel), pitch, velocity};
    MidiUSB.sendMIDI(noteOff);
}
void controlChange(byte channel, byte control, byte value)
{
    midiEventPacket_t event = {0x0B, (uint8_t)(0xB0 | channel), control, value};
    MidiUSB.sendMIDI(event);
}