
// Project: Bounce_Library_Test
// Author : Raphaël Favre
// Date   : 08.09.19
// Version: 1.0
// Description: Toggle LEDs by pressing buttons using the Bounce2 library
//  
// Include the Bounce2 library found here :
// https://github.com/thomasfredericks/Bounce2
#include <Bounce2.h>

int ledState_1 = LOW;
int ledState_2 = LOW;
int counter_1 = 0;
int counter_2 = 0;


Bounce debouncer_1 = Bounce(); // Instantiate a Bounce object
Bounce debouncer_2 = Bounce(); // Instantiate a Bounce object

void setup() {
  
  debouncer_1.attach(8,INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
  debouncer_1.interval(25); // Use a debounce interval of 25 milliseconds

  debouncer_2.attach(9,INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
  debouncer_2.interval(25); // Use a debounce interval of 25 milliseconds
    
  pinMode(2,OUTPUT); // Setup the LED
  pinMode(3,OUTPUT); // Setup the LED
  digitalWrite(2,ledState_1); // Apply LED state
  digitalWrite(3,ledState_2); // Apply LED state

  Serial.begin(9600);         // Set communication rate to 9600 bauds     
}

void loop() {

   debouncer_1.update();          // Update the Bounce instance
   debouncer_2.update();          // Update the Bounce instance
   
   if (debouncer_1.rose()) {      // Call code if button transitions from HIGH to LOW
     ledState_1 = !ledState_1;    // Toggle LED state
     digitalWrite(2,ledState_1);  // Apply new LED state
     counter_1++;
     
     //Transmission for button 1
     Serial.print("Le bouton 1 a été appuyé ");
     Serial.print(counter_1,DEC);
     Serial.println(" fois");
     
   }
   
   if (debouncer_2.fell()) {      // Call code if button transitions from LOW to HIGH
     ledState_2 = !ledState_2;    // Toggle LED state
     digitalWrite(3,ledState_2);  // Apply new LED state
     counter_2++;                 

     //Transmission for button 2 
     Serial.print("Le bouton 2 a été appuyé ");
     Serial.print(counter_2,DEC);
     Serial.println(" fois");
   }
   
}
