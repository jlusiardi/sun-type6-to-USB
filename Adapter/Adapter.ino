#include <SoftwareSerial.h>

//https://github.com/NicoHood/HID
#include "HID-Project.h"

SoftwareSerial keyboard_in(14, 15, true); // RX, TX


#define down 0
#define up 1

// data from sparc keyboard definition page 10ff and HID Usage Tables page 53ff
uint8_t data[] = {
  /*
   * 1st row
   */
   //118,  down, KEY_HELP,
  //246,  up,   KEY_HELP,
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
  // HELP
  // Again
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
  41,   down, KEYPAD_EQUAL_SIGN,
  169,  up,   KEYPAD_EQUAL_SIGN,
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

  /*
   * 3rd row
   */
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

  /*
   * 4th row
   */
  76,   down,  KEY_LEFT_CTRL,
  204,  up,    KEY_LEFT_CTRL,
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

  /*
   * 5th row
   */
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
  20,   down,  KEY_UP_ARROW,
  148,  up,    KEY_UP_ARROW,

  /*
   * 6th row
   */
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
  //67,   down, KEY_COMPOSE,
  //195,  up,   KEY_COMPOSE,
  13,   down,  KEY_RIGHT_ALT,
  141,  up,    KEY_RIGHT_ALT,
  24,   down,  KEY_LEFT_ARROW,
  152,  up,    KEY_LEFT_ARROW,
  27,   down,  KEY_DOWN_ARROW,
  155,  up,    KEY_DOWN_ARROW,
  28,   down,  KEY_RIGHT_ARROW,
  156,  up,    KEY_RIGHT_ARROW,
  94,   down,  98, // KEY_NUMPAD_0
  222,  up,    98,
};

int data_len = sizeof(data) / 3;

void setup() {
  // open the serial port:
  Serial.begin(1200);
  keyboard_in.begin(1200);
  Keyboard.begin();
}

void loop() {
  // check for incoming serial data:
  if (keyboard_in.available() > 0) {
    uint8_t inChar = keyboard_in.read();

      int index;
      for (index = 0; index < data_len; index++) {
        if (inChar == data[index * 3]) {
          uint8_t val = data[index * 3 + 2];
          Serial.print("val: ");
          Serial.println(val, HEX);
          if (data[index * 3 + 1] == down) {
            Serial.println("press");
            Keyboard.press((KeyboardKeycode)val);
          }
          if (data[index * 3 + 1] == up) {
            Serial.println("release");
            Keyboard.release((KeyboardKeycode)val);
          }
        }
      }
      if (inChar == 127) {
        Keyboard.releaseAll();
      }

    if (inChar == 0x40)
      Serial.println();
    else
      Serial.println(inChar);
  }
}

