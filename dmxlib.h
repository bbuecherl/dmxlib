#ifndef DMXLIB_H_
#define DMXLIB_H_

#include "Arduino.h"
#include <inttypes.h>
#include "isr.h"

namespace DMXLib {
  // base class for serial interactions
  class SerialInteractor {
  public:
    void start();
    void stop();
    void use(HardwareSerial *serial);
  protected:
    HardwareSerial *serial_;
    bool running_;
  };

  // base class for pwm interactions
  class PWMInteractor {
  public:
    void use(uint16_t pin);
    void start();
    void stop();
  protected:
    uint16_t pin_;
    bool running_;
  };

  // Base class for Readers
  class Reader {
  public:
    void setStart(uint16_t start);
    uint16_t getStart();
    void setLength(uint16_t length);
    uint16_t getLength();
    void setListener(void (*listener)(uint8_t *));
    bool isRunning();

  protected:
    uint16_t start_;
    uint16_t length_;
    void (*listener_)(uint8_t *);
  };

  // Base class for Writers
  class Writer {
  public:
    void setChannels(uint16_t channels);
    uint16_t getChannels();
    bool isRunning();
    void start();
    void stop();

    void set(uint16_t channel, uint8_t value);
  protected:
    uint8_t state_;
    uint16_t channels_;
    uint8_t *dmx_;
  };

  // serial reader
  class DMXSerialReader: public Reader, public SerialInteractor {
  public:
    void read();
    void start();
    void stop();
  private:
    uint8_t state_;
    uint8_t *dmx_;
  };

  // pwm reader
  class DMXPWMReader: public Reader, public PWMInteractor {
  public:
    void read();
    void start();
    void stop();
  };

  // serial writer
  class DMXSerialWriter: public Writer, public SerialInteractor {
    void start();
    void stop();
    void write();
  };

  // pwm writer
  class DMXPWMWriter: public Writer, public PWMInteractor {
  public:
    void write();
    void start();
    void stop();
  private:
    void send_byte(volatile uint8_t val);
    volatile uint8_t *port_;
    uint8_t bit_;
    uint8_t state_;
  };
}

#endif // DMXLIB_H_
