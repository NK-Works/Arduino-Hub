//     This code is made by Anneshu Nag, Student ID- 2210994760     //
//                        Dated- 24/08/2023                         //

// In this code, I am sending the recorded data of the humidity and //
// temperature to the ThingSpeak website and creating a graph to    // 
// represent the collected data in the form of a graph.             //

// Include the required libraries for this application
#include <WiFiNINA.h>   // Required for the WiFi connection
#include "ThingSpeak.h"   // Required for establising communication with ThingSpeak website
#include "DHT.h"  // Required for reading the DHT sensor values

// Define the digital pin connected to the DHT sensor
#define DHTPIN 2
// Define the type of DHT sensor being used
#define DHTTYPE DHT22

// Initialize the DHT sensor with the specified pin and type
DHT dht(DHTPIN, DHTTYPE);

// Define the SSID (WiFi network name) and password for connection
#define SECRET_SSID "SSID"
#define SECRET_PASS "PASS"

// Define the ThingSpeak channel ID and write API key
#define SECRET_CH_ID CHANNEL_ID
#define SECRET_WRITE_APIKEY "API_KEY"

// Store the SSID and password in character arrays
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

// Initialize a WiFi client
WiFiClient client;

// Store the ThingSpeak channel number and write API key
unsigned long requiredChannelID = SECRET_CH_ID;
const char* requiredChannelAPIKey = SECRET_WRITE_APIKEY;

// Setup function runs once at the beginning
void setup() {
  // Start serial communication
  Serial.begin(9600);
  // Wait for serial connection to be established
  while (!Serial) {
  }

  // Check if communication with WiFi module failed
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("WiFi communication failed!");
    while (true)
      ;
  }
  // Initializing the internal LED to indicate if the WiFi connection if generated without looking into the serial monitor
  pinMode(LED_BUILTIN, OUTPUT);
  // Initialize ThingSpeak communication
  ThingSpeak.begin(client);
  // Initialize DHT sensor
  dht.begin();
}

// Loop function runs repeatedly
void loop() {
  // Delay for 2 seconds
  delay(2000);

  // Check if WiFi is not connected
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to SSID: ");
    Serial.println(SECRET_SSID);
    
    // Keep attempting to connect until connected
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, pass);
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnection Generated.");
  }
  // Turn on the built-in LED to indicated WiFi connection establishment
  digitalWrite(LED_BUILTIN, HIGH);

  // Read humidity and temperature from DHT sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if DHT sensor reading is valid
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print humidity and temperature readings
  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(temperature);
  Serial.print(F("°C "));

  // Set ThingSpeak fields with humidity and temperature values
  ThingSpeak.setField(1, humidity);
  ThingSpeak.setField(2, temperature);

  // Send data to ThingSpeak channel and check for success
  int updateData = ThingSpeak.writeFields(requiredChannelID, requiredChannelAPIKey);
  if (updateData == 200) {
    Serial.println("Channel update successful.");
  } else {
    Serial.println("Problem updating channel. HTTP error code " + String(updateData));
  }

  // Delay for 30 seconds before looping again 
  delay(30000);
}
