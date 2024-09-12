/* This Arduino code toggles an LED connected to pin 13 whenever */
/* a button on pin 2 is pressed, with state feedback via Serial. */

// Define the pin connected to the button
const uint8_t BTN_PIN = 2;
// Define the pin connected to the LED
const uint8_t LED_PIN = 13;

// Initialize variables to track the previous state of the button and the current state of the LED
volatile uint8_t buttonPrevState = LOW;
volatile uint8_t ledState = LOW;

// Setup function to run once at the beginning
void setup()
{
  // Set the button pin as input with internal pull-up resistor
  pinMode(BTN_PIN, INPUT_PULLUP);
  // Set the LED pin as output
  pinMode(LED_PIN, OUTPUT);
  // Start serial communication at 9600 bps
  Serial.begin(9600);
  
  // Attach interrupt to handle button state changes
  attachInterrupt(digitalPinToInterrupt(BTN_PIN), buttonInterrupt, CHANGE);
}

// Loop function to run repeatedly
void loop()
{
  // No need for delay in the loop
  // Can be used to write other functionality
}

// Interrupt service routine to handle button state changes
void buttonInterrupt()
{
  // Read the current state of the button
  uint8_t buttonState = digitalRead(BTN_PIN);
  
  // Print button state, previous button state, LED state to serial monitor
  Serial.print(buttonState);
  Serial.print(buttonPrevState);
  Serial.print(ledState);
  Serial.println("");
  
  // Check if the button state has changed
  if(buttonState != buttonPrevState)
  {
    // Toggle the LED state
    ledState = !ledState;
    // Update the LED with the new state
    digitalWrite(LED_PIN, ledState);
  }
  
  // Update the previous button state
  buttonPrevState = buttonState;
}
