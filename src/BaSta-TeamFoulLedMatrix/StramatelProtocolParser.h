#ifndef StramatelProtocolParser_h
#define StramatelProtocolParser_h

#include "Troolean.h"

const int MessageSize = 54;
const byte MessageStart = 0xF8;
const int GameClockMinuteHigh = 4;
const int GameClockMinuteLow = 5;
const int GameClockSecondHigh = 6;
const int GameClockSecondLow = 7;
const int ShotClockHigh = 48;
const int ShotClockLow = 49;
const int TeamFoulsHome = 15;
const int TeamFoulsGuest = 16;
const int GameClockRunning = 20;

class StramatelProtocolParser
{
  public:
    StramatelProtocolParser();
    void push(byte value);
    bool isValidMessage();
    byte getMessageByte(int index);
    void setMessageByte(int index, byte value);
    Troolean isGameClockZero();
    Troolean isShotClockZero();
  private:
    byte _message[MessageSize];
    int _messagePointer = 0;
    Troolean isValueZero(int startIndex, int endIndex);
};

#endif