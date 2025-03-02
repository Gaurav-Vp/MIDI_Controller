#include "LED_lights.h"

/////////////////////////////////////////////
// LED panel
#define MicrophonePin A3
#define numSamples 10 // Number of samples for smoothing
#define interval 2    // Speed of LED switching for POV effect

int patternMode = 0; // Current LED pattern mode

/////////////////////////////////////////////
// LED panel
int sampleBuffer[numSamples]; // Store recent mic values
int sampleIndex = 0;          // Index for circular buffer
long sampleSum = 0;           // Sum of samples for moving average
int baseline = 0;             // Baseline noise level (set during calibration)
uint8_t currentLED = 0;       // Tracks which LED is currently "lit"
uint8_t ledLevel = 0;         // Number of LEDs to light up (based on sound)
unsigned long previousMillis = 0;

/////////////////////////////////////////////
// LED panel
// Function to initialize baseline noise level
void initMicrophone_LEDlights()
{
    initShiftRegisters();
    pinMode(MicrophonePin, INPUT);

    long total = 0;
    for (int i = 0; i < 100; i++)
    { // Collect 100 samples for baseline
        total += analogRead(MicrophonePin);
        delay(5); // Small delay to avoid excessive reads
    }
    baseline = total / 100; // Set baseline to average noise level
}

// Function to get a smoothed microphone value
int getFilteredMicValue()
{
    int rawValue = analogRead(MicrophonePin); // Read raw mic value

    // Remove DC offset by subtracting baseline
    int centeredValue = rawValue - baseline;

    // Apply noise gate (ignore small fluctuations)
    if (abs(centeredValue) < 2)
        centeredValue = 0;

    // Moving average filter (smooths out fluctuations)
    sampleSum -= sampleBuffer[sampleIndex];    // Remove oldest sample
    sampleBuffer[sampleIndex] = centeredValue; // Add new sample
    sampleSum += centeredValue;                // Update sum

    sampleIndex = (sampleIndex + 1) % numSamples; // Circular buffer
    return sampleSum / numSamples;                // Return smoothed value
}
// Function to map microphone input to LED levels

void updateLEDLevel()
{
    int micValue = getFilteredMicValue();            // Read & filter microphone input
    int amplifiedMicValue = micValue * 8;            // Increase sensitivity
    ledLevel = map(amplifiedMicValue, 0, 200, 0, 5); // Convert to LED range (0-5)
    if (ledLevel < 0)
        ledLevel = 0;
    if (ledLevel > 5)
        ledLevel = 5;
}
// Function to create a POV effect for LEDs

void persistencePattern()
{
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval)
    {
        previousMillis = currentMillis;

        // Light up one LED at a time, but cycle through them quickly
        uint8_t ledState = (1 << currentLED);
        updateShiftRegister(ledState);

        // Move to the next LED in the range defined by ledLevel
        currentLED++;
        if (currentLED > ledLevel)
        {
            currentLED = 0; // Reset LED cycle
        }
    }
}

void breathingEffect()
{
    static uint8_t brightness = 0;
    static bool increasing = true;

    if (ledLevel > 0)
    {
        if (increasing)
        {
            brightness += 5;
            if (brightness >= 255)
                increasing = false;
        }
        else
        {
            brightness -= 5;
            if (brightness <= 0)
                increasing = true;
        }

        uint8_t ledState = (1 << ledLevel); // Light up the current level of LEDs
        updateShiftRegister(ledState);
        analogWrite(ledState, brightness);
    }
}

void vuMeter()
{
    uint8_t ledState = (1 << ledLevel) - 1; // Light up all LEDs up to ledLevel
    updateShiftRegister(ledState);
}

void knightRiderEffect()
{
    static int direction = 1;

    uint8_t ledState = (1 << currentLED);
    updateShiftRegister(ledState);

    if (currentLED == 0)
        direction = 1;
    else if (currentLED == ledLevel)
        direction = -1;

    currentLED += direction;
}

void randomSparkles()
{
    uint8_t ledState = random(0, (1 << (ledLevel + 1)) - 1); // Random pattern within range
    updateShiftRegister(ledState);
}

void waveEffect()
{
    static uint8_t waveIndex = 0;
    uint8_t ledState = (1 << waveIndex);
    updateShiftRegister(ledState);

    waveIndex = (waveIndex + 1) % ledLevel;
}

void runLEDEffects()
{
    updateLEDLevel(); // Adjust LED intensity based on sound

    switch (patternMode)
    {
    case 0:
        persistencePattern();
        break;
    case 1:
        breathingEffect();
        break;
    case 2:
        vuMeter();
        break;
    case 3:
        knightRiderEffect();
        break;
    case 4:
        randomSparkles();
        break;
    case 5:
        waveEffect();
        break;
    }
}