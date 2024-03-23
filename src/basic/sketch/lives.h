#pragma once

void view_bricks();
void draw_live_b(int num, bool state);
void draw_live(int num);
void game_ower();

class {
  public:
  operator int() {
    return lives;
  }

  int operator=(int n) {
    lives = n;
    return lives;
  }

  int operator+=(int n) {
    if(lives<3) lives+=n;
    draw_live(lives);
    draw_live(lives-1);
    return lives;
  }

  int operator-=(int n) {
    lives-=n;
    if(lives==0) game_ower();
    draw_live(lives);
    draw_live(lives+1);
    return lives;
  }

  /*int operator++() {
    if(lives<3) lives+=1;
    return lives;
  }

  int operator--() {
    if(lives>1) lives-=1;
    else game_ower();
    return lives;
  }*/

  int lives = 3;
} lives;

void game_ower() {
  tft.fillRect(0,0,tft.width(),tft.height(),BLACK);
  tft.setTextSize(5);
  tft.setCursor(7, 111);
  tft.println("Game Ower!");
  while(1){}
}

void view_down() {
  tft.fillRect(0, tft.height() - 20, tft.width(), 20, WHITE);

  view_bricks();

  for (int i = 0; i < 3; i++) draw_live(i+1);
}

void view_bricks() {
  for (int c = 0; c < 10; c++) tft.drawRGBBitmap(c * 32, tft.height() - 20 - 16, brick, 32, 16);
}

void draw_live_b(int num, bool state) {
  tft.drawRGBBitmap(tft.width() - (10 + 15) * (num), tft.height() - 20 + 2, state?live:nlive, 15, 16);
}

void draw_live(int num) {
  draw_live_b(num, num<=lives);
}

