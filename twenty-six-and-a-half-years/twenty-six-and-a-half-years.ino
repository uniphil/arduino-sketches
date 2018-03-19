#include "MicroView.h"

#define BUTTON 1
#define TYPING_DELAY 100
#define TYPING_VARIANCE TYPING_DELAY / 2
#define LINE_PAUSE 500
#define BLINK_PERIOD 500
#define RESULT_BLINK_PERIOD 160
#define RESULT_BLINKS 2

const uint8_t W = uView.getLCDWidth();
const uint8_t H = uView.getLCDHeight();

void setup() {
  uView.begin();
  uView.clear(PAGE);
  uView.display();

  pinMode(BUTTON, INPUT);
}

void loop() {
  compute();
  decay();
}

void type(String msg) {
  for (int i = 0; i < msg.length(); i++) {
    delay(random(TYPING_DELAY - TYPING_VARIANCE, TYPING_DELAY + TYPING_VARIANCE));
    uView.print(msg[i]);
    uView.display();
  }
}

void enter() {
  uView.print("\n");
  delay(LINE_PAUSE);
}

void blinkCursor(uint8_t times) {
  for (int i = 0; i < times; i++) {
    uView.writeNoAdvance('_');
    uView.display();
    delay(BLINK_PERIOD / 2);
    uView.writeNoAdvance(' ');
    uView.display();
    delay(BLINK_PERIOD / 2);
  }
}

void compute() {
  uView.clear(PAGE);
  uView.display();
  uView.setCursor(0, 0);
  delay(200);

  type("Am I gay?\n");
  enter();

  type("Attracted to women ");
  blinkCursor(random(2, 6));
  uView.writeNoAdvance('Y', BLACK, NORM);
  uView.print('\n');
  uView.display();
  enter();
  delay(500);

  type("> ");
  delay(200);
  for (int i = 0; i < RESULT_BLINKS; i++) {
    uView.setCursor((uView.getFontWidth() + 1) * 2, uView.getFontHeight() * 5);
    uView.print("        ");
    uView.display();
    delay(RESULT_BLINK_PERIOD / 2);

    uView.setCursor((uView.getFontWidth() + 1) * 2, uView.getFontHeight() * 5);
    uView.setColor(BLACK);
    uView.print("straight");
    uView.setColor(WHITE);
    uView.display();
    delay(RESULT_BLINK_PERIOD / 2);
  }

  delay(1600);
}

void decay() {
  int lines = 600;
  int maxDelay = 16;
  for (int i = 0; i < lines; i++) {
    if (random(0, 2)) {
      uView.line(0, random(H), W, random(H), BLACK, NORM);
    } else {
      uView.line(random(W), 0, random(W), H, BLACK, NORM);
    }
    uView.display();
    delay(maxDelay * (lines - i) / lines);
  }
  uView.clear(PAGE);
  uView.display();
}

