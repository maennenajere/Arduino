// This Arduino script reads values from four analog pins and prints them to the serial port.
// It is used to monitor various sensors (door, window, motion) and an alarm system.

// These constants won't change. They're used to give names to the pins used:
const int analogInPin0 = A0;  // Pin A0 used for reading
const int analogInPin1 = A1;  // Pin A1 used for reading
const int analogInPin2 = A2;  // Pin A2 used for reading
const int analogInPin3 = A3;  // Pin A3 used for reading

int doorSensor = 0;    // Variable for door sensor
int windowSensor = 0;  // Variable for window sensor
int motionSensor = 0;  // Variable for motion sensor
int alarm = 0;         // Variable for alarm status

void setup() {
  // Initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // Read the analog in value:
  doorSensor = analogRead(analogInPin0); // Read from pin A0 and store in doorSensor
  windowSensor = analogRead(analogInPin1); // Read from pin A1 and store in windowSensor
  motionSensor = analogRead(analogInPin2); // Read from pin A2 and store in motionSensor
  alarm = analogRead(analogInPin3); // Read from pin A3 and store in alarm

  // Print the results to the Serial Monitor:
  Serial.print(doorSensor / 1023.0); // Scale doorSensor value to range 0-1
  Serial.print("\t  "); // Print a tab for spacing
  Serial.print(windowSensor / 1023.0); // Scale windowSensor value to range 0-1
  Serial.print("\t  "); // Print a tab for spacing
  Serial.print(motionSensor / 1023.0); // Scale motionSensor value to range 0-1
  Serial.print("\t  "); // Print a tab for spacing
  Serial.println(alarm / 1023.0); // Scale alarm value to range 0-1 and print with line break

  // Wait 20 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(20);
}
