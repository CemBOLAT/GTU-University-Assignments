int oeration;
int counter = 0;

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
    case 49:
      digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
      break;
    case 50:
      digitalWrite(LED_BUILTIN, LOW);
      delay(1000);
      break;
    case 51:
      counter = 0;
      while (counter++ <= 2)
      {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(1000);
        digitalWrite(LED_BUILTIN, LOW);
        delay(1000);
      }
      break;
    case 52:
      int sqr = 0;
      sqr = Serial.parseInt();
      Serial.println();
      Serial.println(sqr * sqr,DEC);
      break;
    }
  }
  delay(200);
}
