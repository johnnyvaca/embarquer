#include <Bounce2.h>
#include <stdlib.h>




int ledEtat_1 = LOW;
int ledEtat_2 = LOW;
int ledEtat_3 = LOW;
int ledEtat_4 = LOW;
int compteur_1 = 0;
int compteur_2 = 0;
int compteur_3 = 0;
int compteur_4 = 0;
int ledB = 2;
int ledJ = 3;
int ledR = 4;
int ledV = 5;

//21 notes
int buzzeur = 6;
Bounce cmdB = Bounce(); // Instantiate a Bounce object
Bounce cmdJ = Bounce(); // Instantiate a Bounce object
Bounce cmdR = Bounce(); // Instantiate a Bounce object
Bounce cmdV = Bounce(); // Instantiate a Bounce object


int haribo[] = {164,0,164, 70,185,164, 0 ,164, 70,164, 0 ,164, 70,185,164, 0 ,164, 70};
int pause[] =  {900,20000,900,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200};
int  noteB  = 329;
int  noteJ  = 261;
int  noteR  = 220;
int  noteV  = 164;
int  erreur = 65;

const int notesClairLune[] = {262, 262, 262, 294, 330, 294, 262, 330, 294, 294, 262 } ;
const int dureeClairLune[] = {400, 400, 400, 400, 800, 800, 400, 400, 400, 400, 1200 };

// this is america childish gambino
void setup() {

  pinMode(buzzeur, OUTPUT);
  cmdB.attach(A2,INPUT_PULLUP); // attach the debouncer to a pin with INPUT_PULLUP mode
  cmdB.interval(25); // Use a debounce interval of 25 milliseconds

  cmdJ.attach(A3,INPUT_PULLUP); // attach the debouncer to a pin with INPUT_PULLUP mode
  cmdJ.interval(25); // Use a debounce interval of 25 milliseconds
  
  cmdR.attach(A4,INPUT_PULLUP); // attach the debouncer to a pin with INPUT_PULLUP mode
  cmdR.interval(25); // Use a debounce interval of 25 milliseconds

  cmdV.attach(A5,INPUT_PULLUP); // attach the debouncer to a pin with INPUT_PULLUP mode
  cmdV.interval(25); // Use a debounce interval of 25 milliseconds




  pinMode(ledB,OUTPUT); // Led Bleu
  pinMode(ledJ,OUTPUT); // Led Jaune
  pinMode(ledR,OUTPUT); // Led Rouge
  pinMode(ledV,OUTPUT); // Led Vert
  digitalWrite(ledB,ledEtat_1); // apply LED state
  digitalWrite(ledJ,ledEtat_2); // apply LED state
  digitalWrite(ledR,ledEtat_3); // apply LED state
  digitalWrite(ledV,ledEtat_4); // apply LED state

  Serial.begin(9600);         // Set communication rate to 9600 bauds  





}

void loop() {
  // put your main code here, to run repeatedly:

   cmdB.update();          // Update the Bounce instance
   cmdJ.update();          // Update the Bounce instance
   cmdR.update();          // Update the Bounce instance
   cmdV.update();          // Update the Bounce instance




   if (cmdB.fell()) {      // Call code if button transitions from HIGH to LOW


    if(compteur_1 == 0){

           ledEtat_1 = !ledEtat_1;    // Toggle LED state
    // digitalWrite(ledB,ledEtat_1);  // apply new LED state
   /////////////////////

   for(int i = 0; i < 11;i++){

      int randomValue = rand() % 4 +2;
      tone(buzzeur, notesClairLune[i]); // Send 1KHz sound signal...
      digitalWrite(randomValue,HIGH);  // apply new LED state
      delay(dureeClairLune[i]);        // ...for 1 sec
      digitalWrite(randomValue,LOW);
    
    
     }
 
   noTone(buzzeur);     // Stop sound...
///////////////
     ledEtat_1 = !ledEtat_1;    // Toggle LED state
     digitalWrite(ledB,ledEtat_1);
    }
    else{
     ledEtat_1 = !ledEtat_1;    // Toggle LED state
     digitalWrite(ledB,ledEtat_1);  // apply new LED state

     delay(3000);
     ledEtat_1 = !ledEtat_1;    // Toggle LED state
     digitalWrite(ledB,ledEtat_1);
     }  
     
     
     compteur_1++;
     
     //Transmission for button 1
     Serial.print("Le bouton 1 a été appuyé ");
     Serial.print(compteur_1,DEC);
     Serial.println(" fois");
   }







   
      if (cmdJ.fell()) {      // Call code if button transitions from HIGH to LOW
   ledEtat_2 = !ledEtat_2;    // Toggle LED state
     digitalWrite(ledJ,ledEtat_2);  // apply new LED state
     compteur_2++;
     
     //Transmission for button 2
     Serial.print("Le bouton 2 a été appuyé ");
     Serial.print(compteur_2,DEC);
     Serial.println(" fois");
      delay(3000);
          ledEtat_2 = !ledEtat_2;    // Toggle LED state
             digitalWrite(ledJ,ledEtat_2);  // apply new LED state
     
   }
      if (cmdR.fell()) {      // Call code if button transitions from HIGH to LOW
         ledEtat_3 = !ledEtat_3;    // Toggle LED state    
     digitalWrite(ledR,ledEtat_3);  // apply new LED state
     compteur_3++;
   
     //Transmission for button 3
     Serial.print("Le bouton 3 a été appuyé ");
     Serial.print(compteur_3,DEC);
     Serial.println(" fois");
      delay(3000);
      ledEtat_3 = !ledEtat_3;    // Toggle LED state
           digitalWrite(ledR,ledEtat_3);  // apply new LED state
     
   }
      if (cmdV.fell()) {      // Call code if button transitions from HIGH to LOW
           ledEtat_4 = !ledEtat_4;    // Toggle LED state
     digitalWrite(ledV,ledEtat_4);  // apply new LED state
     compteur_4++;
     
     //Transmission for button 4
     Serial.print("Le bouton 4 a été appuyé ");
     Serial.print(compteur_4,DEC);
     Serial.println(" fois");
      delay(3000);
      ledEtat_4 = !ledEtat_4;    // Toggle LED state
           digitalWrite(ledV,ledEtat_4);  // apply new LED state
   }





   

}
