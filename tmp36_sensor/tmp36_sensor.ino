const int tempPin = A0;
const int referenceVoltage = 5; // we using 5V

void setup()
{
  Serial.begin(9600);
  while(!Serial);
  Serial.println("System booted");
}

void loop()
{
  //read analog value
  int reading = analogRead(tempPin);
  //convert the reading to voltage
  float voltage = (reading / 1024.0) * referenceVoltage;
  //convert to temperature
  float temp = (voltage - 0.5)/0.01;
  
  Serial.print("temperature : ");
  Serial.println(temp);
  
}