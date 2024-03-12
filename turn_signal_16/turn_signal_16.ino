
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define stripPin 14

#define rows 16                // y
#define cols 16                // x
#define stripCount rows* cols  //amount of neopixels

#define turnBright 20     //initial brightness
#define raveDecrement 10  //raveMode brightness reduction

//foto test
uint8_t rood[] = {247, 247, 239, 239, 240, 241, 247, 140, 123, 143, 243, 243, 244, 244, 244, 239, 247, 248, 240, 239, 241, 241, 106, 155, 233, 145, 134, 242, 244, 244, 244, 239, 245, 246, 238, 237, 238, 236, 41, 213, 231, 193, 83, 239, 242, 242, 242, 237, 253, 253, 244, 243, 245, 48, 212, 238, 235, 235, 170, 114, 249, 249, 249, 245, 238, 238, 230, 231, 231, 57, 208, 238, 237, 246, 171, 110, 234, 234, 235, 230, 1, 12, 16, 16, 16, 194, 229, 238, 250, 244, 181, 37, 5, 5, 5, 6, 48, 210, 233, 233, 228, 226, 37, 215, 241, 182, 26, 61, 45, 34, 33, 26, 236, 101, 156, 229, 226, 230, 38, 217, 177, 55, 22, 44, 35, 32, 21, 96, 246, 242, 146, 141, 231, 239, 169, 132, 68, 58, 28, 34, 31, 19, 123, 231, 247, 248, 234, 143, 164, 240, 114, 65, 63, 40, 34, 30, 16, 138, 236, 239, 252, 253, 244, 153, 152, 116, 65, 61, 39, 33, 29, 23, 12, 163, 248, 244, 252, 252, 218, 103, 135, 66, 62, 37, 33, 31, 24, 22, 123, 92, 200, 244, 248, 249, 211, 34, 68, 64, 39, 10, 7, 11, 25, 110, 219, 83, 191, 239, 247, 236, 15, 64, 58, 49, 46, 223, 244, 209, 47, 110, 204, 195, 47, 219, 248, 236, 13, 45, 70, 213, 247, 247, 245, 241, 243, 171, 107, 125, 33, 220, 248, 243, 116, 117, 192, 242, 247, 247, 246, 241, 244, 244, 174, 117, 118, 230};
uint8_t groen[] = {247, 247, 239, 239, 239, 241, 247, 140, 28, 142, 242, 243, 244, 244, 244, 239, 247, 248, 240, 238, 240, 241, 106, 33, 35, 74, 133, 242, 244, 244, 244, 239, 245, 245, 237, 236, 238, 236, 38, 34, 92, 89, 83, 238, 242, 241, 241, 236, 253, 253, 244, 244, 244, 47, 32, 97, 105, 130, 159, 114, 249, 249, 249, 245, 238, 238, 231, 231, 231, 50, 92, 105, 113, 230, 162, 112, 234, 234, 234, 230, 1, 2, 7, 6, 7, 88, 102, 110, 225, 229, 200, 89, 9, 10, 10, 7, 38, 32, 38, 42, 81, 103, 19, 201, 226, 180, 53, 151, 155, 157, 144, 43, 236, 95, 31, 78, 102, 142, 26, 202, 199, 128, 54, 155, 158, 126, 43, 97, 246, 242, 140, 66, 150, 215, 158, 176, 154, 142, 120, 157, 114, 39, 124, 230, 247, 248, 234, 135, 146, 225, 174, 154, 152, 156, 158, 111, 31, 138, 235, 238, 252, 253, 243, 153, 142, 175, 157, 155, 159, 160, 125, 44, 17, 163, 248, 244, 252, 252, 218, 97, 177, 155, 155, 160, 161, 141, 44, 34, 93, 69, 199, 243, 248, 249, 211, 64, 152, 152, 159, 31, 15, 20, 36, 86, 153, 58, 191, 239, 247, 235, 25, 151, 135, 62, 46, 223, 244, 209, 47, 84, 132, 65, 10, 218, 248, 236, 20, 103, 92, 213, 247, 247, 245, 240, 243, 171, 49, 21, 9, 220, 248, 243, 116, 116, 192, 242, 248, 247, 246, 241, 243, 244, 174, 117, 117, 230};
uint8_t blauw[] = {247, 247, 238, 238, 239, 240, 246, 139, 36, 142, 242, 242, 243, 243, 243, 238, 247, 248, 239, 238, 239, 239, 105, 43, 53, 39, 133, 242, 243, 243, 244, 238, 245, 245, 236, 235, 237, 235, 39, 47, 45, 38, 80, 238, 241, 241, 241, 236, 253, 253, 244, 243, 244, 47, 44, 41, 42, 48, 51, 113, 248, 248, 248, 244, 237, 238, 230, 229, 230, 46, 36, 40, 43, 74, 52, 108, 234, 233, 234, 230, 1, 3, 6, 6, 6, 34, 39, 42, 74, 74, 64, 30, 8, 12, 12, 12, 38, 46, 54, 53, 46, 42, 10, 66, 74, 61, 21, 61, 145, 200, 195, 128, 235, 96, 39, 47, 43, 52, 12, 67, 67, 45, 40, 151, 202, 186, 111, 102, 246, 241, 135, 30, 54, 72, 52, 58, 52, 63, 152, 201, 182, 95, 132, 230, 246, 247, 233, 131, 50, 73, 56, 51, 52, 179, 201, 179, 84, 144, 234, 238, 252, 253, 243, 153, 47, 57, 51, 49, 175, 204, 191, 152, 67, 163, 248, 243, 251, 252, 217, 44, 58, 51, 50, 174, 205, 196, 152, 148, 158, 78, 199, 243, 247, 248, 210, 24, 52, 52, 174, 39, 18, 39, 145, 162, 183, 67, 190, 239, 246, 235, 13, 51, 47, 47, 46, 222, 244, 209, 47, 95, 161, 123, 27, 218, 247, 236, 11, 37, 65, 212, 246, 246, 245, 240, 242, 170, 75, 68, 19, 220, 248, 242, 116, 116, 192, 240, 247, 246, 246, 241, 243, 243, 173, 117, 117, 230};


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

