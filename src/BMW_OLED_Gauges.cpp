
#include <Arduino.h>
#include "globals.h"
#include "read_can_messages.h"
#include "parse_can_messages.h"
#include "init_screen.h"
#include "boost_gauge.h"

/// Full program outline
// Files
//log_data.cpp
//transmit_data.cpp



void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Init canbus at 100Khz
  initCan(100E3);
  
  // Init screen
  initScreen();

  // Display Boot Logo
  switchScreens(0); //make draw the boot logo
  delay(3000); // Sleep for 3 seconds to give boot illusion
  
  // Set default screen to 0/BOOST
  switchScreens(3);
}

void loop() {
  // put your main code here, to run repeatedly:

  readCanMessages();

}
