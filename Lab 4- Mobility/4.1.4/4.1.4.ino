#include "WebpageLab4_1_4.h"
#include "html510.h"

const char* ssid = "Kevin_router";  // specified SSID for the access point
const char* password = "";
HTML510Server h(80); // create an HTTP server on port 80

// Motor control pins connected to the SN754410
const int enablePin = 5; // Enable pin (EN)
const int motorinput_1 = 7;    // Input 1
const int motorinput_2 = 8;    // Input 2 

//LEDC
const int ledcChannel = 1;  //LEDC channel for PWM control
const int ledcResolution = 14;    // LEDC resolution (14-bit)

void handleRoot(){
  Serial.println("Handling root...");
  h.sendhtml(body);
}
void MotorSpeedHandler() {
  int speed= h.getVal();
  Serial.print("% speed of motor : ");
  Serial.println(speed);
  ledcWrite(ledcChannel, 12000 * 0.01 * speed);
  delay(10);
  h.sendhtml("");
}

void MotorDirectionHandler() {
  String action = h.getText();
  Serial.print("Setting motor direction to: ");
  Serial.println(action);
  if (action == "forward") {
    // Set motor direction to forward
    digitalWrite(motorinput_1, HIGH);
    digitalWrite(motorinput_2, LOW);
  } else if (action == "reverse") {
    // Set motor direction to reverse
    digitalWrite(motorinput_1, LOW);
    digitalWrite(motorinput_2, HIGH);
  } else if (action == "STOP") {
    // Stop motor
    digitalWrite(motorinput_1, LOW);
    digitalWrite(motorinput_2, LOW);
  }
}
void setup() {
  Serial.begin(115200);

  // Initialize motor control pins
  pinMode(enablePin, OUTPUT);
  pinMode(motorinput_1, OUTPUT);
  pinMode(motorinput_2, OUTPUT);

  // Set up LEDC for PWM
  ledcSetup(ledcChannel, 100, ledcResolution ); // configure LEDC settings
  ledcAttachPin(enablePin, ledcChannel ); // Attach PWM channel to the enablePin

  // Connect to Wi-Fi
  Serial.begin(115200);
  Serial.print("Access Point ");
  Serial.print(ssid);
  WiFi.softAP(ssid,password);
  WiFi.softAPConfig(IPAddress(192, 168, 1, 171), IPAddress(192, 168, 5, 2), IPAddress(255, 255, 255, 0));


  h.begin();

  // set up routes for controlling motor speed and direction
  h.attachHandler("/motor?speed=", MotorSpeedHandler);
  h.attachHandler("/motor?direction=", MotorDirectionHandler);
  h.attachHandler("/", handleRoot);
}

void loop() {
  h.serve();
  delay(10);
}
