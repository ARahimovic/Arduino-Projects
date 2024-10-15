#define CALIBRATING

const int dataPin  = 2;
const int latchPin = 3;
const int clockPin = 4; 
const int ldrPin = A5;
//we have 8 bit led
uint8_t leds = 0;


#ifdef CALIBRATING
  int minVal = 1023;
  int maxVal = 0;
  unsigned long calibrationTime = 20000; // 5 seconds
  unsigned long startTime = 0; 
  bool isCalibrated = false;
#endif

void setup()
{
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  
  Serial.begin(9600);
  while(!Serial);
  UpdateShiftRegister(0);

  #ifdef CALIBRATING 
    startTime = millis(); // get current Time
  #endif
}

void loop()
{
  // this is a 10 bit ADC, gives a value between 0 - 1023
  int ldrReading = analogRead(ldrPin);

  #ifdef CALIBRATING
    if(! isCalibrated)
    {
      calibratingValues(ldrReading);
      unsigned long currentTime = millis();
      if( (currentTime - startTime) > calibrationTime)
      {
      isCalibrated = true;
          Serial.println("Calibration complete.");
      }
      else
      {
        // Provide feedback during calibration
          Serial.print("Calibrating... Min: ");
          Serial.print(minVal);
          Serial.print(" Max: ");
          Serial.println(maxVal);
        //otherwise continue calibrating
        return;   
      }
      
    }
    
    ldrReading = map(ldrReading, minVal, maxVal, 0, 255);
  #endif
  
  
  //the shift register can get value between 0 - 255
  UpdateShiftRegister(ldrReading);
  
  Serial.print("LDR value : ");
  Serial.println(ldrReading);
  delay(100);

}

void UpdateShiftRegister(uint8_t value)
{
  leds = value & 0xFF ;
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, leds);
  digitalWrite(latchPin,HIGH);
}

#ifdef CALIBRATING
  void calibratingValues(int reading)
  {
    if(reading < minVal)
      minVal = reading;
    
    if(reading > maxVal)
      maxVal = reading;
    
  }
#endif