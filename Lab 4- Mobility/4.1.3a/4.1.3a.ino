#include <WiFi.h>
#include <WiFiUdp.h>

//WiFi setup
const char* ssid = "BachelorPad2022";
const char* password = "shangchi";
WiFiUDP UDPTestServer;
const IPAddress myIP(192, 168, 1, 171);     // my IP address
IPAddress friendIP(192, 168, 1, 101);       // friend's IP address

// define pins
#define potPin A4
const int ledPin = 1;

// Define the LEDC channel and frequency range
const int ledcChannel = 1;
const int freq = 25;
const int ledcResolution = 11; // 12-bit resolution

void setup() {
Serial.begin(115200);
analogReadResolution(12); // 12-bit ADC resolution
// Configure LEDC PWM channel
ledcSetup(ledcChannel, freq, ledcResolution);
ledcAttachPin(ledPin, ledcChannel);


Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.config(myIP, IPAddress(192, 168, 1, 1),IPAddress(255, 255, 255, 0));
WiFi.begin(ssid, password);
UDPTestServer.begin(2198); // any UDP port# up to 65535
// but higher is safer > 1023
while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }
  Serial.println("WiFi connected");
}
const int UDP_PACKET_SIZE = 100; 
byte sendBuffer[UDP_PACKET_SIZE];           // create the sendBuffer array

// allow packets up to 100 bytes
 byte packetBuffer[UDP_PACKET_SIZE];  // buffer for incoming UDP packets

void fncUdpSend(int i) // send 2 byte int i
{
byte udpBuffer[2];
udpBuffer[0] = i & 0xff; // send 1st (LSB) byte of i
udpBuffer[1] = i>>8; // send 2nd (MSB) byte of i
UDPTestServer.beginPacket(friendIP, 2198);
UDPTestServer.write(udpBuffer, 2); // send 2 bytes in udpBuffer
UDPTestServer.endPacket();
}


void handleUDPServer() {
int i, cb = UDPTestServer.parsePacket();
if (cb) {
UDPTestServer.read(packetBuffer, cb);
i = (packetBuffer[0] + (packetBuffer[1]<<8)); // puts 2 bytes into int
Serial.println(i); // prints the number (note no need to convert to asii)
}
}

void loop() {
 
  int potValue = analogRead(potPin); // read the value from the potentiometer
  int dutyCycle = map(potValue, 0, 4095, 0, 4095); // map potentiometer to LEDC duty cycle range (0-4095)
  
  // Set the LEDC duty cycle
  handleUDPServer();
  delay(50); 

  // send the dutyCycle value over UDP
  fncUdpSend(dutyCycle);
  delay(50); // Adjust delay as needed for smooth control
}