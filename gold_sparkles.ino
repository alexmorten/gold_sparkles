 
#include <Adafruit_NeoPixel.h>
 
#define PIN 12
#define N_LEDS 16
#define N_TRAIL 16

#define BIG_N_LEDS 60
#define BIG_DATA_PIN 10

 

Adafruit_NeoPixel big_strip = Adafruit_NeoPixel(BIG_N_LEDS, BIG_DATA_PIN, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);
 
void setup() {
  strip.begin();
  big_strip.begin();
  
    for (uint16_t i=0; i < BIG_N_LEDS; i++) {
      big_strip.setPixelColor(i, strip.Color(0, 0 , 0));
    }
 
  // Update LED contents, to start they are all 'off'
  big_strip.show();
}
  
void loop() {
//  bigColorWipe(bigColor(25, 25, 25), 50);  
  uint16_t upper_limit = 50;
  uint16_t lower_limit = 20;
  for(int16_t i=lower_limit; i<upper_limit; i = i + 1) {
    big_strip.begin();
    chase(strip.Color(i, i, 0));
    bigColorWipe(strip.Color(i, i, 0));
    random_LED();
    random_LED();
    random_LED();
    random_LED();
    big_strip.show();
    strip.show();
    delay(15);
  }
   for(int16_t i=upper_limit; i>lower_limit; i = i - 1) {
    chase(strip.Color(i, i, 0));
    bigColorWipe(strip.Color(i, i, 0));
    random_LED(); 
    random_LED();
    random_LED();
    random_LED();
    big_strip.show();
    strip.show();
    delay(5);
  }
}

static void random_LED(){
  int r = random(0, N_LEDS);
  int red = random(100,255);
  int green = random(100,255);
  int blue = random(100,255);
  strip.setPixelColor(r, strip.Color(red, green , blue));

  r = random(0, BIG_N_LEDS);
  big_strip.setPixelColor(r, strip.Color(red, green , blue));
}

static void chase(uint32_t c) {
  for(int16_t i=0; i<strip.numPixels()+N_TRAIL; i++) {
      for(int16_t s=0;s<N_TRAIL; s++){
        int16_t offset_index = i-s;
        if (offset_index < 0){
         strip.setPixelColor(N_LEDS - offset_index, c);  
        }else {
          strip.setPixelColor(offset_index, c);  
        }
      }
      strip.setPixelColor(i  , c); // Draw new pixel
      strip.show();
  }
}

static void chase_i(uint32_t c, uint16_t i) {
    strip.setPixelColor(i, c); // Draw new pixel
    for(uint16_t s=0;s<N_TRAIL; s++){
      strip.setPixelColor(i-s, c-(c/N_TRAIL)*(s+1));
    }
    strip.show();
    
}

static void show_all(uint32_t c){
  for(uint16_t i=0; i<strip.numPixels()+N_TRAIL; i++) {
      strip.setPixelColor(i , c); // Draw new pixel
  }
}

// fill the dots one after the other with said color
// good for testing purposes
void bigColorWipe(uint32_t c) {
  int i;
 
  for (i=0; i < 144; i++) {
      big_strip.setPixelColor(i, c);
  }
//  big_strip.show();
}
 

