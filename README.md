# LuLidar 

LuLidar is a sensor fusion testing platform for Lidar-like 3D sensing applications.

## Note

Pin connection need to connect DO (data), CLK (clock), CS (chip select) and Prg(program input) pins to the Arduino board.
Use AS5145(uint16_t DataPin, uint16_t ClockPin, uint16_t ChipSelectPin, uint16_t ProgramInputPin); to initialize.
And simply use the encoder_degrees() function to get the absolute degree from AS5145.

  e.g. int value = myAS5145.encoder_degrees();

For debugging, you can use the encoder_value() function to get the raw value.





## Dependency

1. AS5145_Arduino by https://github.com/howardmumu/AS5145_Arduino