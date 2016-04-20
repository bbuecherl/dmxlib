#include "dmxlib.h"

void DMXLib::PWMInteractor::use(uint16_t pin) {
  this->pin_ = pin;
  if(this->running_) {
    //stop();
    //start();
  }
}
