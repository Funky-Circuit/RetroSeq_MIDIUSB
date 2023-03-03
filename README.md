# RetroSeq_MIDIUSB
MIDI USB sequencer with tracker inspired GUI based on an Arduino Micro

it uses the following libraries:
- https://github.com/adafruit/Adafruit_SSD1306
- https://github.com/adafruit/Adafruit-GFX-Library
- https://github.com/arduino-libraries/MIDIUSB

the sequencer consist in 4 button (going from digital 4 to 7 pins), a potetentiometer (on A0) and a SSD1306 (on the SPI pins, SDA on digital 2 and SCL on 3 digital 3)

it's a 8 step sequencer with 3 menu allowing you to change the note, octave and velocity of each step
it can reads the MIDI clock message in order to be synchronized with any DAW

the next update should add some fonctionnalities such as:
- 16 setp
- 16 pattern and a selection menu for them
- saving system
