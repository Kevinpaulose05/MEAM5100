#include "WebpageLab4_1_EC2.h"
#include "html510.h"

#define ENCODER_PIN 18  // connected to D-18 (GPIO 18) pin of ESP32
#define ENCODER_NUMBER 20   //number of slits in the encoder
 
const char* ssid = "Kevin_router";  // specified SSID for the access point
const char* password = "";
HTML510Server h(80); // create an HTTP server on port 80

// Motor control pins connected to the SN754410
const int enablePin = 5; // Enable pin (EN)
const int motorinput_1 = 7;    // Input 1
const int motorinput_2 = 8;    // Input 2 

//LEDC
const int ledcChannel = 1;
const int ledcResolution = 14;

// Variables for Encoder (ChatGPT logic prompt)
unsigned long T1 = 0, T2 = 0, T;  // Time variables for measuring RPM
bool MeasDone = 0;                // Flag for measuring state
int Motor_RPM = 0;                // Motor RPM value

void INT0_ISR(void)
{
  if(MeasDone)
  {
    T2 = micros();
    T = T2 - T1;
    MeasDone = 0;
  }
  else
  {
    T1 = micros();
    MeasDone = 1;
  }
}
 

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
  } else if (action == "backward") {
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

  // Encoder
  pinMode(ENCODER_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN), INT0_ISR, RISING);

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
  Motor_RPM = (60000000) / (T * ENCODER_NUMBER); // 1 minute = 60,00,000 microseconds
  Serial.print("Motor RPM: ");
  Serial.println(Motor_RPM);
  delay(100);
}