#include "dmxlib.h"

#define PIN_DMX 11
#define PIN_RED 2
#define PIN_YELLOW 3
#define PIN_GREEN 4

DMXLib::DMXPWMWriter writer;
uint8_t x = 0;
int8_t y = 1;
uint8_t value = 0;
uint16_t channel = 0;

void setup() {
  Serial.begin(115200);
  writer.setChannels(512);
  writer.use(PIN_DMX);
  writer.start();

  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_YELLOW, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);

  digitalWrite(PIN_GREEN, HIGH);
}

void loop() {
  if(Serial.available() > 0) {
    digitalWrite(PIN_YELLOW, HIGH);
    uint16_t c = Serial.read();

    if ((c >= '0') && (c <= '9')) {
      value = 10*value + c - '0';
    } else {
      if (c == 'c') channel = value;
      else if (c == 'w') {
        writer.set(channel, value);
      }
      value = 0;
    }
  } else {
    digitalWrite(PIN_YELLOW, LOW);
  }
}

bool toggle = 0;

ISR_FUNCTION() {
  digitalWrite(PIN_RED, toggle ? HIGH : LOW);
  toggle = toggle ? 0 : 1;
  writer.write();
}
