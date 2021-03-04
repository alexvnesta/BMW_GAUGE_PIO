#ifndef OIL_GAUGE_H
#define OIL_GAUGE_H

void drawOilGauge(void);
void readOilSensorData(void);
float normaliseOilSensorData(int m);
void addOilSensorHistory(int val);
int getOilSensorHistory(int index);
extern int oilPressure;
#endif
