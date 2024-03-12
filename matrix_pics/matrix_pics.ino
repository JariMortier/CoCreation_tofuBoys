
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define stripPin 14

#define rows 16                // y
#define cols 16                // x
#define stripCount rows* cols  //amount of neopixels

#define turnBright 255     //initial brightness
#define raveDecrement 10  //raveMode brightness reduction

//foto test
uint8_t rood[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0, 0, 0, 0, 255, 255, 255, 0, 0, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0, 0, 0, 0, 255, 255, 255, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0, 0, 0, 0, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 255, 255, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t groen[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0, 0, 0, 0, 255, 255, 255, 0, 0, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0, 0, 0, 0, 255, 255, 255, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0, 0, 0, 0, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 255, 255, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t blauw[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0, 0, 0, 0, 255, 255, 255, 0, 0, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0, 0, 0, 0, 255, 255, 255, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0, 0, 0, 0, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 125, 125, 125, 125, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 125, 125, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 255, 255, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


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
      if (i % 2 == 0) {
        strip.setPixelColor(cols * i + j, strip.Color(reds[cols * i + j], greens[cols * i + j], blues[cols * i + j]));  // even rows
      } else {
        strip.setPixelColor(cols * i + (rows - j), strip.Color(reds[cols * i + (rows - j)], greens[cols * i + (rows - j)], blues[cols * i + (rows - j)]));  // odd rows
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
   /* if (t1 - t0 >= 150) {
      t0 = millis();
      if (random(0, 100) >= 80) {
        catState = uint8_t(random(3));
      }
    }*/
    switch (catState) {
      case 0:
        rgb_img(rood, groen, blauw);
        //cat_open(LOW, 1);
        break;

      case 1:
        cat_open(HIGH, 1);
        break;

      case 2:
        cat_closed(1);
        break;
    }
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
