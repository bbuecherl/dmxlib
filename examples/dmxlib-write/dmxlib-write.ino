#include "dmxlib.h"

#define PIN_DMX 11

DMXLib::DMXPWMWriter writer;
uint8_t x = 0;
int8_t y = 1;

void setup() {
  writer.setChannels(512);
  writer.use(PIN_DMX);
  writer.start();
}

void loop() {
  if(x > 254) {
    y = -1;
  } else if(x < 1) {
    y = 1;
  }
  x += y;
  writer.set(1, x);
  delay(4);
}

ISR_FUNCTION() {
  writer.write();
}
