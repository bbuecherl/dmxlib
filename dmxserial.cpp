#include "dmxlib.h"

void DMXLib::SerialInteractor::use(HardwareSerial *serial) {
  this->serial_ = serial;
  if(this->running_) {
    //stop();
    //start();
  }
}
