#define OFFSET_START_VALUE_ADDRESS 0

struct OFFSET
{
    byte type;
    byte f1;
    byte f2;
    byte f3;
    byte f4;
    byte f5;
    byte f6;
};

extern struct OFFSET offsetData;

extern void getOffset();
extern long convert();
extern void setOffset(OFFSET payload);
extern bool compareOffset(OFFSET oldOffset, OFFSET newOffset);