#include "dmxlib.h"

#define PIN_OUT 10

DMXLib::DMXSerialReader reader;

void setup() {
  pinMode(PIN_OUT, OUTPUT);

  reader.setStart(0);
  reader.setLength(1);
  reader.setListener(dmxListener);
  reader.use(&Serial);
  reader.start();
}

void loop() {
  reader.read();
}

void dmxListener(uint8_t *dmx) {
 analogWrite(PIN_OUT, dmx[0]);
}
