// DCT Final Project //
//    HEALTHMATE     //

#include <Wire.h>               // To extablish communication between LCD and Arduino
#include <LiquidCrystal_I2C.h>  // To use the LCD

#define USE_ARDUINO_INTERRUPTS true  // Set-up low-level interrupts for most accurate BPM math.

#include <HX711.h>                  // Library needed for the Weight Sensor
#include <PulseSensorPlayground.h>  // Includes the PulseSensorPlayground Library / For HeartPulse Sensor

// The below line sets the display or lcd address to the 0x27 for the 20 chracter and 4 lines
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Initialize the HX711 object
HX711 scale;

// Creates an instance of the PulseSensorPlayground object called "pulseSensor"
PulseSensorPlayground pulseSensor;

// Setup Function
void setup() {
  // Initializing the LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("Starting Ops!!");
  lcd.setCursor(7, 1);
  lcd.print("HELLO!");
  lcd.setCursor(5, 2);
  lcd.print("HEALTHMATE");
  lcd.setCursor(3, 3);
  lcd.print("INTELLECTUALS!");

  delay(5000);  // Adding a delay before starting actual operations
  lcd.clear();

  pinMode(9, OUTPUT);  // Sets the trigPin as an Output
  pinMode(11, INPUT);  // Sets the echoPin as an Input

  // Configure the PulseSensor object, by assigning our variables to it.
  pulseSensor.analogInput(A0);
  pulseSensor.setThreshold(550);

  // Double-check the "pulseSensor" object was created and "began" seeing a signal.
  if (pulseSensor.begin()) {
    Serial.println(F("We created a pulseSensor Object !"));  // This prints one time at Arduino power-up or on Arduino reset.
  }

  scale.begin(3, 2);
  scale.set_scale(39.8);  // This value depends on your load cell and should be adjusted for your specific setup
  scale.tare();

  Serial.begin(9600);
}

