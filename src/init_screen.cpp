#include "globals.h"
#include "init_screen.h"
#include "boost_gauge.h"
#include "oil_gauge.h"
#include "read_can_messages.h"
#include "multi_gauge.h"
#include "cartesian_graph.h"

U8G2_SSD1306_128X64_NONAME_1_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 18, /* data=*/ 23, /* cs=*/ 22, /* dc=*/ 16, /* reset=*/ 17);

int dim = 34;
int val = 0;     // variable for reading the pin status
int inPin = 15;
int number_of_screens = 7;

void initScreen(){
  u8g2.begin();
  startMillis = millis(); // start timer for reading sensor data
  dim = 34; // Set initial display dim value
}


void drawBootLogo(){
  Serial.println("Drawing Boot Logo");

  /*
  static unsigned char M_logo[] = {
  0x13, 0x00, 0x15, 0x00, 0x93, 0xcd, 0x55, 0xa5, 0x93, 0xc5, 0x00, 0x80,
0x00, 0x60};
   */

    u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB12_tr);
    u8g2.drawStr(0,30,"Willkommen!");
    //u8g2.drawXBMP(40, 33, 16, 7, M_logo);
  } while ( u8g2.nextPage() );

}

void drawDisplayOff(){
  u8g2.setPowerSave(1);  
}

void switchScreens(int current_screen){
  if (current_screen == 0){
    Serial.println("Current Screen Selection is 0");
    u8g2.setPowerSave(0);
    drawBootLogo();
    while(true){
        readCanMessages();
    }
  }
  else if (current_screen == 1){
    Serial.println("Current Screen Selection is 1");

    u8g2.setPowerSave(0);  // Turn screen on
    startMillis = 0;
    while (true){
        readCanMessages();
        drawBoostGauge();
    }
  }
  else if (current_screen == 2){
    Serial.println("Current Screen Selection is 2");
    u8g2.setPowerSave(0);  // Turn screen on
    startMillis = 0;
        while (true){

        readCanMessages();
        drawOilGauge();
    }
  }
  else if (current_screen == 3){
    Serial.println("Current Screen Selection is 3");

    u8g2.setPowerSave(0);  // Turn screen on
    while (true){
        readCanMessages();
        drawMultiGauge();
    }
  }
    else if (current_screen == 4){
    Serial.println("Current Screen Selection is 4");

    u8g2.setPowerSave(0);  // Turn screen on
    setupGraph();

    while (true){
        readCanMessages();
        drawGraph();
        //drawVirtualDyno();
    }
    }
    else if (current_screen == 5){
    Serial.println("Current Screen Selection is 5");

    u8g2.setPowerSave(0);  // Turn screen on
    while (true){
        //checkButton();
        readCanMessages();
        //drawZeroSixty();
    }
    }
    else if (current_screen == 6){
    Serial.println("Current Screen Selection is 6");

    u8g2.setPowerSave(0);  // Turn screen off
    while (true){
        //checkButton();
        readCanMessages();
        //drawBluetoothConnect();
    }
    }
    else if (current_screen == 7){
    Serial.println("Current Screen Selection is 7");

    u8g2.setPowerSave(1);  // Turn screen off
    while (true){
        //checkButton();
        readCanMessages();
    }
  }
}
