/* This code is made by Anneshu Nag, Student ID- 2201994760*/
/*    LED blinks every 2 seconds using Timer Interrupt     */

const byte LED_PIN = 13;
const byte METER_PIN = A4;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(METER_PIN, INPUT);
  Serial.begin(9600);
  startTimer(0.5);
}

void loop() {
 // Read the analog value from the potentiometer
 int potValue = analogRead(METER_PIN);
 double timerFrequency = map(potValue, 0, 1023, 1, 10) / 10.0;
 Serial.println(timerFrequency);
 startTimer(timerFrequency);
 delay((1/timerFrequency) * 1000);
}
//  Setting up the Timer Interrupt 
void startTimer(double timerFrequency) {
  noInterrupts();
  
  // Calculate the timer period based on the timer frequency double
  double prescaler = 1024.0;
  double clockSpeed = 16000000.0;
  uint16_t timerPeriod = (uint16_t)((clockSpeed / (prescaler * timerFrequency))- 1);

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 31249;              // Setting compare match value (16MHz/1024/0.5Hz)
  TCCR1B |= (1 << WGM12);     // Turn on CTC mode
  TCCR1B |= (1 << CS12) | (1 << CS10); //Setting CS12 bit for 1024 prescaler
  TIMSK1 |= (1 << OCIE1A);  //Enable timer compare interrupt
  interrupts();
}

ISR(TIMER1_COMPA_vect) {
  digitalWrite(LED_PIN, digitalRead(LED_PIN) ^ 1);
}