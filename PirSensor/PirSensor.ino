const int sensorPin = 2;
const int ledPin = 5;

void setup()
{
  pinMode(sensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int reading = digitalRead(sensorPin);
  if(reading)
  {
    Serial.println("Detected movement");
    digitalWrite(ledPin, HIGH);
  }  
  else
  {
    digitalWrite(ledPin, LOW);
  }
}