#include "dmxlib.h"

void DMXLib::SerialInteractor::use(HardwareSerial *serial) {
  this->serial_ = serial;
  if(this->running_) {
    this->serial_->begin(250000);
  }
}