void cat_open(bool mirror, uint8_t yShift) {
  uint8_t whites[] = { 37, 38, 41, 42, 52, 55, 56, 59, 115, 116, 117, 122, 123, 124, 131, 132, 133, 138, 139, 140, 147, 148, 154, 155, 163, 164, 165, 170, 171, 172 };  //len 30
  uint8_t pinks[] = { 71, 72, 86, 87, 88, 89 };                                                                                                                         //len 6

  if (yShift != 0) {
    for (int i = 0; i < 30; i++) {
      if (int8_t(floor(whites[i] / 16)) % 2 == 0) {  // mirror even lines
        whites[i] = floor(whites[i] / 16) * 16 + 15 - (whites[i] % 16);
      }
      whites[i] += 16 * yShift;
      whites[i] %= 256;
      if (whites[i] < 0) {
        whites[i] += 256;
      }
    }
    for (int i = 0; i < 6; i++) {
      if (int8_t(floor(pinks[i] / 16)) % 2 == 0) {  // mirror even lines
        pinks[i] = floor(pinks[i] / 16) * 16 + 15 - (pinks[i] % 16);
      }
      pinks[i] += 16 * yShift;
      pinks[i] %= 256;
      if (pinks[i] < 0) {
        pinks[i] += 256;
      }
    }
  }

  if (mirror) {
    for (int i = 0; i < 30; i++) {
      strip.setPixelColor(floor(whites[i] / 16) * 16 + 15 - (whites[i] % 16), white);
    }
    for (int i = 0; i < 6; i++) {
      strip.setPixelColor(floor(pinks[i] / 16) * 16 + 15 - (pinks[i] % 16), pink);
    }
  } else {
    for (int i = 0; i < 30; i++) {
      strip.setPixelColor(whites[i], white);
    }
    for (int i = 0; i < 6; i++) {
      strip.setPixelColor(pinks[i], pink);
    }
  }
}

