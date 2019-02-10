/*
  BAPS Serial (Over USB) Controller
  First deployed on an Arduino Nano in the MattchBox by Matthew Stratford, Winter 2018-19
  Keepalive feature added in BAPS Server 2.7.1
*/

// Pins D2 to D7 for BAPS 1 Play, Stop, BAPS 2 Play...
const int noOfPins = 6;
int buttonPins[noOfPins] = {2,3,4,5,6,7};
int buttonDelay[noOfPins];
int buttonStates[noOfPins];
// Pins 8, 9, 10 for BAPS 1,2,3 Play, (stop can also be implemented if more pins are available.)
int ledPins[noOfPins]    = {8,0,9,0,10,0};
int ledTimeouts[noOfPins];
int keepAlive = 100;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 2400 bits per second:
  Serial.begin(2400);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  int j;
  for (j = 0; j < noOfPins; j++) {
  // make the pushbutton's pin an input:
    pinMode(buttonPins[j], INPUT_PULLUP);
    // make the led pins outputs
    // output pin must be high to turn off LEDs.
    pinMode(ledPins[j], OUTPUT);
    digitalWrite(ledPins[j], HIGH);
  }
  // BAPS Conn OK LED
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int i;
  for (i = 0; i < noOfPins; i++)
  {
    // Add some debouncing by counting up if the input changes.
    int readValue = digitalRead(buttonPins[i]);
    if (readValue != buttonStates[i]) {
      buttonDelay[i]++;
    } else {
      buttonDelay[i] = 0;
    }
    // If the input pin has changed for 5 loops, it's probably not noise.
    if (buttonDelay[i] > 5) {
      buttonStates[i] = readValue;
      // The input shorts to ground when a button is pressed.
      if (readValue == 0) {
        // Set the LED of the channel triggered to turn on for 100 cycles
        ledTimeouts[i] = 100;
        // BAPS is expecting a raw byte of 1-6 (as defined in the config menu)
        Serial.write(i+1);
      }
    }
    // Light the LED if it currently has a countdown remaining.
    if (ledTimeouts[i] != 0 && ledPins[i] != 0) {
      ledTimeouts[i]--;
      digitalWrite(ledPins[i], LOW);
    } else {
      digitalWrite(ledPins[i], HIGH);
    }
  }
  delay(10);        // delay in between reads for stability
  // Implement keepalive, every second send 255 to the BAPS Server, if it replies, light CONN led.
  keepAlive--;
  if (keepAlive == 0) {
    keepAlive = 1000;
    Serial.write(255);
    byte data[1];
    data[0] = 0;
    Serial.readBytes(data, 1);
    if (data[0] == 255) {
      digitalWrite(13, LOW);
    } else {
      digitalWrite(13, HIGH);
    }
  }
}
