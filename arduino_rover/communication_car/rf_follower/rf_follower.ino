//   C++ Codes on Arduino IDE    //
//     Bluetooth-based Rover     //
//    Robotics Final Project     //
//    Reciever-Follower Module   //

#include <Wire.h>
#include <VirtualWire.h>

// Setting up some variables
const int motorPin1 = 4;   // Purple colour / Represents backward (alone & backward) right
const int motorPin2 = 6;   // WP Red / Represents forward (alone & forward) left
const int motorPin3 = 10;  // Red color / Represents forward (alone & forward right
const int motorPin4 = 12;  // Orange colour / Represents backward (alone & reverse alone
// Can Change depending on how circuit is connected and Wiring is done

const int speedPin1 = 3;  // Red color / Represents forward (alone & forward right
const int speedPin2 = 5;  // Orange colour / Represents backward (alone & reverse alone

const int RfRxPin = 11;

char rfInput;  // Stores the input coming from the RF
char *data;

const int speed = 145;

void setup() {
  Serial.begin(9600);
  // Setting all the input and the output pins
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  pinMode(speedPin1, OUTPUT);
  pinMode(speedPin2, OUTPUT);

  analogWrite(speedPin1, speed);
  analogWrite(speedPin2, speed);

  vw_set_rx_pin(RfRxPin);
  vw_setup(2000);
  pinMode(RfRxPin, INPUT);
  vw_rx_start();

  stop();
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  Serial.println(buf[0]);
  Serial.println(speed);

  if (vw_get_message(buf, &buflen)) {

    if (buf[0] == 'f') {
      forward();
      // delay(speed*10);
    } else if (buf[0] == 'r') {
      right();
    } else if (buf[0] == 'l') {
      left();
    } else if (buf[0] == 'g') {
      backward();
    } else if (buf[0] == 's') {
      stop();
    }
  }
  if (Serial.available()) {
    char command = Serial.read();

    if (command == 'F') {
      forward();
    } else if (command == 'R') {
      right();
    } else if (command == 'L') {
      left();
    } else if (command == 'G') {
      backward();
    } else if (command == 'S') {
      stop();
    }
  }
}

void stop() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
}

void right() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
}

void left() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
}
void forward() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
}

void backward() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
}