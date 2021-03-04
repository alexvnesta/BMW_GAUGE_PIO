#ifndef ARDUINO_H
#define ARDUINO_H
#include <Arduino.h>
#endif

#ifndef SPI_H
#define SPI_H
#include <SPI.h>
#endif

#ifndef INIT_SCREEN_H
#define INIT_SCREEN_H
#include <U8g2lib.h>

void initScreen();
void drawBootLogo();
void drawDisplayOff();
void switchScreens(int current_screen = 0);

#endif