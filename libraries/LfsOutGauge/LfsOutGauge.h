/*
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

#ifndef LfsOutGauge_h
#define LfsOutGauge_h

#include <stdint.h>

struct UDPOutGaugePacket {
	uint32_t time;
	char car[4];
	uint16_t flags;
	uint8_t gear;
	uint8_t player_id;
	float speed;
	float rpm;
	float boost;
	float engtemp;
	float fuel;
	float oilpress;
	float oiltemp;
	uint32_t dashlights;
	uint32_t showlights;
	float throttle;
	float brake;
	float clutch;
	char display1[16];
	char display2[16];
	int32_t id;
};

#define LFS_MAX_PACKET_SIZE sizeof(UDPOutGaugePacket)

#define OG_SHIFT     0x0001
#define OG_CTRL      0x0002
#define OG_TURBO     0x2000
#define OG_KM        0x4000
#define OG_BAR       0x8000

#define DL_SHIFT     0x0001
#define DL_FULLBEAM  0x0002
#define DL_HANDBRAKE 0x0004
#define DL_PITSPEED  0x0008
#define DL_TC        0x0010
#define DL_SIGNAL_L  0x0020
#define DL_SIGNAL_R  0x0040
#define DL_OILWARN   0x0080
#define DL_BATTERY   0x0100
#define DL_ABS       0x0200

char gearChar(int g)
{
	switch (g) {
	case 0:
		return 'r';
	case 1:
		return 'n';
	case 2:
		return '1';
	case 3:
		return '2';
	case 4:
		return '3';
	case 5:
		return '4';
	case 6:
		return '5';
	case 7:
		return '6';
	case 8:
		return '7';
	}
	return '*';
}

#endif
