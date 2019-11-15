/*
Auteur : Johnny Vaca
Date : 15.11.2019
Description : Jeu du Simon - Projet Embarqué - Filère Informatique CPNV
*/
#include <Bounce2.h>

const int MAX = 4;    // Score MAXIMAL du jeu

// notes sonnées à l'allumage des leds correspondantes 
const int noteB = 329;
const int noteJ = 261;
const int noteR = 220;
const int noteV = 164;
const int erreur = 65;



const int buzzeur = 6; // numero du port du buzzzeur

//Numéros des ports des leds
const int ledB = 2;
const int ledJ = 3;
const int ledR = 4;
const int ledV = 5;

//Mettre des variables qui vont correspondre à l'état des leds
int ledEtatB = LOW;
int ledEtatJ = LOW;
int ledEtatR = LOW;
int ledEtatV = LOW;


int commencerPartie = 0; // vérifie si on a déjà choisis le niveau de dificulté au début de l'alimentation

// Variable qui vont prendre la valeur correspondant au clique des boutons plus tard
int ledEtat = -1;
int led = -1;
int note = -1;

int tourSimon = 1; // va dire quand est-ce que simon peut jouer
int memoireSimon[MAX]; // va garder dans le tableau 
int cmdClique = tourSimon; // On dit que la première personne qui va jouer, c'est Simon
int cliqueJoueur = 0; // Nombre de fois que le joueur va cliquer sur la totalité des boutons
int numTour = 0; // Stocke le numero du Tour dans la partie


int tempsPause = 1000; // donne le temps d'attente entre les clignotements de leds quand Simon Joue
int compteurtempsPause = 1; // compte le nombre de fois qu'on passe à un autre tour

//initialisation de nouveaux objets Bounce
Bounce cmdB = Bounce();
Bounce cmdJ = Bounce(); 
Bounce cmdR = Bounce(); 
Bounce cmdV = Bounce(); 


// FONCTION QUI JOUE LE JUNGLE DE DEMARRAGE ET DE PERDANT
void jungle() {

  const int notesClairLune[] = {262,262,262,294,330,294,262,330,294,294,262};
  const int dureeClairLune[] = {400,400,400,400,800,800,400,400,400,400,1200};

  //BOUCLE QUI VA JUSQU'A LA LONGEUR DU TABLEAU DU JUNGLE
  for (int i = 0; i < 11; i++) {

  int ledAleatoire = random(4)+2;// valeur qui prends 4 valeurs depuis 0+2

    //jeu de lumières qui clignotent
    tone(buzzeur, notesClairLune[i]);
    digitalWrite(ledAleatoire, HIGH);
    delay(dureeClairLune[i]);
    digitalWrite(ledAleatoire, LOW);

  }

  noTone(buzzeur);// taire le buzzeur

}
void sonGagnant(){


  const int notesMario[]={2637, 2637, 0, 2637, 0, 2093, 2637, 0, 3136, 0, 0, 0, 1568, 0, 0, 0};
const int durationMario = 120;

  for (int i = 0; i < 11; i++) {

  int ledAleatoire = random(4)+2;// valeur qui prends 4 valeurs depuis 0+2

    //jeu de lumières qui clignotent
    if(notesMario[i] == 0){
       noTone(buzzeur);// taire le buzzeur
      
      }else{
        tone(buzzeur, notesMario[i]);
        }
    
    digitalWrite(ledAleatoire, HIGH);
    delay(durationMario);
    digitalWrite(ledAleatoire, LOW);

  }

  noTone(buzzeur);// taire le buzzeur

  
}

//Stockage de tous les coups de simon durant une partie dans la mémoire de Simon
void simonEnregistre() {
 
  for (int i = 0; i < MAX; i++) {
    int randomSimon = random(4)+2; // valeur qui prends 4 valeurs depuis 0+2

    memoireSimon[i] = randomSimon; // stocke dans la mémoire de Simon

    Serial.print("touche ");
    Serial.print(i + 1, DEC);
    Serial.print(" = ");
    Serial.print(memoireSimon[i] - 1);
    Serial.println(" ");

  }
}



void setup() {

  pinMode(buzzeur, OUTPUT); // mettre le buzzeur en mode de sortie 

  //Indique les ports utilisés pour chaque bouton et explique le temps d'interval maximal de changement d'état
  cmdB.attach(A2, INPUT_PULLUP);
  cmdB.interval(25);

  cmdJ.attach(A3, INPUT_PULLUP);
  cmdJ.interval(25);

  cmdR.attach(A4, INPUT_PULLUP);
  cmdR.interval(25);

  cmdV.attach(A5, INPUT_PULLUP);
  cmdV.interval(25);

// indique les ports de sortie de chaque led
  pinMode(ledB, OUTPUT); // Led Bleu
  pinMode(ledJ, OUTPUT); // Led Jaune
  pinMode(ledR, OUTPUT); // Led Rouge
  pinMode(ledV, OUTPUT); // Led Vert


  //mettre toutes les leds en etat LOW
  digitalWrite(ledB, ledEtatB); 
  digitalWrite(ledJ, ledEtatJ); 
  digitalWrite(ledR, ledEtatR);
  digitalWrite(ledV, ledEtatV); 

  Serial.begin(9600); // indique le port utilisé pour le moiniteur serie. Utilie pour débeug
randomSeed(analogRead(0)); // initialise des mises à jour des valeurs aleatoires pour n'importe laquel de fonction Random 
}


