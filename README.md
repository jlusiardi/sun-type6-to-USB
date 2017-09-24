# sun-type6-to-USB
This project is about building an adapter to bring a SUN Type 6 keyboard to modern computer via USB by using an arduiono micro.

## schematic

The protocol of the SUN Type 6 keyboards in based on 1200 baud serial with inverted logic. So connect:
 * the keyboards GND (right most pin of the internal connector) to some GND pin of the Arduino
 * the keyboards VCC (2nd pin from the right) to VCC on the Arduino (5V is fine)
 * the "to keyboard" line (4th from the right) goes to the TX pin of a SoftwareSerial (in the sketch it uses pin 15)
 * the "from keyboard" line (5th from the right) goes to the RX pin of a SoftwareSerial (in the sketch it uses pin 15)
 
## code 

The communication with the keyboard is performed over a SoftwareSerial because this supports the inverted logic of the keyboard (see https://www.arduino.cc/en/Reference/SoftwareSerial for more details). 

The keyboard's protocol is described in the "SPARC Keyboard Specification" (see https://sparc.org/wp-content/uploads/2014/01/KBD.pdf.gz).

To control the USB communication (and the function as proper HID) I chose Nico Hood's HID project (see https://github.com/NicoHood/HID, commit 3c5000c4b606b85054150a201f0c6229a9148068) over Arduino's Keyboard functionality (https://www.arduino.cc/en/Reference/MouseKeyboard).

