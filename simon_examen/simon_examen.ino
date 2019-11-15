/*
Auteur : Johnny Vaca
Date : 15.11.2019
Description : Jeu du Simon - Projet Embarqué - Filère Informatique CPNV
*/
#include <Bounce2.h>
#include <stdlib.h>
#include <time.h>


const int MAX = 3;
const int noteB = 329;
const int noteJ = 261;
const int noteR = 220;
const int noteV = 164;
const int erreur = 65;
const int buzzeur = 0;
const int ledB = 2;
const int ledJ = 3;
const int ledR = 4;
const int ledV = 5;

int ledEtatB = LOW;
int ledEtatJ = LOW;
int ledEtatR = LOW;
int ledEtatV = LOW;
int compteur_1 = 0;

int ledEtat = -1;
int led = -1;
int note = -1;

int memorySimon[MAX];
int memoryJoueur[MAX];
int clique = 1;
int compteurJoueur = 1;

int cliqueJoueur = 0;
int tour = 0;
int ii = 0;

Bounce cmdB = Bounce(); // Instantiate a Bounce object
Bounce cmdJ = Bounce(); // Instantiate a Bounce object
Bounce cmdR = Bounce(); // Instantiate a Bounce object
Bounce cmdV = Bounce(); // Instantiate a Bounce object

void jungle() {

  const int notesClairLune[] = {262,262,262,294,330,294,262,330,294,294,262};
  const int dureeClairLune[] = {400,400,400400,800,800,400,400,400,400,1200};
  
  for (int i = 0; i < 11; i++) {
    
    srand(time(NULL));

    int randomValue = rand() % 4 + 2;

    tone(buzzeur, notesClairLune[i]);
    digitalWrite(randomValue, HIGH);
    delay(dureeClairLune[i]);
    digitalWrite(randomValue, LOW);

  }

  noTone(buzzeur);

}

void eteindreTout() {

  digitalWrite(ledEtatB, LOW);
  digitalWrite(ledEtatJ, LOW);
  digitalWrite(ledEtatR, LOW);
  digitalWrite(ledEtatV, LOW);

}

void simonEnregistre() {
  for (int i = 0; i < MAX; i++) {

    srand(time(NULL));
    int randomSimon = rand() % 4 + 2;

    memorySimon[i] = randomSimon;

    Serial.print("touche ");
    Serial.print(i + 1, DEC);
    Serial.print(" = ");
    Serial.print(memorySimon[i] - 1);
    Serial.println(" ");

  }
}

void setup() {

  pinMode(buzzeur, OUTPUT);
  cmdB.attach(A2, INPUT_PULLUP);
  cmdB.interval(25);

  cmdJ.attach(A3, INPUT_PULLUP);
  cmdJ.interval(25);

  cmdR.attach(A4, INPUT_PULLUP);
  cmdR.interval(25);

  cmdV.attach(A5, INPUT_PULLUP);
  cmdV.interval(25);

  pinMode(ledB, OUTPUT); // Led Bleu
  pinMode(ledJ, OUTPUT); // Led Jaune
  pinMode(ledR, OUTPUT); // Led Rouge
  pinMode(ledV, OUTPUT); // Led Vert
  digitalWrite(ledB, ledEtatB); // apply LED state
  digitalWrite(ledJ, ledEtatJ); // apply LED state
  digitalWrite(ledR, ledEtatR); // apply LED state
  digitalWrite(ledV, ledEtatV); // apply LED state

  Serial.begin(9600);

}

int acceleration = 1000;
int compteurAcceleration = 1;
void loop() {
  cmdB.update();
  cmdJ.update();
  cmdR.update();
  cmdV.update();

  if (cmdB.fell()) {
    if (compteur_1 == 0) {

      simonEnregistre();
      jungle();

      compteur_1++;
    } else {
      compteur_1 = 1;
      clique = 2;
      ledEtatB = !ledEtatB;
      ledEtat = ledEtatB;
      led = ledB;
      note = noteB;

    }

  }

  if (compteur_1 == 1) {

    if (clique == 1) {

      if (cliqueJoueur == tour || tour == 0) {
        tour++;
        if (tour <= MAX) {
          for (ii = 0; ii < tour; ii++) {
            if (compteurAcceleration % 3 == 0 && ii == 0) {
              acceleration -= 100;
            }
            delay(acceleration);
            if (memorySimon[ii] == 2)
              tone(buzzeur, noteB);
            if (memorySimon[ii] == 3)
              tone(buzzeur, noteJ);
            if (memorySimon[ii] == 4)
              tone(buzzeur, noteR);
            if (memorySimon[ii] == 5)
              tone(buzzeur, noteV);

            digitalWrite(memorySimon[ii], HIGH); // apply LED state
            Serial.print("touche ");
            Serial.print(ii + 1, DEC);
            Serial.print(" = ");
            Serial.print(memorySimon[ii] - 1);
            Serial.print(" et Temps =  ");
            Serial.print(acceleration);
            Serial.print(" CompteurAcceleration =  ");
            Serial.print(compteurAcceleration);
            Serial.print(" CompteurAcceleration%3 =  ");
            Serial.print(compteurAcceleration % 3);
            Serial.println(" ");
            delay(250);
            digitalWrite(memorySimon[ii], LOW); // apply LED state
            noTone(buzzeur);

          }
        } else {

          Serial.print("fini");
          Serial.println(" ");
          jungle();
          asm("jmp 0x0000");
        }

        compteurAcceleration++;
        clique = 0;
        cliqueJoueur = 0;

      }

    }

    if (cmdJ.fell()) {
      clique = 3;
      ledEtatJ = !ledEtatJ;
      ledEtat = ledEtatJ;
      led = ledJ;
      note = noteJ;

    }

    if (cmdR.fell()) {
      clique = 4;
      ledEtatR = !ledEtatR;
      ledEtat = ledEtatR;
      led = ledR;
      note = noteR;

    }

    if (cmdV.fell()) {
      clique = 5;
      ledEtatV = !ledEtatV;
      ledEtat = ledEtatV;
      led = ledV;
      note = noteV;

    }

  }

  if (cliqueJoueur < tour) {

    if (clique == 2 || clique == 3 || clique == 4 || clique == 5) {

      digitalWrite(led, ledEtat);
      if (clique == memorySimon[cliqueJoueur]) {

        tone(buzzeur, note);
        Serial.print("VRAI touche : ");

      } else {

        tone(buzzeur, erreur);
        Serial.print("FAUX touche : ");
        tour = 0;
        jungle();
      }

      Serial.print(cliqueJoueur + 1, DEC);
      Serial.print("          moi = ");
      Serial.print(clique - 1, DEC);
      Serial.print("  ||   Simon = ");
      Serial.print(memorySimon[cliqueJoueur] - 1, DEC);
      Serial.println(" fois");

      delay(250);
      noTone(buzzeur);

      ledEtat = !ledEtat;

      ledEtatB = ledEtat;
      ledEtatJ = ledEtat;
      ledEtatR = ledEtat;
      ledEtatV = ledEtat;
      digitalWrite(led, ledEtat);
      compteurJoueur++;
      clique = 1;
      led = -1;
      note = -1;

      cliqueJoueur++;
    }

  }

}
