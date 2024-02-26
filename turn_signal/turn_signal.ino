
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define stripPin 14
#define stripCount 34  //amount of neopixels

#define turnBright 100    //initial RaveMode brightness
#define raveDecrement 10  //raveMode brightness reduction



Adafruit_NeoPixel strip(stripCount, stripPin, NEO_GRB);

//initialising global vars
bool initLeft = HIGH;
bool initRight = HIGH;
uint8_t turnState = 1;
int8_t turnPix = 0;
uint32_t bright = strip.Color(255, 255, 255);
uint32_t orange = strip.Color(255, 80, 0);
uint32_t red = strip.Color(255, 0, 0);


void setup() {
  pinMode(32, INPUT);
  pinMode(35, INPUT);
  pinMode(33, INPUT);
  strip.begin();
  strip.show();
  randomSeed(analogRead(34));
  Serial.begin(9600);
}

void loop() {
  bool buttonLeft = digitalRead(35);  //tri-stable switch left
  bool buttonRight = digitalRead(33);  //tri-stable switch right
  bool buttonBrake = digitalRead(32); // brake switch

  strip.setBrightness(turnBright);

  //strip.setPixelColor(ravePix - i, strip.ColorHSV(raveHue, 255, max(raveBright - (raveDecrement * i), 0)));
  strip.fill(0, 0, stripCount);  //clear canvas

  if (buttonBrake) {
    strip.fill(red, 0, stripCount);
  }

  if (buttonLeft) {
    if (initLeft) {
      turnPix = 9;
      initLeft = LOW;
    }

    for (int i = 0; i < min(3, int(turnPix) + 1); i++) {
      strip.setPixelColor(turnPix - i, orange);
    }
    turnPix--;

    if (turnPix < 0) {
      turnPix = 9;
    }
  } else {
    initLeft = HIGH;
  }

  if (buttonRight) {
    if (initRight) {
      turnPix = stripCount - 10;
      initRight = LOW;
    }

    strip.fill(orange, turnPix, 3);
    turnPix++;
    if (turnPix > stripCount) {
      turnPix = stripCount - 10;
    }
  } else {
    initRight = HIGH;
  }

  strip.show();
  delay(100);
}
