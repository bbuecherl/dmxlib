#include "dmxlib.h"

void DMXLib::Writer::setChannels(uint16_t channels) {
  if(this->dmx_) {
    free(this->dmx_);
  }
  this->channels_ = channels;
  this->dmx_ = (uint8_t *) malloc(channels * sizeof(uint8_t));
  for(uint16_t i = 0; i < this->channels_; ++i) {
    this->dmx_[i] = 0;
  }
  this->state_ = 0;
}

uint16_t DMXLib::Writer::getChannels() {
  return this->channels_;
}

void DMXLib::Writer::set(uint16_t channel, uint8_t value) {
  this->dmx_[channel] = value;
}
