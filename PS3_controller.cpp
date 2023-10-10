#include "main.h"

void PS3_Controller_Setup()
{
  // Define On Connection Function
  Ps3.attachOnConnect(onConnect);
  Ps3.attachOnDisconnect(onDisconnect);

  // Emulate console as specific MAC address (change as required)
  Ps3.begin("38:4f:f0:c3:c4:9e");
}