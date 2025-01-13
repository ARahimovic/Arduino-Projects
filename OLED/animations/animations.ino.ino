/**
We will use the u8G2 library as it is the one compatible with our OLED display microcontroller (SH1106)
**/

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

const int animationDelay = 100;
int currentTime = 0;
int previousTime = 0;
int startCol = 128;
int offset = 0;

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup(void) {
  u8g2.begin();
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  int h = u8g2.getHeight();
  int w = u8g2.getWidth();
}

void loop(void) {

  currentTime = millis();
  if ((currentTime - previousTime) > animationDelay)
  {
    previousTime = currentTime;
    u8g2.clearBuffer();
    u8g2.drawStr(startCol-offset, 32, "scrollingText"); // scroll to the left
   
    offset += 2;
    if((startCol - offset) <= 0)
    {
      startCol = 128;
      offset = 0;
    }
  
  u8g2.sendBuffer();			
      
  }
 
}

