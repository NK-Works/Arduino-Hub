// IR- Receiver Code //
#include <IRremote.h>  // >v3.0.0
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 4);

#define PIN_RECV 7

void setup() {
  Serial.begin(9600);          //initialize serial connection to print on the Serial Monitor of the Arduino IDE
  IrReceiver.begin(PIN_RECV);  // Initializes the IR receiver object
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("Detecting...");
  delay(5000);
  lcd.clear();

  pinMode(4, OUTPUT);
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.println("Received something...");
    IrReceiver.printIRResultShort(&Serial);  // Prints a summary of the received data
    Serial.println();

    Serial.println("Detected Changes!");
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Chnages");
    lcd.setCursor(3, 1);
    lcd.print("Detected!");

    digitalWrite(4, HIGH);
    delay(1000);
    digitalWrite(4, LOW);

    IrReceiver.resume();  // Important, enables to receive the next IR signal
    delay(1000);
  } else {
    lcd.clear();
    Serial.println("Not Detected!");
    lcd.setCursor(0, 0);
    lcd.print("Not Detected!");
    delay(1000);
  }
}