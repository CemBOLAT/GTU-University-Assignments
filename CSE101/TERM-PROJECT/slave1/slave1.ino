// C++ code

int lamb;
int player;
#define TOP_LEFT_CORVER 2
#define TOP_LEFT_MID 4
#define TOP_LEFT_3 3

#define TOP_MID_CORVER 5
#define TOP_MID_MID 7
#define TOP_MID_3 6

#define TOP_RIGHT_CORVER 8
#define TOP_RIGHT_MID 10
#define TOP_RIGHT_3 9

void setup()
{
  Serial.begin(9600);
  pinMode(TOP_LEFT_CORVER, OUTPUT);
  pinMode(TOP_LEFT_MID, OUTPUT);
  pinMode(TOP_LEFT_3, OUTPUT);
  pinMode(TOP_MID_CORVER, OUTPUT);
  pinMode(TOP_MID_MID, OUTPUT);
  pinMode(TOP_MID_3, OUTPUT);
  pinMode(TOP_RIGHT_CORVER, OUTPUT);
  pinMode(TOP_RIGHT_MID, OUTPUT);
  pinMode(TOP_RIGHT_3, OUTPUT);
}

void loop()
{
  if (Serial.available() > 0)
  {
    lamb = Serial.parseInt();
    Serial.flush();
    //Serial.println(player);
    if (lamb == 2)
    {
      while (Serial.available() < 0);
      
      player = Serial.parseInt();
      if (player == 11)
      {
         digitalWrite(TOP_LEFT_CORVER, HIGH);
         digitalWrite(TOP_LEFT_MID, HIGH); 
      }
      else
      {
         digitalWrite(TOP_LEFT_CORVER, HIGH);
         digitalWrite(TOP_LEFT_3, HIGH); 
      }
    }
    else if (lamb == 3)
    {
      while (Serial.available() < 0);
      
      player = Serial.parseInt();
      if (player == 11)
      {
         digitalWrite(TOP_MID_CORVER, HIGH);
         digitalWrite(TOP_MID_MID, HIGH); 
      }
      else
      {
         digitalWrite(TOP_MID_CORVER, HIGH);
         digitalWrite(TOP_MID_3, HIGH); 
      }
    }
 	else if (lamb == 4)
    {
      while (Serial.available() < 0)
       
      player = Serial.parseInt();
      //Serial.println(player);
      if (player != 11) // GARİP ŞEYLER OLUYOR
      {
         digitalWrite(TOP_RIGHT_CORVER, HIGH);
         digitalWrite(TOP_RIGHT_MID, HIGH); 
      }
      else
      {
         digitalWrite(TOP_RIGHT_CORVER, HIGH);
         digitalWrite(TOP_RIGHT_3, HIGH); 
      }
    }
    else if (lamb == 33)
    {
         digitalWrite(TOP_RIGHT_CORVER, LOW);
         digitalWrite(TOP_RIGHT_MID, LOW); 
         digitalWrite(TOP_RIGHT_3, LOW);
         digitalWrite(TOP_MID_CORVER, LOW); 
         digitalWrite(TOP_MID_MID, LOW);
         digitalWrite(TOP_MID_3, LOW); 
         digitalWrite(TOP_LEFT_CORVER, LOW);
         digitalWrite(TOP_LEFT_MID, LOW); 
         digitalWrite(TOP_LEFT_3, LOW); 
    }
  }
  /*
  int i = 2;
  while (i <= 10)
  {
      digitalWrite(i,HIGH);
    delay(1000);
    digitalWrite(i,LOW);
    i++;
  }
  */
  /*
  digitalWrite(TOP_MID_CORVER,HIGH);
  digitalWrite(TOP_MID_MID,HIGH);
  digitalWrite(TOP_LEFT_CORVER,HIGH);
  digitalWrite(TOP_LEFT_MID,HIGH);
  digitalWrite(TOP_RIGHT_CORVER,HIGH);
  digitalWrite(TOP_RIGHT_MID,HIGH);
  */
}