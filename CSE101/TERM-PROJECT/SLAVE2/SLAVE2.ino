
int lamb;
int player;

#define MID_LEFT_CORNER 2
#define MID_LEFT_MID 4
#define MID_LEFT_1 3

#define MID_RIGHT_MID 10
#define MID_RIGHT_3 8
#define MID_RIGHT_CORNER 9

#define MID_MID_CORNER 5
#define MID_MID_MID 7
#define MID_MID_3 6

void setup()
{
  Serial.begin(9600);
  pinMode(MID_LEFT_1, OUTPUT);
  pinMode(MID_LEFT_MID, OUTPUT);
  pinMode(MID_LEFT_CORNER, OUTPUT);
  pinMode(MID_RIGHT_MID, OUTPUT);
  pinMode(MID_RIGHT_3, OUTPUT);
  pinMode(MID_RIGHT_CORNER, OUTPUT);
  pinMode(MID_MID_CORNER, OUTPUT);
  pinMode(MID_MID_MID, OUTPUT);
  pinMode(MID_MID_3, OUTPUT);
}

void loop()
{
  if (Serial.available() > 0)
  {
    lamb = Serial.parseInt();
    Serial.flush();
    if (lamb == 5)
    {
      player = Serial.parseInt();
      //Serial.println(player);
      if (player == 11)
      {
         digitalWrite(MID_LEFT_MID, HIGH);
         digitalWrite(MID_LEFT_CORNER, HIGH); 
      }
      else
      {
         digitalWrite(MID_LEFT_CORNER, HIGH);
         digitalWrite(MID_LEFT_1, HIGH); 
      }
    }
    else if (lamb == 6)
    {
      player = Serial.parseInt();
      //Serial.println(player);
      if (player == 11)
      {
         digitalWrite(MID_MID_CORNER, HIGH);
         digitalWrite(MID_MID_MID, HIGH); 
      }
      else
      {
         digitalWrite(MID_MID_CORNER, HIGH);
         digitalWrite(MID_MID_3, HIGH); 
      }
    }
 	else if (lamb == 7)
    {
      player = Serial.parseInt();
      //Serial.println(player);
      if (player == 11)
      {
         digitalWrite(MID_RIGHT_3, HIGH);
         digitalWrite(MID_RIGHT_MID, HIGH); 
      }
      else
      {
         digitalWrite(MID_RIGHT_CORNER, HIGH);
         digitalWrite(MID_RIGHT_3, HIGH); 
      }
    }
    else if (lamb == 33)
    {
         digitalWrite(MID_LEFT_1, LOW);
         digitalWrite(MID_LEFT_MID, LOW); 
         digitalWrite(MID_LEFT_CORNER, LOW);
         digitalWrite(MID_MID_CORNER, LOW); 
         digitalWrite(MID_MID_MID, LOW);
         digitalWrite(MID_MID_3, LOW); 
         digitalWrite(MID_RIGHT_MID, LOW);
         digitalWrite(MID_RIGHT_3, LOW); 
         digitalWrite(MID_RIGHT_CORNER, LOW); 
    }
  }
  //delay (1000);
}	