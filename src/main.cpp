/* FreqCount - Example with serial output
 * http://www.pjrc.com/teensy/td_libs_FreqCount.html
 *
 * This example code is in the public domain.
 */

#include <FreqCount.h>
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <LcdKeypad.h>

// Creates 3 custom char for the menu display
byte downArrow[8] = {
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b10101, // * * *
  0b01110, //  ***
  0b00100  //   *
};

byte upArrow[8] = {
  0b00100, //   *
  0b01110, //  ***
  0b10101, // * * *
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b00100  //   *
};

byte menuCursor[8] = {
  B01000, //  *
  B00100, //   *
  B00010, //    *
  B00001, //     *
  B00010, //    *
  B00100, //   *
  B01000, //  *
  B00000  //
};

enum AppModeValues
{
  APP_NORMAL_MODE,
  APP_MENU_MODE,
  APP_PROCESS_MENU_CMD
};

int appMode;
byte lcd_key;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 3, 6, 7);

void setup() {
  // init serial 
  Serial.begin(9600);
  Serial.println("Starting...");

  backLightOn();
  Serial.println("Back light on");

  // set up the LCD's number of columns and rows:
  lcd.begin(LCD_COLS, LCD_ROWS);

  // Creates the byte for the 3 custom characters
  lcd.createChar(0, menuCursor);
  lcd.createChar(1, upArrow);
  lcd.createChar(2, downArrow);

  Serial.println("LCD initialized");
  Serial.println("Characters created");

  lcd.clear();
  Serial.println("Lcd clear");

  lcd.print("Freq counter v1"); // print a simple message
  lcd.setCursor(4,1);
  lcd.print("by waf3l"); // print a simple message
  Serial.println("Displayed welcome message");
  delay(3000);
  lcd.clear();

  // fall in to normal mode by default.
  appMode = APP_NORMAL_MODE;
  Serial.println("Set app mode");

  // start the freq counter
  FreqCount.begin(1000);
}

