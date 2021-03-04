#ifndef GLOBALS_H
#define GLOBALS_H

#include <U8g2lib.h>


extern int boostPressure;

extern const unsigned long period;

extern unsigned long startMillis;
extern unsigned long currentMillis;

extern int global_screen_value;
extern int dim;

extern U8G2_SSD1306_128X64_NONAME_1_4W_SW_SPI u8g2;

#endif