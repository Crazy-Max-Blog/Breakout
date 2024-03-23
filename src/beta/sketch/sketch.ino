#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

//#define NO_SCREENSAVER  // Без заставки

#define TFT_CS   15
#define TFT_RST  2
#define TFT_DC   0
#define TFT_MOSI 4
#define TFT_CLK  16
#define TFT_LED  17
#define TFT_MISO 5

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

int rx = 2;
int ry = 170;

#include "btn.h"
#define BTN_L 18
#define BTN_R 19

//btn bl(BTN_L);
//btn br(BTN_R);

btn bl(BTN_L);
btn br(BTN_R);

#include "images.h"
#include "lives.h"
#include "Balls.h"

Ball b(3, 3, 3);

void setup() {
  Serial.begin(9600);
  Serial.println("ILI9341 Test!"); 

	pinMode(TFT_LED, OUTPUT);
	digitalWrite(TFT_LED, HIGH);
 
  tft.begin();
  tft.setRotation(3);

#ifndef NO_SCREENSAVER
	int w = 320;
	int h = 240;
	
	for(int y=0;y<h-1;y++){
    for(int x=0;x<w;x++){
			uint16_t d = l[(y+1)*w+x];
      if(d or l[(y)*w+x]) tft.drawLine(x,y,x,h-1,l[(y+1)*w+x]);
    }
  }

	delay(2500);
#endif
	
	tft.fillRect(0,0,tft.width(),tft.height(),BLUE);

  //tft.println("Hello World!");

	//Serial.println("l");
	//lives-=1;
	//Serial.println("d");

  view_down();
	tft.drawRGBBitmap(rx, ry, rocket, 64, 32);
	b.update();
	fill(BLUE);
  ellipse(3, 3, 3*2+4, 3*2+4);
}

void view_rocket(bool b) {
	//tft.drawRGBBitmap(rx, ry, rocket, 64, 32);
	if(b and rx+64<320) {
		rx+=2;
		tft.drawLine(rx-2, ry, rx-2, ry+31,  BLUE);
		tft.drawLine(rx-1, ry, rx-1, ry+31,  BLUE);
		tft.drawLine(rx, ry, rx, ry+31, BLACK);

		tft.drawLine(rx+63, ry+1, rx+63, ry+20, RED);
		tft.drawLine(rx+63, ry+22, rx+63, ry+30, RED);
		
		tft.drawLine(rx+62, ry+1, rx+62, ry+20, RED);
		tft.drawLine(rx+62, ry+22, rx+62, ry+30, RED);

		tft.drawLine(rx+64, ry, rx+64, ry+31, BLACK);
	} else if((!b) and rx>0) {
		rx-=2;

		tft.drawLine(rx+1, ry+1, rx+1, ry+20, RED);
		tft.drawLine(rx+1, ry+22, rx+1, ry+30, RED);
		
		//tft.drawLine(rx, ry+1, rx-2, ry+20, RED);
		//tft.drawLine(rx, ry+22, rx-2, ry+30, RED);

		tft.drawLine(rx+63, ry, rx+63, ry+31, BLACK);
		tft.drawLine(rx+64, ry, rx+64, ry+31, BLUE);
		tft.drawLine(rx+65, ry, rx+65, ry+31, BLUE);

		tft.drawLine(rx, ry, rx, ry+31,  BLACK);
	}
	Serial.println("456");
}

/*bool btn_v(byte pin) {
	static bool b;
	static long t;
	bool bv = digitalRead(pin);
	if(bv and !b) {b=1; t = millis();}
	if(bv and b and millis()-t>1000) return true;
	return false;
}*/
void loop(void) {
	if(lives>0) b.update();
	//if(bl) {lives+=1;draw_live(lives);draw_live(lives-1);}
	//if(br) {lives-=1;draw_live(lives);draw_live(lives+1);}

	if(bl) {view_rocket(1);}
	if(br) {view_rocket(0);}
	
	//static long l, r;
	//if(digitalRead(BTN_L) and millis()-l>10) {l=millis();view_rocket(1);}
	//if(digitalRead(BTN_R) and millis()-r>10) {r=millis();view_rocket(0);}
  delay(1);
}