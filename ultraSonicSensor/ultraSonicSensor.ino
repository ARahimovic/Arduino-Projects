const int echo = 3;
const int trigger = 5; 

const int ledPins[4] = {8,9,10,11};
const int distanceThreshold[] = {40,30,20,10};

void setup() {

    pinMode(trigger, OUTPUT);
    pinMode(echo, INPUT);
    
    for(int i = 0; i < 4; i++)
    {
      pinMode(ledPins[i], OUTPUT);
    }

    for(int i = 0; i < 4; i++)
    {
      digitalWrite(ledPins[i], LOW);
    }

    Serial.begin(9600);

}

void loop() {
  //clear the trigger first
  digitalWrite(trigger, LOW);
  delay(2);
  //set the trigger for 10 ms
  digitalWrite(trigger, HIGH);
  delay(10);
  digitalWrite(trigger, LOW);

  //read the time of the signal received : it is the time for the sound to go and come back
  long duration = pulseIn(echo, HIGH);
  // distance(cm) = speed * time ; speed of sound = 343 m/s
  float distance = 0.0343 * duration / 2; 

  Serial.print("Distance : ");
  Serial.println(distance);

  // Light up LEDs based on distance
  for(int i = 0; i < 4; i++)
    {
      if (distance < distanceThreshold[i]) 
        digitalWrite(ledPins[i], HIGH);
      if (distance > distanceThreshold[i]) 
        digitalWrite(ledPins[i], LOW);
    }
}