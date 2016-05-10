#include "dmxlib.h"

enum {IDLE, BREAK, START_BIT, LISTEN};

void DMXLib::DMXPWMReader::start() {
  pinMode(this->pin_, INPUT);
  digitalWrite(this->pin_, HIGH);
  this->state_ = IDLE;
  this->idlestart_ = micros();
  this->running_ = 1;
}

void DMXLib::DMXPWMReader::read() { // inside ISR(PCINTx_vect)
  if(!this->running_) return;
  static uint16_t count;
  uint8_t state = this->state_;
  uint8_t val = analogRead(this->pin_);

  if(state == IDLE && this->idlestart_ + 88 < micros()) {
    this->state_ = BREAK;
    count = this->start_;
  } else if(state == BREAK) {
    if(val == 0) {
      this->state_ = START_BIT;
    } else {
      this->state_ = IDLE;
      this->idlestart_ = micros();
    }
  } else if(state == START_BIT) {
    if(--count == 0) {
      this->state_ = LISTEN;
    }
  } else if(state == LISTEN) {
    this->dmx_[count++] = val;
    if(count >= this->length_) {
      this->state_ = IDLE;
      this->idlestart_ = micros();
      this->listener_(this->dmx_);
    }
  }
}

void DMXLib::DMXPWMReader::stop() {
  this->running_ = 0;
}
