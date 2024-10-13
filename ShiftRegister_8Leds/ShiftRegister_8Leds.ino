// C++ code
//

const int dataPin  = 2;
const int latchPin = 3;
const int clockPin = 4; 

//we have 8 bit led
uint8_t leds = 0;

void setup()
{
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void loop()
{
  //All leds On
  UpdateShiftRegister(0xFF);
  delay(1000);
  //All Leds off
  UpdateShiftRegister(0x00);
  delay(1000);
  //half leds off
  UpdateShiftRegister(0xF0);
  delay(1000);
  //the other half off
  UpdateShiftRegister(0x0F);
  delay(1000);
  // one by one
  UpdateShiftRegister(0xAA);
  delay(1000);
}

void UpdateShiftRegister(uint8_t value)
{
  leds = value & 0xFF ;
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, leds);
  digitalWrite(latchPin,HIGH);
}