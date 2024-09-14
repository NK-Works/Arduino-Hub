#include "SPI.h"
#include "MFRC522.h"

#define SS_PIN 10
#define RST_PIN 9


MFRC522 rfid(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
 
  Serial.println("waiting for card...");
}
void loop() {
  // put your main code here, to run repeatedly:
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  // Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  // Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }
  String strID = "";
  for (byte i = 0; i < 4; i++) {
    strID +=
      (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
      String(rfid.uid.uidByte[i], HEX) +
      (i != 3 ? ":" : "");
  }
  strID.toUpperCase();
  //Serial.print("Tap card key: ");
  //Serial.println(strID);
  delay(500);

  if (strID.indexOf("2D:32:3F:7A") >= 0) {  //put your own tap card key;   put your own rfid code of the tag in " C6:05:DA:2B "
   
    
    Serial.println("*Authorised acces*");
  
  }
  else 
  {
   
    Serial.println("*Acces denied*");
   
  }
  
}