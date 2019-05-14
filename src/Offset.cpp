#include <Arduino.h>
#include <Offset.h>
#include <EEPROM.h>

OFFSET offsetData;

void getOffset() {
    EEPROM.get(OFFSET_START_VALUE_ADDRESS, offsetData);
};

OFFSET setOffset() {

};