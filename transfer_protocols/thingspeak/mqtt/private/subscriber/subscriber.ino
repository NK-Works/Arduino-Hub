#include <PubSubClient.h>
#include <WiFiNINA.h>

const char ssid[] = "SSID";
const char pass[] = "PASS";
const char broker[] = "BROKER";
int port = 8883;

const char mqttUser[] = "USER_NAME";
const char mqttPass[] = "USER_PASS";

WiFiSSLClient net;
PubSubClient client(net);

const int ledPin = 4;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("WiFi connected.");

  client.setServer(broker, port);
  client.setCallback(callback);
}

void callback(char* topic, byte* payload, unsigned int length) {
  String payloadStr;
  for (unsigned int i = 0; i < length; i++) {
    payloadStr += (char)payload[i];
  }

  Serial.print("Received message on topic: ");
  Serial.println(topic);
  Serial.print("Message payload: ");
  Serial.println(payloadStr);

  if (String(topic) == "Task3.3" && payloadStr == "wave") {
    Serial.println("Received 'wave' message");
    
    // Flash the LED three times
    for (int i = 0; i < 3; i++) {
      digitalWrite(ledPin, HIGH);
      delay(300);
      digitalWrite(ledPin, LOW);
      delay(300);
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ArduinoClient", mqttUser, mqttPass)) {
      Serial.println("Connected to MQTT broker");
      client.subscribe("Task3.3");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
