#define ANALOG_PIN A1   // Use a ADC-capable pin
#define LED A4        // Use a PWM-capable pin
int ledState = LOW;     // ledState used to set the LED
long previousMilli = 0;  // will store last time LED was updated

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);   // set LED pin as output

  // LEDC setup
  ledcSetup(0, 30, 12);  // LEDC channel 0, 30Hz frequency, 12-bit resolution
  ledcAttachPin(LED, 0);
  pinMode(ANALOG_PIN, INPUT); // set analog pin as input
}

void loop() {
  int dutyCycle;
  int potValue = analogRead(ANALOG_PIN);  // read the analog value from the potentiometer
  dutyCycle = map(potValue, 0 , 4095, 10, 1000); // map to 12-bit range (10-1000)

  // printing potentiometer values and corresponding duty cycles
  Serial.print("Potentiometer Value: ");
  Serial.print(potValue);
  delay(50);
  Serial.print("\t Duty Cycle: "); 
  Serial.println(dutyCycle);
  delay(50);

  unsigned long currentMilli = millis();
  if (currentMilli - previousMilli > 67) {  // 1000ms / 15Hz = 66.67ms
    previousMilli = currentMilli;

    // set LED brightness using LEDC PWM
    ledcWrite(0, dutyCycle);  // use LEDC channel 0 to set duty cycle

    // toggle LED state
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;

    // update the LED state
    digitalWrite(LED, ledState);
  }
}
