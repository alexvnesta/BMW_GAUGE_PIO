#include <Arduino.h>
#include "globals.h"
#include "parse_can_messages.h"
#include <U8g2lib.h>
#include "zero_sixty.h"

static int lastSpeed = -1;
static uint32_t lastSpeedTime = 0;

static uint32_t distance = 0;
static uint32_t startTime = 0;

long dataTime = 0;
 
#define STAGE_IDLE 0
#define STAGE_WAIT_START 1
#define STAGE_MEASURING 2
 
#define FONT_SIZE_SMALL u8g2_font_5x8_mf
#define FONT_SIZE_XLARGE u8g2_font_freedoomr10_mu
#define FONT_SIZE_MEDIUM u8g2_font_shylock_nbp_t_all

static byte stage = STAGE_IDLE;
 
#define SPEED_THRESHOLD_1 60 /* kph */
#define SPEED_THRESHOLD_2 100 /* kph */
#define SPEED_THRESHOLD_3 200 /* kph */
#define DISTANCE_THRESHOLD 400 /* meters */
 
static uint16_t times[4] = {0};
 

/// FIX TIMERLOOP AND SHOWTIMERRESULTS!!!!
 
void setupZeroSixty(){
    initTimerScreen();
}

void drawZeroSixty(){
    Serial.print("current Speed:");
    Serial.println(speed);

    
    timerLoop();

    char buf[10];
    unsigned int t = (millis() - startTime) / 1000;
    sprintf(buf, "%02u:%02u", t / 60, t % 60);
    u8g2.setFont(FONT_SIZE_SMALL);
    u8g2.drawStr(97,64,buf);
}

void timerLoop(){
    uint32_t elapsed = millis() - startTime;
    uint16_t n;
    dataTime = millis();
    u8g2.setFont(FONT_SIZE_XLARGE);

    // estimate distance
    distance += (uint32_t)(speed + lastSpeed) * (dataTime - lastSpeedTime) / 2 / 3600;
    
    if (lastSpeed != speed) {
        //speed = speed % 1000, 3;
        u8g2.drawStr(0,54,"mph");
        lastSpeed = speed;
    }
    lastSpeedTime = dataTime;
    
    if (stage == STAGE_WAIT_START) {
        if (speed == 0) {
            stage = STAGE_MEASURING;
            startTime = lastSpeedTime;
        
            lastSpeed = 0;
            distance = 0;

            memset(times, 0, sizeof(times));
            initTimerScreen();
        }
    }
    else if (stage == STAGE_MEASURING) {
        // display elapsed time (mm:ss:mm)
        n = elapsed / 1000;
        if (n == 100) { 
            u8g2.setCursor(0, 20); 
            u8g2.print(n, 2); 
            n = (elapsed % 1000) / 100; 
            u8g2.setFont(FONT_SIZE_MEDIUM); 
            u8g2.setCursor(32, 20); 
            u8g2.print('.'); 
            u8g2.print('0' + n); 
        } 
        if (times[2] == 0 && speed == SPEED_THRESHOLD_3) {
            times[2] = elapsed / 100;
            stage = STAGE_IDLE;
            //u8g2.clear(0, 0, 128, 24);
            showTimerResults();
            u8g2.setFont(FONT_SIZE_MEDIUM);
            u8g2.setCursor(0, 0);
            u8g2.print("DONE!");
        } 
        else if (times[1] == 0 && speed == SPEED_THRESHOLD_2) {
            times[1] = elapsed / 100;
            showTimerResults();
        } 
        else if (times[0] == 0  && speed == SPEED_THRESHOLD_1) {
            times[0] = elapsed / 100;
            showTimerResults();
        } 
        else if (speed == 0) {
            // speed go back to 0
            stage = STAGE_IDLE;
        }
        if (distance == 0) {
            u8g2.setFont(FONT_SIZE_SMALL);
            u8g2.setCursor(62, 6);
        }
        if (distance == 400) {
            u8g2.print(400, 3);
        }
        if (!times[3]) {
            times[3] = elapsed / 100;
            showTimerResults();
        }
        else {
            u8g2.print(distance, 3);
        }
    }
    else {
        if (speed == 0) {
        stage = STAGE_WAIT_START;
        initTimerScreen();
        u8g2.setFont(FONT_SIZE_MEDIUM);
        u8g2.setCursor(0, 24);
        u8g2.print(" GET");
        u8g2.setCursor(0, 48);
        u8g2.print("READY");
        delay(500);
        }
    }
}

void showTimerResults(){
    u8g2.firstPage();
    do{
    u8g2.setFont(FONT_SIZE_SMALL);
    u8g2.drawStr(56,12," 0~60:  --");
    u8g2.drawStr(56,24," 0~100:  --");
    u8g2.drawStr(56,36," 0~200:  --");
    u8g2.drawStr(56,48," 400m:  --");
    u8g2.setFont(FONT_SIZE_MEDIUM);
    char buf[8];
    if (times[0]) {
        sprintf(buf, "%2d.%1d", times[0] / 10, times[0] % 10);
        Serial.println(times[0]);
        u8g2.setCursor(92, 12);
        u8g2.print(buf);
    }
    if (times[1]) {
        sprintf(buf, "%2d.%1d", times[1] / 10, times[1] % 10);
        Serial.println(buf);
        u8g2.setCursor(92, 24);
        u8g2.print(buf);
    }
    if (times[2]) {
        sprintf(buf, "%2d.%1d", times[2] / 10, times[2] % 10);
        Serial.println(buf);
        u8g2.setCursor(92, 36);
        u8g2.print(buf);
    }
    if (times[3]) {
        sprintf(buf, "%2d.%1d", times[3] / 10, times[3] % 10);
        Serial.println(buf);
        u8g2.setCursor(92, 48);
        u8g2.print(buf);
    }
    }while (u8g2.nextPage());

}

void initTimerScreen(){
    //SOMEHOW ClEAR THE SCREEN!!!!
    u8g2.firstPage();
    do{
        showTimerResults();
        u8g2.setFont(FONT_SIZE_SMALL);
        char spd[6];
        sprintf(spd, "%f", speed);

        u8g2.drawStr(24,48,spd);
        u8g2.drawStr(24,48,"mph");
    }while (u8g2.nextPage());

}