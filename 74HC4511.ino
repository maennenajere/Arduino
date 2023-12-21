/* 
* Lukee numeron Serial Monitorin syötekentän kautta, 
* muuttaa sen nelibittiseksi binääriluvuksi käyttäen bcd-koodausta,
* ja tulostaa sen seitsensegmenttinäytölle dekooderin 74HC4511 välityksellä.
*/

// Määritellään ensin mille Arduinon pinneille dekooderin 74HC4511 syötepinnit on kytketty
int dekooderi_A = 3;
int dekooderi_B = 4;
int dekooderi_C = 5;
int dekooderi_D = 6;


void setup() {
  // Avataan sarjaporttiyhteys lukemista ja kirjoittamista varten
  Serial.begin(9600);

  // Asetetaan pinnit kirjoitusmoodiin
  pinMode(dekooderi_A, OUTPUT);
  pinMode(dekooderi_B, OUTPUT);
  pinMode(dekooderi_C, OUTPUT);
  pinMode(dekooderi_D, OUTPUT);
  
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


// Funktio, joka laittaa näytön pimeäksi (miksi?)
void nollaa_naytto() {
  digitalWrite(dekooderi_A, HIGH);
  digitalWrite(dekooderi_B, HIGH);
  digitalWrite(dekooderi_C, HIGH);
  digitalWrite(dekooderi_D, HIGH);
}


// Funktio, joka kirjoittaa luvun näytölle dekooderin kautta
// Huomaa, että luku otetaan funktioon sisään merkkinä (char), koska sellainen saadaan Serial Monitorista
void kirjoita_naytolle(int luku) {
  if (luku == '0'){
    // Tyhjennetään ensin näyttö
    nollaa_naytto();

    // Luku 0 on nelibittisenä binäärilukuna 0000, vastaten dekooderin pinnejä DCBA
    digitalWrite(dekooderi_A, LOW);
    digitalWrite(dekooderi_B, LOW);
    digitalWrite(dekooderi_C, LOW);
    digitalWrite(dekooderi_D, LOW);
  }
  else if (luku == '1'){
    digitalWrite(dekooderi_A, HIGH);
    digitalWrite(dekooderi_B, LOW);
    digitalWrite(dekooderi_C, LOW);
    digitalWrite(dekooderi_D, LOW);
  }
  else if (luku == '2') {
    digitalWrite(dekooderi_A, LOW);
    digitalWrite(dekooderi_B, HIGH);
    digitalWrite(dekooderi_C, LOW);
    digitalWrite(dekooderi_D, LOW);
  }
  else if (luku == '3') {
    digitalWrite(dekooderi_A, HIGH);
    digitalWrite(dekooderi_B, HIGH);
    digitalWrite(dekooderi_C, LOW);
    digitalWrite(dekooderi_D, LOW);
  }
  else if (luku == '4') {
    digitalWrite(dekooderi_A, LOW);
    digitalWrite(dekooderi_B, LOW);
    digitalWrite(dekooderi_C, HIGH);
    digitalWrite(dekooderi_D, LOW);
  }
  else if (luku == '5') {
    digitalWrite(dekooderi_A, HIGH);
    digitalWrite(dekooderi_B, LOW);
    digitalWrite(dekooderi_C, HIGH);
    digitalWrite(dekooderi_D, LOW);
  }
  else if (luku == '6') {
    digitalWrite(dekooderi_A, LOW);
    digitalWrite(dekooderi_B, HIGH);
    digitalWrite(dekooderi_C, HIGH);
    digitalWrite(dekooderi_D, LOW);
  }
  else if (luku == '7') {
    digitalWrite(dekooderi_A, HIGH);
    digitalWrite(dekooderi_B, HIGH);
    digitalWrite(dekooderi_C, HIGH);
    digitalWrite(dekooderi_D, LOW);
  }
  else if (luku == '8') {
    digitalWrite(dekooderi_A, LOW);
    digitalWrite(dekooderi_B, LOW);
    digitalWrite(dekooderi_C, LOW);
    digitalWrite(dekooderi_D, HIGH);
  }
  else if (luku == '9') {
    digitalWrite(dekooderi_A, HIGH);
    digitalWrite(dekooderi_B, LOW);
    digitalWrite(dekooderi_C, LOW);
    digitalWrite(dekooderi_D, HIGH);
  }
  else if (isAlpha(luku)) {
    // Jos syötät minkä tahansa kirjaimen, pimenee näyttö
    nollaa_naytto();
  }
}
