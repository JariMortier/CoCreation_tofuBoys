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

#define turnBright 100    //initial brightness
#define raveDecrement 10  //raveMode brightness reduction

#define decTresh -2 //deceleration treshold (m/s²)

//foto test
uint8_t rood[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 164, 124, 51, 58, 66, 17, 20, 72, 105, 142, 175, 194, 37, 17, 0, 0, 130, 107, 67, 54, 42, 11, 16, 69, 88, 107, 137, 155, 81, 48, 0, 0, 74, 80, 93, 47, 3, 1, 11, 64, 60, 51, 76, 92, 155, 98, 0, 0, 102, 84, 51, 23, 0, 0, 13, 76, 55, 22, 34, 41, 75, 48, 0, 0, 132, 91, 16, 10, 10, 3, 15, 82, 49, 0, 0, 0, 7, 5, 0, 0, 138, 112, 66, 104, 137, 40, 23, 13, 6, 0, 0, 0, 105, 69, 0, 0, 132, 111, 73, 106, 134, 41, 21, 2, 0, 0, 0, 0, 130, 86, 0, 0, 99, 89, 70, 52, 36, 17, 12, 1, 0, 0, 0, 0, 179, 117, 0, 0, 103, 98, 89, 50, 13, 8, 20, 84, 50, 0, 0, 0, 97, 64, 0, 0, 115, 112, 107, 52, 0, 0, 30, 175, 106, 5, 7, 8, 4, 2, 0, 0, 146, 113, 52, 22, 0, 0, 20, 119, 100, 65, 90, 104, 49, 29, 0, 0, 164, 113, 21, 6, 0, 0, 15, 88, 96, 99, 136, 158, 74, 43, 0, 0, 47, 100, 198, 211, 208, 95, 75, 70, 118, 168, 91, 47, 98, 63, 0, 0, 28, 63, 127, 135, 133, 61, 48, 44, 74, 107, 57, 28, 62, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t groen[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 204, 185, 150, 173, 196, 187, 193, 226, 213, 194, 214, 226, 167, 102, 0, 0, 201, 182, 146, 134, 126, 120, 134, 209, 199, 177, 193, 202, 179, 110, 0, 0, 197, 177, 139, 71, 10, 9, 38, 182, 175, 150, 157, 161, 200, 126, 0, 0, 201, 181, 145, 69, 1, 1, 34, 194, 147, 70, 73, 75, 96, 60, 0, 0, 203, 186, 153, 80, 14, 11, 42, 194, 115, 1, 1, 1, 14, 9, 0, 0, 194, 193, 191, 185, 177, 148, 125, 38, 16, 1, 1, 1, 188, 123, 0, 0, 198, 194, 186, 196, 203, 161, 131, 14, 1, 1, 1, 1, 213, 139, 0, 0, 223, 193, 138, 174, 207, 130, 99, 10, 1, 1, 1, 1, 214, 141, 0, 0, 223, 206, 173, 141, 111, 67, 66, 95, 54, 1, 1, 1, 114, 75, 0, 0, 219, 218, 215, 105, 1, 1, 34, 193, 118, 8, 11, 13, 11, 6, 0, 0, 209, 190, 153, 73, 1, 1, 35, 202, 161, 93, 134, 158, 132, 81, 0, 0, 204, 174, 119, 56, 1, 1, 36, 207, 184, 140, 202, 239, 199, 123, 0, 0, 148, 168, 205, 212, 216, 224, 221, 200, 200, 200, 168, 149, 202, 127, 0, 0, 93, 106, 130, 135, 139, 144, 141, 125, 126, 127, 105, 93, 127, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t blauw[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 158, 128, 74, 61, 51, 15, 20, 75, 111, 150, 173, 187, 60, 34, 0, 0, 120, 107, 83, 56, 32, 9, 16, 66, 93, 121, 141, 152, 94, 57, 0, 0, 59, 72, 98, 50, 2, 1, 9, 50, 62, 73, 88, 96, 151, 95, 0, 0, 94, 79, 54, 25, 0, 0, 12, 69, 56, 33, 39, 43, 73, 46, 0, 0, 132, 91, 15, 9, 10, 4, 17, 82, 49, 0, 0, 0, 8, 6, 0, 0, 146, 113, 53, 94, 134, 59, 42, 14, 6, 0, 0, 0, 114, 75, 0, 0, 139, 111, 61, 100, 137, 60, 40, 4, 0, 0, 0, 0, 138, 90, 0, 0, 100, 89, 68, 71, 72, 24, 14, 1, 0, 0, 0, 0, 173, 114, 0, 0, 94, 89, 80, 57, 35, 11, 20, 83, 49, 0, 0, 0, 94, 62, 0, 0, 96, 94, 89, 43, 0, 0, 29, 173, 105, 5, 7, 8, 3, 1, 0, 0, 136, 104, 45, 19, 0, 0, 20, 118, 101, 69, 91, 104, 39, 22, 0, 0, 158, 109, 21, 6, 0, 0, 15, 88, 99, 104, 138, 158, 59, 34, 0, 0, 71, 116, 199, 211, 208, 98, 76, 57, 107, 166, 105, 71, 82, 52, 0, 0, 43, 73, 127, 135, 133, 63, 49, 36, 68, 105, 66, 44, 52, 33, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


Adafruit_NeoPixel strip(stripCount, stripPin, NEO_GRB);

//initialising global vars
uint32_t red = strip.Color(255, 0, 0);
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

  t1 = millis();  // keeping up to date

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
