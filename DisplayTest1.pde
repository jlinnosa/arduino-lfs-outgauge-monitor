/*
  DisplayTest1.pde:
 This is a simple sketch to test my LFS OutGauge packet parser.
 It outputs received data on a 20x4 LCD screen.
 
 Copyright (c) 2012 Jaakko Linnosaari

Permission is hereby granted, free of charge, to any person 
obtaining a copy of this software and associated documentation 
files (the "Software"), to deal in the Software without 
restriction, including without limitation the rights to use, 
copy, modify, merge, publish, distribute, sublicense, and/or 
sell copies of the Software, and to permit persons to whom the 
Software is furnished to do so, subject to the following 
conditions:

The above copyright notice and this permission notice shall be 
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
OTHER DEALINGS IN THE SOFTWARE.
 
 */


#include <stdio.h>
#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <Udp.h>         // UDP library from: bjoern@cs.stanford.edu 12/30/2008
#include "LfsOutGauge.h"
#include <LiquidCrystal.h>

// do customize these to fit your environment...
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 0, 177 };
unsigned int localPort = 8888;

char packetBuffer[UDP_TX_PACKET_MAX_SIZE];

// initialize LCD object
LiquidCrystal lcd(20, 19, 21, 26, 25, 24, 23);

int max_speed = 0;
int max_rpm = 0;
char car[4] = { 0,0,0,0 };

// display buffers
char* line[4];

void hashbar(char* str,int offset, int length, float value, int max_value) {
  int n = length*(value/(max_value-100));
  for (int i=0; i<length; i++) {
    str[i+offset]= (i<n) ? '#' : ' ';
  }
}

void updateDisplay(UDPOutGaugePacket *p) {

  int speed = (int)(p->speed*3.6);
  int rpm = (int)p->rpm;
  
  // if the car changes, reset max values
  if (strncmp(p->car,car,4)) {
    strncpy(car,p->car,4);
    max_speed=0;
    max_rpm=0;
  }
  
  if (speed>max_speed) max_speed=speed;
  if (rpm>max_rpm) max_rpm=rpm;

  snprintf(line[0],21,"g:%c      %03d   %05d",gearChar(p->gear),speed,rpm);
  snprintf(line[1],21,"        speed   rpm ");
  snprintf(line[2],21,"____.    %03d   %05d",max_speed,max_rpm);
  snprintf(line[3],21,"%-4s|",p->car);
  hashbar(line[3],5,15,p->rpm,max_rpm);
  line[3][20]=0;
  for (int i=0; i<4; i++) {
    lcd.setCursor(0,i);
    lcd.print(line[i]);
  }
}

void setup() {
  Ethernet.begin(mac,ip);
  Udp.begin(localPort);
  lcd.begin(20, 4);
  lcd.setCursor(0,1);
  lcd.print("   Hello, World!");

  for (int i=0; i<4; i++)
    line[i] = (char*)malloc(21);
}

void loop() {

  byte remoteIp[4];
  unsigned int remotePort;

  int packetSize = Udp.available();
  if(packetSize)
  {
    Udp.readPacket(packetBuffer,UDP_TX_PACKET_MAX_SIZE, remoteIp, remotePort);
    UDPOutGaugePacket* p = ((UDPOutGaugePacket*)&packetBuffer);

    updateDisplay(p);
  }

}
