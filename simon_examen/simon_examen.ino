#include <Bounce2.h>
#include <stdlib.h>



const int MAX = 31;


int ledEtatB = LOW;
int ledEtatJ = LOW;
int ledEtatR = LOW;
int ledEtatV = LOW;
int compteur_1 = 0;
int ledB = 2;
int ledJ = 3;
int ledR = 4;
int ledV = 5;
int ledEtat = -1;
int led = -1;
int note = -1;
int noteB = 329;
int noteJ = 261;
int noteR = 220;
int noteV = 164;
int erreur = 65;
int buzzeur = 6;
int memorySimon[MAX];
int memoryJoueur[MAX];
int clique = 1;
int compteurJoueur = 0;
int cliqueSimon = 0;
int cliqueJoueur = 0;

int tourSimon = 1;


Bounce cmdB = Bounce(); // Instantiate a Bounce object
Bounce cmdJ = Bounce(); // Instantiate a Bounce object
Bounce cmdR = Bounce(); // Instantiate a Bounce object
Bounce cmdV = Bounce(); // Instantiate a Bounce object



void jungle()
{

  const int
  notesClairLune[] = {262, 262, 262, 294, 330, 294, 262, 330, 294, 294, 262};
  const int
  dureeClairLune[] = {400, 400, 400, 400, 800, 800, 400, 400, 400, 400, 1200};
  for (int i = 0;i < 11;
  i++
  )
  {

    int randomValue = rand() % 4 + 2;

    tone(buzzeur, notesClairLune[i]); 
    digitalWrite(randomValue, HIGH);  
    delay(dureeClairLune[i]);    
    digitalWrite(randomValue, LOW);


  }

  noTone(buzzeur);      

}

void eteindreTout()
{

  digitalWrite(ledEtatB, LOW);
  digitalWrite(ledEtatJ, LOW);
  digitalWrite(ledEtatR, LOW);
  digitalWrite(ledEtatV, LOW);

}


void simonEnregistre()
{
  for (int i = 0;i < MAX;i++)
  {

    int randomSimon = rand() % 4 + 2;

    memorySimon[i] = randomSimon;

    Serial.print("touche ");
    Serial.print(i+1, DEC);
    Serial.print(" = ");
    Serial.print(memorySimon[i] - 1);
    Serial.println(" ");

  }
}

void simonJoue(int niveau){
  
}

void setup()
{

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
int maximum = 1;


void loop()
{
cmdB.update();         
  cmdJ.update();        
  cmdR.update();       
  cmdV.update();      

  if (cmdB.fell()) {   
  if (compteur_1 == 0) {
   
      simonEnregistre();
      jungle();

     

      compteur_1++;
    }else    
    {
        clique = 2;
        ledEtatB = !ledEtatB;
        ledEtat = ledEtatB;
        led = ledB;
        note = noteB;  
    }
  
  }


    if( compteur_1 == 1){


      if(clique == 1){
            for(int i = 0; i < compteurJoueur; i++)
          {
                
                   delay(1000);
                tone(buzzeur, erreur);
                digitalWrite(memorySimon[i], HIGH); // apply LED state
                Serial.print("touche ");
                Serial.print(i+1, DEC);
                Serial.print(" = ");
                Serial.print(memorySimon[i] - 1);
                Serial.println(" ");
                delay(250);
                digitalWrite(memorySimon[i], LOW); // apply LED state
                noTone(buzzeur);
       
          }
          clique = 0;
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
  

  if(compteurJoueur+1 <= MAX)
  {

      if(clique == 2 || clique == 3 || clique == 4 || clique == 5 ){




    
    
            digitalWrite(led, ledEtat);   
            if (clique == memorySimon[compteurJoueur]) {
            
            
            tone(buzzeur, note);
            Serial.print("VRAI touche : ");
            
            } 
            
            else {
            
            tone(buzzeur, erreur);
            Serial.print("FAUX touche : ");
            }
            
            
            Serial.print(compteurJoueur+1, DEC);
            Serial.print("          moi = ");
            Serial.print(clique-1, DEC);
            Serial.print("  ||   Simon = ");
            Serial.print(memorySimon[compteurJoueur] - 1, DEC);
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
            maximum++;
    
        }

  
  }


}


/*          for(int i = 0; i < maximum; i++)
          {
          
                digitalWrite(memorySimon[i], HIGH); // apply LED state
                Serial.print("touche ");
                Serial.print(i+1, DEC);
                Serial.print(" = ");
                Serial.print(memorySimon[i] - 1);
                Serial.println(" ");
                delay(250);
                digitalWrite(memorySimon[i], LOW); // apply LED state
       
          }

          */
