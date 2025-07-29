#include "StramatelProtocolParser.h"

const int Baudrate = 19200;
const int TeamSelectionPin = 11;

StramatelProtocolParser protocolParser;

void setup()
{
  Serial.begin(Baudrate);
  Serial1.begin(Baudrate);

  pinMode(TeamSelectionPin, INPUT);

  // TODO: Initiazation of LED matrix
}

void loop()
{ 
  // RECEIVE
  if (!Serial1.available() > 0)
    return;
  
  // Read next byte from input
  byte value = Serial1.read();

  Serial.write(value);

  protocolParser.push(value);

  // PARSE
  if (!protocolParser.isValidMessage())
    return;

  // CONTROL
  
  bool teamSelection = digitalRead(TeamSelectionPin);
  int teamFoulMessageByte = teamSelection ? TeamFoulsGuest : TeamFoulsHome;
  byte teamFoulValue = protocolParser.getMessageByte(teamFoulMessageByte);

  char output = '-';
  if (teamFoulValue >= 0x30 || teamFoulValue <= 0x39)
    output = teamFoulValue;
  
  // TODO: Refresh LED matrix information
}
