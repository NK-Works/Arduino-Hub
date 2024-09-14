/* This code is made by Anneshu Nag, Student ID- 2201994760*/
/* Sense-Think-Act Board using Ultrasonic Motion Sensor */

const int triggerPin = 9;  // Trigger pin for ultrasonic sensor
const int echoPin = 10;    // Echo pin for ultrasonic sensor
const int ledPin = 13;     // Built-in LED pin

void setup() {
  Serial.begin(9600);      // Initialize serial communication
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  long duration = pulseIn(echoPin, HIGH);  // Measure the pulse duration from the ultrasonic sensor
  int distance = duration / 58;           // Convert the pulse duration to distance in centimeters

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 100) {
    Serial.println("Object detected!");  // Print detection status to Serial Monitor
    digitalWrite(ledPin, HIGH);          // Turn on the LED
  } else {
    Serial.println("No object detected.");  // Print detection status to Serial Monitor
    digitalWrite(ledPin, LOW);              // Turn off the LED
  }

  delay(1000);  // Add a small delay for stability
}
