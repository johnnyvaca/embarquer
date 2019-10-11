void setup() 
{
  int cmdY = 8;
  int cmdB = 9;
  int led1 = 5;
  int led2 = 4;
  pinMode(cmdY,INPUT);
  pinMode(cmdB,INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() 
{
  int cmdY = 8;
  int cmdB = 9;
  
  int led1 = 5;
  int led2 = 4;
  
  int readY;
  int readB;
  
  readY = digitalRead(cmdY);
  readB = digitalRead(cmdB);
  
  if(readY == HIGH)
  {
    digitalWrite(led1, HIGH);
  }
  else
  {
    digitalWrite(led1, LOW);
  }
  
  if(readB == LOW)
  {
    digitalWrite(led2, HIGH);
  }
  else
  {
    digitalWrite(led2, LOW);
    
  }

}
