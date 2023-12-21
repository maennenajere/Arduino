


// These constants won't change. They're used to give names to the pins used:
const int analogInPin0 = A0;  //kerrotaan ohjelmalle, mitä pinnejä käytetään 
const int analogInPin1 = A1; 
const int analogInPin2 = A2;
const int analogInPin3 = A3;

int ovisensori = 0;    //nimetään muuttujat    
int ikkunasensori = 0; 
int liikesensori = 0;
int halyytys = 0;


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  ovisensori = analogRead(analogInPin0); //luetaan AnalogInPin0 A0 pinniltä lukema ja tallennetaan se ovisensori muuttujalle
  ikkunasensori  = analogRead(analogInPin1); //sama kuin edellä, mutta eri pinni ja muuttuja
  liikesensori = analogRead(analogInPin2);
  halyytys = analogRead(analogInPin3);
  

  // print the results to the Serial Monitor:
  Serial.print(ovisensori /1023.0); //otetaan ovisensori-muuttujan arvo ja skaalataan se välille 0-1, eli jaetaan 1023:lla
  Serial.print("\t  "); //tulostetaan lukujen väliin sarkain (tabulaattori), jotta tulokset tulevat samalle riville erikseen toisistaan
  Serial.print(ikkunasensori /1023.0);
  Serial.print("\t  ");
  Serial.print(liikesensori /1023.0);
  Serial.print("\t  ");
  Serial.println(halyytys /1023.0); //huomaa tässä komennossa ln -pääte, joka tekee rivinvaihdon


  // wait 20 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(20);
}
