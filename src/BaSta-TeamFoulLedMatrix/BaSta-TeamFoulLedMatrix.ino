#include <Adafruit_Protomatter.h>

#include "StramatelProtocolParser.h"
#include "BebasNeue-Regular.h"

const int Baudrate = 19200;
const int TeamSelectionPin = A5;

uint8_t RgbPins[]  = {2, 3, 4, 5, 6, 7};
uint8_t AddrPins[] = {A0, A1, A2, A3};
uint8_t ClockPin   = 8;
uint8_t LatchPin   = 10;
uint8_t OePin      = 9;
 
const char *arr[] = {"/", "0", "1", "2", "3", "4" };

Adafruit_Protomatter matrix(64, 1, 1, RgbPins, 4, AddrPins, ClockPin, LatchPin, OePin, true);
StramatelProtocolParser protocolParser;
byte inputState = 0;
byte displayState = 0;

void setup()
{
  Serial.begin(Baudrate);
  Serial1.begin(Baudrate);

  pinMode(TeamSelectionPin, INPUT_PULLUP);

  // Initialize matrix
  ProtomatterStatus status = matrix.begin();
  if (status != PROTOMATTER_OK)
    for (;;);

  updateDisplay();
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
  int teamFoulMessageByte = teamSelection ? TeamFoulsHome : TeamFoulsGuest;
  byte teamFoulValue = protocolParser.getMessageByte(teamFoulMessageByte);

  byte newState = 0;
  if (teamFoulValue >= 0x30 || teamFoulValue <= 0x35)
    newState = teamFoulValue - 0x30 + 1;

  if (newState != inputState)
  {
    inputState = newState;
    displayState = newState;
    updateDisplay();
  }

  if (inputState == 5 && protocolParser.getMessageByte(GameClockRunning) == 0x31)
  {
    displayState = 6;
    updateDisplay();
  }
}

void updateDisplay()
{
  if (displayState < 6)
  {
    matrix.setRotation(1);
    matrix.setFont(&BebasNeue_Regular40pt7b);
    matrix.fillScreen(matrix.color565(0, 0, 0));
    matrix.setCursor(1, 59);
    matrix.setTextSize(1);
    matrix.print(arr[displayState]);
  }
  else
  {
    matrix.fillScreen(matrix.color565(255, 0, 0));
  }
  matrix.show();
}