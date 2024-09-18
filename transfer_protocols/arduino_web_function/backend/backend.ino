/* This code is made by Anneshu Nag, Student ID- 2210994760  */
/*                    Dated- 02/09/2023                      */

/* This is the Arduino code that connects to the firebase real-times database. */

// Importing the required libraries for building this project
#include <Firebase_Arduino_WiFiNINA.h>

// Configuring firebase
#define FIREBASE_HOST "FIREBASE_HOST"
#define FIREBASE_AUTH "FIREBASE_AUTH"

// Defining the pins for the LED
const int redLED = 2;
const int yellowLED = 3;
const int greenLED = 4;

// Setting up the WiFi
char ssid[] = "SSID";
char pass[] = "PASS";

// Creating the firebase object
FirebaseData object;
// Defining the path of the database where the data is stored
String path = "/mypath/caught";

// Setup function
void setup()
{
  Serial.begin(9600);
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  // Connecting to the WiFi
  while (WiFi.begin(ssid, pass) != WL_CONNECTED)
  {
    Serial.print(".");
    delay(5000);
  }

  Serial.print("You're connected to the ");
  Serial.println(ssid);
  Serial.print("WiFi localIP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  // Initialising the firebase connection
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, ssid, pass);
  Firebase.reconnectWiFi(true);

  // Setting up with all LEDs off 
  if (Firebase.setString(object, path, "switchoff"))
  {
    Serial.println("Setup Complete!");
  }
  else
  {
    Serial.println("Error: " + object.errorReason());
  }
}

// The loop function
void loop()
{
  // Fetching the data from firebase database
  if (Firebase.getString(object, path))
  {
    // Comparing the data fetched with the statements given
    if (object.stringData() == "red")
    {
      digitalWrite(redLED, HIGH);
      digitalWrite(yellowLED, LOW);
      digitalWrite(greenLED, LOW);
      Serial.println("Red LED is on.");  
    }
    else if (object.stringData() == "yellow")
    {
      digitalWrite(redLED, LOW);
      digitalWrite(yellowLED, HIGH);
      digitalWrite(greenLED, LOW);
      Serial.println("Yellow LED is on.");
    }
    else if (object.stringData() == "green")
    {
      digitalWrite(yellowLED, LOW);
      digitalWrite(redLED, LOW);
      digitalWrite(greenLED, HIGH);
      Serial.println("Green LED is on.");
    }
    else if (object.stringData() == "switchoff")
    {
      digitalWrite(yellowLED, LOW);
      digitalWrite(redLED, LOW);
      digitalWrite(greenLED, LOW);
      Serial.println("All LEDs are off.");
    }
   
  }
  else
  {
    Serial.println("Error!");
  }
}