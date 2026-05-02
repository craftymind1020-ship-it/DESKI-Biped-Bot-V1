#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "BluetoothSerial.h"
#include <ESP32Servo.h>

BluetoothSerial SerialBT;

// ---------------- OLED ----------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ---------------- Servos ----------------
Servo leftLeg;
Servo rightLeg;

#define LEFT_SERVO_PIN 25
#define RIGHT_SERVO_PIN 26

int neutralPos = 90;

// ---------------- Eye sizes ----------------
const int EYE_WIDTH = 18;
const int EYE_HEIGHT = 16;
const int EYE_RADIUS = 4;

// ---------------- Eye positions ----------------
const int BASE_LEFT_X = 40;
const int BASE_RIGHT_X = 90;
const int BASE_EYE_Y = 14;

// ---------------- States ----------------
bool sleeping = false;
bool happy = false;
bool smiling = false;
bool angry = false;
bool crying = false;
bool shooting = false;

unsigned long stateStart = 0;

// ------------------------------------------------
// 🚶 FORWARD (FINAL WORKING LOGIC)
void stepForward() {

  leftLeg.write(neutralPos);   // keep left locked

  // 🔥 QUICK KICK
  rightLeg.write(128);
  delay(120);

  // 🔥 PUSH
  rightLeg.write(115);
  delay(800);

  // RETURN
  rightLeg.write(neutralPos);
  delay(1000);
}

// ------------------------------------------------
// 👀 NORMAL EYES
void drawEyes(int offsetX, int offsetY, bool blinking) {
  display.clearDisplay();

  int leftX = BASE_LEFT_X + offsetX - EYE_WIDTH / 2;
  int rightX = BASE_RIGHT_X + offsetX - EYE_WIDTH / 2;
  int eyeY = BASE_EYE_Y + offsetY - EYE_HEIGHT / 2;

  if (!blinking) {
    display.fillRoundRect(leftX, eyeY, EYE_WIDTH, EYE_HEIGHT, EYE_RADIUS, SSD1306_WHITE);
    display.fillRoundRect(rightX, eyeY, EYE_WIDTH, EYE_HEIGHT, EYE_RADIUS, SSD1306_WHITE);
  } else {
    int y = BASE_EYE_Y + offsetY;
    display.drawFastHLine(leftX, y, EYE_WIDTH, SSD1306_WHITE);
    display.drawFastHLine(rightX, y, EYE_WIDTH, SSD1306_WHITE);
  }

  display.display();
}

// ------------------------------------------------
void drawClosedEyes() {
  display.clearDisplay();
  display.drawFastHLine(BASE_LEFT_X - 9, BASE_EYE_Y, 18, SSD1306_WHITE);
  display.drawFastHLine(BASE_RIGHT_X - 9, BASE_EYE_Y, 18, SSD1306_WHITE);
  display.display();
}

// ------------------------------------------------
void sleepBubble() {
  for (int r = 2; r <= 6; r++) {
    display.clearDisplay();
    drawClosedEyes();
    display.drawCircle(70, 4, r, SSD1306_WHITE);
    display.display();
    delay(140);
  }
}

// ------------------------------------------------
void drawHappyEyes(bool withSmile) {
  display.clearDisplay();

  display.drawLine(32, 14, 40, 18, SSD1306_WHITE);
  display.drawLine(40, 18, 48, 14, SSD1306_WHITE);

  display.drawLine(80, 14, 88, 18, SSD1306_WHITE);
  display.drawLine(88, 18, 96, 14, SSD1306_WHITE);

  if (withSmile) {
    display.drawLine(58, 24, 70, 24, SSD1306_WHITE);
    display.drawLine(56, 22, 58, 24, SSD1306_WHITE);
    display.drawLine(70, 24, 72, 22, SSD1306_WHITE);
  }

  display.display();
}

// ------------------------------------------------
void drawAngryEyes() {
  display.clearDisplay();

  display.drawLine(28, 6, 52, 10, SSD1306_WHITE);
  display.drawLine(100, 6, 76, 10, SSD1306_WHITE);

  display.drawFastHLine(32, 14, 18, SSD1306_WHITE);
  display.drawFastHLine(80, 14, 18, SSD1306_WHITE);

  display.display();
}

