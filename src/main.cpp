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

  // read the buttons
  lcd_key = getButton();   

  // depending on which button was pushed, we perform an action
  switch (lcd_key){               
    
    case BUTTON_NONE_ANALOG_VALUE:{
      break;
    }
    
    case BUTTON_SELECT_ANALOG_VALUE:{
      
      if (appMode == APP_NORMAL_MODE)
      {
        // end the freq counter
        FreqCount.end();

        // set app menu mode
        appMode = APP_MENU_MODE;

        // display menu

        mainMenuDraw(lcd);
        drawCursor(lcd);
        break;
      }

      else if (appMode == APP_MENU_MODE)
      {
        appMode = APP_PROCESS_MENU_CMD;
      }

      else if (appMode == APP_PROCESS_MENU_CMD)
      {
        appMode = APP_MENU_MODE;
        //TODO: return to proper position
        mainMenuDraw(lcd);
        drawCursor(lcd);
        break;
      }

      else 
      {
        break;
      }
      
      

      //lcd.print("SELECT");  //  push button "SELECT" and show the word on the screen
      // break;
    }

    case BUTTON_RIGHT_ANALOG_VALUE:{             //  push button "RIGHT" and show the word on the screen
      if (appMode == APP_NORMAL_MODE)
      {
        // do nothing
        break;
      }

      else if (appMode == APP_MENU_MODE)
      {
        // enter to menu item
        // and process the item
        appMode = APP_PROCESS_MENU_CMD;
        break;
      }

      else if (appMode == APP_PROCESS_MENU_CMD)
      {
        // do nothing
        break;
      }

      else 
      {
        break;
      }
    }

    case BUTTON_LEFT_ANALOG_VALUE:{
      if (appMode == APP_NORMAL_MODE)
      {
        // do nothing
        break;
      }

      else if (appMode == APP_MENU_MODE)
      {
        // go back from menu to app
        appMode = APP_NORMAL_MODE;

        //TODO clear all menu counters and position
        lcd.clear();
        FreqCount.begin(1000);
        break;
      }

      else if (appMode == APP_PROCESS_MENU_CMD)
      {
        // go out from menu item and go back to menu
        // set app menu mode
        appMode = APP_MENU_MODE;
        lcd.clear();
        mainMenuDraw(lcd);
        drawCursor(lcd);
        break;
      }

      else 
      {
        break;
      }
    }  

    case BUTTON_UP_ANALOG_VALUE:{
      if (appMode == APP_NORMAL_MODE)
      {
        // do nothing
        break;
      }

      else if (appMode == APP_MENU_MODE)
      {
        // Go thru menu items up
        break;
      }

      else if (appMode == APP_PROCESS_MENU_CMD)
      {
        // change value up
        break;
      }

      else 
      {
        break;
      }
    }

    case BUTTON_DOWN_ANALOG_VALUE:{
      if (appMode == APP_NORMAL_MODE)
      {
        // do nothing
        break;
      }

      else if (appMode == APP_MENU_MODE)
      {
        // Go thru menu items down
        break;
      }

      else if (appMode == APP_PROCESS_MENU_CMD)
      {
        // change value down
        break;
      }

      else 
      {
        break;
      }
    }

    default: {
      appMode = APP_NORMAL_MODE;
    }
 
  }
}

