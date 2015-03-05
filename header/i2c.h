/*
 * i2c.h
 *
 * Created: 03.11.2014 16:33:04
 * Author: Benjamin Frank
 */ 

#ifndef I2C_H_
#define I2C_H_

#include <util/twi.h>
#define I2C_READ 1
#define I2C_WRITE 0

void init_i2c();
void send_i2c(uint8_t);
int8_t read_i2c();
int8_t readAck_i2c();
void send_address_i2c(uint8_t adr, uint8_t w);
void start_i2c();
void connect_i2c(uint8_t,uint8_t);
void stop_i2c();

#endif /* I2C_H_ */