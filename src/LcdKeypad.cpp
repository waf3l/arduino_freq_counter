#include "LcdKeypad.h"
#include <LiquidCrystal.h>
#include <Offset.h>

volatile byte displayBrightness = 4;
volatile byte backlightState = 1;

// menu names
String menuItems[] = {"OFFSET", "PRESCALER", "EXIT"};

// Menu control variables
int menuPage = 0;
int maxMenuPages = round(((sizeof(menuItems) / sizeof(String)) / 2) + .5);
int cursorPosition = 0;

void backLightOn()
{
  backlightState = 1;
  pinMode(BACKLIGHT_PIN, INPUT);
}

void backLightOff()
{
  backlightState = 0;
  pinMode(BACKLIGHT_PIN, OUTPUT);
  digitalWrite(BACKLIGHT_PIN, LOW);
}

byte getButton(){               

    byte button;
    button = analogRead(BUTTON_PIN);

    if (button > 230 && button < 260) return BUTTON_NONE_ANALOG_VALUE; 

    Serial.println("Pressed button: " + String(button));
    
    // For V1.1 us this threshold
    if (button < 40)   return BUTTON_RIGHT_ANALOG_VALUE; 
    if (button < 70)  return BUTTON_DOWN_ANALOG_VALUE; 
    if (button < 140)  return BUTTON_UP_ANALOG_VALUE; 
    if (button < 220)  return BUTTON_SELECT_ANALOG_VALUE; 
    if (button < 230)  return BUTTON_LEFT_ANALOG_VALUE;   

    return BUTTON_NONE_ANALOG_VALUE;
}

// This function will generate the 2 menu items that can fit on the screen. They will change as you scroll through your menu. Up and down arrows will indicate your current menu position.
void mainMenuDraw(LiquidCrystal lcd) {
  Serial.print(menuPage);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(menuItems[menuPage]);
  lcd.setCursor(1, 1);
  lcd.print(menuItems[menuPage + 1]);
  if (menuPage == 0) {
    lcd.setCursor(15, 1);
    lcd.write(byte(2));
  } else if (menuPage > 0 and menuPage < maxMenuPages) {
    lcd.setCursor(15, 1);
    lcd.write(byte(2));
    lcd.setCursor(15, 0);
    lcd.write(byte(1));
  } else if (menuPage == maxMenuPages) {
    lcd.setCursor(15, 0);
    lcd.write(byte(1));
  }
}

// When called, this function will erase the current cursor and redraw it based on the cursorPosition and menuPage variables.
void drawCursor(LiquidCrystal lcd) {
  for (int x = 0; x < 2; x++) {     // Erases current cursor
    lcd.setCursor(0, x);
    lcd.print(" ");
  }

  // The menu is set up to be progressive (menuPage 0 = Item 1 & Item 2, menuPage 1 = Item 2 & Item 3, menuPage 2 = Item 3 & Item 4), so
  // in order to determine where the cursor should be you need to see if you are at an odd or even menu page and an odd or even cursor position.
  if (menuPage % 2 == 0) {
    if (cursorPosition % 2 == 0) {  // If the menu page is even and the cursor position is even that means the cursor should be on line 1
      lcd.setCursor(0, 0);
      lcd.write(byte(0));
    }
    if (cursorPosition % 2 != 0) {  // If the menu page is even and the cursor position is odd that means the cursor should be on line 2
      lcd.setCursor(0, 1);
      lcd.write(byte(0));
    }
  }
  if (menuPage % 2 != 0) {
    if (cursorPosition % 2 == 0) {  // If the menu page is odd and the cursor position is even that means the cursor should be on line 2
      lcd.setCursor(0, 1);
      lcd.write(byte(0));
    }
    if (cursorPosition % 2 != 0) {  // If the menu page is odd and the cursor position is odd that means the cursor should be on line 1
      lcd.setCursor(0, 0);
      lcd.write(byte(0));
    }
  }
}

