#include "dmxlib.h"

#define PIN_DMX 11

DMXLib::DMXPWMWriter writer;
uint8_t x = 0;
int8_t y = 1;

void setup() {
  Serial.begin(115200);
  writer.setChannels(512);
  writer.use(PIN_DMX);
  writer.start();
  writer.set(5, 36);
  writer.set(6, 5);
  writer.set(7, 100);
  writer.set(12, 1);
}

void loop() {
  if(x > 254) {
    y = -1;
  } else if(x < 1) {
    y = 1;
  }
  x += y;
  writer.set(0, x);
  writer.set(1, x);
  writer.set(5, x);

  delay(4);
}

ISR_FUNCTION() {
  writer.write();
}
