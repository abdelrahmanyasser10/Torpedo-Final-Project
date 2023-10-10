#include "main.h"

void sender()
{
  WiFiClient client = server.available();
  float angle = get_angle();
  if (client) {
 
    client.print(angle);
    client.stop();
  }
}