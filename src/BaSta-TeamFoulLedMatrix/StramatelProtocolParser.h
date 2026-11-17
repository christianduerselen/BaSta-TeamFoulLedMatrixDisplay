#ifndef StramatelProtocolParser_h
#define StramatelProtocolParser_h

#include "Troolean.h"

const int MessageSize = 54;
// The vendor PDF documents 0xF8 as the start byte, but real consoles vary the low three bits:
// 0xF9 and 0xFD were both seen on the wire. Anything from 0xF8 upwards opens a frame; the
// inter-console bytes a main console appends after each frame (E0 E8 E4) fall outside it.
const byte StartByteFamily = 0xF8;
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