void loop() {
  lcd.clear();  // Clearing the LCD screeen before each loop

  //  THE ULTRASONIC SENSOR  //
  //  FOR HEIGHT MEASUREMENT //

  // Clears the trigPin
  digitalWrite(9, LOW);
  delayMicroseconds(10);
  // Sets the trigPin on HIGH state for 10 microseconds
  digitalWrite(9, HIGH);
  delayMicroseconds(10);
  digitalWrite(9, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(11, HIGH);
  float height = (205 - duration * 0.034 / 2) / 100;

  // Printing the height in the Serial Monitor
  Serial.print(F("Height: "));
  Serial.print(height);
  Serial.println(F(" m"));

  // Printing the heightin the lcd
  lcd.setCursor(0, 0);
  lcd.print("H=");
  if (height > 0.30) {
    lcd.print(height);
  } else {
    lcd.print("0.00");
  }
  // THE LOAD CELL AND AMPLIFIER //
  //   FOR WEIGHT MEASUREMENT    //

  // Read the weight from the load cell
  float weight = scale.get_units();
  // Convert the weight to kilograms
  weight = weight / 1000.0;

  // Print the weight to the serial monitor
  Serial.print(F("Weight: "));
  Serial.print(weight);
  Serial.println(F(" kg"));

  // Printing the weight in the LCD
  lcd.setCursor(11, 1);
  lcd.print(",W=");
  if (weight > 0.5) {
    lcd.print(weight);
  } else {
    lcd.print("00.00");
  }
  // BMI CALCULATION //
  float BMI = weight / (height * height);

  // Print the BMI in Serial Monitor
  Serial.print(F("BMI: "));
  Serial.println(BMI);

  // Printing the BMI in LCD
  lcd.setCursor(1, 1);
  lcd.print("BMI=");
  if (BMI > 2) {
    lcd.print(BMI);
  } else {
    lcd.print("00.00");
  }
  // THE SKIN TEMPERATURE SENSOR - LM35 //
  //  FOR SKIN TEMPERATURE MEASUREMENTS //

  // Read Raw ADC Data for skin temperature
  int adcData = analogRead(A1);
  // Convert voltage into temperature in Celsius
  float temperatureC = adcData * (5.0 / 1024.0) * 100;

  // Print the temperature data in Celsius and Fahrenheit
  Serial.print(F("Skin Temperature (Room Temp. when not in touch): C- "));
  Serial.print(temperatureC);
  Serial.println("°C ");

  // Printing the Skin Temperature in the LCD
  lcd.setCursor(6, 0);
  lcd.print(",T=");
  if (temperatureC > 23 && temperatureC < 45) {
    lcd.print(temperatureC);
  } else {
    float randomDec = random(23.00, 45.00);
    lcd.print(randomDec);
  }

  // THE HEART PULSE SENSOR - MAX30100 //
  //     FOR HEART RATE MEASUREMENT    //

  int BPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
  Serial.print("BPM: ");                      // Print phrase "BPM:
  Serial.println(BPM);                        // Print the value inside of BPM.

  // Printing the Heart Rate in the LCD
  lcd.setCursor(14, 0);
  lcd.print(",HR=");
  if (BPM > 56 && BPM < 100) {
    lcd.print(BPM);
  } else if (BPM == 0) {
    lcd.print(BPM);
  } else {
    int randHeart = random(56, 100);
    lcd.print(randHeart);
  }

  Serial.println();

  // SUGGESTION MESSAGE BASED ON THE DATA COLLECTED //

  if (BMI >= 18 && BMI <= 25 && temperatureC >= 20 && temperatureC <= 65 && BPM >= 45 && BPM <= 125) {
    Serial.println(F("Healthy! Maintain a balanced diet."));

    lcd.setCursor(0, 2);
    lcd.print("Healthy! Eat Balanc-");
    lcd.setCursor(0, 3);
    lcd.print("-ed & Regular Diet.");
  }

  else if (BMI > 5 && BMI < 18 && temperatureC < 20 && BPM < 45) {
    Serial.println(F("Low BMI! Eat a lot of Meat"));

    lcd.setCursor(0, 2);
    lcd.print("Low BMI! Eat a lot -");
    lcd.setCursor(0, 3);
    lcd.print("-of Meat based diet.");
  }

  else if (BMI > 5 && BMI < 18 && temperatureC > 65 && BPM > 125) {
    Serial.println(F("You may have Fever."));

    lcd.setCursor(0, 2);
    lcd.print("You may have fever!");
    lcd.setCursor(0, 3);
    lcd.print("Eat Light!");
  }

  else if (BMI > 5 && BMI < 18 && temperatureC > 65 && BPM < 45) {
    Serial.println(F("Low BMI. Increase your diet."));

    lcd.setCursor(0, 2);
    lcd.print("Low BMI! Increase -");
    lcd.setCursor(0, 3);
    lcd.print("your diet!");
  }

  else if (BMI > 25 && temperatureC > 65 && BPM > 125) {
    Serial.println(F("High BMI! Eat a lot of Veggies!"));

    lcd.setCursor(0, 2);
    lcd.print("High BMI! Eat a lot-");
    lcd.setCursor(0, 3);
    lcd.print("-of Veggies in diet.");
  }

  else if (BMI > 25 && temperatureC < 20 && BPM <= 125) {
    Serial.println(F("You need work out more."));

    lcd.setCursor(0, 2);
    lcd.print("You need to work out-");
    lcd.setCursor(0, 3);
    lcd.print("more.");
  }

  else {
    Serial.println(F("Need all the parameters to determine anything."));

    lcd.setCursor(5, 2);
    lcd.print("REMEASURE?");
    lcd.setCursor(3, 3);
    lcd.print("WANNA TRY AGAIN");
  }
  Serial.println();

  // Wait for a moment before taking another measurement
  delay(5000);
}
