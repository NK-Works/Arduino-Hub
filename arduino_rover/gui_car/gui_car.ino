//  C++ Codes on Arduino IDE  //
//    Bluetooth-based Rover   //
//        LCD with I2C        //
//         GUI Control        //
//  Speed Control through GUI //
//    Delay Input-Contorl     //

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Setting up some variables
const int motorPin1 = 4;   // Green colour / Represents backward (alone & backward) right
const int motorPin2 = 6;   // Orange colour / Represents forward (alone & forward) left
const int motorPin3 = 10;  // Yellow color / Represents forward (alone & forward) right
const int motorPin4 = 11;  // Blue colour / Represents backward (alone & reverse) left

const int speedPinA = 9;
const int speedPinB = 5;

// The speed variable keeps the value of the speed of the car
int speed;

// The below line sets the display or lcd address to the 0x27 for the 16 chracter and two line
LiquidCrystal_I2C lcd(0x27, 16, 4);

String input;  // Stores the input coming from the Bluetooth

String command;    // Stores the directional command
int delayOrspeed;  // Stores the time or speed part of the input

void setup() {
  Serial.begin(9600);
  // Setting all the input and the output pins
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(speedPinA, OUTPUT);
  pinMode(speedPinB, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("Connecting...");
  lcd.setCursor(0, 1);
  lcd.print("COMMAND TO CHECK");
  delay(3000);

  speed = 0;
  analogWrite(speedPinA, speed);
  analogWrite(speedPinB, speed);

  lcd.clear();
  stop();
}

void loop() {

  if (Serial.available()) {
    delay(100);
    lcd.clear();

    // Taking the Bluetooth command
    while (Serial.available()) {
      input = Serial.readString();

      // Splitting the command into command and delay/speed parts
      int spaceIndex = input.indexOf(' ');  // Find the index of the space character

      command = input.substring(0, spaceIndex);                // Extracting the command substring
      delayOrspeed = input.substring(spaceIndex + 1).toInt();  // Extracting the delay/speed substring and convert to integer

      if (command == "forward") {
        Serial.println(command);
        Serial.println(delayOrspeed);

        lcd.setCursor(0, 0);
        lcd.print("Forward! S= ");
        lcd.print(speed);
        lcd.setCursor(0, 1);
        lcd.print("Don't Rush Press");
        forward();

        delay(delayOrspeed * 1000);
        lcd.clear();
        stop();
      }

      else if (command == "right") {
        Serial.println(command);
        Serial.println(delayOrspeed);

        lcd.setCursor(0, 0);
        lcd.print("Right! S= ");
        lcd.print(speed);
        lcd.setCursor(0, 1);
        lcd.print("Don't Rush Press");
        right();

        delay(delayOrspeed * 1000);
        lcd.clear();
        stop();
      }

      else if (command == "left") {
        Serial.println(command);
        Serial.println(delayOrspeed);

        lcd.setCursor(0, 0);
        lcd.print("Left! S= ");
        lcd.print(speed);
        lcd.setCursor(0, 1);
        lcd.print("Don't Rush Press");
        left();

        delay(delayOrspeed * 1000);
        lcd.clear();
        stop();
      }

      else if (command == "backward") {
        Serial.println(command);
        Serial.println(delayOrspeed);

        lcd.setCursor(0, 0);
        lcd.print("Backward! S= ");
        lcd.print(speed);
        lcd.setCursor(0, 1);
        lcd.print("Don't Rush Press");
        backward();

        delay(delayOrspeed * 1000);
        lcd.clear();
        stop();
      }

      else if (command == "stop") {
        Serial.println(command);
        Serial.println(delayOrspeed);

        stop();
        lcd.clear();
      }

      else if (command == "speed") {
        Serial.println(command);

        speed = delayOrspeed;
        Serial.println(speed);

        lcd.setCursor(2, 0);
        lcd.print("Speed: ");
        lcd.print(speed);
        lcd.setCursor(0, 1);
        lcd.print("Don't Rush Press");

        analogWrite(speedPinA, speed);
        analogWrite(speedPinB, speed);
      }

      else if (command == "quit") {
        Serial.println(command);
        lcd.setCursor(1, 0);
        lcd.print("Reverting Ops!");
        lcd.setCursor(0, 1);
        lcd.print("Reverting S= ");
        lcd.print(speed);

        delay(delayOrspeed * 1000);
        lcd.clear();
        setup();
      }
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
  lcd.setCursor(2, 0);
  lcd.print("Car Stopped!");
  lcd.setCursor(2, 1);
  lcd.print("Stored S= ");
  lcd.print(speed);

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