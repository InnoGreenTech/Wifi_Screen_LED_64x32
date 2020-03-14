/*
Author:	Vitali Gottselig
*/
#include "ESP8266RGBmatrixPanel.h"

ESP8266RGBmatrixPanel::ESP8266RGBmatrixPanel(uint8 r1, uint8 g1, uint8 bl1, uint8 r2, uint8 g2, uint8 bl2, uint8 latch) : Adafruit_GFX(64,32)
{
	//G1	R1 |
	//GND	B1 |
	//G2	R2 |
	//GND	B2  |
	//B		A   |
	//D		C  |
	//LAT	CLK|
	//GND	OE |
	// !!!IMPORTANT for ABCD-Pins see readme IMPORTANT!!!
	//CLK MUST BE CONNECTED ON D0!  
	//OE connected with LAT

	R1 = r1;
	G1 = g1;
	BL1 = bl1;
	R2 = r2;
	G2 = g2;
	BL2 = bl2;
	LAT = latch;

	pinMode(D0, OUTPUT);
	pinMode(LAT, OUTPUT);
	pinMode(R1, OUTPUT);
	pinMode(G1, OUTPUT);
	pinMode(BL1, OUTPUT);
	pinMode(G2, OUTPUT);
	pinMode(R2, OUTPUT);
	pinMode(BL2, OUTPUT);

	fillScreen(0);
}

void ESP8266RGBmatrixPanel::testmuster()
{
	//Testmuster
	for (int x = 0; x < 64; x++)
	{
		for (int y = 0; y < 32; y++)
		{
			pixel[x][y] = 0;
			if (x == 2 * y)pixel[x][y] |= rmask;
			if (x == 0 || y == 0) pixel[x][y] |= gmask;
			if (x == 63 || y == 31 || x + 2 * y == 63) pixel[x][y] |= bmask;
		}
	}
	uint16 color = rmask;

	fillCircle(16, 16, 5,  color);
}

/* void ESP8266RGBmatrixPanel::updateDisplay()
{
	for (int y = 0; y < 16; y++)
	{
		int i = 0;

		for (int x = 0; x < 64; x++)
		{
			prts = 0;
			if ((pixel[x][y] & rmask) > layer)
				prts |= (1 << R1);
			if (((pixel[x][y] & gmask) >> 4) > layer)
				prts |= (1 << G1);
			if (((pixel[x][y] & bmask) >> 8) > layer)
				prts |= (1 << BL1);
			if ((pixel[x][y + 16] & rmask) > layer)
				prts |= (1 << R2);
			if (((pixel[x][y + 16] & gmask) >> 4) > layer)
				prts |= (1 << G2);
			if (((pixel[x][y + 16] & bmask) >> 8) > layer)
				prts |= (1 << BL2);
			*(IOPtr) = prts;
			*(tikPtr) = tik;
			*(tikPtr) = tok;
		}
		*(IOPtr) |= (1 << LAT);
		delayMicroseconds(10);
	}

	layer += 1;
	if (layer > 14) layer = 0;
} */
void ESP8266RGBmatrixPanel::updateDisplay()
{
	for (int y = 0; y < 8; y++)
	{
		int i = 0;

		for (int x = 0; x < 64; x++)
		{
			prts = 0;
			if ((pixel[x][y+8] & rmask) > layer)
				prts |= (1 << R1);
			if (((pixel[x][y+8] & gmask) >> 4) > layer)
				prts |= (1 << G1);
			if (((pixel[x][y+8] & bmask) >> 8) > layer)
				prts |= (1 << BL1);
			
			if ((pixel[x][y+24] & rmask) > layer)
				prts |= (1 << R2);
			if (((pixel[x][y+24] & gmask) >> 4) > layer)
				prts |= (1 << G2);
			if (((pixel[x][y+24] & bmask) >> 8) > layer)
				prts |= (1 << BL2);
		
			*(IOPtr) = prts;
			*(tikPtr) = tik;
			*(tikPtr) = tok;
		}	
		
		for (int x = 0; x < 64; x++)
		{
			
			prts = 0;
			
			if ((pixel[x][y+0] & rmask) > layer)
				prts |= (1 << R1);
			if (((pixel[x][y+0] & gmask) >> 4) > layer)
				prts |= (1 << G1);
			if (((pixel[x][y+0] & bmask) >> 8) > layer)
				prts |= (1 << BL1);
			
			if ((pixel[x][y + 16] & rmask) > layer)
				prts |= (1 << R2);
			if (((pixel[x][y + 16] & gmask) >> 4) > layer)
				prts |= (1 << G2);
			if (((pixel[x][y + 16] & bmask) >> 8) > layer)
				prts |= (1 << BL2);
			
			*(IOPtr) = prts;
			*(tikPtr) = tik;
			*(tikPtr) = tok;
			
		}
		
//		delayMicroseconds(5);	
		*(IOPtr) |= (1 << LAT);
		delayMicroseconds(10);
	}

	layer += 1;
	if (layer > 6) layer = 0;	
}

void ESP8266RGBmatrixPanel::drawPixel(int16_t x, int16_t y, uint16_t c) {
	if (x>63) x=63;
	if (y>31) y=31;
	if (x<0)  x=0;
	if (y<0)  y=0;
	pixel[x][y] = c;
}

void ESP8266RGBmatrixPanel::fillScreen(uint16_t c) {
	for (int x = 0; x < 64; x++)
	{
		for (int y = 0; y < 32; y++)
		{
			pixel[x][y] = c;
		}
	}
}

void ESP8266RGBmatrixPanel::drawBitmap(String* bytes)
{
	fillScreen(0);
	uint8 imgWidth = 0;
	uint8 imgHeigth = 0;

	if (bytes->length() > 22)
	{
		imgWidth = (uint8)((*bytes)[18]);
		imgHeigth = (uint8)((*bytes)[22]);
	}
	
	if (imgWidth != 64 || imgHeigth != 32)
	{
		//error square
		uint8 x0 = (64 - 16) / 2;
		uint8 y0 = (32 - 16) / 2;
		uint8 x1 = x0 + 16;
		uint8 y1 = y0 + 16;
		fillScreen(0);
		drawRect(x0, y0, 17, 17, rmask);
		drawLine(x0, y0, x1, y1, rmask);
		drawLine(x0, y1, x1, y0, rmask);
		return;
	}
	uint8 dataOffset = 54;
	uint8 x = 0;
	uint8 y = 31;
	for (uint16 i = dataOffset; i < bytes->length()-3; i += 3)
	{
		pixel[x][y] = 0;
		uint16 b = (uint16)((*bytes)[i]);
		uint16 g = (uint16)((*bytes)[i + 1]);
		uint16 r = (uint16)((*bytes)[i + 2]);

		//0b00000000RRRRRRRR -> 0b000000000000RRRR
		r = r >> 4;
		r = r & rmask;
		//0b00000000GGGGGGGG -> 0b00000000GGGG0000
		g = g >> 0;
		g &= gmask;

		//0b00000000BBBBBBBB -> 0b0000BBBB00000000
		b = b << 4;
		b &= bmask;

		pixel[x][y] |= r;
		pixel[x][y] |= g;
		pixel[x][y] |= b;

		x++;
		if (x >= 64)
		{
			x = 0;
			y--;
		}
	}

}



