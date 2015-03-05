# I2C-Atmega32u4

This is a i2c library for an atmega32u4. 

Port D0 -> SCL
Port D1 -> SDA

void init_i2c();
This method initialize the i2c bus.

void connect_i2c(uint8_t adr, uint8_t w)
This method call "void start_i2c()" to send the start condition and "void send_address_i2c(uint8_t adr, uint8_t w)"
to send the address ("adr") of the hardware and a bit ("w") for read or write access.

The "void stop_i2c()" method send the stop condtion.

"void send_i2c(uint8_t data)" Send one byte to the I2C hardware.

"int8_t read_i2c()" recive one byte followed by a stop condition.

"int8_t readAck_i2c()" receive on byte and request for more data.
