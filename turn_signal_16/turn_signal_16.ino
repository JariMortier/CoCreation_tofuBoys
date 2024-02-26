
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define stripPin 14
#define stripCount 256  //amount of neopixels
#define rows 16
#define cols 16

#define turnBright 20    //initial brightness
#define raveDecrement 10  //raveMode brightness reduction



Adafruit_NeoPixel strip(stripCount, stripPin, NEO_GRB);

//initialising global vars
bool initLeft = HIGH;
bool initRight = HIGH;
bool catMirror = LOW;
bool blinker = HIGH;
uint8_t turnState = 1;
int16_t turnPix = 0;
uint32_t white = strip.Color(255, 255, 255);
uint32_t orange = strip.Color(255, 80, 0);
uint32_t red = strip.Color(255, 0, 0);
uint32_t pink = strip.Color(255, 10, 125);
uint32_t t0 = millis(); //overflow after 49 days
uint32_t t1 = millis(); //overflow after 49 days

void cat_open(bool mirror){
  const uint8_t whites[] = {37, 38, 41, 42, 52, 55, 56, 59, 115, 116, 117, 122, 123, 124, 131, 132, 133, 138, 139, 140, 147, 148, 154, 155, 163, 164, 165, 170, 171, 172}; //len 30
  const uint8_t pinks[] = {71, 72, 86, 87, 88, 89}; //len 6

  if (mirror){
    for (int i = 0; i < 30; i++){
      strip.setPixelColor(floor(whites[i] / 16) * 16 + 15 - (whites[i] % 16), white);
    }
    for (int i = 0; i < 6; i++){
      strip.setPixelColor(floor(pinks[i] / 16) * 16 + 15 - (pinks[i] % 16), pink);
    }
  } else {
    for (int i = 0; i < 30; i++){
      strip.setPixelColor(whites[i], white);
    }
    for (int i = 0; i < 6; i++){
      strip.setPixelColor(pinks[i], pink);
    }
  }
}

void cat_closed(){
  const uint8_t whites[] = {37, 38, 41, 42, 52, 55, 56, 59, 114, 118, 121, 125, 131, 133, 138, 140, 148, 155}; //len 18
  const uint8_t pinks[] = {71, 72, 86, 87, 88, 89}; //len 6

  for (int i = 0; i < 18; i++){
    strip.setPixelColor(whites[i], white);
  }
  for (int i = 0; i < 6; i++){
    strip.setPixelColor(pinks[i], pink);
  }
}

void turn(bool right){ //arg for mirror
  const uint8_t oranges[] = {22, 41, 42, 52, 54, 73, 76, 82, 86, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 110, 112, 127, 128, 143, 145, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 169, 173, 179, 182, 201, 203, 213, 214, 233}; //len 44

  if (right){
    for (int i = 0; i < 44; i++){
      strip.setPixelColor(floor(oranges[i] / 16) * 16 + 15 - (oranges[i] % 16), orange);
    }
  } else {
    for (int i = 0; i < 44; i++){
      strip.setPixelColor(oranges[i], orange); // array img[3][16x16] => setpixelcolor(img[0][i], img[1][i], img[2][i])
    }
  }
}

void excl1(){
  const uint8_t reds[] = {};
}

void excl2(){
  const uint8_t whites[] = {};
  const uint8_t reds[] = {};
}

void excl3(){
  const uint8_t whites[] = {};
  const uint8_t reds[] = {};
}

void excl4(){
  const uint8_t whites[] = {};
  const uint8_t reds[] = {};
}

void setup() {
  millis(); //overflow after 49 days
  millis(); //overflow after 49 days
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
  bool buttonLeft = digitalRead(35);  //tri-stable switch left
  bool buttonRight = digitalRead(33);  //tri-stable switch right
  bool buttonBrake = digitalRead(32); // brake switch
  t1 = millis(); // keeping up to date

  strip.fill(0, 0, stripCount);  //clear canvas

  if(!(buttonBrake || buttonLeft) && !buttonRight){
    if (t1 - t0 >= 1000){
      t0 = millis();
      if (catMirror){
        catMirror = LOW;
      } else {
        catMirror = HIGH;
      }
      Serial.println(catMirror);
    }
    cat_open(catMirror);
  }

  if (buttonBrake) {
    cat_closed();
  }

  if (buttonLeft) {
    if (t1 - t0 >= 600){
      t0 = millis();
      if (blinker){
        blinker = LOW;
      } else {
        blinker = HIGH;
      }
    }
    if (blinker){
      turn(LOW);
    }
  }

  if (buttonRight) {
    if (t1 - t0 >= 600){
      t0 = millis();
      if (blinker){
        blinker = LOW;
      } else {
        blinker = HIGH;
      }
    }
    if (blinker){
      turn(HIGH);
    }
  }

  strip.show();
  delay(20); // consistency delay 
}
