char  operation;
  
void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if (Serial.available() > 0)
  {
    operation = Serial.read();
    Serial.flush();
    switch (operation)
    {
    case '1':
      digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
      break;
    case '2':
      digitalWrite(LED_BUILTIN, LOW);
      delay(1000);
      break;
    case '3':
      int counter = 0;
      while (counter++ <= 2)
      {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(1000);
        digitalWrite(LED_BUILTIN, LOW);
        delay(1000);
        //Serial.println(counter);
      }
      break;
    }
    case '4':
      int sqr = 0;
      sqr = Serial.parseInt();
      Serial.println(sqr * sqr);
  }
  delay(200);
}