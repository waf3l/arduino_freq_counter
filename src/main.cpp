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
  lcd.setCursor(0,0);
  if (FreqCount.available()) {
    unsigned long count = FreqCount.read();
    Serial.println(count);
    lcd.print(String("Freq: ") + String(count));
  }

  lcd.setCursor(0,1);
  
  lcd_key = getButton();   // read the buttons

   switch (lcd_key){               // depending on which button was pushed, we perform an action

    case BUTTON_RIGHT_ANALOG_VALUE:{             //  push button "RIGHT" and show the word on the screen
      lcd.print("RIGHT ");
      break;
    }
    case BUTTON_LEFT_ANALOG_VALUE:{
      lcd.print("LEFT   "); //  push button "LEFT" and show the word on the screen
      break;
    }    
    case BUTTON_UP_ANALOG_VALUE:{
      lcd.print("UP    ");  //  push button "UP" and show the word on the screen
      break;
    }
    case BUTTON_DOWN_ANALOG_VALUE:{
      lcd.print("DOWN  ");  //  push button "DOWN" and show the word on the screen
      break;
    }
    case BUTTON_SELECT_ANALOG_VALUE:{
      lcd.print("SELECT");  //  push button "SELECT" and show the word on the screen
      break;
    }
    case BUTTON_NONE_ANALOG_VALUE:{
      break;
    }
   }
}






// #include <Arduino.h>
// #include <LiquidCrystal.h>
// #include <LcdKeypad.h>
// #include <TimerOne.h>

// enum AppModeValues
// {
//   APP_NORMAL_MODE,
//   APP_MENU_MODE,
//   APP_PROCESS_MENU_CMD
// };

// byte lcd_key = 0;

// byte appMode = APP_NORMAL_MODE;

// // initialize the library with the numbers of the interface pins
// LiquidCrystal lcd(8, 9, 4, 5, 6, 7);


// void setup() {
//   // init serial 
//   Serial.begin(9600);
//   Serial.println("Starting...");

//   backLightOn();
//   Serial.println("Back light on");
  
//   // set up the LCD's number of columns and rows:
//   lcd.begin(LCD_COLS, LCD_ROWS);
//   Serial.println("LCD initialized");
//   lcd.clear();
//   Serial.println("Lcd clear");
//   lcd.print("Freq counter v1"); // print a simple message
//   lcd.setCursor(4,1);
//   lcd.print("by waf3l"); // print a simple message
//   Serial.println("Displayed welcome message");
//   delay(3000);
//   lcd.clear();
  
//   // fall in to normal mode by default.
//   appMode = APP_NORMAL_MODE;
//   Serial.println("Set app mode");

//   // Use soft PWM for backlight, as hardware PWM must be avoided for some LCD shields.
//   Timer1.initialize();
//   Timer1.attachInterrupt(lcdBacklightISR, 500);

//   setBacklightBrightness(1);
// }

// void loop() {
//    //lcd.setCursor(9,1);             // move cursor to second line "1" and 9 spaces over
//    //lcd.print(millis()/1000);       // display seconds elapsed since power-up

//   lcd.setCursor(0,1);             // move to the begining of the second line
//   lcd_key = getButton();   // read the buttons

//    switch (lcd_key){               // depending on which button was pushed, we perform an action

//        case BUTTON_RIGHT_ANALOG_VALUE:{             //  push button "RIGHT" and show the word on the screen
//             lcd.print("RIGHT ");
//             break;
//        }
//        case BUTTON_LEFT_ANALOG_VALUE:{
//              lcd.print("LEFT   "); //  push button "LEFT" and show the word on the screen
//              break;
//        }    
//        case BUTTON_UP_ANALOG_VALUE:{
//              lcd.print("UP    ");  //  push button "UP" and show the word on the screen
//              break;
//        }
//        case BUTTON_DOWN_ANALOG_VALUE:{
//              lcd.print("DOWN  ");  //  push button "DOWN" and show the word on the screen
//              break;
//        }
//        case BUTTON_SELECT_ANALOG_VALUE:{
//              lcd.print("SELECT");  //  push button "SELECT" and show the word on the screen
//              break;
//        }
//    }
// }
