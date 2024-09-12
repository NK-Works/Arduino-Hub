/* This code is made by Anneshu Nag, Student ID- 2201994760*/
/*   Sense-Think-Act Board using Ultrasonic & PIR Sensor   */
/*          Updating LED status using Interruption         */

const int triggerPin = 9;  // Trigger pin for ultrasonic sensor
const int echoPin = 2;     // Echo pin for ultrasonic sensor
const int pirPin = 3;      // PIR sensor pin
const int ledPin = 13;     // Built-in LED pin

volatile bool objectDetected = false;  // Flag to indicate object detection

void setup() {
  Serial.begin(9600);      // Initialize serial communication
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // Attach the interrupt to the interruptFunction on CHANGE edge of echoPin
  attachInterrupt(digitalPinToInterrupt(echoPin), interruptFunction, CHANGE);
}

void loop() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // Measure the pulse duration from the ultrasonic sensor
  long duration = pulseIn(echoPin, HIGH);
  // Convert the pulse duration to distance in centimeters
  int distance = duration / 58;

  Serial.print("\nDistance: ");
  Serial.print(distance);
  Serial.println(" cm\n");

  if (distance < 100) {
    objectDetected = true;
    // Print detection status to Serial Monitor
    Serial.println("Object detected by Ultrasonic Sensor!");
  } else if (digitalRead(pirPin) == HIGH) {
    Serial.println("Object detected by PIR sensor!");
    objectDetected = true;
  } else {
    objectDetected = false;
    Serial.println("No object detected by eithor of the sensors.");
    digitalWrite(ledPin, LOW); 
  }
  
  delay(1000);  // Add delay for stability
}

// Interrupt function to control the LED based on the echoPin state
void interruptFunction() {
  if (objectDetected) {
    digitalWrite(ledPin, HIGH);         
  }
}