// Pin assignments for shift register control
int clockpin = 6, latchpin = 7, datapin = 8;

// Array to store button pin numbers
int buttonPins[] = { 2, 3, 4, 5 };

// Array to store LED pin numbers
int ledPins[] = { A0, A1, A2, A3 };

// Array to store binary values for 7-segment display digits 0-9
int segdisp[] = { 0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00100111, 0b01111111, 0b01101111 };

// Pin assignment for the buzzer
const int buzzerPin = 9;

// Array of frequencies corresponding to different tones
const int frequencies[] = { 277, 311, 370, 415 };

// Melodies for winning and losing scenarios
const int winMelody[] = { 262, 294, 330, 349, 392, 440, 494 };
const int loseMelody[] = { 523, 494, 440, 321, 392, 349, 330 };

// Function to set a number on the 7-segment display
void setNumber(int z) {
  // Start communication with shift register
  digitalWrite(latchpin, LOW);
  // Clear the display
  shiftOut(datapin, clockpin, MSBFIRST, 0);
  shiftOut(datapin, clockpin, MSBFIRST, 0);
  // End communication
  digitalWrite(latchpin, HIGH);

  // Display a single digit or two digits based on the value of z
  if (z < 10) {
    // For a single digit
    digitalWrite(latchpin, LOW);
    shiftOut(datapin, clockpin, MSBFIRST, segdisp[z]);
    shiftOut(datapin, clockpin, MSBFIRST, 0);
    digitalWrite(latchpin, HIGH);
  } else if (z >= 10) {
    // For two digits
    int c = z % 10;  // Get the ones place
    int e = z / 10;  // Get the tens place
    digitalWrite(latchpin, LOW);
    shiftOut(datapin, clockpin, MSBFIRST, segdisp[c]);
    shiftOut(datapin, clockpin, MSBFIRST, segdisp[e]);
    digitalWrite(latchpin, HIGH);
  }
}

// Function to play a melody
void playMelody(const int melody[], int size) {
  for (int i = 0; i < size; i++) {
    // Play each note in the melody array
    tone(buzzerPin, melody[i]);
    // Here, you can add a delay based on the length of the note you want
    delay(200);  // Example: delay of 300 milliseconds for each note
    noTone(buzzerPin);
  }
}


// Setup function for initializing the game
void setup() {
  // Begin serial communication at 9600 baud rate
  Serial.begin(9600);
  // Initialize random number generation
  randomSeed(analogRead(9) + millis() * 2);
  // Set button pins as inputs and LED pins as outputs
  for (int i = 0; i < 4; i++) {
    pinMode(buttonPins[i], INPUT);
    pinMode(ledPins[i], OUTPUT);
  }
  // Set pins for shift register as outputs
  pinMode(latchpin, OUTPUT);
  pinMode(clockpin, OUTPUT);
  pinMode(datapin, OUTPUT);
  // Initialize the buzzer pin as output
  pinMode(buzzerPin, OUTPUT);

  // Enable pin change interrupts for buttons
  PCICR |= bit(PCIE2);
  PCMSK2 |= (1 << PCINT18);
  PCMSK2 |= (1 << PCINT19);
  PCMSK2 |= (1 << PCINT20);
  PCMSK2 |= (1 << PCINT21);

  digitalWrite(ledPins[3], HIGH);  // Turn on the LED connected to A0
}

// Game variables
int gameTime = 2000, gotten = 0;
volatile bool correct = false;
volatile bool buttonPressed = false;
volatile int randNumber = 0;
int gamerunning = 69;
int oldrand = -1;

#define STACK_SIZE 3

class IntQueue {
private:
  int queue[STACK_SIZE];
  int front, rear;

public:
  IntQueue()
    : front(0), rear(0) {}

  bool push(int value) {
    if ((rear + 1) % STACK_SIZE == front) {
      return false;  // Queue is full
    }
    queue[rear] = value;
    rear = (rear + 1) % STACK_SIZE;
    return true;
  }

  int peek() {
    if (front == rear) {
      return -1;  // Queue is empty
    }
    return queue[front];
  }

  bool pop() {
    if (front == rear) {
      return false;  // Queue is empty
    }
    front = (front + 1) % STACK_SIZE;
    return true;
  }

  void clear() {
    for (int i = 0; i < STACK_SIZE; i++) {
      queue[i] = 0;  // or -1 or any other value indicating an empty space
    }
    front = 0;
    rear = 0;
  }
};

