#include "MENU_.h"

/////////////////////////////////////////////
// Menu System
typedef enum
{
    MAIN_MENU,
    SETTINGS_MENU,
    ABOUT_MENU,
    ANIMATIONS_MENU,
    SETTINGS_MENU_LED,
    SETTINGS_MENU_BUTTONS,
    SETTINGS_MENU_POTS,
    SETTINGS_MENU_RESET,
    ANIMATIONS_MENU_ANIM1,
    ANIMATIONS_MENU_ANIM2,
    ANIMATIONS_MENU_ANIM3,
    SETTINGS_MENU_LED_Persistance,
    SETTINGS_MENU_LED_Breathing,
    SETTINGS_MENU_LED_VU,
    SETTINGS_MENU_LED_KnightRider,
    SETTINGS_MENU_LED_RandomSparkles,
    SETTINGS_MENU_LED_Wave
} MenuState;
// Menu items
const char *mainMenuItems[] = {
    "About",
    "Settings",
    "Animations"};
const char *settingsMenuItems[] = {
    "LED Mode",
    "Buttons",
    "Potentiometers",
    "Reset",
    "Back"};
const char *settingsLedModeItems[] = {
    "Persistance",
    "Breathing",
    "VU",
    "KnightRider",
    "RandomSparkles",
    "Wave",
    "Back"};
const char *aboutMenuItems[] = {
    "Auther",
    "Contact",
    "Email"};
const char *animationsMenuItems[] = {
    "Animation 1",
    "Animation 2",
    "Animation 3",
    "Back"};

/////////////////////////////////////////////
// Menu structure
typedef struct
{
    const char **items;
    uint8_t itemCount;
    uint8_t currentSelection;
} Menu;
// Global menu state
MenuState currentMenu = MAIN_MENU;
Menu currentSubMenu;

/////////////////////////////////////////////
// Menu System
// Initialize menu
void initializeMenu()
{
    switch (currentMenu)
    {
    case MAIN_MENU:
        currentSubMenu.items = mainMenuItems;
        currentSubMenu.itemCount = 3;
        break;
    case SETTINGS_MENU:
        currentSubMenu.items = settingsMenuItems;
        currentSubMenu.itemCount = 4;
        break;
    case ABOUT_MENU:
        currentSubMenu.items = aboutMenuItems;
        currentSubMenu.itemCount = 3;
        break;
    case ANIMATIONS_MENU:
        currentSubMenu.items = animationsMenuItems;
        currentSubMenu.itemCount = 4;
        break;
    case SETTINGS_MENU_LED:
        currentSubMenu.items = settingsLedModeItems;
        currentSubMenu.itemCount = 7;
        break;
    }
    currentSubMenu.currentSelection = 0;
}

// Update display with current menu
void updateMenuDisplay()
{
    if (!backlightCState)
    {
        return;
    }

    switch (currentMenu)
    {
    case MAIN_MENU:
        lcdClear();
        lcdSetCursor(0, 0);
        lcdPrint("Main Menu:");
        lcdSetCursor(1, 0);
        lcdPrint(currentSubMenu.items[currentSubMenu.currentSelection]);
        break;
    case SETTINGS_MENU:
        lcdClear();
        lcdSetCursor(0, 0);
        lcdPrint("Settings:");
        lcdSetCursor(1, 0);
        lcdPrint(currentSubMenu.items[currentSubMenu.currentSelection]);
        break;
    case ABOUT_MENU:
        updateAboutMenuDisplay();
        break;
    case ANIMATIONS_MENU:
        lcdClear();
        lcdSetCursor(0, 0);
        lcdPrint("Animations:");
        lcdSetCursor(1, 0);
        lcdPrint(currentSubMenu.items[currentSubMenu.currentSelection]);
        break;
    case SETTINGS_MENU_LED:
        lcdClear();
        lcdSetCursor(0, 0);
        lcdPrint("LED Mode:");
        lcdSetCursor(1, 0);
        lcdPrint(currentSubMenu.items[currentSubMenu.currentSelection]);
        break;
    default:
        lcdPrint("NULL            ");
        return;
    }
}

// Handle menu navigation
void handleMenuRotation(uint8_t rotationDirection)
{
    if (rotationDirection == CLOCKWISE)
    {
        if (currentSubMenu.currentSelection < currentSubMenu.itemCount - 1)
        {
            currentSubMenu.currentSelection++;
        }
        else
        {
            return;
        }
    }
    else if (rotationDirection == COUNTER_CLOCKWISE)
    {
        if (currentSubMenu.currentSelection > 0)
        {
            currentSubMenu.currentSelection--;
        }
        else
        {
            return;
        }
    }

    updateMenuDisplay();
}