// ------------------------------------------------
void cryAnimation() {
  static int tearY = 18;

  display.clearDisplay();
  drawClosedEyes();

  display.drawLine(36, tearY, 36, tearY + 4, SSD1306_WHITE);
  display.drawLine(88, tearY, 88, tearY + 4, SSD1306_WHITE);

  display.display();

  tearY += 2;
  if (tearY > 28) tearY = 18;

  delay(120);
}

// ------------------------------------------------
void shootAnimation() {
  for (int x = 0; x < 110; x += 4) {
    display.clearDisplay();

    display.fillRect(x, BASE_EYE_Y - 1, 6, 3, SSD1306_WHITE);
    display.fillTriangle(x + 6, BASE_EYE_Y - 2, x + 10, BASE_EYE_Y, x + 6, BASE_EYE_Y + 2, SSD1306_WHITE);

    display.display();
    delay(80);
  }

  display.clearDisplay();
  display.drawRoundRect(30, 2, 22, 24, 3, SSD1306_WHITE);
  display.drawRoundRect(76, 2, 22, 24, 3, SSD1306_WHITE);
  display.display();

  delay(500);

  display.clearDisplay();
  for (int i = 0; i < 12; i++) {
    display.drawLine(random(128), random(32), random(128), random(32), SSD1306_WHITE);
  }

  display.display();
  delay(2000);
}

// ------------------------------------------------
// 🎮 COMMAND HANDLER
void handleCommand(String cmd) {

  if (cmd.startsWith("forward")) {
    int steps = cmd.substring(8).toInt();
    if (steps <= 0) steps = 1;

    for (int i = 0; i < steps; i++) {
      stepForward();
    }
  }

  else if (cmd == "sleep") sleeping = true;

  else if (cmd == "wake") {
    sleeping = happy = smiling = angry = crying = false;
  }

  else if (cmd == "shoot") shooting = true;

  else if (cmd == "cheese") {
    happy = true;
    stateStart = millis();
  }

  else if (cmd == "smile") {
    smiling = true;
    stateStart = millis();
  }

  else if (cmd == "cry") crying = true;

  else if (cmd == "you are ugly" || cmd == "you are stupid" || cmd == "you look bad") {
    angry = true;
    stateStart = millis();
  }
}

// ------------------------------------------------
void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_EYES");

  Wire.begin(21, 22);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.setRotation(2);  // 🔥 FIX UPSIDE-DOWN OLED

  leftLeg.attach(LEFT_SERVO_PIN);
  rightLeg.attach(RIGHT_SERVO_PIN);

  leftLeg.write(neutralPos);
  rightLeg.write(neutralPos);

  randomSeed(esp_random());
}

// ------------------------------------------------
void loop() {

  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim(); cmd.toLowerCase();
    handleCommand(cmd);
  }

  if (SerialBT.available()) {
    String cmd = SerialBT.readStringUntil('\n');
    cmd.trim(); cmd.toLowerCase();
    handleCommand(cmd);
  }

  // -------- STATES --------
  if (sleeping) {
    drawClosedEyes();
    sleepBubble();
    return;
  }

  if (shooting) {
    shootAnimation();
    shooting = false;
    return;
  }

  if (crying) {
    cryAnimation();
    return;
  }

  if (angry) {
    drawAngryEyes();
    if (millis() - stateStart > 4000) angry = false;
    return;
  }

  if (smiling) {
    drawHappyEyes(true);
    if (millis() - stateStart > 5000) smiling = false;
    return;
  }

  if (happy) {
    drawHappyEyes(false);
    if (millis() - stateStart > 5000) happy = false;
    return;
  }

  // -------- NORMAL --------
  int offsetX = random(-6, 7);
  int offsetY = random(-3, 4);

  drawEyes(offsetX, offsetY, false);
  delay(random(1200, 3000));

  drawEyes(offsetX, offsetY, true);
  delay(120);
}
