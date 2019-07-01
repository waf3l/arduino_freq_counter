#include <Arduino.h>
#include <Offset.h>
#include <EEPROM.h>

OFFSET offsetData;

void getOffset() {
    EEPROM.get(OFFSET_START_VALUE_ADDRESS, offsetData);
};

void setOffset(OFFSET payload) {
    EEPROM.put(OFFSET_START_VALUE_ADDRESS, payload);
};

bool compareOffset(OFFSET oldOffset, OFFSET newOffset) {
    if (oldOffset.type != newOffset.type) {
        return false;
    } else if (oldOffset.f1 != newOffset.f1) {
        return false;
    } else if (oldOffset.f2 != newOffset.f2) {
        return false;
    } else if (oldOffset.f3 != newOffset.f3) {
        return false;
    } else if (oldOffset.f4 != newOffset.f4) {
        return false;
    } else if (oldOffset.f5 != newOffset.f5) {
        return false;
    } else if (oldOffset.f6 != newOffset.f6) {
        return false;
    } else {
        return true;
    }
}

long convert() {
    return offsetData.f6*1+offsetData.f5*10+offsetData.f4*100+offsetData.f3*1000+offsetData.f2*10000+offsetData.f1*100000;
}