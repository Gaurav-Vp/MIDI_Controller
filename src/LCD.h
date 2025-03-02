#ifndef LCD_H
#define LCD_H

#include "ShiftRegister.h"

extern bool LCD_Initialized;

/////////////////////////////////////////////
// LCD Display 16x2
// Pin assignments for LCD on IC 595
#define RS 2         // Register Select pin
#define EN 3         // Enable pin
#define D4 4         // Data pin D4
#define D5 5         // Data pin D5
#define D6 6         // Data pin D6
#define D7 7         // Data pin D7
#define LCD_WIDTH 16 // Adjust this based on your LCD (16x2, 20x4, etc.)

void lcdInit();
void LCDintro();
void lcdCommand(unsigned char cmd);
void lcdData(unsigned char data);
void lcdClear();
void lcdPrint(const char *str);
void lcdSetCursor(int row, int col);
void lcdPrintRight(const char *str, int row);
void lcdScrollInFromRight(const char *str, int row);

#endif // LCD_H