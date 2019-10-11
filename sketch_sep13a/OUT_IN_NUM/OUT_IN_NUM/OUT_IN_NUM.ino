void setup() {
  int l1 = 2;
  int l2 = 3;
  int l3 = 4;
  int l4 = 5;
  int s1 = 8;
  int s2 = 9;
  int s3 = 10;
  int s4 = 11;
  pinMode(l1,OUTPUT);
  pinMode(l2,OUTPUT);
  pinMode(l3,OUTPUT);
  pinMode(l4,OUTPUT);
  pinMode(s1,INPUT_PULLUP);
  pinMode(s2,INPUT_PULLUP);
  pinMode(s3,INPUT_PULLUP);
  pinMode(s4,INPUT_PULLUP);
}

void loop() {
  int l1 = 2;
  int l2 = 3;
  int l3 = 4;
  int l4 = 5;
  int s1 = 8;
  int s2 = 9;
  int s3 = 10;
  int s4 = 11;
  int r1 = digitalRead(s1);
  int r2 = digitalRead(s2);
  int r3 = digitalRead(s3);
  int r4 = digitalRead(s4);
  if(r1 == HIGH && r2 == HIGH && r3 == HIGH && r4 == HIGH)
  {
    digitalWrite(l1, LOW);
  }
  else
  {

    if((r1 == LOW )&&(r2 == HIGH && r3 == HIGH && r4 == HIGH))
    {
      digitalWrite(l1,HIGH);
      digitalWrite(l2,HIGH);
      digitalWrite(l3,LOW);
      digitalWrite(l4,LOW);
      
    }
    else
    {
            digitalWrite(l1,LOW);
      digitalWrite(l2,LOW);
            digitalWrite(l3,LOW);
      digitalWrite(l4,LOW);
    }
    
    if((r2 == LOW && r4 == LOW)&&(r1 == HIGH && r3 == HIGH))
    {
      digitalWrite(l3,HIGH);
      digitalWrite(l4,HIGH);
      digitalWrite(l1,LOW);
      digitalWrite(l2,LOW);
      
    }
    else
    {
            digitalWrite(l1,LOW);
      digitalWrite(l2,LOW);
            digitalWrite(l3,LOW);
      digitalWrite(l4,LOW);
    }


    if((r3 == LOW || r4 == LOW)&&(r1 == HIGH && r2 == HIGH))
    {
        digitalWrite(l1,HIGH);
        digitalWrite(l2,HIGH);
        delay(250);
        digitalWrite(l1,LOW);
        digitalWrite(l2,LOW);
        digitalWrite(l3,HIGH);
        delay(250);
        digitalWrite(l3,LOW);
        digitalWrite(l4,HIGH);
        delay(250);
        digitalWrite(l4,LOW);
      


      
    }
    else
    {
      digitalWrite(l1,LOW);
      digitalWrite(l2,LOW);
      digitalWrite(l3,LOW);
      digitalWrite(l4,LOW);
    }
  
  
  }


}
