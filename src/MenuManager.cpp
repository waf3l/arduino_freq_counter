#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>

// String menuItems[] = {"ITEM 1", "ITEM 2", "ITEM 3", "ITEM 4", "ITEM 5", "ITEM 6"};

// // Navigation button variables
// int readKey;
// int savedDistance = 0;

// // Menu control variables
// int menuPage = 0;
// int maxMenuPages = round(((sizeof(menuItems) / sizeof(String)) / 2) + .5);
// int cursorPosition = 0;

// // Creates 3 custom characters for the menu display
// byte downArrow[8] = {
//   0b00100, //   *
//   0b00100, //   *
//   0b00100, //   *
//   0b00100, //   *
//   0b00100, //   *
//   0b10101, // * * *
//   0b01110, //  ***
//   0b00100  //   *
// };

// byte upArrow[8] = {
//   0b00100, //   *
//   0b01110, //  ***
//   0b10101, // * * *
//   0b00100, //   *
//   0b00100, //   *
//   0b00100, //   *
//   0b00100, //   *
//   0b00100  //   *
// };

// byte menuCursor[8] = {
//   B01000, //  *
//   B00100, //   *
//   B00010, //    *
//   B00001, //     *
//   B00010, //    *
//   B00100, //   *
//   B01000, //  *
//   B00000  //
// };

// // Setting the LCD shields pins
// LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// void setup() {

//   // Initializes serial communication
//   Serial.begin(9600);

//   // Initializes and clears the LCD screen
//   lcd.begin(16, 2);
//   lcd.clear();

//   // Creates the byte for the 3 custom characters
//   lcd.createChar(0, menuCursor);
//   lcd.createChar(1, upArrow);
//   lcd.createChar(2, downArrow);
// }

// void loop() {
//   mainMenuDraw();
//   drawCursor();
//   operateMainMenu();
// }

