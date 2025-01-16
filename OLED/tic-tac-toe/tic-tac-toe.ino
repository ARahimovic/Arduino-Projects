#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

int joystickPin = 9;
int cursorX = 0;
int cursorY = 0;
const int deadzone = 300;
const int delayCursor = 100; each 100 ms , take input
int previousCursorTime = 0;

//U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

bool isGameOver = false;
bool isPlayer1 = true;

char board[3][3] ={
  {' ', ' ', ' '},
  {' ', ' ', ' '},
  {' ', ' ', ' '}
};


int screenWidth, screenHeight;
const int cellWidth = 30;
const int cellHeight = 20;
int charXWidth = 0;
int charOWidth = 0;


void updateCursorPosition()
{
  int joyX = analogRead(A0);
  int joyY = analogRead(A1);

  int mappedX = map(joyX, 0 , 1023, -1, 1);
  int mappedY = map(joyY, 0 , 1023, -1, 1);
  
  cursorX += mappedX;
  if(cursorX > 2)
    cursorX = 0;
  else if (cursorX < 0)
     cursorX = 2;

  cursorY += mappedY;
  if(cursorY > 2)
    cursorY = 0;
  else if (cursorY < 0)
     cursorY = 2;
  

}

void setup() {
  Serial.begin(9600);

  pinMode(joystickPin, INPUT_PULLUP);
  // put your setup code here, to run once:
  u8g2.begin();
  u8g2.clearBuffer();	
//  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  screenHeight = u8g2.getHeight();
  screenWidth = u8g2.getWidth();
  charXWidth = u8g2.getStrWidth("X");
  charOWidth = u8g2.getStrWidth("O");

  drawBoard();
}

void drawBoard()
{

  u8g2.firstPage(); // Start the page loop
  do {
    //Draw the grid
    for (int i = 0; i <= 3; i++) {
      u8g2.drawLine(0, i * cellHeight, 3 * cellWidth, i * cellHeight); // Horizontal lines
      u8g2.drawLine(i * cellWidth, 0, i * cellWidth, 3 * cellHeight); // Vertical lines
    }
  
    // Draw board contents
    for (int row = 0; row < 3; row++) {
      for (int col = 0; col < 3; col++) {
        char ch = board[row][col];
        if (ch != ' ') {
          int xPos = (col * cellWidth) + (cellWidth - u8g2.getStrWidth(&ch)) / 2;
          int yPos = (row * cellHeight) + cellHeight - (cellHeight - u8g2.getAscent()) / 2;
          char str[2] = {ch, '\0'};
          u8g2.drawStr(xPos, yPos, str);
        }
      }
    }
    // Display player info
    u8g2.drawStr(95, 15, "Plr 1");
    u8g2.drawStr(95, 35, "Plr 2");

  } while (u8g2.nextPage()); 

}

bool isDraw()
{
  for(int i =0; i <3; i++)
  {
    for(int j =0; j<3; j++)
    {
      if(board[i][j] == ' ')
        return false;
    }
  }
  return true;
}

bool isWin(int x, int y)
{
  //check row
  for(int i =0; i <3; i++)
  {
    if(board[i][y] != board[x][y])
      break;

    if (i == 2)
      return true;
  }

  //check column
  for(int i =0; i<3; i++)
  {
    if(board[x][i] != board[x][y])
      break;
    if(i == 2)
      return true;
  }

  //check diagonal
  if(x == y)
  {
    for(int i =0; i <3; i++)
    {
      if(board[i][i] != board[x][y])
        break;
      if(i == 2)
        return true;
    }
  }

  //check anti-diagonal
  if(x + y == 2)
  {
    for(int i =0; i <3; i++)
    {
      if(board[x][y] != board[i][2-i])
        break;
      if(i == 2)
        return true;
    }
  }
//if all checks dont work, it is not a win condition
  return false;
}

void takeInput()
{
  char cell = isPlayer1 ? 'X':'O';
  while (Serial.available()) {
    Serial.read(); // Clear any leftover characters
  }

  Serial.println("Player : enter position 1-9");
  
  if(!Serial.available()){return ;} 
  //while(!Serial.available());

 if(Serial.available()){

  char input = Serial.read();
  int pos = input -'0';
  Serial.println(pos);

  if(pos < 1 || pos > 9)
  {
    Serial.println("Invalid position! Please enter 1-9");
    return;
  }

  int row = (pos - 1)/ 3;
  int col = (pos - 1) %3;

  // Check if cell is occupied
  if (board[row][col] != ' ') {
    Serial.println("Position already taken! Try again.");
    return;
  }

  board[row][col] = cell;
  //draw the board after each input
  drawBoard();
  
  //check if there is a win or draw
  if(isWin(row, col))
  {
    drawWinBoard();
    isGameOver = true;
    return;
  }
  else if (isDraw())
  {
    drawDrawBoard();
    isGameOver = true;
    return;
  }

  isPlayer1 = !isPlayer1;

 }

}

void drawWinBoard()
{
    char *str = isPlayer1 ?"player 1 (X)" : "Player 2 (O)"; 
    u8g2.firstPage();
    do
    {
    u8g2.drawStr(0, screenHeight / 2, str);
    u8g2.drawStr(u8g2.getStrWidth(str), screenHeight / 2, " WON");

    }while (u8g2.nextPage()); 
}

void drawDrawBoard()
{
    u8g2.firstPage();
    do
    {
    u8g2.drawStr(0, screenHeight / 2, "It is a Draw");
    }while (u8g2.nextPage()); 
}

void restartGame()
{
  for(int i =0; i <3; i++)
  {
    for(int j =0; j<3; j++)
    {
      board[i][j] = ' ';
    }
  }

  isGameOver = false;
  isPlayer1 = true;

  drawBoard();
}
void loop() {
  if(isGameOver)
  {
    delay(5000);
    restartGame();
  }

  if(millis() - previousCursorTime > delayCursor)
  {
    previousCursorTime = millis();
    updateCursorPosition();
  }
  
  takeInput();

  
}