void handleMenuPress(bool selectPressed)
{
    if (selectPressed)
    {
        // Handle menu selection
        switch (currentMenu)
        {
        case MAIN_MENU:
            switch (currentSubMenu.currentSelection)
            {
            case 0:
                currentMenu = ABOUT_MENU2;
                break;
            case 1:
                currentMenu = SETTINGS_MENU;
                break;
            case 2:
                currentMenu = ANIMATIONS_MENU;
                break;
            }
            break;
            ////////////////////////////////////////////////////////////////////////////////////////////
        case ANIMATIONS_MENU:
            switch (currentSubMenu.currentSelection)
            {
            case 0:
                // currentMenu = ANIMATIONS_MENU_ANIM1;
                currentMenu = MAIN_MENU;
                break;
            case 1:
                // currentMenu = ANIMATIONS_MENU_ANIM2;
                currentMenu = MAIN_MENU;
                break;
            case 2:
                // currentMenu = ANIMATIONS_MENU_ANIM3;
                currentMenu = MAIN_MENU;
                break;
            default:
                currentMenu = MAIN_MENU;
            }
            break;
        case SETTINGS_MENU:
            switch (currentSubMenu.currentSelection)
            {
            case 0:
                // currentMenu = SETTINGS_MENU_RESET;
                currentMenu = SETTINGS_MENU_LED;
                break;
            case 1:
                // currentMenu = SETTINGS_MENU_BUTTONS;
                currentMenu = MAIN_MENU;
                break;
            case 2:
                // currentMenu = SETTINGS_MENU_POTS;
                currentMenu = MAIN_MENU;
                break;
            default:
                currentMenu = MAIN_MENU;
            }
            break;
        case ABOUT_MENU:
            switch (currentSubMenu.currentSelection)
            {
            default:
                currentMenu = MAIN_MENU;
            }
            break;
        case SETTINGS_MENU_LED:
            switch (currentSubMenu.currentSelection)
            {
            case SETTINGS_MENU_LED_Persistance:
                patternMode = 0;
                currentMenu = MAIN_MENU;
                break;
            case SETTINGS_MENU_LED_Breathing:
                patternMode = 1;
                currentMenu = MAIN_MENU;
                break;
            case SETTINGS_MENU_LED_VU:
                patternMode = 2;
                currentMenu = MAIN_MENU;
                break;
            case SETTINGS_MENU_LED_KnightRider:
                patternMode = 3;
                currentMenu = MAIN_MENU;
                break;
            case SETTINGS_MENU_LED_RandomSparkles:
                patternMode = 4;
                currentMenu = MAIN_MENU;
                break;
            case SETTINGS_MENU_LED_Wave:
                patternMode = 5;
                currentMenu = MAIN_MENU;
                break;
            default:
                currentMenu = MAIN_MENU;
                break;
            }
        }
        initializeMenu();
    }
    updateMenuDisplay();
}

void updateAboutMenuDisplay()
{
    lcdClear();
    delay(2);
    switch (currentSubMenu.currentSelection)
    {
    case 0:
        lcdSetCursor(0, 0);
        lcdPrint("About:");
        lcdPrintRight(aboutMenuItems[currentSubMenu.currentSelection], 0);
        lcdSetCursor(1, 0);
        lcdPrint("Gaurav Sharma"); // Credits
        break;
    case 1:
        lcdSetCursor(0, 0);
        lcdPrint("About:");
        lcdPrintRight(aboutMenuItems[currentSubMenu.currentSelection], 0);
        lcdSetCursor(1, 0);
        lcdPrint("+91 7378002807"); // Contact
        break;
    case 2:
        lcdSetCursor(0, 0);
        lcdPrint("Email:   gaurav18.sh@icloud.com"); // Email
        lcdSetCursor(1, 0);
        lcdPrint("8.sh@icloud.com"); // Email
        break;
    }
}

/////////////////////////////////////////////
// LCD
void HandleLCD()
{
    if (!backlightPState && backlightCState)
    {
        // LCD Display 16x2
        LCD_Initialized = false;
        lcdInit(); // Initialize LCD

        currentMenu = MAIN_MENU; // Reset menu state
        initializeMenu();        // Initialize menu

        currentSubMenu.currentSelection = 0; // Reset menu selection
        updateMenuDisplay();                 // Display the menu
    }
    backlightPState = backlightCState;
}