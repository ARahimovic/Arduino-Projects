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

  Serial.begin(9600);
  while (! Serial);
  Serial.println("enter a value from 0 to 255 to output in LED /n");
}

void loop()
{
  if (Serial.available() > 0) {

    // Take user input as a string
    String userInput = Serial.readStringUntil('\n'); // Read until newline
    // Convert string to integer, trimming any non-numeric characters
    int val = userInput.toInt(); // Convert the string to an integer
    if (val > 255 )
      val = 255;

    //take user input :
    //char inputByte = Serial.read(); // returns a 8 bit char but will take into account the enter charachter , we can ignore that eitheri by an if statement and check each charachter
    //uint8_t val = inputByte - '0';
    Serial.println("received byte = ");
    Serial.println(val);
    UpdateShiftRegister(val);
    Serial.println("led value = : %d");
    Serial.println(leds);
    
  }
}

void UpdateShiftRegister(uint8_t value)
{
  leds = value & 0xFF ;
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, leds);
  digitalWrite(latchPin,HIGH);
}

void cascadingLeds()
{
  for(int i = 0; i < 8; i++)
  {
    bitSet(leds,i);
    UpdateShiftRegister(leds);
    delay(500);
  }
}

void BinaryCounter()
{
  for(int i = 0; i < 255; i++)
  {
    UpdateShiftRegister(i);
    delay(500);
  } 
}

