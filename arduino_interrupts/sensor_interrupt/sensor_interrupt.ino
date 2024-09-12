/* This code is made by Anneshu Nag, Student ID- 2201994760*/
/*   Sense-Think-Act Board using Ultrasonic Motion Sensor  */
/*          Updating LED status using Interruption         */

const int triggerPin = 9;  // Trigger pin for ultrasonic sensor
const int echoPin = 2;     // Echo pin for ultrasonic sensor
const int ledPin = 13;     // Built-in LED pin

volatile bool objectDetected = false;  // Flag to indicate object detection

void setup() {
  Serial.begin(9600);      // Initialize serial communication
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
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
  int distance = duration / 58;  // Convert the pulse duration to distance in centimeters

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 100) {
    objectDetected = true;
  } else {
    objectDetected = false;
  }

  delay(1000);  // Add delay for stability
}

// Interrupt function to control the LED based on the echoPin state
void interruptFunction() {
  if (objectDetected) {
    Serial.println("Object detected!");  // Print detection status to Serial Monitor
    digitalWrite(ledPin, HIGH);          
  } else {
    Serial.println("No object detected.");  
    digitalWrite(ledPin, LOW);              
  }
}
