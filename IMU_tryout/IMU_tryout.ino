
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu; //SDA 21, SCL 22

#define stripPin 14

#define rows 16                // y
#define cols 16                // x
#define stripCount rows* cols  //amount of neopixels

#define turnBright 10    //initial brightness
#define raveDecrement 10  //raveMode brightness reduction

#define decTresh -2 //deceleration treshold (m/s²)

//foto test
uint8_t rood[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 255, 255, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t groen[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 255, 255, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t blauw[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 255, 255, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 125, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 125, 125, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 125, 125, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 125, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


Adafruit_NeoPixel strip(stripCount, stripPin, NEO_GRB);

//initialising global vars
bool blinker = LOW;
bool initRight = HIGH;
bool initLeft = HIGH;
uint16_t yScroll = 0;
int8_t shiftRight = 0;
int8_t shiftLeft = 0;
uint8_t turnState = 1;
uint8_t catState = 0;
int16_t turnPix = 0;
//uint32_t white = strip.Color(255, 255, 255);
//uint32_t orange = strip.Color(255, 80, 0);
uint32_t red = strip.Color(255, 0, 0);
//uint32_t pink = strip.Color(255, 10, 125);
uint32_t t0 = millis();  //overflow after 49 days
uint32_t t1 = millis();  //overflow after 49 days

// array img[3][16x16] => setpixelcolor(img[0][i], img[1][i], img[2][i])

void rgb_img(uint8_t reds[], uint8_t greens[], uint8_t blues[]) {  // kan 1 for loop worden
  for (int i = 0; i <= rows; i++) {
    for (int j = 0; j <= cols; j++) {
      if (i % 2 == 0) {
        strip.setPixelColor(cols * i + j, strip.Color(reds[cols * i + j], greens[cols * i + j], blues[cols * i + j]));  // odd rows
      } else {
        strip.setPixelColor(cols * i + j, strip.Color(reds[cols * i - 1 + (rows - j)], greens[cols * i - 1 + (rows - j)], blues[cols * i - 1 + (rows - j)]));  // even rows
      }
    }
  }
}

void excl1() {
  const uint8_t reds[] = {97, 98, 99, 100, 101, 102, 103, 104, 108, 109, 113, 114, 115, 116, 118, 119, 120, 121, 122, 123, 124, 125, 126, 129, 130, 131, 132, 133, 134, 135, 136, 137, 139, 140, 141, 142, 146, 147, 151, 152, 153, 154, 155, 156, 157, 158};  //len 46

  for (int i = 0; i < 46; i++) {
    strip.setPixelColor(reds[i], red);
  }
}

void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(turnBright);
  randomSeed(analogRead(34));

  if (!mpu.begin()) {
    strip.fill(red, 0, stripCount);
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  
}

void loop() {

  t1 = millis();                       // keeping up to date

  strip.fill(0, 0, stripCount);  //clear canvas

// welke waarde constant tussen 9 en 10 m/s²? => downwards
// rem is in tegengestelde richting van de richting waar werd versneld.

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  if (a.acceleration.x <= decTresh) {
    excl1();
  } else {
    rgb_img(rood, groen, blauw);
  }

  strip.show();

  delay(150);  // consistency delay
}
