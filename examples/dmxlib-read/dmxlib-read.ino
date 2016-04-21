#include "dmxlib.h"

#define PIN_OUT 13

DMXLib::DMXSerialReader reader;

void setup() {
  pinMode(PIN_OUT, OUTPUT);
  pinMode(12, OUTPUT);
  initSerial();

  reader.setStart(1);
  reader.setLength(1);
  reader.setListener(dmxListener);
  //reader.use(&Serial);
  reader.start();
}

void loop() {
  delayMicroseconds(1);
}

bool toggle = 0;

ISR(USART_RX_vect) {
  reader.read();
  digitalWrite(12, toggle ? HIGH : LOW);
  toggle = toggle ? 0 : 1;
}

void dmxListener(uint8_t *dmx) {
 analogWrite(PIN_OUT, dmx[0]);
}

void initSerial() {
  uint16_t baud_setting =  ( ( (((F_CPU)/8)/(250000)) - 1 ) / 2 );
  // assign the baud_setting to the USART Baud Rate Register
  UCSR0A = 0;
  UBRR0H = baud_setting >> 8;
  UBRR0L = baud_setting;

  UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}
