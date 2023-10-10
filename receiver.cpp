#include "main.h"

void receive()
{
  // Check if a client has connected
  WiFiClient client = server.available();

  if (client)
  {
    // Read the data from the client
    while (client.connected())
    {
      if (client.available())
      {
        String X = client.readStringUntil('\n');
        CX = X.toInt();
      }   
    }
  }
}