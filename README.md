# BMW_GAUGE_PIO

This is a work in progress project.  

I am making a set of gauges for my e90 bmw using the following hardware:  

1. ESP32 Dev Board.  
2. MCP2511 CAN Transceiver.  
3. 5V pressure sensors (50 PSI for Boost, 100 PSI for Oil Pressure).  
4. 5v to 3v logic converter.  
5. 12v to 5v step down.  
6. 0.96" OLED SPI display (128x64)

The project will have the following features:

1) Boost Pressure gauge.  
2) Oil Pressure gauge.  
3) multi-gauge - boostp, oilp, coolant temp, battery voltage.  
4) Horsepower and torque real time graph!  
5) 0-60, 120, 1/4 mile, 60-0 brake timers.  
6) display off mode for stealth look.  

My display is incorporated directly into the gauge cluster itself, so it is easy to see and looks somewhat integrated. 
It's a far cry from factory though.  

Required connections:
1) Can HI and LO - on cluster PCB.  
2) 12V power and ground - on cluster PCB.  
3) 3.3v screen switched - (changes ESP32 from sleep to active for power draw considerations).  

Potentially will also include data logging and bluetooth data download to smartphone via bluetooth...