void cat_closed(uint8_t yShift) {
  uint8_t whites[] = { 37, 38, 41, 42, 52, 55, 56, 59, 114, 118, 121, 125, 131, 133, 138, 140, 148, 155 };  //len 18
  uint8_t pinks[] = { 71, 72, 86, 87, 88, 89 };                                                             //len 6

  if (yShift != 0) {
    for (int i = 0; i < 18; i++) {
      if (int8_t(floor(whites[i] / 16)) % 2 == 0) {  // mirror even lines
        whites[i] = floor(whites[i] / 16) * 16 + 15 - (whites[i] % 16);
      }
      whites[i] += 16 * yShift;
      whites[i] %= 256;
      if (whites[i] < 0) {
        whites[i] += 256;
      }
    }
    for (int i = 0; i < 6; i++) {
      if (int8_t(floor(pinks[i] / 16)) % 2 == 0) {  // mirror even lines
        pinks[i] = floor(pinks[i] / 16) * 16 + 15 - (pinks[i] % 16);
      }
      pinks[i] += 16 * yShift;
      pinks[i] %= 256;
      if (pinks[i] < 0) {
        pinks[i] += 256;
      }
    }
  }

  for (int i = 0; i < 18; i++) {
    strip.setPixelColor(whites[i], white);
  }
  for (int i = 0; i < 6; i++) {
    strip.setPixelColor(pinks[i], pink);
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

void excl2() {
  const uint8_t whites[] = { 26, 27, 36, 37, 38, 56, 57, 59, 68, 71, 72, 73, 74, 75, 83, 92, 98, 109, 113, 126, 129, 142, 145, 158, 161, 174, 177, 190, 193, 206, 210, 221, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236 };  //len 42
  const uint8_t reds[] = { 103, 104, 135, 136, 151, 152, 167, 168, 183, 184, 199, 200 };                                                                                                                                         //len 12

  for (int i = 0; i < 42; i++) {
    strip.setPixelColor(whites[i], white);
  }
  for (int i = 0; i < 12; i++) {
    strip.setPixelColor(reds[i], red);
  }
}

void excl3() {
  const uint8_t whites[] = { 26, 27, 36, 37, 38, 56, 57, 59, 68, 71, 72, 73, 74, 75, 83, 92, 98, 109, 113, 126, 129, 142, 145, 158, 161, 174, 177, 190, 193, 206, 210, 221, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236 };  //len 42
  const uint8_t reds[] = { 101, 104, 107, 133, 136, 139, 148, 151, 154, 165, 168, 171, 180, 183, 186, 197, 200, 203 };                                                                                                           //len 18

  for (int i = 0; i < 42; i++) {
    strip.setPixelColor(whites[i], white);
  }
  for (int i = 0; i < 18; i++) {
    strip.setPixelColor(reds[i], red);
  }
}

void excl4() {
  const uint8_t whites[] = { 26, 27, 36, 37, 38, 56, 57, 59, 68, 71, 72, 73, 74, 75, 83, 92, 98, 109, 113, 126, 129, 142, 145, 158, 161, 174, 177, 190, 193, 206, 210, 221, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236 };  //len 42
  const uint8_t reds[] = { 100, 101, 103, 104, 106, 107, 132, 133, 135, 136, 138, 139, 148, 149, 151, 152, 154, 155, 164, 165, 167, 168, 170, 171, 180, 181, 183, 184, 186, 187, 196, 197, 199, 200, 202, 203 };                 //len 36

  for (int i = 0; i < 42; i++) {
    strip.setPixelColor(whites[i], white);
  }
  for (int i = 0; i < 36; i++) {
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
