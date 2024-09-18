/* This code is made by Anneshu Nag, Student ID- 2210994760  */
/*                    Dated- 30/08/2023                      */

#include <WiFiNINA.h>
#include <Wire.h>
#include <BH1750.h>

// WiFi credentials
char ssid[] = "SSID";
char pass[] = "PASS";

WiFiClient myClient;
BH1750 lightMeter;  // Create an instance of the BH1750 light sensor library
const int ledCheck = 2;

char HOST_NAME[] = "maker.ifttt.com";   // Website
String PATH_NAME = "TRIGGER_NAME";  // Key and Trigger

void setup() {
  // Start WiFi connection
  WiFi.begin(ssid, pass);
  Serial.begin(9600);
  pinMode(ledCheck, OUTPUT);

  // Wait until Serial is ready
  while (!Serial)
    ;

  // Attempt to connect to WiFi
  while (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, pass);
    Serial.println("Connecting to WiFi...");
    delay(1000);
  }
  Serial.println("WiFi - Connected.\n");

  Wire.begin();
  lightMeter.begin();
  Serial.println("+ Light-Intensity Sensing Started! +");
  delay(500);

  // Print a header for the program
  Serial.println("------------------------------");
  Serial.println("|     IFTTT - Webhook        |");
  Serial.println("|     -By Anneshu Nag        |");
  Serial.println("------------------------------");
}

void loop() {
  float lux = lightMeter.readLightLevel();
  Serial.print("Light Intensity: ");
  Serial.println(lux);

  // The conditions are specified here
  if (lux > 1000) {
    Serial.println("Condition is Triggered!");
    Serial.println(">> It's very bright!");
    sendDatatoIFTTT("Bright_Light:", lux);   // Sending data for this condition
  } else if (lux > 600) {
    Serial.println("Condition is not Triggered!");
    Serial.println(">> It's moderately bright.\n");  // Not sending data for this condition
  } else if (lux > 200) {
    Serial.println("Condition is not Triggered!");
    Serial.println(">> It's a bit dim.\n");   // Not sending data for this condition
  } else {
    Serial.println("Condition is Triggered!");
    Serial.println(">> It's dark.");
    sendDatatoIFTTT("Dim:", lux);   // Sending data for this condition
  }

  delay(10000);  // Delay before looping again
}

void sendDatatoIFTTT(String msg, float luxVal) {
  // Check WiFi connection and client connection
  if (!myClient.connected() && WiFi.status() == WL_CONNECTED) {
    if (myClient.connect(HOST_NAME, 80)) {
      Serial.println("\nConnected to server.\n");
    } else {
      Serial.println("\nConnection failed.\n");
    }
  }
  // Prepare the payload and send the HTTP request
  String payLoad = "?value1=" + msg + "&value2=" + String(luxVal);
  myClient.println("GET " + PATH_NAME + payLoad + " HTTP/1.1");
  myClient.println("Host: " + String(HOST_NAME));
  myClient.println("Connection: close");
  myClient.println();

  // Read and print the server response
  while (myClient.connected()) {
    if (myClient.available()) {
      char c = myClient.read();
      Serial.print(c);
    }
  }
  Serial.println(" \n");
}