#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

int screenWidth, screenHeight;
const int cellWidth = 30;
const int cellHeight = 20;
int charXWidth = 0;
int charOWidth = 0;

const int refreshRate = 60;
const int refreshDelay = 100/refreshRate;
bool boardNeedsUpdate = true;

bool isPlayer1 = true;

char board[3][3] ={
  {' ', ' ', 'O'},
  {'X', ' ', ' '},
  {' ', 'X', 'O'}
};

void setup() {
  Serial.begin(9600);
  Serial.println("Enter row and column numbers separated by space:");
  // put your setup code here, to run once:
  u8g2.begin();
  u8g2.clearBuffer();	
  u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  //u8g2.setFont(u8g2_font_6x10_tf );
  screenHeight = u8g2.getHeight();
  screenWidth = u8g2.getWidth();
  charXWidth = u8g2.getStrWidth("X");
  charOWidth = u8g2.getStrWidth("O");
}

void drawBoard()
{
  //draw Horizontal Lines
  u8g2.drawLine(0, 0, 90, 0);
  u8g2.drawLine(0, 20, 90, 20);
  u8g2.drawLine(0, 40, 90, 40);
  u8g2.drawLine(0, 60, 90, 60);
  // draw Vertical Lines
  u8g2.drawLine(0, 0, 0, 60);
  u8g2.drawLine(30, 0, 30, 60);
  u8g2.drawLine(60, 0, 60, 60);
  u8g2.drawLine(90, 0, 90, 60);

  for(int i = 0; i < 3; i++)
  {
    for(int j=0; j <3; j++)
    {
      int strWidth = charXWidth;
      char ch = ' ';
      if(board[i][j] == 'X')
      {
         strWidth = charXWidth;
         ch = 'X';
      }
      else if(board[i][j] == 'O')
      {
        strWidth = charOWidth;
        ch = 'O';
      }
      else
      {
        ch =' ';
      }

      int xPos = (cellWidth - strWidth)/2 + j *  cellWidth;
      int yPos = cellHeight-((cellHeight-u8g2.getAscent())/2) + i * cellHeight;
      char str[2] = {ch, '\0'};
      u8g2.drawStr(xPos,yPos, str);    
    }
  }
}

void takeInput()
{
  char cell = ' ';
  if(isPlayer1)
    cell = 'X';
  else
    cell = 'O';
  
  int row = Serial.parseInt();
  int col = Serial.parseInt();

  board[row][col] = cell;
  
  isPlayer1 != isPlayer1;
}
void loop() {
  // put your main code here, to run repeatedly:

  // if(boardNeedsUpdate)
  // {
    u8g2.clearBuffer();
    takeInput();
    drawBoard();
    u8g2.drawStr(95,15,"Plr 1");
    u8g2.drawStr(95,35,"Plr 2");

    u8g2.sendBuffer();
    
    //u8g2.setCursor(90, screenHeight / 2);
    
    //boardNeedsUpdate = false;
  // }  

  
  
}
