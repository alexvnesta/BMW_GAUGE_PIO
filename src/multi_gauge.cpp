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

    u8g2.firstPage();
    do {
    u8g2.setFont(u8g2_font_ncenB12_tr);
    //u8g2.drawStr(0,12,"Boost:");
    //u8g2.setCursor(80,12);
    //u8g2.print(boostPressure);
    u8g2.drawStr(0,12,"TORQ:");
    u8g2.setCursor(80,12);
    u8g2.print(torquelbf);
    //u8g2.drawStr(0,25,"OilP:");
    //u8g2.setCursor(80,25);
    //u8g2.print(oilPressure);
    u8g2.drawStr(0,25,"SPED:");
    u8g2.setCursor(80,25);
    u8g2.print(speed);
    u8g2.drawStr(0,37,"VLTG:");
    u8g2.setCursor(80,37);
    u8g2.print(voltage);
    u8g2.drawStr(0,49,"RPM:");
    u8g2.setCursor(80,49);
    u8g2.print(rpm);
    u8g2.drawStr(0,61,"CTEMP:");
    u8g2.setCursor(80,61);
    u8g2.print(coolantF);
  } while ( u8g2.nextPage() );


}