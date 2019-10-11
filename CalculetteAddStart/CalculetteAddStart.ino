
// Project: CalculetteAddStart
// Author : Raphaël Favre
// Date   : 08.09.19
// Version: 1.0
// Description: Only function displayVal is implemeted
  

/*
 * This function is designed to convert a number between 0 and 15 into binary 
 * and displayed with four LED connected to ports 2 to 5 
 * 
 * value : The input number between 0 to 15
 * No return (void) 
 */
 #include <Bounce2.h>

 int ledState_1 = LOW;
 int ledState_2 = LOW;
 int ledState_3 = LOW;
 int ledState_4 = LOW;
 int counter_1 = 0;
 int counter_2 = 0;
 int counter_3 = 0;
 int counter_4 = 0;
 Bounce debouncer_1 = Bounce();
 Bounce debouncer_2 = Bounce();
 Bounce debouncer_3 = Bounce();
 Bounce debouncer_4 = Bounce();
void displayVal(int value){
    debouncer_1.attach(8,INPUT_PULLUP);
    debouncer_2.interval(25);
    for(int i=2;i<=5;i++)digitalWrite(i,LOW);
    
    if (value >= 8)digitalWrite(5,HIGH);
    value = value%8;
    if (value >= 4)digitalWrite(4,HIGH);
    value = value%4;
    if (value >= 2)digitalWrite(3,HIGH);
    value = value%2;
    if (value >= 1)digitalWrite(2,HIGH);
}

void setup() {
  for(int i=2;i<=5;i++)pinMode(i,OUTPUT);
   
}

void loop() {

  displayVal(0);  // Example with number 9 converted into binary and displayed 
  delay(500);
  
}
