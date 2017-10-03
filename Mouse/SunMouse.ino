
#include "Mouse.h"
#include <SoftwareSerial.h>

SoftwareSerial keyboard_in(8, 9, true); // RX, TX


#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINT(...) Serial.print(__VA_ARGS__)
#define DEBUG_PRINTLN(...) Serial.println(__VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#define DEBUG_PRINTLN(...)
#endif

void setup() {
    keyboard_in.begin(1200);
    Serial.begin(115200);
}

int8_t data[] = {0, 0, 0, 0, 0};
uint8_t index = 0;

#define RIGHTBUTTON  0b00000001
#define MIDDLEBUTTON 0b00000010
#define LEFTBUTTON   0b00000100

void handleButton(char inButton, char outButton) {
  if ((data[0] & inButton) == 0) {
    if (!Mouse.isPressed(outButton)) {
      Mouse.press(outButton);
    }
  } else {
    if (Mouse.isPressed(outButton)) {
      Mouse.release(outButton);
    }
  }
}

void loop() {

  while (keyboard_in.available() > 0) {
    uint8_t inChar = keyboard_in.read();
    data[index] = inChar;
    index++;
  }
  if(index == 5) {
    // handling of button
    handleButton(LEFTBUTTON, MOUSE_LEFT);
    handleButton(MIDDLEBUTTON, MOUSE_MIDDLE);
    handleButton(RIGHTBUTTON, MOUSE_RIGHT);

    int dx = (data[1]+ data[3]);
    int dy = -(data[2]+data[4]);
    Mouse.move(dx, dy, 0);

    index = 0;
  }
}
