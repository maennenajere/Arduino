/* 
* Lukee numeron Serial Monitorin syötekentän kautta ja tulostaa sen seitsensegmenttinäytölle.
*/

// Määritellään ensin mille Arduinon pinneille näytön eri segmentit on kytketty
int segmentti_A = 3;
int segmentti_B = 4;
int segmentti_C = 5;
int segmentti_D = 6;
int segmentti_E = 7;
int segmentti_F = 8;
int segmentti_G = 9;


void setup() {
  // Avataan sarjaporttiyhteys lukemista ja kirjoittamista varten
  Serial.begin(9600);

  // Asetetaan pinnit kirjoitusmoodiin
  pinMode(segmentti_A, OUTPUT);
  pinMode(segmentti_B, OUTPUT);
  pinMode(segmentti_C, OUTPUT);
  pinMode(segmentti_D, OUTPUT);
  pinMode(segmentti_E, OUTPUT);
  pinMode(segmentti_F, OUTPUT);
  pinMode(segmentti_G, OUTPUT);
  
  // Tyhjennetään näyttö kutsumalla erillistä funktiota nollaa_naytto, joka on määritelty funktion loop jälkeen
  nollaa_naytto();
}


void loop() {
  // Yritetään lukea syötettyä arvoa vain, jos jotain on saatavilla
  if(Serial.available()){
    // Luetaan luku Serial Monitorin syötekentästä
    // Huomaa, että arvo on merkki (char) eikä kokonaisluku (int)
    char syotetty_luku = Serial.read();

    // Kirjoitetaan arvo näytölle kutsumalla erillistä funktiota kirjoita_naytolle, joka on määritelty funktion nollaa_naytto jälkeen
    kirjoita_naytolle(syotetty_luku);
  }
}


// Funktio, joka laittaa jokaisen näytön segmentin pimeäksi
void nollaa_naytto() {
  digitalWrite(segmentti_A, LOW);
  digitalWrite(segmentti_B, LOW);
  digitalWrite(segmentti_C, LOW);
  digitalWrite(segmentti_D, LOW);
  digitalWrite(segmentti_E, LOW);
  digitalWrite(segmentti_F, LOW);
  digitalWrite(segmentti_G, LOW);
}


// Funktio, joka kirjoittaa luvun näytölle
// Huomaa, että luku otetaan funktioon sisään merkkinä (char), koska sellainen saadaan Serial Monitorista
void kirjoita_naytolle(char luku) {
  if (luku == '0'){
    nollaa_naytto();

    // Laitetaan oikeat segmentit päälle
    digitalWrite(segmentti_F, HIGH);
    digitalWrite(segmentti_A, HIGH);
    digitalWrite(segmentti_B, HIGH);
    digitalWrite(segmentti_C, HIGH);
    digitalWrite(segmentti_D, HIGH);
    digitalWrite(segmentti_E, HIGH);
  }
  else if (luku == '1'){
    // Tyhjennetään ensin näyttö
    nollaa_naytto();

    // Laitetaan oikeat segmentit päälle
    digitalWrite(segmentti_B, HIGH);
    digitalWrite(segmentti_C, HIGH);
  }
  else if (luku == '2') {
  nollaa_naytto();
  
   digitalWrite(segmentti_A, HIGH);
   digitalWrite(segmentti_B, HIGH);
   digitalWrite(segmentti_G, HIGH);
   digitalWrite(segmentti_E, HIGH);
   digitalWrite(segmentti_D, HIGH);
   
  }
  else if (luku == '3') {
  nollaa_naytto();

    digitalWrite(segmentti_A, HIGH);
    digitalWrite(segmentti_B, HIGH);
    digitalWrite(segmentti_G, HIGH);
    digitalWrite(segmentti_C, HIGH);
    digitalWrite(segmentti_D, HIGH);
  }
  else if (luku == '4') {
  nollaa_naytto();

    digitalWrite(segmentti_F, HIGH);
    digitalWrite(segmentti_G, HIGH);
    digitalWrite(segmentti_B, HIGH);
    digitalWrite(segmentti_C, HIGH);
  }
  else if (luku == '5') {
  nollaa_naytto();

    digitalWrite(segmentti_A, HIGH);
    digitalWrite(segmentti_F, HIGH);
    digitalWrite(segmentti_G, HIGH);
    digitalWrite(segmentti_C, HIGH);
    digitalWrite(segmentti_D, HIGH);
  }
  else if (luku == '6') {
  nollaa_naytto();

    digitalWrite(segmentti_A, HIGH);
    digitalWrite(segmentti_F, HIGH);
    digitalWrite(segmentti_G, HIGH);
    digitalWrite(segmentti_C, HIGH);
    digitalWrite(segmentti_D, HIGH);
    digitalWrite(segmentti_E, HIGH);
  }
  else if (luku == '7') {
  nollaa_naytto();

    digitalWrite(segmentti_A, HIGH);
    digitalWrite(segmentti_B, HIGH);
    digitalWrite(segmentti_C, HIGH);
  }
  else if (luku == '8') {
  nollaa_naytto();

    digitalWrite(segmentti_A, HIGH);
    digitalWrite(segmentti_B, HIGH);
    digitalWrite(segmentti_C, HIGH);
    digitalWrite(segmentti_D, HIGH);
    digitalWrite(segmentti_E, HIGH);
    digitalWrite(segmentti_F, HIGH);
    digitalWrite(segmentti_G, HIGH);
  }
  else if (luku == '9') {
  nollaa_naytto();

    digitalWrite(segmentti_F, HIGH);
    digitalWrite(segmentti_A, HIGH);
    digitalWrite(segmentti_G, HIGH);
    digitalWrite(segmentti_B, HIGH);
    digitalWrite(segmentti_C, HIGH);
    digitalWrite(segmentti_D, HIGH);
  }

  else if (isAlpha(luku)) {
    // Jos syötät minkä tahansa kirjaimen, sytyttää G-segmentin
    nollaa_naytto();
    digitalWrite(segmentti_G, HIGH);

  }
}
