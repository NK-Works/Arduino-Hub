//           C++ Codes on Arduino IDE           //
// Bluetooth-based Rover with Ultrasonic Sensor //

// Setting up some variables
int A = 9;
int B = 5;
int speed;

char input;  // Stores the input coming from the Bluetooth
long duration;
long distance;
const int MAX_DISTANCE = 35;  // Maximum distance threshold in centimeters

// Ultrasonic sensor pins
const int trigPin = 13;
const int echoPin = 12;

bool isBluetoothConnected = false;  // Flag to track Bluetooth connection status

void setup() {
  Serial.begin(9600);
  // Setting all the input and output pins
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  pinMode(9, OUTPUT);
  pinMode(5, OUTPUT);

  // Ultrasonic sensor pin modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // The potentiometer output is received and transformed here
  speed = 200;
  analogWrite(A, speed);
  analogWrite(B, speed);
}

void loop() {
  calculateDistance();
  // Check if the car is connected to Bluetooth
  if (Serial.available()) {
    isBluetoothConnected = true;
  } else {
    isBluetoothConnected = false;
  }

  if (distance > MAX_DISTANCE) {
    // Taking the Bluetooth command
    if (isBluetoothConnected) {
      if (Serial.available()) {
        input = Serial.read();
        Serial.println(speed);
        Serial.println(input);

        if (input == 'F') {
          forward();
        } else if (input == 'R') {
          right();
        } else if (input == 'L') {
          left();
        } else if (input == 'G') {
          backward();
        } else if (input == 'S') {
          stop();
        }
      }
    }
  }

  else if (isBluetoothConnected && distance <= MAX_DISTANCE) {
    stop();

    stop();
    delay(1000);
    backward();
    delay(1000);
    stop();
  }

  else if (!isBluetoothConnected && distance <= MAX_DISTANCE) {
    stop();
  }
}

void backward() {
  digitalWrite(4, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
}

void stop() {
  digitalWrite(4, LOW);
  digitalWrite(6, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}

void forward() {
  digitalWrite(4, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
}

void right() {
  digitalWrite(4, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
}

void left() {
  digitalWrite(4, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
}

void calculateDistance() {
  // Clear the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send the ultrasonic pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the echo pulse duration
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance
  distance = (duration / 29) / 2;  // Distance in centimeters
  Serial.println(distance);
  delay(100);
}