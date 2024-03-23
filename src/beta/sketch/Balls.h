class CVector {
  public:
  CVector() {
    x = 0;
    y = 0;
  }
  
  CVector(int a, int b) {
    x = a;
    y = b;
  }

  CVector(float a, float b) {
    x = a;
    y = b;
  }

  void mult(int m) {
    x*=m; 
    y*=m;
  }

  void add(CVector v) {
    x += v.x;
    y += v.y;
  }

  float x, y;
};

uint16_t f = 0;

void fill(int v) {
  f = v;
}

void ellipse(int x, int y, int r1, int r2) {
  tft.fillCircle(x, y, r1, f);
}

int width = tft.width();
int height = tft.height();

class Ball {
  public:
  CVector position;
  CVector velocity;

  float radius, m;

  Ball(float x, float y, float r_) {
    position.x=x;
    position.y=y;
    velocity.x=1;
    velocity.y=1;
    //velocity.mult(3); // *3
    radius = r_;
    m = radius*.1;
  }

  void update() {
    //position.x += velocity.x;
    //position.y += velocity.y;
    fill(BLUE);
    //stroke(51);
    ellipse(position.x, position.y, radius*2+4, radius*2+4);
    position.add(velocity);
    fill(0);
    //stroke(0);
    ellipse(position.x, position.y, radius*2, radius*2);
    checkBoundaryCollision();
  }

  void mmm() {
    lives-=1;
    update();
    delay(1000);
  }

  void checkBoundaryCollision() {
    if (position.x > 320-radius*2.5) {
      position.x = 320-radius*2.5;
      velocity.x *= -1;
    } else if (position.x < radius) {
      position.x = radius;
      velocity.x *= -1;
    } else if (position.y >= 190) {
      fill(BLUE);
      ellipse(position.x, position.y, radius*2+4, radius*2+4);
      fill(0);
      position.y = 170-radius*4;
      position.x = rx+32;
      velocity.y *= -1;
      mmm();
    } else if (position.y < radius+16) {
      position.y = radius+16;
      velocity.y *= -1;
    } else if (position.y >=170-radius*4 && (rx+64>position.x-radius && position.x>rx+radius)) {
      position.y = 170-radius*4;
      velocity.y *= -1;
    }
  }

  void display() {
    //noStroke();
    fill(204);
    ellipse(position.x, position.y, radius*2, radius*2);
  }
};
