#define commonAnode

const int redPin = 3;
const int greenPin = 5;
const int bluePin = 6;

void setup() {
  // put your setup code here, to run once:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

 setColor(255,0,0); // red
 delay(500);
 setColor(0,255,0); // green
 delay(500);
 setColor(0,0,255); // blue
 delay(500); 

  Serial.begin(9600);
}

void loop() {
  setColor(255,0,0); // red
  delay(500);
  setColor(0,255,0); // green
  delay(500);
  setColor(0,0,255); // blue
  delay(500);
  setColor(255,255,0);
  delay(500);
  setColor(255,255,255);
  delay(500);
  setColor(90,90,90);
  delay(500);

}

void setColor(int red, int green, int blue)
{
  #ifdef commonAnode
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif

   if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255) {
    Serial.println("Error in RGB value. Values must be between 0 and 255.");
    return; // Exit the function if the values are invalid
  }
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
  Serial.println("calling func");
}

