#include <SoftwareSerial.h>

//https://github.com/NicoHood/HID
#include "HID-Project.h"

#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINT(...) Serial.print(__VA_ARGS__)
#define DEBUG_PRINTLN(...) Serial.println(__VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#define DEBUG_PRINTLN(...)
#endif

SoftwareSerial keyboard_in(14, 15, true); // RX, TX

byte led_cmd[2] = { 0x0E, 0x00 };
#define NUMLOCK 1
#define COMPOSE 2
#define SCROLLOCK 4
#define CAPSLOCK 8

#define down 0
#define up 1

// data from sparc keyboard definition page 10ff and HID Usage Tables page 53ff
uint8_t data[] = {
  /*
   * 1st row
   */
  118,  down, KEY_HELP,
  246,  up,   KEY_HELP,
  //15,   down, KEY_BLANK,
  //143,  up,   KEY_BLANK,
  5,    down, KEY_F1, //
  133,  up,   KEY_F1, //
  6,    down, KEY_F2, //
  134,  up,   KEY_F2, //
  8,    down, KEY_F3, //
  136,  up,   KEY_F3, //
  10,   down, KEY_F4, //
  138,  up,   KEY_F4, //
  12,   down, KEY_F5,//
  140,  up,   KEY_F5,
  14,   down, KEY_F6,
  142,  up,   KEY_F6,
  16,   down, KEY_F7,
  144,  up,   KEY_F7,
  17,   down, KEY_F8,
  145,  up,   KEY_F8,
  18,   down, KEY_F9,
  146,  up,   KEY_F9,
  7,    down, KEY_F10,
  135,  up,   KEY_F10,
  9,    down, KEY_F11,
  137,  up,   KEY_F11,
  11,   down, KEY_F12,
  139,  up,   KEY_F12,
  22,   down, KEY_PRINTSCREEN,   // Print Screen
  150,  up,   KEY_PRINTSCREEN,  //
  23,   down, KEY_SCROLL_LOCK,   // Scroll Lock
  151,  up,   KEY_SCROLL_LOCK,
  21,   down, KEY_PAUSE,   // Pause
  149,  up,   KEY_PAUSE,
  45,   down, KEY_VOLUME_MUTE,  // MUTE
  173,  up,   KEY_VOLUME_MUTE,
  2,    down, KEY_VOLUME_DOWN,  // VOL DOWN
  130,  up,   KEY_VOLUME_DOWN,
  4,    down, KEY_VOLUME_UP,  // VOL UP
  132,  up,   KEY_VOLUME_UP,
  48,   down, KEY_POWER,
  176,  up,   KEY_POWER,

  /*
   * 2nd row
   */
  1,    down, KEY_STOP,   // Stop
  81,   up,   KEY_STOP,
  3,    down, KEY_AGAIN,  // Again
  83,   up,   KEY_AGAIN,
  29,   down, KEY_ESC,
  157,  up,   KEY_ESC,
  30,   down, KEY_1,
  158,  up,   KEY_1,
  31,   down, KEY_2,
  159,  up,   KEY_2,
  32,   down, KEY_3,
  160,  up,   KEY_3,
  33,   down, KEY_4,
  161,  up,   KEY_4,
  34,   down, KEY_5,
  162,  up,   KEY_5,
  35,   down, KEY_6,
  163,  up,   KEY_6,
  36,   down, KEY_7,
  164,  up,   KEY_7,
  37,   down, KEY_8,
  165,  up,   KEY_8,
  38,   down, KEY_9,
  166,  up,   KEY_9,
  39,   down, KEY_0,
  167,  up,   KEY_0,
  40,   down, KEY_MINUS,
  168,  up,   KEY_MINUS,
  41,   down, KEY_EQUAL,
  169,  up,   KEY_EQUAL,
  88,   down, KEY_BACKSLASH,
  216,  up,   KEY_BACKSLASH,
  42,   down, HID_KEYBOARD_GRAVE_ACCENT_AND_TILDE,
  170,  up,   HID_KEYBOARD_GRAVE_ACCENT_AND_TILDE,
  44,   down, KEY_INSERT,
  172,  up,   KEY_INSERT,
  52,   down, KEY_HOME,
  180,  up,   KEY_HOME,
  96,   down, KEY_PAGE_UP,
  224,  up,   KEY_PAGE_UP,
  98,   down, KEY_NUM_LOCK, //NUMLOC
  226,  up,   KEY_NUM_LOCK,
  0x2E, down, KEYPAD_DIVIDE,
  0xAE, up,   KEYPAD_DIVIDE,
  0x2F, down, KEYPAD_MULTIPLY,
  0xAF, up,   KEYPAD_MULTIPLY,
  0x47, down, KEYPAD_SUBTRACT,
  0xC7, up,   KEYPAD_SUBTRACT,

  /*
   * 3rd row
   */
  0x19, down, KEY_CRSEL_PROPS,
  0x99, up,   KEY_CRSEL_PROPS,
  0x1A, down, KEY_UNDO,
  0x9A, up,   KEY_UNDO,
  53,   down, KEY_TAB,
  181,  up,   KEY_TAB,
  54,   down, KEY_Q,
  182,  up,   KEY_Q,
  55,   down, KEY_W,
  183,  up,   KEY_W,
  56,   down, KEY_E,
  184,  up,   KEY_E,
  57,   down, KEY_R,
  185,  up,   KEY_R,
  58,   down, KEY_T,
  186,  up,   KEY_T,
  59,   down, KEY_Y,
  187,  up,   KEY_Y,
  60,   down, KEY_U,
  188,  up,   KEY_U,
  61,   down, KEY_I,
  189,  up,   KEY_I,
  62,   down, KEY_O,
  190,  up,   KEY_O,
  63,   down, KEY_P,
  191,  up,   KEY_P,
  64,   down, KEY_LEFT_BRACE,
  192,  up,   KEY_LEFT_BRACE,
  65,   down, KEY_RIGHT_BRACE,
  193,  up,   KEY_RIGHT_BRACE,
  43,   down, KEY_BACKSPACE,
  171,  up,   KEY_BACKSPACE,
  66,   down, KEY_DELETE,
  195,  up,   KEY_DELETE,
  74,   down, KEY_END,
  202,  up,   KEY_END,
  123,  down, KEY_PAGE_DOWN,
  251,  up,   KEY_PAGE_DOWN,
  0x44, down, KEYPAD_7,
  0xC4, up,   KEYPAD_7,
  0x45, down, KEYPAD_8,
  0xC5, up,   KEYPAD_8,
  0x46, down, KEYPAD_9,
  0xC6, up,   KEYPAD_9,
  0x7D, down, KEYPAD_ADD,
  0xFD, up,   KEYPAD_ADD,

  /*
   * 4th row
   */
  //0x31, down, //FRONT
  //0xB1, up,
  0x33, down, KEY_COPY,
  0xB3, up,   KEY_COPY,
  76,   down, KEY_LEFT_CTRL,
  204,  up,   KEY_LEFT_CTRL,
  77,   down, KEY_A,
  205,  up,   KEY_A,
  78,   down, KEY_S,
  206,  up,   KEY_S,
  79,   down, KEY_D,
  207,  up,   KEY_D,
  80,   down, KEY_F,
  208,  up,   KEY_F,
  81,   down, KEY_G,
  209,  up,   KEY_G,
  82,   down, KEY_H,
  210,  up,   KEY_H,
  83,   down, KEY_J,
  211,  up,   KEY_J,
  84,   down, KEY_K,
  212,  up,   KEY_K,
  85,   down, KEY_L,
  213,  up,   KEY_L,
  86,   down, KEY_SEMICOLON,
  214,  up,   KEY_SEMICOLON,
  87,   down, KEY_QUOTE,
  215,  up,   KEY_QUOTE,
  89,   down, KEY_RETURN,
  217,  up,   KEY_RETURN,
  0x5B, down, KEYPAD_4,
  0xDB, up,   KEYPAD_4,
  0x5C, down, KEYPAD_5,
  0xDC, up,   KEYPAD_5,
  0x5D, down, KEYPAD_6,
  0xDD, up,   KEYPAD_6,

  /*
   * 5th row
   */
  0x48, down, KEY_EXECUTE,
  0xC8, up,   KEY_EXECUTE,
  0x49, down, KEY_PASTE,
  0xC9, up,   KEY_PASTE,
  99,   down, KEY_LEFT_SHIFT,
  227,  up,   KEY_LEFT_SHIFT,
  100,  down, KEY_Z,
  228,  up,   KEY_Z,
  101,  down, KEY_X,
  229,  up,   KEY_X,
  102,  down, KEY_C,
  230,  up,   KEY_C,
  103,  down, KEY_V,
  231,  up,   KEY_V,
  104,  down, KEY_B,
  232,  up,   KEY_B,
  105,  down, KEY_N,
  233,  up,   KEY_N,
  106,  down, KEY_M,
  234,  up,   KEY_M,
  107,  down, KEY_COMMA,
  235,  up,   KEY_COMMA,
  108,  down, KEY_PERIOD,
  236,  up,   KEY_PERIOD,
  109,  down, KEY_SLASH,
  237,  up,   KEY_SLASH,
  110,  down, KEY_RIGHT_SHIFT,
  238,  up,   KEY_RIGHT_SHIFT,
  20,   down, KEY_UP_ARROW,
  148,  up,   KEY_UP_ARROW,
  0x70, down, KEYPAD_1,
  0xF0, up,   KEYPAD_1,
  0x71, down, KEYPAD_2,
  0xF1, up,   KEYPAD_2,
  0x72, down, KEYPAD_3,
  0xF2, up,   KEYPAD_3,
  0x5A, down, KEYPAD_ENTER,
  0xDA, up,   KEYPAD_ENTER, 

  /*
   * 6th row
   */
  0x5F, down, KEY_FIND,
  0xDF, up,   KEY_FIND,
  0x61, down, KEY_CUT,
  0xE1, up,   KEY_CUT,
  119,  down, KEY_CAPS_LOCK,
  247,  up,   KEY_CAPS_LOCK,
  19,   down, KEY_LEFT_ALT,
  147,  up,   KEY_LEFT_ALT,
  120,  down, KEY_LEFT_GUI,
  248,  up,   KEY_LEFT_GUI,
  121,  down, KEY_SPACE,
  249,  up,   KEY_SPACE,
  122,  down, KEY_RIGHT_GUI,
  250,  up,   KEY_RIGHT_GUI,
  0x43, down, KEY_APPLICATION,
  0xC3, up,   KEY_APPLICATION,
  13,   down,  KEY_RIGHT_ALT,
  141,  up,    KEY_RIGHT_ALT,
  24,   down,  KEY_LEFT_ARROW,
  152,  up,    KEY_LEFT_ARROW,
  27,   down,  KEY_DOWN_ARROW,
  155,  up,    KEY_DOWN_ARROW,
  28,   down,  KEY_RIGHT_ARROW,
  156,  up,    KEY_RIGHT_ARROW,
  0x5E, down,  KEYPAD_0, // KEY_NUMPAD_0
  0xDE, up,    KEYPAD_0,
  0x32, down,   KEYPAD_DOT,
  0xB2, up,     KEYPAD_DOT,
};