void menuItem1(LiquidCrystal lcd) {
  
  byte curPosStart = 0;
  byte curPosEnd = 5;
  byte curPos = 0;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SET OFFSET VAL:");

  getOffset();

  lcd.setCursor(0,1);
  if (offsetData.f1 >= 0 && offsetData.f1 <= 9){
    lcd.print(offsetData.f1);
  } else {
    lcd.print(0);
    offsetData.f1 = 0;
  }

  lcd.setCursor(1,1);
  if (offsetData.f2 >= 0 && offsetData.f2 <= 9){
    lcd.print(offsetData.f2);
  } else {
    lcd.print(0);
    offsetData.f2 = 0;
  }
  
  lcd.setCursor(2,1);
  if (offsetData.f3 >= 0 && offsetData.f3 <= 9){
    lcd.print(offsetData.f3);
  } else {
    lcd.print(0);
    offsetData.f3 = 0;
  }
  
  lcd.setCursor(3,1);
  if (offsetData.f4 >= 0 && offsetData.f4 <= 9){
    lcd.print(offsetData.f4);
  } else {
    lcd.print(0);
    offsetData.f4 = 0;
  }
  
  lcd.setCursor(4,1);
  if (offsetData.f5 >= 0 && offsetData.f5 <= 9){
    lcd.print(offsetData.f5);
  } else {
    lcd.print(0);
    offsetData.f5 = 0;
  }

  lcd.setCursor(5,1);
  if (offsetData.f6 >= 0 && offsetData.f6 <= 9){
    lcd.print(offsetData.f6);
  } else {
    lcd.print(0);
    offsetData.f6 = 0;
  }
  delay(200);
  lcd.setCursor(0,1);
  lcd.blink();

  int activeButton = 0;

  while (activeButton == 0) {

    byte button = getButton();

    switch (button) {
      case BUTTON_LEFT_ANALOG_VALUE:
        if (curPos > curPosStart) {
          curPos --;
          lcd.noBlink();
          lcd.setCursor(curPos,1);
          lcd.blink();
        }
        break;
      case BUTTON_RIGHT_ANALOG_VALUE:
        if (curPos < curPosEnd) {
          curPos ++;
          lcd.noBlink();
          lcd.setCursor(curPos,1);
          lcd.blink();
        }
        break;
      case BUTTON_UP_ANALOG_VALUE:
        if (curPos == 0) {
          if (offsetData.f1 < 9) {
            offsetData.f1 ++;
            lcd.print(offsetData.f1);
            lcd.setCursor(curPos,1);
          }
        }  else if (curPos == 1) {
          if (offsetData.f2 < 9) {
            offsetData.f2 ++;
            lcd.print(offsetData.f2);
            lcd.setCursor(curPos,1);
          }
        } else if (curPos == 2) {
          if (offsetData.f3 < 9) {
            offsetData.f3 ++;
            lcd.print(offsetData.f3);
            lcd.setCursor(curPos,1);
          }        
        } else if (curPos == 3) {
          if (offsetData.f4 < 9) {
            offsetData.f4 ++;
            lcd.print(offsetData.f4);
            lcd.setCursor(curPos,1);
          }        
        } else if (curPos == 4) {
          if (offsetData.f5 < 9) {
            offsetData.f5 ++;
            lcd.print(offsetData.f5);
            lcd.setCursor(curPos,1);
          }        
        } else if (curPos == 5) {
          if (offsetData.f6 < 9) {
            offsetData.f6 ++;
            lcd.print(offsetData.f6);
            lcd.setCursor(curPos,1);
          }        
        }
        break;
      case BUTTON_DOWN_ANALOG_VALUE:
        if (curPos == 0) {
          if (offsetData.f1 > 0) {
            offsetData.f1 --;
            lcd.print(offsetData.f1);
            lcd.setCursor(curPos,1);
          }
        }  else if (curPos == 1) {
          if (offsetData.f2 > 0) {
            offsetData.f2 --;
            lcd.print(offsetData.f2);
            lcd.setCursor(curPos,1);
          }
        } else if (curPos == 2) {
          if (offsetData.f3 > 0) {
            offsetData.f3 --;
            lcd.print(offsetData.f3);
            lcd.setCursor(curPos,1);
          }        
        } else if (curPos == 3) {
          if (offsetData.f4 > 0) {
            offsetData.f4 --;
            lcd.print(offsetData.f4);
            lcd.setCursor(curPos,1);
          }        
        } else if (curPos == 4) {
          if (offsetData.f5 > 0) {
            offsetData.f5 --;
            lcd.print(offsetData.f5);
            lcd.setCursor(curPos,1);
          }        
        } else if (curPos == 5) {
          if (offsetData.f6 > 0) {
            offsetData.f6 --;
            lcd.print(offsetData.f6);
            lcd.setCursor(curPos,1);
          }        
        }
        break;
      case BUTTON_SELECT_ANALOG_VALUE:
        activeButton = 1;
        lcd.noBlink();
        break;
    }
    delay(200);
  }
}

void menuItem2(LiquidCrystal lcd) { // Function executes when you select the 2nd item from main menu

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Sub Menu 2");

  // while (activeButton == 0) {
  //   int button;
  //   readKey = analogRead(0);
  //   if (readKey < 790) {
  //     delay(100);
  //     readKey = analogRead(0);
  //   }
  //   button = evaluateButton(readKey);
  //   switch (button) {
  //     case 4:  // This case will execute if the "back" button is pressed
  //       button = 0;
  //       activeButton = 1;
  //       break;
  //   }
  // }
}

void menuItem3(LiquidCrystal lcd) { // Function executes when you select the 3rd item from main menu

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Sub Menu 3");

  // while (activeButton == 0) {
  //   int button;
  //   readKey = analogRead(0);
  //   if (readKey < 790) {
  //     delay(100);
  //     readKey = analogRead(0);
  //   }
  //   button = evaluateButton(readKey);
  //   switch (button) {
  //     case 4:  // This case will execute if the "back" button is pressed
  //       button = 0;
  //       activeButton = 1;
  //       break;
  //   }
  // }
}
