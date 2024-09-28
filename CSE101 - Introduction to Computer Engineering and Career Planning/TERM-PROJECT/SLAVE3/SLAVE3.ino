int lamb;
int player;
#define BOTTOM_LEFT_CORNER 2
#define BOTTOM_LEFT_2 3
#define BOTTOM_LEFT_MID 4

#define BOTTOM_RIGHT_MID 9
#define BOTTOM_RIGHT_CORNER 8
#define BOTTOM_RIGHT_3 10

#define BOTTOM_MID_1 6
#define BOTTOM_MID_MID 7
#define BOTTOM_MID_CORNER 5

void setup()
{ 
  Serial.begin(9600);
  pinMode(BOTTOM_LEFT_CORNER, OUTPUT);
  pinMode(BOTTOM_LEFT_2, OUTPUT);
  pinMode(BOTTOM_LEFT_MID, OUTPUT);
  pinMode(BOTTOM_RIGHT_MID, OUTPUT);
  pinMode(BOTTOM_RIGHT_CORNER, OUTPUT);
  pinMode(BOTTOM_RIGHT_3, OUTPUT);
  pinMode(BOTTOM_MID_1, OUTPUT);
  pinMode(BOTTOM_MID_MID, OUTPUT);
  pinMode(BOTTOM_MID_CORNER, OUTPUT);
}


void loop()
{
if (Serial.available() > 0)
  {
    lamb = Serial.parseInt();
    Serial.flush();
    if (lamb == 8)
    {
      player = Serial.parseInt();
      //Serial.println(player);
      if (player == 11)
      {
         digitalWrite(BOTTOM_LEFT_MID, HIGH);
         digitalWrite(BOTTOM_LEFT_CORNER, HIGH); 
      }
      else
      {
         digitalWrite(BOTTOM_LEFT_CORNER, HIGH);
         digitalWrite(BOTTOM_LEFT_2, HIGH); 
      }
    }
    else if (lamb == 9)
    {
      player = Serial.parseInt();
      //Serial.println(player);
      if (player == 11)
      {
         digitalWrite(BOTTOM_MID_CORNER, HIGH);
         digitalWrite(BOTTOM_MID_MID, HIGH); 
      }
      else
      {
         digitalWrite(BOTTOM_MID_CORNER, HIGH);
         digitalWrite(BOTTOM_MID_1, HIGH); 
      }
    }
 	else if (lamb == 10)
    {
      player = Serial.parseInt();
      //Serial.println(player);
      if (player == 11)
      {
         digitalWrite(BOTTOM_RIGHT_CORNER, HIGH);
         digitalWrite(BOTTOM_RIGHT_MID, HIGH); 
      }
      else
      {
         digitalWrite(BOTTOM_RIGHT_CORNER, HIGH);
         digitalWrite(BOTTOM_RIGHT_3, HIGH); 
      }
    }
	else if (lamb == 33)
    {
         digitalWrite(BOTTOM_LEFT_CORNER, LOW);
         digitalWrite(BOTTOM_LEFT_2, LOW); 
         digitalWrite(BOTTOM_LEFT_MID, LOW);
         digitalWrite(BOTTOM_MID_1, LOW); 
         digitalWrite(BOTTOM_MID_MID, LOW);
         digitalWrite(BOTTOM_MID_CORNER, LOW); 
         digitalWrite(BOTTOM_RIGHT_MID, LOW);
         digitalWrite(BOTTOM_RIGHT_CORNER, LOW); 
         digitalWrite(BOTTOM_RIGHT_3, LOW); 
    }
  }
  //delay (1000);
}