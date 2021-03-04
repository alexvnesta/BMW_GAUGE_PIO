#ifndef READ_CAN_MESSAGES_H_
#define READ_CAN_MESSAGES_H_

#include <CAN.h>
#include <Arduino.h>

void initCan(long baudrate = 100E3);
void readCanMessages();

#endif