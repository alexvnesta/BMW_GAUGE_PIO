#ifndef PARSE_CAN_MESSAGES_H_
#define PARSE_CAN_MESSAGES_H_
#include <CAN.h>
#include <Arduino.h>

void parseCanMessage(long id, long message[]);

extern float voltage;
extern float speed;
extern float torquenm;
extern float torquelbf;
extern float rpm;
extern float coolantF;

#endif