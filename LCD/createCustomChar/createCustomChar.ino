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
  digitalWrite(LCD_brightnessPin, HIGH); // Initial brightness
  
  //create a custom char, need to create it before lcd.begin
  byte smiley[8] = 
  {
    0b00000000,
    0b00010001,
    0b00000000,
    0b00010001,
    0b00001110,
    0b00000000,
    0b00000000,
    0b00000000,
    };
  lcd.createChar(0, smiley);
  
  lcd.begin(columns, rows);
  lcd.setCursor(0,0);
  
  
 
  lcd.write(byte(0));
}

void loop() {
  
}