int data_len = sizeof(data) / 3;

void setup() {
  // open the serial port:
  Serial.begin(115200);
  keyboard_in.begin(1200);
  BootKeyboard.begin();

  // Test if all LEDs are working
  led_cmd[1] |= 0b00001111;
  keyboard_in.write(led_cmd, 2);
  delay(500);
  led_cmd[1] = 0;
  keyboard_in.write(led_cmd, 2);
}

uint8_t leds = 0;

void loop() {
  // check for incoming serial data:
  if (keyboard_in.available() > 0) {
    uint8_t inChar = keyboard_in.read();
    DEBUG_PRINT("Char: 0X");
    DEBUG_PRINTLN(inChar, HEX);

    int index;
    for (index = 0; index < data_len; index++) {
      if (inChar == data[index * 3]) {
        uint8_t val = data[index * 3 + 2];
        if (data[index * 3 + 1] == down) {
          DEBUG_PRINTLN("press");
          BootKeyboard.press((KeyboardKeycode)val);
        }
        if (data[index * 3 + 1] == up) {
          DEBUG_PRINTLN("release");
          BootKeyboard.release((KeyboardKeycode)val);
        }
      }
    }
      // Power Button
    if(inChar == 176) {
      BootKeyboard.wakeupHost();
    }
    if (inChar == 127) {
      BootKeyboard.releaseAll();
    }
  }

  if (leds != BootKeyboard.getLeds()) {
    leds = BootKeyboard.getLeds();
    DEBUG_PRINT("LEDs: 0b");
    DEBUG_PRINTLN(leds, BIN);

   if (leds & LED_NUM_LOCK) {
      led_cmd[1] |= NUMLOCK;
    } else {
      led_cmd[1] &= ~NUMLOCK;
    }
   if (leds & LED_CAPS_LOCK) {
      led_cmd[1] |= CAPSLOCK;
    } else {
      led_cmd[1] &= ~CAPSLOCK;
    }
    if (leds & LED_SCROLL_LOCK) {
      led_cmd[1] |= SCROLLOCK;
    } else {
      led_cmd[1] &= ~SCROLLOCK;
    }
    if (leds & LED_COMPOSE) {
      led_cmd[1] |= COMPOSE;
    } else {
      led_cmd[1] &= ~COMPOSE;
    }

    keyboard_in.write(led_cmd, 2);
  }
}
