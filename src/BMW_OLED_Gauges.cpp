
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

void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason){
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }
}

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Init canbus at 100Khz
  initCan(100E3);
  
  // Init screen
  initScreen();

  //Wakeup reason
  print_wakeup_reason();

  // Display Boot Logo
  drawBootLogo(); //make draw the boot logo
  delay(2000); // Sleep for 3 seconds to give boot illusion
  
  // Set default screen to 1/BOOST
  switchScreens(1);
}

void loop() {
  // put your main code here, to run repeatedly:
  readCanMessages(can_ids, sizeof(can_ids)/sizeof(can_ids[0]));
}