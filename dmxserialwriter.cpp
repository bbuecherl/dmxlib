#include "dmxlib.h"

void DMXLib::DMXSerialWriter::start() {
  this->running_ = 1;
  this->serial_->begin(250000);
}

void DMXLib::DMXSerialWriter::stop() {
  this->running_ = 0;
}

void DMXLib::DMXSerialWriter::write() {
  if(!this->running_) return;
  // TODO
}
