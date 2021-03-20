#include "parse_can_messages.h"
#include "read_can_messages.h"
#include "cartesian_graph.h"
#include "init_screen.h"
#include "globals.h"

long RADIO_ID = 1250;
long STEERING_WHEEL_ID = 470; //1D6 HEX
long BATTERY_ID = 948; //3B4 HEX
long SPEED_ID = 422; //1A6 HEX
long TORQUE_ID = 168; //0A8
long RPM_ID = 170; //0AA
long COOLANT_ID = 464; //1D0

long can_ids[6] = {STEERING_WHEEL_ID, BATTERY_ID, SPEED_ID, TORQUE_ID, RPM_ID, COOLANT_ID};
long steering_wheel_can_array[1] = {STEERING_WHEEL_ID};

float voltage = 0;
float speed = 0;
float torquenm = 0;
float torquelbf = 0;
float rpm = 0; 
float coolantC = 0;
float coolantF = 0;

u_long lastButtonPress = 0;

int clickCounter = 0;

int checkNumClicks(){
  int max_delay = 800;
  int returnVal = 0;
  clickCounter += 1;
    lastButtonPress = millis();
    // wait for user to press the button again
    while ((millis() - lastButtonPress < max_delay) && clickCounter == 1)
    {
        readCanMessages(steering_wheel_can_array, sizeof(steering_wheel_can_array)/sizeof(steering_wheel_can_array[0]));
        // if button pressed again
        if (clickCounter == 2)
        {
            Serial.println("Button pressed twice!");
            returnVal = 2;
            clickCounter = 0;
            return(returnVal);
            break;

        }
    }

    // if on timeout no button pressed it means the button pressed only one time
    if (clickCounter == 1)
    {
        Serial.println("Button pressed once!");
        clickCounter = 0;
        returnVal = 1;
        lastButtonPress = millis();
        return(returnVal);
    }
  return 0;
}

void parseCanMessage(long id, long message[8]) {
  Serial.println();
  //Serial.print("PARSING ID:");
  //Serial.println(id, HEX);

  if (id == STEERING_WHEEL_ID){
    Serial.println("STEERING WHEEL BUTTON!!!!!");
    delay(3000);

    if (message[0] == 192 && message[1] == 13){
      //Serial.println("MATCHES VOICE BUTTON!");
      int numClicks = checkNumClicks();

      if(numClicks == 2 && global_screen_value == 4){
        //Double click event and on virtual dyno page
        resetVirtualDyno();
        //clickCounter = 0;

      }
      else if(numClicks == 2 && global_screen_value == 5){
        //Double click event and on zero sixty page
        //clickCounter = 0;

        //resetZeroSixty();
      }
      else if(numClicks == 2){
        Serial.println("DOUBLE ClICK!");
        //clickCounter = 0;

        //resetZeroSixty();
      }
      else if(numClicks == 1){
        //Single click event
        Serial.println("SINGLE ClICK!");
        lastButtonPress = millis();
        //clickCounter = 0;


        if (global_screen_value < 7) global_screen_value += 1;
        else {global_screen_value = 0;}
        switchScreens(global_screen_value);
      }
    }
  }

  else if (id == BATTERY_ID){
    voltage = (((message[1]-240 )*256)+message[0])/68;
    Serial.print("Voltage: ");
    Serial.println(voltage);


  }
  else if (id == SPEED_ID){
    //speed = (((message[1]-208)*256)+message[0])/16;
    speed = (message[0]);
    Serial.print("Speed: ");
    Serial.println(speed);
  }
  else if (id == TORQUE_ID){
    torquenm = ((message[2]*256)+message[1]) / 32;
    torquelbf = (torquenm*0.73756214728);
    Serial.print("Torque: ");
    Serial.println(torquenm);
  }
  else if (id == RPM_ID){
    rpm = ((message[5] * 256) + message[4] ) / 4;
    Serial.print("RPM: ");
    Serial.println(rpm);
  }
  else if (id == COOLANT_ID){
    coolantC = message[0] - 48;
    coolantF = (coolantC*1.8)+32;
    Serial.print("Coolant C: ");
    Serial.println(coolantC);
  }
}
