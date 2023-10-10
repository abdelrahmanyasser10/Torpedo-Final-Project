#include "main.h"

void communication_setup()
{
    // Create Access Point
    WiFi.softAP(ssid,password);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);

    server.begin(); // Start the server
}