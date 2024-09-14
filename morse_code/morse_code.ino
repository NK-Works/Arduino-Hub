// This code is made by Anneshu Nag, Student ID- 2210994760 //
//                    Dated- 23/08/2023                     //

//                This is a Blink Program                   //
//         It blinks the in-built LED using Morse Code      //

// Defining some constants that are to be used in the code
const int ledPin = LED_BUILTIN;     // Built-in LED connected to digital pin 13
const int buttonPin = 2;            // Push button connected to digital pin 2
const int morseUnitDuration = 200;  // Duration in milliseconds for a single unit of Morse code

bool blinking = false;  // Initially keeping the checker to false state so that the LED doesn't blink until the button is pressed

String blinkInput;  // Declaring the varaible to store the user given name

unsigned long lastButtonPress = 0;  // Variable to track the time of the last button press

void setup() {
  Serial.begin(9600);   // Setting up the serial communication for getting the user input

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);  // Activating the internal pull-up resistor for the push button
  attachInterrupt(digitalPinToInterrupt(buttonPin), interruptBlink, FALLING);   // Attaching interruption to jump if the Morse Code is blinking and forcefully stopping the blink
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {  // Low means the button is pressed
    blinking = !blinking;               // Changing the status of the checker depending on whether it is true or false
    delay(100);                         // Setting the delay to avoid multiple button presses in quick succession
  }

  if (blinking) {
    // put your main code here, to run repeatedly:
    Serial.print("Enter Name: ");
    while (Serial.available() == 0) {}
    blinkInput = Serial.readString();
    blinkInput.toUpperCase();
    Serial.println(blinkInput);

    blinkUserInput();
  } else {
    digitalWrite(ledPin, LOW);  // Turn off the LED when not blinking
  }
}

void blinkUserInput() {
  for (int i = 0; i < blinkInput.length(); i++) {
    alphabetsMorse(blinkInput[i]);
    delay(morseUnitDuration * 3);  // Pausing between two letters of the Morse Code
  }
  Serial.println("+ Click the button again to enter a new name +\n");
  blinking = false;
}

void dot() {
  digitalWrite(ledPin, HIGH);
  delay(morseUnitDuration);
  digitalWrite(ledPin, LOW);
  delay(morseUnitDuration);
}

void dash() {
  digitalWrite(ledPin, HIGH);
  delay(morseUnitDuration * 3);  // 3X extra time blink for the dashes
  digitalWrite(ledPin, LOW);
  delay(morseUnitDuration);
}

// Dot function without any delay for the last blink of the letter
void finalDot() {
  digitalWrite(ledPin, HIGH);
  delay(morseUnitDuration);
  digitalWrite(ledPin, LOW);
}

// Dash function without any delay for the last blink of the letter
void finalDash() {
  digitalWrite(ledPin, HIGH);
  delay(morseUnitDuration * 3);
  digitalWrite(ledPin, LOW);
}

// Morse Codes for all the 26 alphabets
void alphabetsMorse(char selectedLetter) {
  // Morse Code patterns for the alphabets
  if (selectedLetter == 'A') {
    // .-
    dot();
    finalDash();
  }
  if (selectedLetter == 'B') {
    // -...
    dash();
    dot();
    dot();
    finalDot();
  }
  if (selectedLetter == 'C') {
    // -.-.
    dash();
    dot();
    dash();
    finalDot();
  }
  if (selectedLetter == 'D') {
    // -..
    dash();
    dot();
    finalDot();
  }
  if (selectedLetter == 'E') {
    // .
    finalDot();
  }
  if (selectedLetter == 'F') {
    // ..-.
    dot();
    dot();
    dash();
    finalDot();
  }
  if (selectedLetter == 'G') {
    // --. 
    dash();
    dash();
    finalDot();
  }
  if (selectedLetter == 'H') {
    // ....
    dot();
    dot();
    dot();
    finalDot();
  }
  if (selectedLetter == 'I') {
    // ..
    dot();
    finalDot();
  }
  if (selectedLetter == 'J') {
    // .---
    dot();
    dash();
    dash();
    finalDash();
  }
  if (selectedLetter == 'K') {
    // -.-
    dash();
    dot();
    finalDash();
  }
  if (selectedLetter == 'L') {
    // .-..
    dot();
    dash();
    dot();
    finalDot();
  }
  if (selectedLetter == 'M') {
    // --
    dash();
    finalDash();
  }
  if (selectedLetter == 'N') {
    // -.
    dash();
    finalDot();
  }
  if (selectedLetter == 'O') {
    // ---
    dash();
    dash();
    finalDash();
  }
  if (selectedLetter == 'P') {
    // .--.
    dot();
    dash();
    dash();
    finalDot();
  }
  if (selectedLetter == 'Q') {
    // --.-
    dash();
    dash();
    dot();
    finalDash();
  }
  if (selectedLetter == 'R') {
    // .-.
    dot();
    dash();
    finalDot();
  }
  if (selectedLetter == 'S') {
    // ...
    dot();
    dot();
    finalDot();
  }
  if (selectedLetter == 'T') {
    // -
    finalDash();
  }
  if (selectedLetter == 'U') {
    // ..-
    dot();
    dot();
    finalDash();
  }
  if (selectedLetter == 'V') {
    // ...-
    dot();
    dot();
    dot();
    finalDash();
  }
  if (selectedLetter == 'W') {
    // .--
    dot();
    dash();
    finalDash();
  }
  if (selectedLetter == 'X') {
    // -..-
    dash();
    dot();
    dot();
    finalDash();
  }
  if (selectedLetter == 'Y') {
    // -.--
    dash();
    dot();
    dash();
    finalDash();
  }
  if (selectedLetter == 'Z') {
    // --..
    dash();
    dash();
    dot();
    finalDot();
  }
  if (selectedLetter == ' ') {
    // Delay for spacing between 2 words
    digitalWrite(ledPin, LOW);
    delay(morseUnitDuration * 7);
  }
}

// Interrupt handler for stopping blinking
void interruptBlink() {
  unsigned long currentTime = millis(); 
  if (currentTime - lastButtonPress > 200) { // Adjust the debounce time as needed
    lastButtonPress = currentTime;
    if (blinking) {
      blinking = false;  // Stop blinking
      blinkInput = "";   // Clearing the input

      // Printing the messages to the user to ask for a new input
      Serial.println("               |Interrupted|");
    }
  }
}