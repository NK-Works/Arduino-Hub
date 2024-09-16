//   C++ Codes on Arduino IDE    //
//     Bluetooth-based Rover     //
//    Robotics Final Project     //
// Transmitter-Main Rover Module //

#include <Wire.h>
#include <VirtualWire.h>

// Setting up some variables
const int motorPin1 = 4;   // Green colour / Represents backward (alone & reverse) right
const int motorPin2 = 6;   // Orange colour / Represents forward (alone & forward) left
const int motorPin3 = 10;  // Yellow color / Represents forward (alone & forward) right
const int motorPin4 = 12;  // Blue colour / Represents backward (alone & reverse) left

const int speedPin1 = 3;
const int speedPin2 = 5;

const int RfTxPin = 11;

const int maxCommands = 100;  // Maximum number of commands
char *commands[maxCommands];  // Array to store the commands
unsigned long timee[maxCommands];

char input;  // Stores the input coming from the Bluetooth

int speed = 150;  // Speed of the car

int dataCount = 0;  // Counter for the number of data points

void setup() {
  Serial.begin(9600);
  // Setting all the input and the output pins
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  pinMode(speedPin1, OUTPUT);
  pinMode(speedPin2, OUTPUT);

  vw_set_tx_pin(RfTxPin);
  vw_setup(2000);

  stop();
}

void loop() {

  analogWrite(speedPin1, speed);
  analogWrite(speedPin2, speed);

  // Taking the Bluetooth command
  if (Serial.available()) {
    input = Serial.read();
    Serial.println(input);

    if (input == 'F') {
      forward();
      commandStore("f");
      Serial.println(input);

      float tim = calculateTime();
      timStore(tim);
      Serial.println(tim);
    } else if (input == 'R') {
      right();
      commandStore("r");
      Serial.println(input);

      float tim = calculateTime();
      timStore(tim);
      Serial.println(tim);

    } else if (input == 'L') {
      left();
      commandStore("l");
      Serial.println(input);

      float tim = calculateTime();
      timStore(tim);
      Serial.println(tim);
    } else if (input == 'G') {
      backward();
      commandStore("g");
      Serial.println(input);

      float tim = calculateTime();
      timStore(tim);
      Serial.println(tim);
    } else if (input == 'S') {
      stop();
      commandStore("s");
      Serial.println(input);

      float tim = calculateTime();
      timStore(tim);
      Serial.println(tim);
    } else if (input == 'T') {
      speed = 0;
      analogWrite(speedPin1, speed);
      analogWrite(speedPin2, speed);

      stop();
      transferData();

      speed = 100;
      analogWrite(speedPin1, speed);
      analogWrite(speedPin2, speed);
    }
  }
}

float calculateTime() {
  unsigned long startTime = millis();
  while (Serial.available() > 0) {
    Serial.read();  // Clear the serial buffer
  }
  while (!Serial.available()) {
    // Wait for a new command to be sent
  }
  unsigned long endTime = millis();
  float elapsedTime = endTime - startTime;  // Diving by 1000 to convert milliseconds to seconds
  return elapsedTime;
}

void commandStore(char *data) {
  commands[dataCount] = data;
  dataCount++;
}

void timStore(float tim) {
  timee[dataCount] = tim;
  dataCount++;
}

void transferData() {
  for (int i = 0; i < maxCommands; i++) {
    float mytime = timee[i];

    char *myOutput = commands[i];

    Serial.println(mytime);
    Serial.println(myOutput);

    vw_send((uint8_t *)myOutput, strlen(myOutput));
    vw_wait_tx();

    delay(mytime);
  }
}

void forward() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
}

void stop() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
}

void backward() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
}

void left() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
}

void right() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
}