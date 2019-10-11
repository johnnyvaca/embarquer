
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
void displayVal(int value){
    
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
