//   C++ Codes on Arduino IDE    //
//     Bluetooth-based Rover     //
//  Digital Twin with RF-Module  //
//    Reciever-Follower Rover    //

#include <Wire.h>
#include <VirtualWire.h>

// Setting up some variables
const int motorPin1 = 4;   // Purple colour / Represents backward (alone & backward) right
const int motorPin2 = 6;   // WP Red / Represents forward (alone & forward) left
const int motorPin3 = 10;  // Red color / Represents forward (alone & forward right
const int motorPin4 = 11;  // Orange colour / Represents backward (alone & reverse alone
// Can Change depending on how circuit is connected and Wiring is done
const int RfRxPin = 3;

char rfInput;  // Stores the input coming from the RF
char *data;

void setup() {
  Serial.begin(9600);
  // Setting all the input and the output pins
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

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
  if (vw_get_message(buf, &buflen)) {
    if (buf[0] == 'f') {
      forward();
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