#include "dmxlib.h"

void DMXLib::DMXSerialWriter::start() {
  this->running_ = 1;
  this->serial_->begin(250000);
  this->state_ = 0;
}

void DMXLib::DMXSerialWriter::stop() {
  this->running_ = 0;
}

void DMXLib::DMXSerialWriter::write() { // inside ISR(USART_RX_vect)
  if(!this->running_) return;

  while(1) {
    if(this->state_ == 0) { // RESET
      this->serial_->begin(10800);
      this->serial_->write((uint8_t)0);
    } else {
      // BREAK
      this->serial_->begin(125000);
      this->serial_->write((uint8_t)1);
      this->serial_->begin(250000);
      // START
      this->serial_->write((uint8_t) 0);
      // CHANNEL
      this->serial_->write(this->dmx_[this->state_ - 1]);
    }

    this->state_++;
    if(this->state_ > this->channels_) {
      this->state_ = 0;
      break;
    }
  }
}
