const int dataPin  = 2;
const int latchPin = 3;
const int clockPin = 4; 
const int pot = A5;

//we have 8 bit led
uint8_t leds = 0;

void setup()
{
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  
  Serial.begin(9600);
}

void loop()
{
  // this is a 10 bit ADC, gives a value between 0 - 2023 
  int potVal = analogRead(pot);
  //the shift register can get value between 0 - 255
  UpdateShiftRegister(potVal / 4);
  
  Serial.print("pot value : ");
  Serial.println(potVal);
  Serial.print("output val : ");
  Serial.println(potVal / 4);
  delay(2000);

}

void UpdateShiftRegister(uint8_t value)
{
  leds = value & 0xFF ;
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, leds);
  digitalWrite(latchPin,HIGH);
}