/* WiFi UDP Send Byte on Button Press
  Based on UDP Send and Receive String
  created 3 February 2019
  by Michael Shiloh
  changed 18 February 2019
  by Magda and Sara
  modified by Sara for distance sensor
*/

#include <SPI.h>
#include <WiFiNINA.h>
#include <WiFiUdp.h>

int status = WL_IDLE_STATUS;
#include "arduino_secrets.h"
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

unsigned int localPort = 2390;      // local port to listen on

char packetBuffer[255]; //buffer to hold incoming packet
char sendBuffer[255];

WiFiUDP Udp;

const int Distance1 = A0;
int val = 0;        // value read from the pot
int outputValue = 0;

int LEDs = 4;


// IP address of the receiving device
IPAddress receivingDeviceAddress(192, 168, 1, 26);
unsigned int receivingDevicePort = 5000;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to WiFi network:p
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to wifi");
//  printWiFiStatus();

  Serial.print("Initializing WiFiUDP library and listening on port ");
  Serial.println(localPort);
  Udp.begin(localPort);

  pinMode(LEDs, OUTPUT);
  pinMode(Distance1, INPUT);
  
}

void loop() {

int val = analogRead(Distance1);
outputValue = map(cal, 0, 1023, 0, 255);
Serial.println(val);
  sendCmnd();
  receiveCmnd();

}

void sendCmnd() {
  int val = analogRead(A0);

//  if ( val > ??) //distance ir really close almost touching device {
//
//    Serial.println("Distance close; sending new state");
//    Udp.beginPacket(receivingDeviceAddress, receivingDevicePort);
//
//    Udp.write(outputValue);
//    Udp.endPacket();
//    

 // }
}

void receiveCmnd(){
  
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();

  // if nobody sent us anything, packetSize
  // would be zero, so a non-zero packetSize
  // means we have something to work on
  if (packetSize) {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remoteIp = Udp.remoteIP();
    Serial.print(remoteIp);
    Serial.print(", port ");
    Serial.println(Udp.remotePort());

    // read the packet into packetBufffer
    int len = Udp.read(packetBuffer, 255);
     digitalWrite(LEDs, packetBuffer[0]);

  }
}

void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("My IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
