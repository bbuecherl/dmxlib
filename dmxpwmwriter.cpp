#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "pins_arduino.h"
#include "dmxlib.h"

void DMXLib::DMXPWMWriter::start() {
  this->running_ = 1;
  this->port_ = portOutputRegister(digitalPinToPort(this->pin_));
  this->bit_ = digitalPinToBitMask(this->pin_);
  this->state_ = 0;

  pinMode(this->pin_, OUTPUT);

  ISR_ENABLE();
}

void DMXLib::DMXPWMWriter::stop() {
  this->running_ = 0;
  ISR_DISABLE();
}

void DMXLib::DMXPWMWriter::send_byte(volatile uint8_t val) {
  uint8_t bit_count, del_count, that_bit;
  volatile uint8_t *that_port = this->port_;
  that_bit = this->bit_;
  __asm__ volatile(
    "cli\n"
    "ld __tmp_reg__,%a[dmxPort]\n"
    "and __tmp_reg__,%[outMask]\n"
    "st %a[dmxPort],__tmp_reg__\n"
    "ldi %[bitCount],11\n" // 11 bit intervals per transmitted byte
    "rjmp bitLoop%=\n" // Delay 2 clock cycles.
  "bitLoop%=:\n"\
    "ldi %[delCount],%[delCountVal]\n"
  "delLoop%=:\n"
    "nop\n"
    "dec %[delCount]\n"
    "brne delLoop%=\n"
    "ld __tmp_reg__,%a[dmxPort]\n"
    "and __tmp_reg__,%[outMask]\n"
    "sec\n"
    "ror %[value]\n"
    "brcc sendzero%=\n"
    "or __tmp_reg__,%[outBit]\n"
  "sendzero%=:\n"
    "st %a[dmxPort],__tmp_reg__\n"
    "dec %[bitCount]\n"
    "brne bitLoop%=\n"
    "sei\n"
    :
      [bitCount] "=&d" (bit_count),
      [delCount] "=&d" (del_count)
    :
      [dmxPort] "e" (that_port),
      [outMask] "r" (~that_bit),
      [outBit] "r" (that_bit),
      [delCountVal] "M" (F_CPU/1000000-3),
      [value] "r" (val)
  );
}

void DMXLib::DMXPWMWriter::write() { // inside ISR_FUNCTION()
  ISR_DISABLE();
  uint16_t bits_left = F_CPU / 31372; // DMX Bit periods per timer tick
  bits_left >>=2; // 25% CPU usage
  while (1) {
    if (this->state_ == 0) {
      // Next thing to send is reset pulse and start code
      // which takes 35 bit periods
      uint8_t i;
      if (bits_left < 35) break;
      bits_left-=35;
      *this->port_ &= ~this->bit_;
      for (i=0; i<11; i++) _delay_us(8);
      *this->port_ |= this->bit_;
      _delay_us(8);
      send_byte(0);
    } else {
      // Now send a channel which takes 11 bit periods
      if (bits_left < 11) break;
      bits_left-=11;
      send_byte(this->dmx_[this->state_-1]);
    }
    // Successfully completed that stage - move state machine forward
    this->state_++;
    if (this->state_ > this->channels_) {
      this->state_ = 0; // Send next frame
      break;
    }
  }
  ISR_ENABLE();
}
