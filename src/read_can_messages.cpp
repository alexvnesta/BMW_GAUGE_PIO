#include "read_can_messages.h"
#include "parse_can_messages.h"

void initCan(long baudrate){
  // start the CAN bus at 100 kbps
  Serial.println("Initializing CAN bus");
  if (!CAN.begin(baudrate)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
}

void readCanMessages(){
    int packetSize = CAN.parsePacket();
    long id;
    
  if (packetSize) {
    // received a packet
    Serial.print("Received ");

    Serial.print("packet with id 0x");
    id = (CAN.packetId());
    Serial.print(CAN.packetId(), HEX);
    
    int counter = 0;
    long message[8] = {0,0,0,0,0,0,0,0};

    // Print each byte of the message in hex separated by a space.
    while (CAN.available()) {
      long chunk = (CAN.read());
      Serial.print(" ");
      Serial.print(chunk, HEX);
      message[counter] = (chunk);
      counter += 1;
    }
    
    parseCanMessage(id, message);

    Serial.println();
  }
}
