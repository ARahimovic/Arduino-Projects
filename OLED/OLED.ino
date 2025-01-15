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


int h, w;


U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);




void setup(void) {
  u8g2.begin();
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  h = u8g2.getHeight();
  w = u8g2.getWidth();
}

void loop(void) {

  u8g2.clearBuffer();
  
  //draw 2 diagonal lines
  u8g2.drawLine(0,0, w -1, h -1);
  u8g2.drawLine(w - 1, 0, 0, h - 1);
  //draw center lines
  u8g2.drawLine((w - 1)/2, 0, (w - 1)/2, h - 1);
  u8g2.drawLine(0, (h - 1)/2, (w - 1), (h - 1)/2);

  u8g2.setCursor(w/2, h/2);
  u8g2.print("Hello World");

  u8g2.sendBuffer();  
      
  }