IntQueue stack;

// Main game loop
void loop() {
  // Check if the game is in a running state
  if (gamerunning == 69) {
    return;
  }

  delay(200);

  // Display the current score
  setNumber(gotten);

  if (gotten == 99) {
    playMelody(winMelody, sizeof(winMelody));
    gotten = 0;
    gamerunning = 69;
    return;
  }

  // Generate a random number for the game logic
  randNumber = random(0, 4);  // Random number between 0 and 3

  if (oldrand == randNumber) {
    randNumber == random(0, 4);
  }

  oldrand = randNumber;

  stack.push(randNumber);

  // Light up the corresponding LED
  digitalWrite(ledPins[3], LOW);
  digitalWrite(ledPins[randNumber], HIGH);

  // Store the current time
  unsigned long startTime = millis();

  // Aika alkaa 1.5 sekunnista ja vähenee lineaarisesti 1.5 / 120 sekuntia per pistettä
  gameTime = max(100, 1500 - gotten * (1.5 / 120));




  // Play a tone corresponding to the random number
  tone(buzzerPin, frequencies[randNumber]);  // Use randNumber for frequency index

  // Game logic for button press and timing
  while (millis() - startTime < gameTime) {
    if (buttonPressed) {
      buttonPressed = false;
      if (correct) {
        stack.pop();
        Serial.println("Won");
        gotten++;
        gameTime -= 10;                 // Adjust this decrement value as needed
        gameTime = max(100, gameTime);  // Ensure gameTime doesn't go below 100ms
        digitalWrite(ledPins[randNumber], LOW);
        correct = false;
        noTone(buzzerPin);  // Turn off the sound
        return;
      } else {
        lostGame();
      }
    }
  }
  digitalWrite(ledPins[randNumber], LOW);
}





// Function to handle the game loss scenario with synchronized LED flashing and buzzer
void lostGame() {
  stack.clear();
  correct = false;
  gotten = 0;
  Serial.println("Lost");
  gameTime = 2000;
  digitalWrite(ledPins[randNumber], LOW);

  // Play the losing melody and flash LEDs in sync
  int melodyLength = sizeof(loseMelody) / sizeof(int);
  for (int i = 0; i < melodyLength; i++) {
    // Play a note
    tone(buzzerPin, loseMelody[i]);

    // Flash all LEDs on
    for (int j = 0; j < 4; j++) {
      digitalWrite(ledPins[j], HIGH);
    }

    // Duration of each note and LED flash
    delay(170);  // Adjust this value to match the duration of a note

    // Turn off the buzzer and LEDs
    noTone(buzzerPin);
    for (int j = 0; j < 4; j++) {
      digitalWrite(ledPins[j], LOW);
    }

    // Delay between notes and LED flashes
    delay(40);  // Adjust this value for the interval between notes
  }

  // Turn on the A0 LED to indicate game can be restarted
  digitalWrite(ledPins[3], HIGH);
  gamerunning = 69;
}



// Debounce settings for button presses
const int debounceDelay = 300;  // Set your debounce delay in milliseconds
unsigned long lastDebounceTime = 0;
volatile byte lastState = 0;  // Variable to store the previous state of the pins

// Function to initialize buttons and handle button interrupts
void initButtonsAndButtonInterrupts() {
  unsigned long hittime = millis();

  // Check for debounce
  if ((hittime - lastDebounceTime) < debounceDelay)
    return;

  // Read the state of pins 2-5
  byte currentState = PIND & B00111100;

  // Determine which button was pressed
  int interruptPin;
  switch (currentState) {
    case 28: interruptPin = A2; break;
    case 44: interruptPin = A1; break;
    case 52: interruptPin = A0; break;
    case 56: interruptPin = A3; break;
    default: return;  // Exit if no recognized button press
  }

  // Check if the pressed button matches the lit LED
  if (interruptPin == ledPins[stack.peek()]) {
    correct = true;
  } else {
    correct = false;
  }

  // Update debounce time
  lastDebounceTime = hittime;

  // Set flag indicating a button press
  buttonPressed = true;

  // Start the game if the correct button is pressed
  if (gamerunning == 69 && interruptPin == ledPins[3]) {
    digitalWrite(ledPins[A0], LOW);
    gamerunning = 1;
    Serial.println("Game started");
    delay(1000);
    correct = true;
  }
}

// Interrupt service routine for handling button presses
ISR(PCINT2_vect) {
  initButtonsAndButtonInterrupts();
}
