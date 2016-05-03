#include "dmxlib.h"

void DMXLib::DMXPWMReader::start() {
  this->running_ = 1;
}

void DMXLib::DMXPWMReader::read() {
  this->running_ = 0;
}

void DMXLib::DMXPWMReader::stop() {
  if(!this->running_) return;
  // TODO
}
