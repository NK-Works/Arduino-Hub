/* This code is made by Anneshu Nag, Student ID- 2201994760*/
/*    More-Inputs Board using Ultrasonic & 2 PIR Sensors   */
/*    Updating LED & Buzzer status using Interruption      */
/*     Sowing External, Internal and Timer Interrupts      */

// Assigning the LED pins for the interrupt outputs
const int ledPin1 = 8;  
const int ledPin2 = 9;  
const int ledPin3 = 11;

// Timer Interrupt using buzzer
const int buzzerPin = 12;

// Assigning the input pins for inducing the interrupts
const int pirInput1 = 2;  
const int pirInput2 = 4;

// Pins for the ultrasonic sensor
const int ultrasonicEchoPin = 3; 
const int ultrasonicTriggerPin = 7;

// Flags to keep track of the sensor inputs
int pir1Detected = LOW;
int ultrasonicDetected = LOW;
int pir2Detected = LOW;

void setup() {
  // Outputs from the LEDs
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

  pinMode(buzzerPin, OUTPUT);

  // Inputs from the sensors
  pinMode(pirInput1, INPUT);
  pinMode(pirInput2, INPUT);
  
  pinMode(ultrasonicTriggerPin, OUTPUT);
  pinMode(ultrasonicEchoPin, INPUT);

  Serial.begin(9600);  // Initialize serial communication

  // Attaching interruption for the PIR and the Ultrasonic Sensor
  attachInterrupt(digitalPinToInterrupt(pirInput1), pir1MotionDetection, CHANGE);   
  attachInterrupt(digitalPinToInterrupt(ultrasonicEchoPin), ultrasonicMotionDetection, CHANGE);

  // Setting up the internal interrupt
  pciSetup(4);
  // Setting up the timer interrupt
  startTimer(0.5);  // Start timer with frequency of 0.5Hz (buzz every 2 seconds)
}

void loop() {
  // Measuring the Ultrasonic sensor readings
  digitalWrite(ultrasonicTriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrasonicTriggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonicTriggerPin, LOW);

  // Measure the pulse duration from the ultrasonic sensor
  long duration = pulseIn(ultrasonicEchoPin, HIGH);
  int distance = duration / 58;  // Convert the pulse duration to distance in centimeters

  // Serial.print("\nDistance: ");
  // Serial.print(distance);
  // Serial.println(" cm\n");

  if (distance < 100) {
    Serial.println("Object detected by Ultrasonic Sensor.");  // Print detection status to Serial Monitor
      Serial.println("- BLUE LED ON -");
    ultrasonicDetected = HIGH;
  } else {
    ultrasonicDetected = LOW;
    Serial.println("No Object detected by Ultrasonic Sensor.");  // Print detection status to Serial Monitor
    Serial.println("- BLUE LED OFF -");
  }
  delay(1000);
}

void pciSetup(byte pin) {
  *digitalPinToPCMSK(pin) |= bit(digitalPinToPCMSKbit(pin));  // Enabling the Pin
  PCIFR |= bit(digitalPinToPCICRbit(pin));                    // Clearing any outstanding interrupt
  PCICR |= bit(digitalPinToPCICRbit(pin));                    // Enabling interrupt for the group
}

// Handle pin change interrupt for D0 to D7 here i.e. Internal Interrupt
ISR(PCINT2_vect)  
{
  pir2MotionDetection();
}

// Handle timer interrupt here
void startTimer(double timerFrequency) {
  noInterrupts();

  // Calculating the value for OCR1A based on the timer frequency
  uint16_t ocrValue = (uint16_t)((F_CPU / (1024.0 * timerFrequency)) - 1);

  // Set the Timer1 registers for CTC mode and set the OCR1A value
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = ocrValue;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);

  interrupts();
}

// Handle buzzer here
ISR(TIMER1_COMPA_vect) {
  // Buzz the buzzer
  digitalWrite(buzzerPin, digitalRead(buzzerPin) ^ 1);
}

// Handle PIR sensor 1 here
void pir1MotionDetection() {
  int val = digitalRead(pirInput1);
  // If motion is detected then perform this
  if (val == HIGH) {                                
    digitalWrite(ledPin1, HIGH);
    if (pir1Detected == LOW) {
      Serial.println("Motion detected on PIR Sensor 1.");
      Serial.println("- GREEN LED ON -");
      pir1Detected = HIGH;  // Set the pir1 flag to high as motion is detected
    }
  } else {  // If motion is stopped then do this 
    digitalWrite(ledPin1, LOW);
    if (pir1Detected == HIGH) {
      Serial.println("Motion stopped on PIR Sensor 1.");
      Serial.println("- GREEN LED OFF -");
      pir1Detected = LOW;  // Set the pir1 flag to low as motion is stopped
    }
  }
}

// Handle Ultrasonic sensor here
void ultrasonicMotionDetection() {
  if (ultrasonicDetected == HIGH) {
    digitalWrite(ledPin2, HIGH);
  } else {
    digitalWrite(ledPin2, LOW);
  }
}

// Handle PIR Sensor 2 here
void pir2MotionDetection() {
  int val = digitalRead(pirInput2);
  // If motion is detected then perform this
  if (val == HIGH) {
    digitalWrite(ledPin3, HIGH);
    if (pir2Detected == LOW) {
      Serial.println("Motion detected on PIR Sensor 2.");
      Serial.println("- RED LED ON -");
      pir2Detected = HIGH;  // Set the pir2 flag to high as motion is detected
    }
  } else {
    digitalWrite(ledPin3, LOW);
    if (pir2Detected == HIGH) {
      Serial.println("Motion ended on PIR Sensor 2.");
      Serial.println("- RED LED OFF -");
      pir2Detected = LOW;  // Set the pir2 flag to low as motion is stopped
    }
  }
}