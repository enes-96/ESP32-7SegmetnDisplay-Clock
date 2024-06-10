#include <Wire.h>
#include <RTClib.h>

#define CUSTOM_SDA_PIN 15
#define CUSTOM_SCL_PIN 0

#define SEG_A 32
#define SEG_B 22
#define SEG_C 19
#define SEG_D 5
#define SEG_E 4
#define SEG_F 33
#define SEG_G 26
#define SEG_DP 18

#define DIGIT_1 27
#define DIGIT_2 25
#define DIGIT_3 21
#define DIGIT_4 23

const int digits[] = {DIGIT_1, DIGIT_2, DIGIT_3, DIGIT_4};

void displayTimeOnDigits(int hours, int minutes);
void displayNumberOnDigit(int num, int digitIndex);
void setSegments(int num);

RTC_DS1307 rtc;

void setup() {
  Wire.begin(CUSTOM_SDA_PIN, CUSTOM_SCL_PIN);
  Serial.begin(9600);

  if (!rtc.begin()) {
    Serial.println("RTC initialization failed!");
    while (1); 
  }

  rtc.adjust(DateTime(__DATE__, __TIME__));

  pinMode(SEG_A, OUTPUT);
  pinMode(SEG_B, OUTPUT);
  pinMode(SEG_C, OUTPUT);
  pinMode(SEG_D, OUTPUT);
  pinMode(SEG_E, OUTPUT);
  pinMode(SEG_F, OUTPUT);
  pinMode(SEG_G, OUTPUT);
  pinMode(SEG_DP, OUTPUT);

  for (int i = 0; i < 4; i++) {
    pinMode(digits[i], OUTPUT); 
    digitalWrite(digits[i], HIGH); 
  }
}

void loop() {
  DateTime now = rtc.now();
  displayTimeOnDigits(now.hour(), now.minute());
}

void displayTimeOnDigits(int hours, int minutes) {
  int hours_tens = hours / 10;
  int hours_units = hours % 10;
  int minutes_tens = minutes / 10;
  int minutes_units = minutes % 10;

  displayNumberOnDigit(hours_tens, 0);
  displayNumberOnDigit(hours_units, 1);
  displayNumberOnDigit(minutes_tens, 2);
  displayNumberOnDigit(minutes_units, 3);
}

void displayNumberOnDigit(int num, int digitIndex) {
  digitalWrite(digits[digitIndex], LOW);
  setSegments(num);
  delay(5); 
  digitalWrite(digits[digitIndex], HIGH);
}

void setSegments(int num) {
  switch (num) {
    case 0: setSegments(HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW); break;
    case 1: setSegments(LOW, HIGH, HIGH, LOW, LOW, LOW, LOW); break;
    case 2: setSegments(HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH); break;
    case 3: setSegments(HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH); break;
    case 4: setSegments(LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH); break;
    case 5: setSegments(HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH); break;
    case 6: setSegments(HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH); break;
    case 7: setSegments(HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW); break;
    case 8: setSegments(HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH); break;
    case 9: setSegments(HIGH, HIGH, HIGH, HIGH, LOW, HIGH, HIGH); break;
  }
}

void setSegments(int a, int b, int c, int d, int e, int f, int g) {
  digitalWrite(SEG_A, a);
  digitalWrite(SEG_B, b);
  digitalWrite(SEG_C, c);
  digitalWrite(SEG_D, d);
  digitalWrite(SEG_E, e);
  digitalWrite(SEG_F, f);
  digitalWrite(SEG_G, g);
}