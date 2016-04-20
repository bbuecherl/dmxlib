# DMXLib for Arduino
-----

## Usage
See `examples/` for simple read and write applications.

### DMXLib::DMXPWMWriter
```c++
// always include the header
#include "dmxlib.h"

// create an instance, the constructor does not take any parameters
DMXLib::DMXPWMWriter writer;

// set channels to write, for this example we use 512 for DMX-512
writer.setChannels(512);

// get channels
uint16_t channels = writer.getChannels();

// set an output pin (has to be a digital PWM pin)
writer.use(11);

// check if the writer has started
bool running = writer.isRunning();

// start writer loop
writer.start();

// stop writer loop
writer.stop();

// set a channel to a value
// channels are 0 to channels-1
// values are 0 to 255
writer.set(1, 255);

// setup the writer loop
ISR_FUNCTION() {
  // writes the current dmx values to the output
  writer.write();
}
```
See `examples/dmxlib-write/dmxlib-write.ino` for a working example
### DMXLib::DMXPWMReader
coming soon

### DMXLib::DMXSerialWriter
coming soon

### DMXLib::DMXSerialReader
```c++
// always include the header
#include "dmxlib.h"

// create an instance, the constructor does not take any parameters
DMXLib::DMXSerialReader reader;

// set the dmx channel we listen for
reader.setStart(0);

// get the dmx channel we listen for
uint16_t start = reader.getStart();

// set the number of dmx channels to listen for
reader.setLength(8);

// get the number of dmx channels to listen for
uint16_t length = reader.getLength();

// set a listener function to be executed everytime the dmx channels are read
reader.setListener(dmxListener);
// the listener function
void dmxListener(uint8_t * values) {
  // do something with the values array containing all dmx channels from `start`
  // to `start+length`
}

// check is reader is currently listening
bool running = reader.isRunning();

// start reading
reader.start();

// stop reading
reader.stop();

// select the serial port to read from, requires a HardwareSerial pointer
reader.use(&Serial);

// read from serial port
// use it inside `ISR(USART0_RX_vect)`, `void loop()` or `void serialEvent()`
reader.read();
```
See `examples/dmxlib-read/dmxlib-read.ino` for a working example
