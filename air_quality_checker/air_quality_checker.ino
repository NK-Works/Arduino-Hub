#define LDRpin A0
int LDRValue = 0;

// lowest and highest sensor readings:
const int sensorMin = 0;     // sensor minimum
const int sensorMax = 1024;  // sensor maximum

int sensorPin = A3;
int sensorThreshold = 85;

void setup() {
  // initialize serial communication @ 9600 baud:
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
}

void loop() {
  // Read LDR sensor value
  LDRValue = analogRead(LDRpin);
  Serial.print("LDR Value: ");
  Serial.print(LDRValue);
  Serial.println();

  // read the sensor on analog A1:
  int sensorReading = analogRead(A1);
  // map the sensor range (four options):
  // ex: 'long  int map(long int, long int, long int, long int, long int)'
  int range = map(sensorReading, sensorMin, sensorMax, 0, 3);

  // range value:
  switch (range) {
    case 0:  // A fire closer than 1.5 feet away.
      Serial.println("** Close  Fire **");
      break;
    case 1:  // A fire between 1-3 feet away.
      Serial.println("**  Distant Fire **");
      break;
    case 2:  // No fire detected.
      Serial.println("No  Fire");
      break;
  }

  // Read Raw ADC Data for temperature
  int adcData = analogRead(A2);
  // Convert voltage into temperature in Celsius
  float temperatureC = adcData * (5.0 / 1024.0) * 100;

  // Print the temperature data in Celsius and Fahrenheit
  Serial.print(F("Temperature (Room Temp.)- C: "));
  Serial.print(temperatureC);
  Serial.println("°C");

  int sensorValue = analogRead(sensorPin);
  int outputValue = map(sensorValue, 0, 1023, 0, 255);
  Serial.print(outputValue);
  if (outputValue > sensorThreshold) {
    Serial.println(" | CO2 concentration in control!");
  } else {
    Serial.println(outputValue);
    Serial.println(" | CO2 concentration is dangerous");
  }

  Serial.println();

  delay(1000);
}
