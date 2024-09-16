//     C++ code     //
// Basic Moving Car //

const int speed = 120;

void setup() {
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  pinMode(9, OUTPUT);
  pinMode(5, OUTPUT);

  analogWrite(9, speed);
  analogWrite(5, speed);
}

void loop() {
  moveForward();
  delay(2000);
  moveBackward();
  delay(2000);
  moveright();
  delay(2000);
  moveForward();
  delay(2000);
  moveleft();
  delay(2000);
  moveForward();
  delay(2000);
}

void moveForward() {
  digitalWrite(4, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
}

void moveBackward() {
  digitalWrite(4, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
}

void moveright() {
  digitalWrite(4, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
}

void moveleft() {
  digitalWrite(4, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
}