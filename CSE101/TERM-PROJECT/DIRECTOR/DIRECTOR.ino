//#include <Adafruit_LiquidCrystal.h>
#include <SoftwareSerial.h>

//Adafruit_LiquidCrystal lcd_1(0);

char	current_player = 'X';
char	table[9] = {' ', ' ', ' ',
                    ' ', ' ', ' ',
                    ' ', ' ', ' ',};
int att = 0;
int	isGameOver = true;
int	send = 1;
int	port;
int winner_pick[8][3] = {
                {0,2,1},
						    {3,4,5},
  						  {6,7,8},
  						  {0,3,6},
  						  {2,4,7},
  						  {1,5,8},
					      {0,4,8},
						    {1,4,6}};
#define TOP_LEFT 0
#define TOP_MID 1
#define TOP_RIGHT 2

#define MID_LEFT 3
#define MID_MID 4
#define MID_RIGHT 5

#define BOTTOM_LEFT 6
#define BOTTOM_MID 7
#define BOTTOM_RIGHT 8

void setup()
{
  Serial.begin(9600);
 //lcd_1.begin(16, 2);
  //lcd_1.setCursor(1,0);
  //lcd_1.print("WELCOME TO XOX");
  
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);

  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);

  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
}


int f_win_check()
{
  int i = 0;
  while (i < 8)
  {
    if (table[winner_pick[i][0]] == table[winner_pick[i][1]] &&
        table[winner_pick[i][1]] == table[winner_pick[i][2]] &&
        table[winner_pick[i][1]] != ' ')
      return (1);
    i++;
  }
    return (0);
}
int	f_digital_read_check()
{
  int i = 2;
  while(i <= 10)
  {
    if (digitalRead(i))
    {
      return i;
    }    
    i++;
  }
  return (0);                
}

char f_next_player(char current_player)
{
  if (current_player == 'X')
    return ('O');
  return ('X');
}

void	f_clear_table()
{
  for (int i = 0; i <= 8; i++)
    table[i] = ' ';
}
void reset_game()
{
  att = 0;
  Serial.println("");
  Serial.println(33,DEC);
  /*
  lcd_1.clear();
  lcd_1.print("PLAYER ");
  lcd_1.print(current_player);
  lcd_1.setCursor(1,1);
  lcd_1.print("Game RESET");
  lcd_1.setCursor(1,0);*/
  f_clear_table();
}

void loop()
{
  while (isGameOver)
  {
    int i = f_digital_read_check(); 

     if (i)
    {/*
      lcd_1.clear();
      lcd_1.print("PLAYER ");
      lcd_1.print(current_player);
      */
      if (i == 4 && table[2] == ' ')
      {
        att++;
        Serial.print(3,DEC);
 		    Serial.println("");
         if (current_player == 'X')
            Serial.println(11,DEC);
       	else
            Serial.println(22,DEC);
         table[2] = current_player;
         if (f_win_check())
        {
          /*
          lcd_1.clear();
          lcd_1.print("PLAYER ");
          lcd_1.print(current_player);
          lcd_1.setCursor(1,1);
          lcd_1.print("WIN THE GAME");
          */
                    reset_game();

          isGameOver = false;
        }
        current_player = f_next_player(current_player);
        delay(100);
      }
      else if (i == 3 && table[1] == ' ')
      {
        att++;
        Serial.print(4,DEC);
 		    Serial.println("");
        if (current_player == 'X')
          Serial.println(11,DEC);
       	else
          Serial.println(22,DEC);
        table[1] = current_player;
        if (f_win_check())
        {
          /*
          lcd_1.clear();
          lcd_1.print("PLAYER ");
          lcd_1.print(current_player);
          lcd_1.setCursor(1,1);
          lcd_1.print("WIN THE GAME");
          */
          reset_game();
          isGameOver = false;
        }
        current_player = f_next_player(current_player);
        delay(100);
      }
      else if (table[i - 2] == ' ' && i != 4 && i != 3)
      {
        att++;
        Serial.print(i,DEC);
 		    Serial.println("");
        if (current_player == 'X')
            Serial.println(11,DEC);
       	else
            Serial.println(22,DEC);
        table[i - 2] = current_player;
        if (f_win_check())
        {
          /*
          lcd_1.clear();
          lcd_1.print("PLAYER ");
          lcd_1.print(current_player);
          lcd_1.setCursor(1,1);
          lcd_1.print("WIN THE GAME");
          */
          isGameOver = false;
          delay (2000);
          //reset_game();
        }
        current_player = f_next_player(current_player);
      }
    }
    if (att == 9 && isGameOver == true)
    {
      /*
       lcd_1.clear();
       lcd_1.print("ITS DRAW");
       */
       delay(1000);
       reset_game();
       isGameOver = false;
       att = 0;
    }
    i = 0;
    //delay(100);
  }
  //isGameOver = true;
  delay(1000);
}