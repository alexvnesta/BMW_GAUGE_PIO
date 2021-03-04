#include "globals.h"
#include <Arduino.h>

const int WIDTH=128;
const int HEIGHT=64;
const int LENGTH=WIDTH;

int analogInValue = 0;

int x;
int y[LENGTH];

void clearY(){
  for(int i=0; i<LENGTH; i++){
    y[i] = -1;
  }
}

void drawY(){
  u8g2.drawPixel(0, y[0]);
  for(int i=1; i<LENGTH; i++){
    if(y[i]!=-1){
      u8g2.drawLine(i-1, y[i-1], i, y[i]);
    }else{
      break;
    }
  }
}

void setupGraph(void) {
  x = 0;
  clearY();
}

void drawGraph(void){
  analogInValue = random(1023);
  
  y[x] = map(analogInValue, 0, 1023, HEIGHT-1, 0);

  u8g2.firstPage();
  do {
    drawY();
  } while(u8g2.nextPage() );
  
  x++;
  if(x >= WIDTH){
    x = 0;
    clearY();
  }
}
