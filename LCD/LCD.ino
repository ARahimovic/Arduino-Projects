#include <LiquidCrystal.h>

const int columns = 16;
const int rows = 2;
const int enablePin = 3;
const int rsPin = 2;
const int LCD_brightnessPin = 9; // PWM pin for backlight brightness control
const int brightnessControlPin = A5; // Analog pin for brightness control

LiquidCrystal lcd(rsPin, enablePin, 4, 5, 6, 7);

int brightnessLevel = 255;

void setup() {
  pinMode(LCD_brightnessPin, OUTPUT);
  analogWrite(LCD_brightnessPin, brightnessLevel); // Initial brightness

  lcd.begin(columns, rows);
  lcd.print("Hello World");
}

void loop() {
  // Read the brightness control value from the potentiometer
  int read = analogRead(brightnessControlPin);
  
  // Scale the analog read (0-1023) to PWM range (0-255)
  brightnessLevel = read / 4; 
  analogWrite(LCD_brightnessPin, brightnessLevel); // Adjust brightness

  // Display brightness percentage
  float percentage = brightnessLevel / 255.0 * 100;

  // Print the brightness percentage on the second row
  lcd.setCursor(0, 1);
  lcd.print("Brightness: ");
  lcd.setCursor(12, 1); // Position to display percentage

  // Print percentage with one decimal place and overwrite leftover chars
  lcd.print(percentage, 1);
  lcd.print("   "); // Clear any leftover characters
}
