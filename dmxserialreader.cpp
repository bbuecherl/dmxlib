#include "dmxlib.h"
#include "Arduino.h"
#include <avr/interrupt.h>
#include <avr/io.h>

enum {IDLE, BREAK, START_BIT, LISTEN};

void DMXLib::DMXSerialReader::start() {
  this->state_ = IDLE;
  this->serial_->begin(250000);
  this->running_ = 1;
}

void DMXLib::DMXSerialReader::read() { // inside ISR(USART_RX_vect)
  if(!this->running_) return;
  static uint16_t count;
  uint8_t USART_state = UCSR0A;
  uint8_t dmx_byte = UDR0;
  uint8_t state = this->state_;

  if(USART_state & (1 << FE0)) {
    count = this->start_;
    this->state_ = BREAK;
  } else if(state == BREAK) {
    if(dmx_byte == 0) {
      this->state_ = START_BIT;
    } else {
      this->state_ = IDLE;
    }
  } else if(state == START_BIT) {
    if(--count == 0) {
      this->state_ = LISTEN;
    }
  } else if(state == LISTEN) {
    this->dmx_[count++] = dmx_byte;
    if(count >= this->length_) {
      this->state_ = IDLE;
      this->listener_(this->dmx_);
    }
  }
}

void DMXLib::DMXSerialReader::stop() {
  this->running_ = 0;
}
