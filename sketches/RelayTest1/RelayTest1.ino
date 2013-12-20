/*
  RelayTest1.pde:
 This is a simple sketch to test my LFS OutGauge packet parser.
 It outputs received data on a 8 channel relay board.
 
 Copyright (c) 2013 Jaakko Linnosaari

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
#include <stdint.h>
#include <SPI.h>		// needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <Udp.h>
#include <LfsOutGauge.h>

// do customize these to fit your environment...
#define LIGHTS_PIN_BASE 30
uint8_t mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
uint8_t ip[] = { 192, 168, 10, 128 };
uint16_t localPort = 6666;

EthernetUDP Udp;
char packetBuffer[LFS_MAX_PACKET_SIZE];

void setLight(uint8_t l, uint32_t state)
{
        // I use every other pin, so multiply pin index by 2...
  	digitalWrite(LIGHTS_PIN_BASE + l*2, state==0 ? LOW : HIGH);
}

void setup()
{
	Ethernet.begin(mac, ip);
	Udp.begin(localPort);

        // init light pins to output mode
	for (uint8_t i = 0; i < 8; i++) {
		pinMode(LIGHTS_PIN_BASE + i, OUTPUT);
                setLight(i, 0);
        }
}

void loop()
{
	int16_t packetSize = Udp.parsePacket();
	if (packetSize) {
		Udp.read(packetBuffer, LFS_MAX_PACKET_SIZE);
		UDPOutGaugePacket *p =
		    ((UDPOutGaugePacket *) & packetBuffer);
                uint32_t l = p->dashlights & p->showlights;
		setLight(0, l & DL_SHIFT);
		setLight(1, l & DL_FULLBEAM);
		setLight(2, l & DL_HANDBRAKE);
		setLight(3, l & DL_SIGNAL_L);
		setLight(4, l & DL_SIGNAL_R);
		setLight(5, l & DL_OILWARN);
		setLight(6, l & DL_BATTERY);
                setLight(7, p->gear==1);
	}

}
