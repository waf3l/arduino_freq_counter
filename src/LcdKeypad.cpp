#include "LcdKeypad.h"

#define BUTTON_REPEAT_DELAY         800
#define BUTTON_REPEAT_SPEED_DELAY   250

const int buttonValues[] = {BUTTON_RIGHT_ANALOG_VALUE,
                            BUTTON_UP_ANALOG_VALUE,
                            BUTTON_DOWN_ANALOG_VALUE,
                            BUTTON_LEFT_ANALOG_VALUE,
                            BUTTON_SELECT_ANALOG_VALUE};

byte buttonBuffer[5];
char buttonBufferCount = 0;
byte button_write_pos = 0;
byte button_read_pos = 0;
volatile byte displayBrightness = 4;
volatile byte backlightState = 1;

unsigned long buttonSampleTime =0;
byte buttonState[5];              // current up or down state for each of the buttons
unsigned long buttonPressTime[5]; // press time for each of the buttons
unsigned long buttonHoldTime[5];  // hold time for each of the buttons

char* padc (char chr, unsigned char count = 0);

// ----------------------------------------------------------------------------------------------------
void backLightOn()
{
  backlightState = 1;
  pinMode(BACKLIGHT_PIN, INPUT);
}

// ----------------------------------------------------------------------------------------------------
void backLightOff()
{
  backlightState = 0;
  pinMode(BACKLIGHT_PIN, OUTPUT);
  digitalWrite(BACKLIGHT_PIN, LOW);
}

// ----------------------------------------------------------------------------------------------------
void setBacklightBrightness(byte brightness)
{
  displayBrightness = constrain(brightness, 1, 4);
}

// ----------------------------------------------------------------------------------------------------
void lcdBacklightISR()
{
  const byte dutyCycle = 4;
  static byte pulseWidth;

  if (!backlightState)
  {
    return;
  }
  if (pulseWidth > dutyCycle)
  {
    pulseWidth = 0;
    //back light On
    pinMode(BACKLIGHT_PIN, INPUT);
  }
  else if (pulseWidth > displayBrightness)
  {
    //back light off
    pinMode(BACKLIGHT_PIN, OUTPUT);
    digitalWrite(BACKLIGHT_PIN, LOW);
  }
  pulseWidth++;
}

byte getButton(){               // read the buttons
    byte button;
    button = analogRead(BUTTON_PIN);       // read the value from the sensor 

    // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
    // we add approx 50 to those values and check to see if we are close
    // We make this the 1st option for speed reasons since it will be the most likely result

    if (button > 230 && button < 260) return BUTTON_NONE_ANALOG_VALUE; 

    Serial.println("Pressed button: " + String(button));

    // For V1.1 us this threshold
    if (button < 40)   return BUTTON_RIGHT_ANALOG_VALUE; 
    if (button < 70)  return BUTTON_DOWN_ANALOG_VALUE; 
    if (button < 140)  return BUTTON_UP_ANALOG_VALUE; 
    if (button < 220)  return BUTTON_SELECT_ANALOG_VALUE; 
    if (button < 230)  return BUTTON_LEFT_ANALOG_VALUE;   

    return BUTTON_NONE_ANALOG_VALUE;                // when all others fail, return this.

}
