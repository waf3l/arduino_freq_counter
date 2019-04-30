/* FreqCount - Example with serial output
 * http://www.pjrc.com/teensy/td_libs_FreqCount.html
 *
 * This example code is in the public domain.
 */

#include <FreqCount.h>
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <LcdKeypad.h>

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
  Serial.println("LCD initialized");
  
  // Creates the byte for the 3 custom characters
  lcd.createChar(0, menuCursor);
  lcd.createChar(1, upArrow);
  lcd.createChar(2, downArrow);
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

  int activeButton = 0;

  while (activeButton == 0) {
    // read the buttons
    lcd_key = getButton();   

    // depending on which button was pushed, we perform an action
    switch (lcd_key){               
      
      case BUTTON_NONE_ANALOG_VALUE:{
        activeButton = 1;
        break;
      }
      
      case BUTTON_SELECT_ANALOG_VALUE:{
        
        if (appMode == APP_NORMAL_MODE)
        {
          // end the freq counter
          FreqCount.end();

          // set app menu mode
          appMode = APP_MENU_MODE;

          activeButton = 1;

          // display menu
          mainMenuDraw(lcd);
          drawCursor(lcd);

          break;
        }

        else if (appMode == APP_MENU_MODE)
        {
          // do nothing
          activeButton = 1;
          break;
        }

        else if (appMode == APP_PROCESS_MENU_CMD)
        {
          // Save the sub menu settings
          // Return to root menu
          // TODO: return to proper position
          appMode = APP_MENU_MODE;
          
          activeButton = 1;

          mainMenuDraw(lcd);
          drawCursor(lcd);

          break;
        }

        else 
        {
          // Something wrong exit
          activeButton = 1;
          break;
        }

      }

      case BUTTON_RIGHT_ANALOG_VALUE:{            
        
        if (appMode == APP_NORMAL_MODE)
        {
          // do nothing
          activeButton = 1;
          break;
        }

        else if (appMode == APP_MENU_MODE)
        {
          // Enter submenu
          // TODO: Logic
          activeButton = 1;
          appMode = APP_PROCESS_MENU_CMD;
          break;
        }

        else if (appMode == APP_PROCESS_MENU_CMD)
        {
          // do nothing
          activeButton = 1;
          break;
        }

        else 
        {
          activeButton = 1;
          break;
        }
      }

      case BUTTON_LEFT_ANALOG_VALUE:{
        
        if (appMode == APP_NORMAL_MODE)
        {
          // do nothing
          activeButton = 1;
          break;
        }

        else if (appMode == APP_MENU_MODE)
        {
          // Go back to normal app mode
          appMode = APP_NORMAL_MODE;

          //TODO clear all menu counters and position
          lcd.clear();
          FreqCount.begin(1000);
          activeButton = 1;
          break;
        }

        else if (appMode == APP_PROCESS_MENU_CMD)
        {
          // Return to root menu without save
          // Set app menu mode
          // TODO: Return to proper position
          activeButton = 1;
          appMode = APP_MENU_MODE;
          lcd.clear();
          mainMenuDraw(lcd);
          drawCursor(lcd);
          break;
        }

        else 
        {
          activeButton = 1;
          break;
        }
      }  

      case BUTTON_UP_ANALOG_VALUE:{
        
        if (appMode == APP_NORMAL_MODE)
        {
          // do nothing
          activeButton = 1;
          break;
        }

        else if (appMode == APP_MENU_MODE)
        {
          // Go thru menu items up
          activeButton = 1;
          break;
        }

        else if (appMode == APP_PROCESS_MENU_CMD)
        {
          // change value up
          activeButton = 1;
          break;
        }

        else 
        {
          activeButton = 1;
          break;
        }
      }

      case BUTTON_DOWN_ANALOG_VALUE:{
        
        if (appMode == APP_NORMAL_MODE)
        {
          // do nothing
          activeButton = 1;
          break;
        }

        else if (appMode == APP_MENU_MODE)
        {
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

          activeButton = 1;

          break;
        }

        else if (appMode == APP_PROCESS_MENU_CMD)
        {
          // change value down
          activeButton = 1;
          break;
        }

        else 
        {
          activeButton = 1;
          break;
        }
      }

      default: {
        activeButton = 1;
        appMode = APP_NORMAL_MODE;
      }
  
    }
  }
  {
    /* code */
  }
}

