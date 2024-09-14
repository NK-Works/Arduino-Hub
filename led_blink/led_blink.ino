// Blinking Two LEDs Simultaneously //

// Setting up variables
int const ledPin1 = 7;
int const ledPin2 = 8;

void setup() {
  // Setting up the pins & their functions
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

void loop() {
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, LOW);
  delay(1000);

  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  delay(1000);
}
