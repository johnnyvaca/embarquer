//Name : Chenille_Base
//Date : 05.09.2019
//Autor: Johnny Vaca

void setup() {
  // initialize digital pins 2 to 5 as an output.
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  Serial.begin(9600);
  
}


void loop() {


int time_delay = 500;

  for(int i = 2 ;i <= 5; i++)
  {
    digitalWrite(i, HIGH);
    delay(time_delay);
    Serial.print("La est relié à la pin ");
    Serial.print(i,DEC);
    Serial.println(" est allumé");
    digitalWrite(i, LOW);
  
    
  }
 


}
