#define ledPin 35

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);

}

void loop() {
  digitalWrite(ledPin, HIGH);
  Serial.println("LED is ON");
  delay(100);

  digitalWrite(ledPin, LOW);
  Serial.println("LED is LOW");
  delay(100);
}
