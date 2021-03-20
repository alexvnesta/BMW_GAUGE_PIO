#include "read_can_messages.h"
#include "parse_can_messages.h"
#include "globals.h"


u_long sleepModeMillis = 0;
int canReadFlag = 0;

void checkSleepMode(){
  /// IF GPIO 12 is low for > 1 second, then put device in sleep mode.
  if (digitalRead(GPIO_NUM_12) == 1){
    sleepModeMillis = millis();
    canReadFlag = 1;
  }
  if (digitalRead(GPIO_NUM_12) == 0 && (millis() - sleepModeMillis > 1000)){
      Serial.println("Sleep Mode Triggered!!");
      Serial.print("GPIO 12 state is: ");
      Serial.println(digitalRead(GPIO_NUM_12));
      Serial.print("For the following milliseconds: ");
      Serial.println(millis() - sleepModeMillis);
      //Make a pin HIGH to shut off can trasceiver
      canReadFlag = 0;
      u8g2.setPowerSave(1);
      esp_sleep_enable_ext0_wakeup(GPIO_NUM_12, HIGH);
      esp_deep_sleep_start();
  }
  
}

void initCan(long baudrate){
  // start the CAN bus at 100 kbps
  Serial.println("Initializing CAN bus");
  if (!CAN.begin(baudrate)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
  canReadFlag = 1;
  //Make a pin LOW to WAKE UP can trasceiver
}

void readCanMessages(long id_list[], int list_length){
  canReadFlag == 1;

  //checkSleepMode(); 

  //if (canReadFlag == 0) return;


  int packetSize = CAN.parsePacket();
  long id;
    
  if (packetSize) {

    // received a packet
    Serial.print("Received packet ");
    id = (CAN.packetId());
    Serial.println(id, HEX);

    //Serial.print("regular packet with id 0x");
    Serial.print("List Length: ");
    Serial.println(list_length);

    for(int entry = 0; entry <= list_length; entry++){
      if (id == id_list[entry]) break;
      if ((entry == list_length && id != id_list[list_length]) || entry > list_length) return;
    }

    Serial.print(id, HEX);
    Serial.println(" is in the list!");

    int counter = 0;
    long message[8] = {0};

    // Print each byte of the message in hex separated by a space.
    while (CAN.available()) {
      long chunk = (CAN.read());
      Serial.print(" ");
      Serial.print(chunk, HEX);
      message[counter] = (chunk);
      counter += 1;
      if (counter >= 8) break;
    }
    
    parseCanMessage(id, message);

    Serial.println();
  }
}
