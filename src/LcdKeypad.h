#include <Arduino.h>
#include <LiquidCrystal.h>

#define LCD_ROWS  2
#define LCD_COLS  16

#define BUTTON_PIN  0
#define BACKLIGHT_PIN 10

#define BUTTON_RIGHT_ANALOG_VALUE   1
#define BUTTON_UP_ANALOG_VALUE      2
#define BUTTON_DOWN_ANALOG_VALUE    3
#define BUTTON_LEFT_ANALOG_VALUE    4
#define BUTTON_SELECT_ANALOG_VALUE  5
#define BUTTON_NONE_ANALOG_VALUE    0

#define PRESCALLER_VALUE_ADDRESS 10

extern int menuPage;
extern int cursorPosition;
extern int maxMenuPages;
extern String menuItems[3];

extern byte getButton ();

extern void backLightOn();
extern void backLightOff();
extern void mainMenuDraw(LiquidCrystal lcd);
extern void drawCursor(LiquidCrystal lcd);

extern void menuItem1(LiquidCrystal lcd);
extern void menuItem2(LiquidCrystal lcd);
extern void menuItem3(LiquidCrystal lcd);