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

void wrapAround(const char *str, int startRow);
void smoothExitRentry(const char *str, int startRow);
void exitSuddenRentry(const char *str, int startRow);

const int animationDelay = 100;
int currentTime = 0;
int previousTime = 0;
int screenHeight = 0;
int screenWidth = 0;

// int startCol = 128;
// int offset = 0;

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup(void) {
  u8g2.begin();
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  screenHeight = u8g2.getHeight();
  screenWidth = u8g2.getWidth();
}

void loop(void) {

  currentTime = millis();
  if ((currentTime - previousTime) > animationDelay)
  {
    previousTime = currentTime;
    u8g2.clearBuffer();
    /*put the animation methods here*/
    exitSuddenRentry("SuddenEntry", 20);
    smoothExitRentry("SmoothRentry", 30);
    wrapAround("wrapAround", 40);
  u8g2.sendBuffer();			
      
  }
 
}


void smoothExitRentry(const char *str, int startRow)
{
  static int startCol = screenWidth-1;
  static int offset = 0;

  u8g2.drawStr(startCol-offset, startRow, str); // scroll to the left
  int length = u8g2.getStrWidth(str);
  offset += 2;
  if((startCol - offset + length) <= 0)
  {
    startCol = 128;
    offset = 0;
  }
}

void exitSuddenRentry(const char *str, int startRow)
{
  static int startCol = screenWidth-1;
  static int offset = 0;

  u8g2.drawStr(startCol-offset, startRow, str); // scroll to the left
   
  offset += 2;
  if((startCol - offset) <= 0)
  {
    startCol = 128;
    offset = 0;
  }
}

void wrapAround(const char *str, int startRow)
{
  static int startCol = screenWidth-1;
  static int offset = 0;
  int textWidth = u8g2.getStrWidth(str);
  int currentPos = startCol - offset;

  u8g2.drawStr(currentPos, startRow, str); // scroll to the left

  if(currentPos < 0 )
  {
    int wrapWidth = -currentPos;
    if(wrapWidth > textWidth)
      wrapWidth = textWidth;

    String text = String(str);
    String subStr = text.substring(0, wrapWidth);
    u8g2.drawStr(screenWidth + currentPos, startRow, subStr.c_str()); // scroll to the left
  }

  offset += 2;
  if(currentPos <= - textWidth)
  {
    startCol = screenWidth - 1 ;
    offset = textWidth + 2;
  }

}

