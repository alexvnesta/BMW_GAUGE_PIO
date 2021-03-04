#include "globals.h"
#include "boost_gauge.h"
#include "oil_gauge.h"
#include "parse_can_messages.h"

void drawMultiGauge(void){
    currentMillis = millis();
    if (currentMillis - startMillis >= period) {
        readSensorData();
        readOilSensorData();
        startMillis = currentMillis;
    }
    // Must convert numbers to char so they can be displayed.
    char bp [12];
    char op [12];
    char vtg [12];
    char c_rpm [12];
    char cool [12];


    sprintf(bp, "%f", boostPressure);
    sprintf(op, "%f", oilPressure);
    sprintf(vtg, "%f", voltage);
    sprintf(c_rpm, "%f", rpm);
    sprintf(cool, "%f", coolantF);


    u8g2.firstPage();
    do {
    u8g2.setFont(u8g2_font_ncenB12_tr);
    u8g2.drawStr(0,12,"Boost:");
    u8g2.drawStr(80,12,bp);
    u8g2.drawStr(0,24,"OilP:");
    u8g2.drawStr(80,24,op);
    u8g2.drawStr(0,36,"VLTG:");
    u8g2.drawStr(80,36,vtg);
    u8g2.drawStr(0,48,"RPM:");
    u8g2.drawStr(80,48,c_rpm);
    u8g2.drawStr(0,60,"CTEMP:");
    u8g2.drawStr(80,60, cool);
  } while ( u8g2.nextPage() );


}