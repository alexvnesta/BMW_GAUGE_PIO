#include "globals.h"
#include "init_screen.h"
#include "boost_gauge.h"
#include "oil_gauge.h"
#include "read_can_messages.h"
#include "parse_can_messages.h"
#include "multi_gauge.h"
#include "cartesian_graph.h"
#include "zero_sixty.h"

U8G2_SSD1306_128X64_NONAME_1_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 18, /* data=*/ 23, /* cs=*/ 22, /* dc=*/ 16, /* reset=*/ 17);

int dim = 34;
int val = 0;     // variable for reading the pin status
int inPin = 15;
int number_of_screens = 6;

void initScreen(){
  u8g2.begin();
  startMillis = millis(); // start timer for reading sensor data
  dim = 34; // Set initial display dim value
}


void drawBootLogo(){

  Serial.println("Drawing Boot Logo");
  #define bmwLogo_width 64
  #define bmwLogo_height 64

static const unsigned char bmwLogo_bits[] PROGMEM = {
   0x00, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x03,
   0xc0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x1c, 0x00, 0x00,
   0x00, 0x00, 0x06, 0xfe, 0x7f, 0x60, 0x00, 0x00, 0x00, 0x00, 0xc1, 0xc7,
   0xe7, 0x83, 0x00, 0x00, 0x00, 0xc0, 0xf8, 0x87, 0xe3, 0x1f, 0x03, 0x00,
   0x00, 0x20, 0xfe, 0x87, 0xe3, 0x7f, 0x04, 0x00, 0x00, 0x10, 0xff, 0x07,
   0xe1, 0xff, 0x08, 0x00, 0x00, 0xc8, 0xff, 0x07, 0xe0, 0xff, 0x13, 0x00,
   0x00, 0xe4, 0xff, 0x27, 0xe4, 0xff, 0x27, 0x00, 0x00, 0xf2, 0xff, 0x27,
   0xe4, 0xff, 0x49, 0x00, 0x00, 0x99, 0xff, 0x67, 0xe6, 0xff, 0x98, 0x00,
   0x80, 0x0c, 0xff, 0xff, 0xff, 0x7f, 0x38, 0x01, 0x40, 0x06, 0xff, 0x07,
   0xe0, 0x7f, 0x6c, 0x02, 0x20, 0x33, 0xfc, 0x00, 0x00, 0x3f, 0xc0, 0x04,
   0x20, 0x19, 0x38, 0xfc, 0x00, 0x1c, 0xc0, 0x04, 0x90, 0x88, 0x18, 0xff,
   0x00, 0x18, 0xe0, 0x09, 0xc8, 0xc1, 0xc4, 0xff, 0x00, 0x20, 0x23, 0x13,
   0xc8, 0x63, 0xe2, 0xff, 0x00, 0xc0, 0x01, 0x12, 0xe8, 0x07, 0xf1, 0xff,
   0x00, 0x80, 0x80, 0x27, 0xe4, 0x0f, 0xf9, 0xff, 0x00, 0x80, 0xe0, 0x27,
   0xe4, 0x9f, 0xfc, 0xff, 0x00, 0x00, 0xf9, 0x27, 0xf2, 0x7f, 0xfe, 0xff,
   0x00, 0x00, 0xfe, 0x4f, 0xf2, 0x7f, 0xfe, 0xff, 0x00, 0x00, 0xfe, 0x4f,
   0xf2, 0x3f, 0xff, 0xff, 0x00, 0x00, 0xfc, 0x4f, 0xfa, 0x3f, 0xff, 0xff,
   0x00, 0x00, 0xfc, 0x5f, 0xf9, 0xbf, 0xff, 0xff, 0x00, 0x00, 0xfc, 0x5f,
   0xf9, 0x9f, 0xff, 0xff, 0x00, 0x00, 0xf8, 0x9f, 0xf9, 0x9f, 0xff, 0xff,
   0x00, 0x00, 0xf8, 0x9f, 0xf9, 0x9f, 0xff, 0xff, 0x00, 0x00, 0xf8, 0x9f,
   0xf9, 0x9f, 0xff, 0xff, 0x00, 0x00, 0xf8, 0x9f, 0xf9, 0x9f, 0xff, 0xff,
   0x00, 0x00, 0xf8, 0x9f, 0xf9, 0x1f, 0x00, 0x00, 0xff, 0xff, 0xf9, 0x9f,
   0xf9, 0x1f, 0x00, 0x00, 0xff, 0xff, 0xf9, 0x9f, 0xf9, 0x1f, 0x00, 0x00,
   0xff, 0xff, 0xf9, 0x9f, 0xf9, 0x1f, 0x00, 0x00, 0xff, 0xff, 0xf9, 0x9f,
   0xf9, 0x1f, 0x00, 0x00, 0xff, 0xff, 0xf9, 0x9f, 0xf9, 0x3f, 0x00, 0x00,
   0xff, 0xff, 0xfd, 0x5f, 0xfa, 0x3f, 0x00, 0x00, 0xff, 0xff, 0xfc, 0x5f,
   0xf2, 0x3f, 0x00, 0x00, 0xff, 0xff, 0xfc, 0x4f, 0xf2, 0x7f, 0x00, 0x00,
   0xff, 0x7f, 0xfe, 0x4f, 0xf2, 0x7f, 0x00, 0x00, 0xff, 0x7f, 0xfe, 0x4f,
   0xe4, 0xff, 0x00, 0x00, 0xff, 0x3f, 0xff, 0x27, 0xe4, 0xff, 0x01, 0x00,
   0xff, 0x9f, 0xff, 0x27, 0xe4, 0xff, 0x01, 0x00, 0xff, 0x8f, 0xff, 0x27,
   0xc8, 0xff, 0x03, 0x00, 0xff, 0xc7, 0xff, 0x13, 0xc8, 0xff, 0x07, 0x00,
   0xff, 0xe3, 0xff, 0x13, 0x90, 0xff, 0x1f, 0x00, 0xff, 0xf8, 0xff, 0x09,
   0x20, 0xff, 0x3f, 0x00, 0x3f, 0xfc, 0xff, 0x04, 0x20, 0xff, 0xff, 0x00,
   0x00, 0xff, 0xff, 0x04, 0x40, 0xfe, 0xff, 0x07, 0xe0, 0xff, 0x7f, 0x02,
   0x80, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x01, 0x00, 0xf9, 0xff, 0xff,
   0xff, 0xff, 0x9f, 0x00, 0x00, 0xf2, 0xff, 0xff, 0xff, 0xff, 0x4f, 0x00,
   0x00, 0xe4, 0xff, 0xff, 0xff, 0xff, 0x27, 0x00, 0x00, 0xc8, 0xff, 0xff,
   0xff, 0xff, 0x13, 0x00, 0x00, 0x10, 0xff, 0xff, 0xff, 0xff, 0x08, 0x00,
   0x00, 0x20, 0xfe, 0xff, 0xff, 0x7f, 0x06, 0x00, 0x00, 0xc0, 0xf8, 0xff,
   0xff, 0x1f, 0x01, 0x00, 0x00, 0x00, 0xc3, 0xff, 0xff, 0xc3, 0x00, 0x00,
   0x00, 0x00, 0x0c, 0xfe, 0x7f, 0x30, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00,
   0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0xc0, 0x01, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0x00 };

    u8g2.firstPage();
  do {
    u8g2.drawXBMP(33, 0, bmwLogo_width, bmwLogo_height, bmwLogo_bits);
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
        readCanMessages(can_ids, sizeof(can_ids)/sizeof(can_ids[0]));
    }
  }
  else if (current_screen == 1){
    Serial.println("Current Screen Selection is 1");
    u8g2.setPowerSave(0);  // Turn screen on
    initScreen();
    while (true){
        readCanMessages(can_ids, sizeof(can_ids)/sizeof(can_ids[0]));
        drawBoostGauge();
    }
  }
  else if (current_screen == 2){
    Serial.println("Current Screen Selection is 2");
    u8g2.setPowerSave(0);  // Turn screen on
    initScreen();
        while (true){
        readCanMessages(can_ids, sizeof(can_ids)/sizeof(can_ids[0]));
        drawOilGauge();
    }
  }
  else if (current_screen == 3){
    Serial.println("Current Screen Selection is 3");

    u8g2.setPowerSave(0);  // Turn screen on
    while (true){
        readCanMessages(can_ids, sizeof(can_ids)/sizeof(can_ids[0]));
        drawMultiGauge();
    }
  }
    else if (current_screen == 4){
    Serial.println("Current Screen Selection is 4");

    u8g2.setPowerSave(0);  // Turn screen on
    setupGraph();

    while (true){
        readCanMessages(can_ids, sizeof(can_ids)/sizeof(can_ids[0]));
        drawGraph();
        //drawVirtualDyno();
    }
    }
    else if (current_screen == 5){
    Serial.println("Current Screen Selection is 5");

    u8g2.setPowerSave(0);  // Turn screen on
    while (true){
        readCanMessages(can_ids, sizeof(can_ids)/sizeof(can_ids[0]));
        drawZeroSixty();
    }
    }
    else if (current_screen == 6){
    Serial.println("Current Screen Selection is 6");

    u8g2.setPowerSave(1);  // Turn screen off
    while (true){
        readCanMessages(can_ids, sizeof(can_ids)/sizeof(can_ids[0]));
    }
  }
}
