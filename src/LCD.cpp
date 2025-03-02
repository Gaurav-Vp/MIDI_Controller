#include "LCD.h"

bool LCD_Initialized = false;

void lcdCommand(unsigned char cmd)
{
    initShiftRegisters();
    lcdInit();

    set_pin(RS, LOW); // Command mode
    set_pin(D4, (cmd >> 4) & 1);
    set_pin(D5, (cmd >> 5) & 1);
    set_pin(D6, (cmd >> 6) & 1);
    set_pin(D7, (cmd >> 7) & 1);

    set_pin(EN, HIGH);
    shiftOutData();
    unsigned long startMicros = micros(); // Start timing
    while (micros() - startMicros < 1)
        ; // Non-blocking delay for 1 microsecond
    set_pin(EN, LOW);
    shiftOutData();

    startMicros = micros(); // Start timing
    while (micros() - startMicros < 200)
        ; // Non-blocking delay for 200 microseconds

    set_pin(D4, cmd & 1);
    set_pin(D5, (cmd >> 1) & 1);
    set_pin(D6, (cmd >> 2) & 1);
    set_pin(D7, (cmd >> 3) & 1);

    set_pin(EN, HIGH);
    shiftOutData();
    startMicros = micros(); // Start timing
    while (micros() - startMicros < 1)
        ; // Non-blocking delay for 1 microsecond
    set_pin(EN, LOW);
    shiftOutData();

    unsigned long startMillis = millis(); // Start timing
    while (millis() - startMillis < 2)
        ; // Non-blocking delay for 2 milliseconds
}

void lcdData(unsigned char data)
{
    initShiftRegisters();
    lcdInit();

    set_pin(RS, HIGH); // Data mode
    set_pin(D4, (data >> 4) & 1);
    set_pin(D5, (data >> 5) & 1);
    set_pin(D6, (data >> 6) & 1);
    set_pin(D7, (data >> 7) & 1);

    set_pin(EN, HIGH);
    shiftOutData();
    unsigned long startMicros = micros(); // Start timing
    while (micros() - startMicros < 1)
        ; // Non-blocking delay for 1 microsecond
    set_pin(EN, LOW);
    shiftOutData();

    startMicros = micros(); // Start timing
    while (micros() - startMicros < 200)
        ; // Non-blocking delay for 200 microseconds

    set_pin(D4, data & 1);
    set_pin(D5, (data >> 1) & 1);
    set_pin(D6, (data >> 2) & 1);
    set_pin(D7, (data >> 3) & 1);

    set_pin(EN, HIGH);
    shiftOutData();
    startMicros = micros(); // Start timing
    while (micros() - startMicros < 1)
        ; // Non-blocking delay for 1 microsecond
    set_pin(EN, LOW);
    shiftOutData();

    unsigned long startMillis = millis(); // Start timing
    while (millis() - startMillis < 2)
        ; // Non-blocking delay for 2 milliseconds
}

void lcdPrint(const char *str)
{
    while (*str)
    {
        lcdData(*str++);
    }
}

void lcdSetCursor(int row, int col)
{
    int row_offsets[] = {0x00, 0x40};            // DDRAM addresses for rows
    lcdCommand(0x80 | (row_offsets[row] + col)); // Set DDRAM address command
}

void lcdClear()
{
    lcdCommand(0x01); // Clear display command
    delay(2);         // Delay to allow command execution
}

void lcdScrollInFromRight(const char *str, int row)
{
    int len = strlen(str);
    for (int pos = LCD_WIDTH; pos >= LCD_WIDTH - len; pos--)
    {
        // lcdClear();
        lcdSetCursor(row, max(0, pos));
        lcdPrint(str);
        delay(200);
    }
}

void lcdPrintRight(const char *str, int row)
{
    int len = strlen(str);                  // Get the string length
    int startCol = max(0, LCD_WIDTH - len); // Calculate starting column

    lcdSetCursor(row, startCol); // Move cursor to right-aligned position
    lcdPrint(str);               // Print text
}

void lcdInit()
{
    if (LCD_Initialized)
        return;             // Prevent re-initialization
    LCD_Initialized = true; // Mark initialization as done

    initShiftRegisters();
    delay(2);
    // Initialization sequence for 4-bit mode
    lcdCommand(0x33); // Initialize in 8-bit mode
    lcdCommand(0x32); // Set to 4-bit mode
    lcdCommand(0x28); // 2 lines, 5x7 matrix
    lcdCommand(0x0C); // Display ON, cursor OFF
    lcdCommand(0x06); // Entry mode set: increment cursor
    lcdCommand(0x01); // Clear display
    delay(2);
    LCDintro();
}

void LCDintro()
{
    // Print on the first line
    lcdPrint("Hello, TALIB ALI");
    // Set cursor to the second line, first column
    lcdSetCursor(1, 0);
    // Print on the second line
    lcdPrint("Welcome Back!");
    delay(2000);
}
