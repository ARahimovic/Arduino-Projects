#include <Wire.h>                   // Include the Wire library for I2C
#include <LiquidCrystal_I2C.h>      // Include the LiquidCrystal_I2C library

// Set the I2C address (change 0x27 if necessary) and specify the dimensions (16x2 or 20x4)
LiquidCrystal_I2C lcd(0x27, 20, 4); // Change to 20, 4 if you're using a 20x4 LCD

void setup() {
  Serial.begin(9600);              // Start serial communication for debugging
  lcd.init();                       // Initialize the LCD
  lcd.backlight();                 // Turn on the backlight
 
  // Check if the LCD is initialized properly
  Serial.println("LCD Initialized Successfully!");

  lcd.setCursor(0, 0);             // Set cursor to first row, first column
  lcd.print("Hello, World!");      // Print message on the first row

  lcd.setCursor(0,3);
  lcd.print("I2C succeful ");      // Print message on the first row

}

void loop() {
  // Update the second row with a counter
  static int counter = 0;          // Static variable to hold the counter
  lcd.setCursor(0, 1);             // Set cursor to second row, first column
  lcd.print("Count: ");             // Print label for count
  lcd.print(counter);               // Print the current count
  
  delay(1000);                     // Wait for 1 second
  counter++;                       // Increment the counter

  // Clear the second row before printing the new count
  lcd.setCursor(0, 1);
  lcd.print("                ");   // Clear the second row
}
