// PIR Sensor //
const int pir_out = 2;
void setup() {
  pinMode(pir_out, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(pir_out) == HIGH) {
    Serial.println("HIGH: Detecting Signals!");
    digitalWrite(13, HIGH);
  } else {
    Serial.println("LOW: No Signals Avaialable!");
    digitalWrite(13, LOW);
  }
  delay(100);
}