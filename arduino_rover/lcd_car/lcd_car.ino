// C++ Codes on Arduino IDE //
//   Bluetooth-based Rover  //
//       LCD with I2C       //

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Setting up some variables
const int motorPin1 = 4; // Green colour / Represents backward (alone & backward) right
const int motorPin2 = 6; // Orange colour / Represents forward (alone & forward) left
const int motorPin3 = 10; // Yellow color / Represents forward (alone & forward) right
const int motorPin4 = 11; // Blue colour / Represents backward (alone & reverse) left
const int speedPinA = 9; 
const int speedPinB = 5;
const int potPin = A0;

// The speed variable keeps the value of the speed of the car
int speed; 

// The below line sets the display or lcd address to the 0x27 for the 16 chracter and two line
LiquidCrystal_I2C lcd(0x27, 16, 4);

char input;    // Stores the input coming from the Bluetooth

void setup()
{
  Serial.begin(9600);
  // Setting all the input and the output pins
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(potPin,INPUT);
  pinMode(speedPinA, OUTPUT); 
  pinMode(speedPinB,OUTPUT);
  
  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("Connecting...");
  lcd.setCursor(0,1);
  lcd.print("COMMAND TO CHECK");
}

void loop()
{
  // The potentiometer output is recieved and transformed here
  speed = analogRead(potPin);
  speed = speed * 0.249;
  analogWrite(speedPinA,speed);
  analogWrite(speedPinB,speed);

  if (Serial.available())
  {
    delay(100); 
    lcd.clear();

    // Taking the Bluetooth command
    while(Serial.available())
    {
      input = Serial.read();
      
      if(input == 'F')
      {
        lcd.setCursor(0, 0);
        lcd.print("Forward! S= ");
        lcd.print(speed);
        lcd.setCursor(0, 1);
        lcd.print("Don't Rush Press");
        forward();
      }

      else if (input == 'R')
      {
        lcd.setCursor(0, 0);
        lcd.print("Right! S= ");
        lcd.print(speed);
        lcd.setCursor(0, 1);
        lcd.print("Don't Rush Press");
        right(); 
      }

      else if (input == 'L')
      {
        lcd.setCursor(0, 0);
        lcd.print("Left! S= ");
        lcd.print(speed);
        lcd.setCursor(0, 1);
        lcd.print("Don't Rush Press");
        left();
      }  

      else if (input == 'G')
      {
        lcd.setCursor(0, 0);
        lcd.print("Backward! S= ");
        lcd.print(speed);
        lcd.setCursor(0, 1);
        lcd.print("Don't Rush Press");
        backward();
      }  
      else if (input == 'S')
      {
        lcd.setCursor(0, 0);
        lcd.print("Stop Car! S= 0");
        lcd.setCursor(0, 1);
        lcd.print("Press a Command");
        stop();
      }
    } 
  }
}  
void forward()
  {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    digitalWrite(motorPin3, HIGH);
    digitalWrite(motorPin4, LOW);
  }

void stop()
  {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, LOW);
  }

void backward()
  {
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, HIGH);
  }

void left()
  {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, HIGH);
  }

void right()
  {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
}