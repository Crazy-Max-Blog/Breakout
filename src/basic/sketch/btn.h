/*class btn {
  public:
    btn(byte pin) {
      _pin = pin;
      pinMode(pin, INPUT);
    }
 
    bool tick() { 
      bool bv = !digitalRead(_pin);
      if(bv==1) {
        if(b!=bv) {
          b=bv;
          t = millis();
          return true;
        }
        /*if(b and millis()-t>=500) {
          t = millis();
          return true;
        }*
      } else if (bv==0 and b!=bv and millis()-t>=100) {
        b=bv;
      }
      return false;
    }

    operator bool() {
      return tick();
    }

    byte _pin;
    bool b;
    long t;
};*/

class btn {
  public:
    btn(byte pin) {
      _pin = pin;
      pinMode(pin, INPUT_PULLUP);
    }
 
    bool tick() { 
      //static bool b;
	    //static long t;
	    bool bv = !digitalRead(_pin);
	    if(bv and !b) {b=1; t = millis();}
	    if(bv) return true; //  and b and millis()-t>=0
      if(!(bv and b)) b=0;
	    return false;
    }

    operator bool() {
      return tick();
    }

    byte _pin;
    bool b;
    long t;
};