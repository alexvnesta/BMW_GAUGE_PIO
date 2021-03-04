#include "parse_can_messages.h"
#include "read_can_messages.h"
#include "init_screen.h"
#include "globals.h"

long RADIO_ID = 1250;
long STEERING_WHEEL_ID = 470; //1D6 HEX
long BATTERY_ID = 948; //3B4 HEX
long SPEED_ID = 436; //1B4 HEX
long TORQUE_ID = 168; //0A8
long RPM_ID = 170; //0AA
long COOLANT_ID = 464; //1D0

float voltage = 0;
float speed = 0;
float torquenm = 0;
float torquelbf = 0;
float rpm = 0; 
float coolantC = 0;
float coolantF = 0;

//(RPM * Torque) / (60 / 2 PI ) / 1000 

void parseCanMessage(long id, long message[8]) {
  Serial.println();
  Serial.print("PARSING ID:");
  Serial.println(id, HEX);

  if (id == STEERING_WHEEL_ID){
    if (message[0] == 192 && message[1] == 013)
      Serial.println("MATCHES VOICE BUTTON!");
      if (global_screen_value < 7){
        global_screen_value += 1;
      }
      else{
        global_screen_value = 0;
      }
    //switch depending on global screen value
    switchScreens(global_screen_value);
  }
  else if (id == BATTERY_ID){
    voltage = (((message[1]-240 )*256)+message[0])/68;
  }
  else if (id == SPEED_ID){
    speed = (((message[1]-208)*256)+message[0])/16;
  }
  else if (id == TORQUE_ID){
    torquenm = (message[2]*256)+message[1] / 32;
    torquelbf = (torquenm*0.73756214728);
  }
  else if (id == RPM_ID){
    rpm = ((message[5] * 256) + message[4] ) / 4;
  }
  else if (id == COOLANT_ID){
    coolantC = message[0] - 48;
    coolantF = (coolantC*1.8)+32;
  }
}
