const int motorPin = 3; // PWM pin

void setup()
{
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
  while (!Serial); // Wait for serial port to connect
  Serial.println("Enter Val from 0 - 255:");
}

void loop()
{
  analogWrite(motorPin, 200);
  /*if (Serial.available())
  {
    String userInput = Serial.readStringUntil('\n'); // Read until newline
    int val = userInput.toInt(); // Convert the string to an integer

    // Input validation
    if (val < 0 || val > 255) {
      Serial.println("Invalid input. Please enter a value between 0 and 255.");
    } else {
      analogWrite(motorPin, val); // Set PWM value
      Serial.print("Current Val: ");
      Serial.println(val);
    }
  }*/
}
