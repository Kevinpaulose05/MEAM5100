void setup() {
  Serial.begin(115200); // Initialize serial communication at a baud rate of 115200
  pinMode(4, OUTPUT);  // set pin 4 as output (controlling LED)
  pinMode(1, INPUT);   // set pin 1 as input (reading the switch state)
}

void loop() {

  if (digitalRead(1) == HIGH) {       // switch is pressed
    Serial.println("Switch Pressed");
    digitalWrite(4, HIGH); // turn ON LED by setting pin 4 to HIGH
    delay(100);
  } else {             // switch is not pressed
    digitalWrite(4, LOW);  // // turn OFF LED by setting pin 4 to LOW
    // Serial.println("Switch Depressed");
    delay(100);
  }
}
