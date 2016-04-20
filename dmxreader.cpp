#include "dmxlib.h"

void DMXLib::Reader::setStart(uint16_t start) {
  this->start_ = start;
}

uint16_t DMXLib::Reader::getStart() {
  return this->start_;
}

void DMXLib::Reader::setLength(uint16_t length) {
  this->length_ = length;
}

uint16_t DMXLib::Reader::getLength() {
  return this->length_;
}

void DMXLib::Reader::setListener(void (*listener)(uint8_t *)) {
  this->listener_ = listener;
}
