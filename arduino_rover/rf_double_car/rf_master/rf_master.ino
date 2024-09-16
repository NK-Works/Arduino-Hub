//   C++ Codes on Arduino IDE    //
//     Bluetooth-based Rover     //
//  Digital Twin with RF-Module  //
//   Transmitter-Master Rover    //

#include <Wire.h>
#include <VirtualWire.h>

// Setting up some variables
const int motorPin1 = 4;   // Green colour / Represents backward (alone & backward) right
const int motorPin2 = 6;   // Orange colour / Represents forward (alone & forward) left
const int motorPin3 = 10;  // Yellow color / Represents forward (alone & forward) right
const int motorPin4 = 11;  // Blue colour / Represents backward (alone & reverse) left
// Can change depending on how circuit is made and wiring is done
const int RfTxPin = 3;

// For RF Transmitter
char *data;

char input;  // Stores the input coming from the Bluetooth

void setup() {
  Serial.begin(9600);
  // Setting all the input and the output pins
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  vw_set_tx_pin(RfTxPin);
  vw_setup(2000);

  stop();
}

void loop() {
  // Taking the Bluetooth command
  if (Serial.available()) {
    input = Serial.read();
    Serial.println(input);

    if (input == 'F') {
      data = "f";
      vw_send((uint8_t *)data, strlen(data));
      vw_wait_tx();

      forward();
    } else if (input == 'R') {
      data = "r";
      vw_send((uint8_t *)data, strlen(data));
      vw_wait_tx();

      right();
    } else if (input == 'L') {
      data = "l";
      vw_send((uint8_t *)data, strlen(data));
      vw_wait_tx();

      left();
    } else if (input == 'G') {
      data = "g";
      vw_send((uint8_t *)data, strlen(data));
      vw_wait_tx();

      backward();
    } else if (input == 'S') {
      data = "s";
      vw_send((uint8_t *)data, strlen(data));
      vw_wait_tx();

      stop();
    }
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
  digitalWrite(motorPin4, HIGH);
}

void right() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
}