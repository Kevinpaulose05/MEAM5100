#include "html510.h"
#include "WebpageLab4_1_3b.h"

#define LED_PIN 1 // Use a PWM-capable pin (GPIO)
#define POT A4  // Use a ADC-capable pin

HTML510Server h(80);  // create an HTTP server instance on port 80
const char* ssid = "Kevin_webLED_router";  // specified SSID for the access point

void handleRoot() {
  h.sendhtml(body);
}

void handleBrightness() {
  int brightness = h.getVal(); // retrieve the brightness value from the request
  int PWM= map(brightness,0,100,0,12000); // map the brightness value to a PWM duty cycle
  Serial.print("Duty: ");
  Serial.println(PWM);
  ledcWrite(1, PWM); // control LED brightness using PWM on LEDC channel 1
  h.sendhtml(body); // send an HTML response
}

void handleFreq() {
  int freq = h.getVal(); // retrieve the frequency value from the request
  ledcSetup(1, freq, 14); // configure LEDC channel 1 with the specified frequency
  ledcAttachPin(LED_PIN, 1);
  Serial.print("freq: ");
  Serial.println(freq);
  h.sendhtml(body); // send an HTML response
}

void setup() {
  pinMode(LED_PIN, OUTPUT); // Set the LED_PIN as output
  Serial.begin(115200);
  WiFi.softAP(ssid, ""); // set up an access point with the specified SSID
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());  // print IP address of access point

  h.begin();    // start the HTML510Server
  h.attachHandler("/brightness?value=", handleBrightness); // handle brightness changes
  h.attachHandler("/frequency?value=", handleFreq); // handle brightness changes
  h.attachHandler("/", handleRoot);
}

void loop() {
  h.serve();  // serve HTTP requests
  delay(10);
}
