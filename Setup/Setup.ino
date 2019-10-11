void setup() {
  // initialize digital pin LED_BUILTIN as an output.
    pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  
}


void loop() {

int i = 2

  while(i < 5)
  {
    digitalWrite(i, HIGH);
    delay(1000);
    digitalWrite(i, LOW);
    delay(1000);
    i++;
    printf("i = %d", i);
  }
 


}
