
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define stripPin 14

#define rows 16                // y
#define cols 16                // x
#define stripCount rows* cols  //amount of neopixels

#define turnBright 255    //initial brightness
#define raveDecrement 10  //raveMode brightness reduction

//foto test
uint8_t rood[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 40, 63, 43, 29, 2, 64, 117, 86, 69, 5, 48, 98, 48, 17, 0, 0, 62, 98, 74, 49, 4, 97, 179, 130, 105, 7, 75, 155, 81, 37, 0, 0, 28, 47, 158, 104, 8, 0, 0, 0, 0, 0, 41, 92, 155, 194, 0, 0, 57, 91, 136, 90, 7, 0, 0, 0, 0, 0, 34, 76, 137, 175, 0, 0, 107, 168, 99, 65, 5, 0, 0, 0, 0, 0, 22, 51, 107, 142, 0, 0, 74, 118, 96, 100, 106, 50, 0, 0, 6, 49, 55, 60, 88, 105, 0, 0, 44, 70, 88, 119, 175, 84, 1, 2, 13, 82, 76, 64, 69, 72, 0, 0, 48, 75, 15, 20, 30, 20, 12, 21, 23, 15, 13, 11, 16, 20, 0, 0, 61, 95, 0, 0, 0, 8, 17, 41, 40, 3, 0, 1, 11, 17, 0, 0, 133, 208, 0, 0, 0, 13, 36, 134, 137, 10, 0, 3, 42, 66, 0, 0, 135, 211, 6, 22, 52, 50, 52, 106, 104, 10, 23, 47, 54, 58, 0, 0, 127, 198, 21, 52, 107, 89, 70, 73, 66, 16, 51, 93, 67, 51, 0, 0, 63, 100, 113, 113, 112, 98, 89, 111, 112, 91, 84, 80, 107, 124, 0, 0, 28, 47, 164, 146, 115, 103, 99, 132, 138, 132, 102, 74, 130, 164, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t groen[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 80, 127, 123, 81, 6, 75, 141, 139, 123, 9, 60, 126, 110, 102, 0, 0, 127, 202, 199, 132, 11, 114, 214, 213, 188, 14, 96, 200, 179, 167, 0, 0, 93, 149, 239, 158, 13, 1, 1, 1, 1, 1, 75, 161, 202, 226, 0, 0, 105, 168, 202, 134, 11, 1, 1, 1, 1, 1, 73, 157, 193, 214, 0, 0, 127, 200, 140, 93, 8, 1, 1, 1, 1, 1, 70, 150, 177, 194, 0, 0, 126, 200, 184, 161, 118, 54, 1, 1, 16, 115, 147, 175, 199, 213, 0, 0, 125, 200, 207, 202, 193, 95, 10, 14, 38, 194, 194, 182, 209, 226, 0, 0, 141, 221, 36, 35, 34, 66, 99, 131, 125, 42, 34, 38, 134, 193, 0, 0, 144, 224, 1, 1, 1, 67, 130, 161, 148, 11, 1, 9, 120, 187, 0, 0, 139, 216, 1, 1, 1, 111, 207, 203, 177, 14, 1, 10, 126, 196, 0, 0, 135, 212, 56, 73, 105, 141, 174, 196, 185, 80, 69, 71, 134, 173, 0, 0, 130, 205, 119, 153, 215, 173, 138, 186, 191, 153, 145, 139, 146, 150, 0, 0, 106, 168, 174, 190, 218, 206, 193, 194, 193, 186, 181, 177, 182, 185, 0, 0, 93, 148, 204, 209, 219, 223, 223, 198, 194, 203, 201, 197, 201, 204, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t blauw[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 33, 52, 34, 22, 1, 62, 114, 90, 75, 6, 46, 95, 57, 34, 0, 0, 52, 82, 59, 39, 3, 94, 173, 138, 114, 8, 73, 151, 94, 60, 0, 0, 44, 71, 158, 104, 8, 0, 0, 0, 0, 0, 43, 96, 152, 187, 0, 0, 66, 105, 138, 91, 7, 0, 0, 0, 0, 0, 39, 88, 141, 173, 0, 0, 105, 166, 104, 69, 5, 0, 0, 0, 0, 0, 33, 73, 121, 150, 0, 0, 68, 107, 99, 101, 105, 49, 0, 0, 6, 49, 56, 62, 93, 111, 0, 0, 36, 57, 88, 118, 173, 83, 1, 4, 14, 82, 69, 50, 66, 75, 0, 0, 49, 76, 15, 20, 29, 20, 14, 40, 42, 17, 12, 9, 16, 20, 0, 0, 63, 98, 0, 0, 0, 11, 24, 60, 59, 4, 0, 1, 9, 15, 0, 0, 133, 208, 0, 0, 0, 35, 72, 137, 134, 10, 0, 2, 32, 51, 0, 0, 135, 211, 6, 19, 43, 57, 71, 100, 94, 9, 25, 50, 56, 61, 0, 0, 127, 199, 21, 45, 89, 80, 68, 61, 53, 15, 54, 98, 83, 74, 0, 0, 73, 116, 109, 104, 94, 89, 89, 111, 113, 91, 79, 72, 107, 128, 0, 0, 43, 71, 158, 136, 96, 94, 100, 139, 146, 132, 94, 59, 120, 158, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


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
uint32_t white = strip.Color(255, 255, 255);
uint32_t orange = strip.Color(255, 80, 0);
uint32_t red = strip.Color(255, 0, 0);
uint32_t pink = strip.Color(255, 10, 125);
uint32_t t0 = millis();  //overflow after 49 days
uint32_t t1 = millis();  //overflow after 49 days

// array img[3][16x16] => setpixelcolor(img[0][i], img[1][i], img[2][i])

void rgb_img(uint8_t reds[], uint8_t greens[], uint8_t blues[]) {  // kan 1 for loop worden
  for (int i = 0; i <= rows; i++) {
    for (int j = 0; j <= cols; j++) {
      if (i % 2 == 1) {
        strip.setPixelColor(cols * i + j, strip.Color(reds[cols * i + j], greens[cols * i + j], blues[cols * i + j]));  // odd rows
      } else {
        strip.setPixelColor(cols * i + j, strip.Color(reds[cols * i - 1 + (rows - j)], greens[cols * i - 1 + (rows - j)], blues[cols * i - 1 + (rows - j)]));  // even rows
      }
    }
  }
}

void turn_outside(bool right, int8_t xShift) {                                                                                                                                                                                            //arg for mirror and horizontal shift
  uint8_t oranges[] = { 22, 41, 42, 52, 54, 73, 76, 82, 86, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 110, 112, 127, 128, 143, 145, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 169, 173, 179, 182, 201, 203, 213, 214, 233 };  //len 44

  if (right) {  //mirror
    for (int i = 0; i < 44; i++) {
      oranges[i] = floor(oranges[i] / 16) * 16 + 15 - (oranges[i] % 16);
    }
  }

  if (xShift != 0) {  // horizontal shift
    for (int i = 0; i < 44; i++) {
      if (int8_t(floor(oranges[i] / 16)) % 2 == 0) {
        oranges[i] = floor(oranges[i] / 16) * 16 + (oranges[i] - xShift) % 16;
      } else {
        oranges[i] = floor(oranges[i] / 16) * 16 + (oranges[i] + xShift) % 16;
      }
    }
  }

  for (int i = 0; i < 44; i++) {
    strip.setPixelColor(oranges[i], orange);
  }
}

void turn_inside(bool right, int8_t colShift) {                                                                                                                                                                                                                      //arg for mirror and horizontal shift
  uint8_t oranges[] = { 53, 74, 75, 83, 84, 85, 106, 107, 108, 109, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 146, 147, 148, 149, 170, 171, 172, 180, 181, 202 };  //len 48

  if (right) {  //mirror
    for (int i = 0; i < 48; i++) {
      oranges[i] = floor(oranges[i] / 16) * 16 + 15 - (oranges[i] % 16);
    }
  }

  if (colShift != 0) {  // horizontal shift
    for (int i = 0; i < 48; i++) {
      if (int8_t(floor(oranges[i] / 16)) % 2 == 0) {
        oranges[i] = floor(oranges[i] / 16) * 16 + (oranges[i] - colShift) % 16;
      } else {
        oranges[i] = floor(oranges[i] / 16) * 16 + (oranges[i] + colShift) % 16;
      }
    }
  }

  for (int i = 0; i < 48; i++) {
    strip.setPixelColor(oranges[i], orange);
  }
}

void excl1() {
  const uint8_t reds[] = { 23, 24, 38, 39, 40, 41, 54, 55, 56, 57, 71, 72, 103, 104, 118, 119, 120, 121, 134, 135, 136, 137, 150, 151, 152, 153, 166, 167, 168, 169, 182, 183, 184, 185, 198, 199, 200, 201, 214, 215, 216, 217, 230, 231, 232, 233 };  //len 46

  for (int i = 0; i < 46; i++) {
    strip.setPixelColor(reds[i], red);
  }
}

void setup() {
  pinMode(32, INPUT);
  pinMode(35, INPUT);
  pinMode(33, INPUT);
  strip.begin();
  strip.show();
  strip.setBrightness(turnBright);
  randomSeed(analogRead(34));
  Serial.begin(9600);
}

void loop() {
  bool buttonLeft = digitalRead(35);   //tri-stable switch left
  bool buttonRight = digitalRead(33);  //tri-stable switch right
  bool buttonBrake = digitalRead(32);  // brake switch
  t1 = millis();                       // keeping up to date

  strip.fill(0, 0, stripCount);  //clear canvas

  if (!(buttonBrake || buttonLeft) && !buttonRight) {
    rgb_img(rood, groen, blauw);
  }

  if (buttonLeft) {
    if (initLeft) {
      initLeft = LOW;
      blinker = HIGH;
      t0 = millis();
      t1 = millis();
    }
    if (t1 - t0 >= 600) {
      t0 = millis();
      if (blinker) {
        blinker = LOW;
      } else {
        blinker = HIGH;
      }
    }
    if (blinker) {
      turn_outside(LOW, 0);
    } else {
      turn_inside(LOW, 0);
    }
  } else {
    initLeft = HIGH;
  }

  if (buttonRight) {
    if (initRight) {
      initRight = LOW;
      blinker = HIGH;
      t0 = millis();
      t1 = millis();
    }
    if (t1 - t0 >= 600) {
      t0 = millis();
      if (blinker) {
        blinker = LOW;
      } else {
        blinker = HIGH;
      }
    }
    if (blinker) {
      turn_outside(HIGH, 0);
    } else {
      turn_inside(HIGH, 0);
    }
  } else {
    initRight = HIGH;
  }

  if (buttonBrake) {  // move brake button when signaling right and left
    excl1();
  }

  strip.show();
  delay(10);  // consistency delay
}
