/* This code is made by Anneshu Nag, Student ID- 2210994760  */
/*                    Dated- 30/08/2023                      */

#include <WiFiNINA.h>

// WiFi credentials
char ssid[] = "My Network-NK";
char pass[] = "19782003";

WiFiClient myClient;

char HOST_NAME[] = "maker.ifttt.com";  // Website
String PATH_NAME = ""; // Key and Trigger
String queryString = "?value1=";

#define LDRpin A0
int LDRValue = 0;

void setup() {
  // Start WiFi connection
  WiFi.begin(ssid, pass);
  Serial.begin(9600);
  
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

  // Print a header for the program
  Serial.println("------------------------------");
  Serial.println("|     IFTTT - Webhook        |");
  Serial.println("|     -By Anneshu Nag        |");
  Serial.println("|   Press 's' to send data   |");
  Serial.println("------------------------------");
}

void loop() {
  // Read LDR sensor value
  LDRValue = analogRead(LDRpin);
  Serial.print("LDR Value: ");
  Serial.print(LDRValue);

  // Read input from Serial Monitor
  char input = Serial.read();
  if (input == 's') {
    Serial.println("");

    // Check WiFi connection and client connection
    if (!myClient.connected() && WiFi.status() == WL_CONNECTED) {
      if (myClient.connect(HOST_NAME, 80)) {
        Serial.println("\nConnected to server.\n");
      } else {
        Serial.println("\nConnection failed.\n");
      }
    }
    // Prepare the payload and send the HTTP request
    String payload = queryString + String(LDRValue);
    myClient.println("GET " + PATH_NAME + payload + " HTTP/1.1");
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
  } else if (input == 'q') {
    Serial.println("");
    // Stop client connection and print a message
    myClient.stop();
    Serial.println();
    Serial.println("Destructive action initiated...");
    Serial.println("*Enter 's' to regenerate connection.*");
    Serial.println("Disconnected.\n");
  } else {
    Serial.println(" | Not sending any data...");
  }
  delay(2000); // Delay before looping again
}