void loop() {
  
  // check the state of app
  if (appMode == APP_NORMAL_MODE)
  {
    // set cursor
    lcd.setCursor(0,0);
    
    // check if freq is available
    if (FreqCount.available()) {
      unsigned long count = FreqCount.read();
      Serial.println(count);
      lcd.print(String("Freq: ") + String(count) + String("hz"));
    }
  }

  int menuLoop = 1;
  // read the buttons
  lcd_key = getButton();   

  while (menuLoop == 1)
  {
    // depending on which button was pushed, we perform an action
    switch (lcd_key){               
      
      case BUTTON_NONE_ANALOG_VALUE:{
        menuLoop = 0;
        break;
      }
      
      case BUTTON_SELECT_ANALOG_VALUE:{
        
        if (appMode == APP_NORMAL_MODE)
        {
          Serial.println("BUTTON_SELECT IN APP_NORMAL_MODE");
          // end the freq counter
          FreqCount.end();

          // set app menu mode
          appMode = APP_MENU_MODE;

          // display menu
          mainMenuDraw(lcd);
          drawCursor(lcd);

          menuLoop = 0;
          break;
        }

        else if (appMode == APP_MENU_MODE)
        {
          // do nothing
          Serial.println("BUTTON_SELECT IN APP_MENU_MODE");
          menuLoop = 0;
          break;
        }

        else if (appMode == APP_PROCESS_MENU_CMD)
        {
          // Save the sub menu settings
          // Return to root menu
          // TODO: return to proper position
          Serial.println("BUTTON_SELECT IN APP_PROCCESS_MENU_MODE");
          appMode = APP_MENU_MODE;

          mainMenuDraw(lcd);
          drawCursor(lcd);

          menuLoop = 0;
          break;
        }

        else 
        {
          // Something wrong exit
          menuLoop = 0;
          break;
        }

      }

      case BUTTON_RIGHT_ANALOG_VALUE:{            
        
        if (appMode == APP_NORMAL_MODE)
        {
          // do nothing
          Serial.println("BUTTON_RIGHT IN APP_NORMAL_MODE");
          menuLoop = 0;
          break;
        }

        else if (appMode == APP_MENU_MODE)
        {
          // Enter submenu
          // TODO: Logic
          Serial.println("BUTTON_RIGHT IN APP_MENU_MODE");
          appMode = APP_PROCESS_MENU_CMD;
          switch (cursorPosition) { // The case that is selected here is dependent on which menu page you are on and where the cursor is.
            case 0:
              menuItem1(lcd);
              break;
            case 1:
              menuItem2(lcd);
              break;
            case 2:
              menuItem3(lcd);
              break;
          }
          menuLoop = 0;
          break;
        }

        else if (appMode == APP_PROCESS_MENU_CMD)
        {
          // do nothing
          Serial.println("BUTTON_RIGHT IN APP_PROCESS_MENU_MODE");
          menuLoop = 0;
          break;
        }

        else 
        {
          menuLoop = 0;
          break;
        }
      }

      case BUTTON_LEFT_ANALOG_VALUE:{
        
        if (appMode == APP_NORMAL_MODE)
        {
          // do nothing
          Serial.println("BUTTON_LEFT IN APP_NORMAL_MODE");
          menuLoop = 0;
          break;
        }

        else if (appMode == APP_MENU_MODE)
        {
          // Go back to normal app mode
          Serial.println("BUTTON_LEFT IN APP_MENU_MODE");
          appMode = APP_NORMAL_MODE;

          //TODO clear all menu counters and position
          lcd.clear();
          FreqCount.begin(1000);
          menuLoop = 0;
          break;
        }

        else if (appMode == APP_PROCESS_MENU_CMD)
        {
          // Return to root menu without save
          // Set app menu mode
          // TODO: Return to proper position
          Serial.println("BUTTON_LEFT IN APP_PROCESS_MENU_MODE");
          appMode = APP_MENU_MODE;

          mainMenuDraw(lcd);
          drawCursor(lcd);

          menuLoop = 0;
          break;
        }

        else 
        {
          menuLoop = 0;
          break;
        }
      }  

      case BUTTON_UP_ANALOG_VALUE:{
        
        if (appMode == APP_NORMAL_MODE)
        {
          // do nothing
          menuLoop = 0;
          break;
        }

        else if (appMode == APP_MENU_MODE)
        {
          // Go thru menu items up
          // check current menu position
          if (menuPage % 2 == 0 and cursorPosition % 2 != 0) {
            menuPage = menuPage - 1;
            menuPage = constrain(menuPage, 0, maxMenuPages);
          }

          if (menuPage % 2 != 0 and cursorPosition % 2 == 0) {
            menuPage = menuPage - 1;
            menuPage = constrain(menuPage, 0, maxMenuPages);
          }

          // set the cursor position
          cursorPosition = cursorPosition - 1;
          cursorPosition = constrain(cursorPosition, 0, ((sizeof(menuItems) / sizeof(String)) - 1));

          mainMenuDraw(lcd);
          drawCursor(lcd);

          menuLoop = 0;
          break;
        }

        else if (appMode == APP_PROCESS_MENU_CMD)
        {
          // change value up
          // TODO: Logic
          menuLoop = 0;
          break;
        }

        else 
        {
          menuLoop = 0;
          break;
        }
      }

      case BUTTON_DOWN_ANALOG_VALUE:{
        
        if (appMode == APP_NORMAL_MODE)
        {
          // do nothing
          menuLoop = 0;
          break;
        }

        else if (appMode == APP_MENU_MODE)
        {
          // Go thru menu down
          // check current menu position
          if (menuPage % 2 == 0 and cursorPosition % 2 != 0) {
            menuPage = menuPage + 1;
            menuPage = constrain(menuPage, 0, maxMenuPages);
          }

          if (menuPage % 2 != 0 and cursorPosition % 2 == 0) {
            menuPage = menuPage + 1;
            menuPage = constrain(menuPage, 0, maxMenuPages);
          }

          // set the cursor position
          cursorPosition = cursorPosition + 1;
          cursorPosition = constrain(cursorPosition, 0, ((sizeof(menuItems) / sizeof(String)) - 1));

          mainMenuDraw(lcd);
          drawCursor(lcd);

          menuLoop = 0;
          break;
        }

        else if (appMode == APP_PROCESS_MENU_CMD)
        {
          // change value down
          // TODO: Logic
          menuLoop = 0;
          break;
        }

        else 
        {
          menuLoop = 0;
          break;
        }
      }

      default: {
        appMode = APP_NORMAL_MODE;
        menuLoop = 0;
        break;
      }

    }
  }
  delay(200);
}

