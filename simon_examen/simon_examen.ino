#include <Bounce2.h>
#include <stdlib.h>


int ledEtatB = LOW;
int ledEtatJ = LOW;
int ledEtatR = LOW;
int ledEtatV = LOW;
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


// int haribo[] = {164, 0, 164, 70, 185, 164, 0, 164, 70, 164, 0, 164, 70, 185, 164, 0, 164, 70};
// int pause[] = {900, 20000, 900, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200};
int noteB = 329;
int noteJ = 261;
int noteR = 220;
int noteV = 164;
int erreur = 65;

const int noteSimon[] = {noteB,noteJ,noteR,noteV};


int memorySimon[32];
int memoryJoueur[32];

int compteurJoueur = 0;

void jungle()
{

  const int
  notesClairLune[] = {262, 262, 262, 294, 330, 294, 262, 330, 294, 294, 262};
  const int
  dureeClairLune[] = {400, 400, 400, 400, 800, 800, 400, 400, 400, 400, 1200};
  for (int i = 0;
  i < 11;
  i++
)
  {

    int
    randomValue = rand() % 4 + 2;

    tone(buzzeur, notesClairLune[i]); // Send 1KHz sound signal...
    digitalWrite(randomValue, HIGH);  // apply new LED state
    delay(dureeClairLune[i]);        // ...for 1 sec
    digitalWrite(randomValue, LOW);


  }

  noTone(buzzeur);     // Stop sound...


}

void eteindreTout()
{

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);


}


void simon()
{
  for (int i = 0;
  i < 32;
  i++
)
  {

    int randomSimon = rand() % 4 + 2;

    memorySimon[i] = randomSimon;

    Serial.print("touche ");
    Serial.print(i, DEC);
    Serial.print(" = ");
    Serial.print(memorySimon[i] - 1);
    Serial.println(" ");

  }
}


void setup()
{

  pinMode(buzzeur, OUTPUT);
  cmdB.attach(A2, INPUT_PULLUP); // attach the debouncer to a pin with INPUT_PULLUP mode
  cmdB.interval(25); // Use a debounce interval of 25 milliseconds

  cmdJ.attach(A3, INPUT_PULLUP); // attach the debouncer to a pin with INPUT_PULLUP mode
  cmdJ.interval(25); // Use a debounce interval of 25 milliseconds

  cmdR.attach(A4, INPUT_PULLUP); // attach the debouncer to a pin with INPUT_PULLUP mode
  cmdR.interval(25); // Use a debounce interval of 25 milliseconds

  cmdV.attach(A5, INPUT_PULLUP); // attach the debouncer to a pin with INPUT_PULLUP mode
  cmdV.interval(25); // Use a debounce interval of 25 milliseconds


  pinMode(ledB, OUTPUT); // Led Bleu
  pinMode(ledJ, OUTPUT); // Led Jaune
  pinMode(ledR, OUTPUT); // Led Rouge
  pinMode(ledV, OUTPUT); // Led Vert
  digitalWrite(ledB, ledEtatB); // apply LED state
  digitalWrite(ledJ, ledEtatJ); // apply LED state
  digitalWrite(ledR, ledEtatR); // apply LED state
  digitalWrite(ledV, ledEtatV); // apply LED state

  Serial.begin(9600);         // Set communication rate to 9600 bauds

}


