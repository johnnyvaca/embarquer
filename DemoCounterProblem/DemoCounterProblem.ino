#include <Bounce2.h>

// Project: DemoCounterProblem
// Author : Raphaël Favre
// Date   : 08.09.19
// Version: 1.0
// Description: demonstrate that "digitalRead()" can't be used to count the number of time a button is pressed


int counter = 0;
int Port8Value = HIGH;

void setup() {
    
  pinMode(8,INPUT_PULLUP);
  
  Serial.begin(9600);

}

void loop() {

  Port8Value = digitalRead(8);
  if (Port8Value == LOW){
    if (Port8Value == HIGH){
    counter++;
    Serial.print("Nombre de fois que le bouton a été appuyé: ");
    Serial.println(counter,DEC);
    }
  }
  delay(25);
}
