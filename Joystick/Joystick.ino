const int joystickPin = 8;
const int readDelay = 300;
int previousReadTime = 0;


void setup() {
  Serial.begin(9600);
  pinMode(joystickPin, INPUT_PULLUP);
}

void loop() {
if(millis() - previousReadTime > readDelay)
{
  previousReadTime = millis();
  int joyX = analogRead(A0);
  int joyY = analogRead(A1);

  int mappedX = map(joyX, 0 , 1023, -1, 1);
  int mappedY = map(joyY, 0 , 1023, -1, 1);
  //Serial.println(joyX);
  Serial.println(mappedX);
  //Serial.println(joyY);


}

}