void loop()
{

  // put your main code here, to run repeatedly:

  cmdB.update();          // Update the Bounce instance
  cmdJ.update();          // Update the Bounce instance
  cmdR.update();          // Update the Bounce instance
  cmdV.update();          // Update the Bounce instance


/// 1 BLEU ////////////////
  if (cmdB.fell()) {      // Call code if button transitions from HIGH to LOW

////// JUNGLE ////////////////////
    if (compteur_1 == 0) {

      jungle();
      simon();
      compteur_1++;
    } else {
      ledEtatB = !ledEtatB;
      digitalWrite(ledB, ledEtatB);
      if (2 == memorySimon[compteurJoueur]) {


        tone(buzzeur, noteB);
        Serial.print("VRAI touche : ");
        Serial.print(compteurJoueur, DEC);
        Serial.print(" moi = 1");
        Serial.print("  ||   Simon = ");
        Serial.print(memorySimon[compteurJoueur] - 1, DEC);
        Serial.println(" fois");


      } else {
        Serial.print("FAUX touche : ");
        Serial.print(compteurJoueur, DEC);
        Serial.print(" moi = 1");
        Serial.print("  ||   Simon = ");
        Serial.print(memorySimon[compteurJoueur] - 1, DEC);
        Serial.println(" fois");
        tone(buzzeur, erreur);

      }
      delay(500);
      noTone(buzzeur);

      ledEtatB = !ledEtatB;
      digitalWrite(ledB, ledEtatB);
      compteurJoueur++;


    }

  }


  if (cmdJ.fell()) {
    ledEtatJ = !ledEtatJ;
    digitalWrite(ledJ, ledEtatJ);


    //Transmission for button 2

    if (3 == memorySimon[compteurJoueur]) {


      Serial.print("VRAI touche : ");
      Serial.print(compteurJoueur, DEC);
      Serial.print(" moi = 2");
      Serial.print("  ||   Simon = ");
      Serial.print(memorySimon[compteurJoueur] - 1, DEC);
      Serial.println(" fois");
      tone(buzzeur, noteJ);


    } else {
      Serial.print("FAUX touche : ");
      Serial.print(compteurJoueur, DEC);
      Serial.print(" moi = 2");
      Serial.print("  ||   Simon = ");
      Serial.print(memorySimon[compteurJoueur] - 1, DEC);
      Serial.println(" fois");
      ;
      tone(buzzeur, erreur);

    }
    delay(500);
    noTone(buzzeur);

    ledEtatJ = !ledEtatJ;
    digitalWrite(ledJ, ledEtatJ);
    compteurJoueur++;

  }


  if (cmdR.fell()) {
    ledEtatR = !ledEtatR;
    digitalWrite(ledR, ledEtatR);
    if (4 == memorySimon[compteurJoueur]) {


      Serial.print("VRAI touche : ");
      Serial.print(compteurJoueur, DEC);
      Serial.print(" moi = 3");
      Serial.print("  ||   Simon = ");
      Serial.print(memorySimon[compteurJoueur] - 1, DEC);
      Serial.println(" fois");
      tone(buzzeur, noteR);


    } else {
      Serial.print("FAUX touche : ");
      Serial.print(compteurJoueur, DEC);
      Serial.print(" moi = 3");
      Serial.print("  ||   Simon = ");
      Serial.print(memorySimon[compteurJoueur] - 1, DEC);
      Serial.println(" fois");
      tone(buzzeur, erreur);

    }
    delay(500);
    noTone(buzzeur);
    ledEtatR = !ledEtatR;
    digitalWrite(ledR, ledEtatR);
    compteurJoueur++;

  }


  if (cmdV.fell()) {
    ledEtatV = !ledEtatV;
    digitalWrite(ledV, ledEtatV);
    if (5 == memorySimon[compteurJoueur]) {


      Serial.print("VRAI touche : ");
      Serial.print(compteurJoueur, DEC);
      Serial.print(" moi = 4");
      Serial.print("  ||   Simon = ");
      Serial.print(memorySimon[compteurJoueur] - 1, DEC);
      Serial.println(" fois");
      tone(buzzeur, noteV);


    } else {
      Serial.print("FAUX touche : ");
      Serial.print(compteurJoueur, DEC);
      Serial.print(" moi = 4");
      Serial.print("  ||   Simon = ");
      Serial.print(memorySimon[compteurJoueur] - 1, DEC);
      Serial.println(" fois");
      tone(buzzeur, erreur);

    }
    delay(500);
    noTone(buzzeur);

    ledEtatV = !ledEtatV;
    digitalWrite(ledV, ledEtatV);
    compteurJoueur++;
  }


}