void loop() {

  // mets à jour l'état de chaque bouton (si il est à 0 ou à  1)
  cmdB.update();
  cmdJ.update();
  cmdR.update();
  cmdV.update();


// des l'appuie sur le bouton relié au port A2,
  if (cmdB.fell()) {
    if (commencerPartie == 0) {

      simonEnregistre(); //  on met dans la memoire de Simon les touchés
      jungle();

      commencerPartie++;
    } else {
      commencerPartie = 1;
      cmdClique = ledB;
      ledEtatB = !ledEtatB; // allume la led
      ledEtat = ledEtatB; // donne etat de la led appuyée
      led = ledB; // donne le port de la led qui correspond au bouton appuyé
      note = noteB; // donné la fréquence de la note qui correspond à la led séléctionnée

    }

  }

// si l'etat de commencer la partie est 1, le jungle à déja sonné
  if (commencerPartie == 1) {

//si c'est au tour de simon de jouer
    if (cmdClique == tourSimon) {

//si il n'y a pas encore un tour ou si le joueur à déjà cliquer la quantité de fois qui correspondent au tour
      if (cliqueJoueur == numTour || numTour == 0) {
        numTour++; // on passe au tour suivant
// if le numero du tour n'est pas son dernier tour
        if (numTour <= MAX) {
         
          for (int i = 0; i < numTour; i++) {

            // tous les 3 tours, le temps de pause entre les leds va diminuer 
            if (compteurtempsPause % 3 == 0 && i == 0) {
              tempsPause -= 100; // 
            }
            delay(tempsPause);


            // buzzeur fait un sons selon la led
            if (memoireSimon[i] == ledB)
              tone(buzzeur, noteB);
            if (memoireSimon[i] == ledJ)
              tone(buzzeur, noteJ);
            if (memoireSimon[i] == ledR)
              tone(buzzeur, noteR);
            if (memoireSimon[i] == ledV)
              tone(buzzeur, noteV);



            // Allume la led et joue la note
            digitalWrite(memoireSimon[i], HIGH); // apply LED state
            Serial.print("touche ");
            Serial.print(i + 1, DEC);
            Serial.print(" = ");
            Serial.print(memoireSimon[i] - 1);
            Serial.print(" et Temps =  ");
            Serial.print(tempsPause);
            Serial.print(" CompteurtempsPause =  ");
            Serial.print(compteurtempsPause);
            Serial.print(" CompteurtempsPause%3 =  ");
            Serial.print(compteurtempsPause % 3);
            Serial.println(" ");
            delay(250);
            digitalWrite(memoireSimon[i], LOW); // apply LED state
            noTone(buzzeur);

          }
        } else {
          // si le numero du tour est le MAX on gagne
          Serial.print("BRAVO VOUS AVEZ GAGNEE!!!");
          Serial.println(" ");
          sonGagnant();
          asm("jmp 0x0000"); // fonction de reset depuis le software
        }

        compteurtempsPause++;

        cliqueJoueur = 0;

      }

    }
 // memes executions qu'avec la led bleu quand commencerPartie = 1
    if (cmdJ.fell()) {
      cmdClique = ledJ;
      ledEtatJ = !ledEtatJ;
      ledEtat = ledEtatJ;
      led = ledJ;
      note = noteJ;

    }

    if (cmdR.fell()) {
      cmdClique = ledR;
      ledEtatR = !ledEtatR;
      ledEtat = ledEtatR;
      led = ledR;
      note = noteR;

    }

    if (cmdV.fell()) {
      cmdClique = ledV;
      ledEtatV = !ledEtatV;
      ledEtat = ledEtatV;
      led = ledV;
      note = noteV;

    }

  }
//
  if (cliqueJoueur < numTour) {

    if (cmdClique == ledB || cmdClique == ledJ || cmdClique == ledR || cmdClique == ledV) {

      digitalWrite(led, ledEtat);
      if (cmdClique == memoireSimon[cliqueJoueur]) {

        tone(buzzeur, note);
        Serial.print("VRAI touche : ");

      } else {

        tone(buzzeur, erreur);
        Serial.print("PERDU !!!  ");
        Serial.print("FAUX touche : ");
         Serial.println(" ");
        numTour = 0;
        simonEnregistre();
        jungle();
      }

      Serial.print(cliqueJoueur + 1, DEC);
      Serial.print("          moi = ");
      Serial.print(cmdClique - 1, DEC);
      Serial.print("  ||   Simon = ");
      Serial.print(memoireSimon[cliqueJoueur] - 1, DEC);
      Serial.println(" fois");

      delay(250);
      noTone(buzzeur);

      ledEtat = !ledEtat;

      ledEtatB = ledEtat;
      ledEtatJ = ledEtat;
      ledEtatR = ledEtat;
      ledEtatV = ledEtat;
      digitalWrite(led, ledEtat);
      cmdClique = tourSimon;
      led = -1;
      note = -1;

      cliqueJoueur++;
    }

  }

}
