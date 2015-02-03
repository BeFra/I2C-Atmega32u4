/*
 * Title: A I2C library using the hardware TWI interface of a Atmega32u4
 * Created: 03.11.2014 13:20:06
 * Author: Benjamin Frank
 */ 
#include <util/twi.h>
#include "header/config_defines.h"
#include "header/i2c.h"
/*
 * Initialization of the I2C bus
 */
void init_i2c() {
	PORTD &= ~(1 << 0);
	PORTD &= ~(1 << 1);
	// TODO Port für SCL und SDA
	TWBR = ((( F_CPU / SCL_CLOCK ) - 16) / 2); 
	TWSR = 0; 
	TWCR = ( 1 << TWEN ); // enable the i2c bus 
}


/*
 * Sends the start condition
 * adr: address of the hardware
 * w: read or write flag
 */
void connect_i2c(uint8_t adr, uint8_t w) {

	start_i2c();
	send_address_i2c(adr,w);

}
/*
 * Sends the start condition
 */
void start_i2c() {

	// send START condition
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	
	// wait until transmission completed
	while ( !(TWCR & (1<<TWINT)))	;
	
	if ((TWSR & 0xF8) != TW_START){
		#ifdef DEBUG
		print("\n   |Error: Start -> ");
		phex(TWSR & 0xF8);
		#endif
	}
}
/*
 * 
 * adr: address of the hardware
 * w: read or write flag
 */
void send_address_i2c(uint8_t adr, uint8_t w) {
	
	TWDR = (adr<<1) | w ;
	TWCR = (1 << TWINT) | (1<<TWEN);
	
	while(!(TWCR & (1 << TWINT)));
	
	if ((TWSR & 0xF8) != TW_MT_SLA_ACK){
		#ifdef DEBUG
		print("\n   |Error: ADRESS -> ");
		phex(TWSR & 0xF8);
		#endif
	}
}

/*
 * sends the stop condition
 */
void stop_i2c() {
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
	while(TWCR & (1 << TWSTO));
}
/*
 * sends one byte to the I2C hardware
 * data: byte to send
 */
void send_i2c(uint8_t data) {

	// send data to the previously addressed device
	TWDR = data;
	TWCR = (1 << TWINT) | (1<<TWEN);
	
	// wait until transmission completed
	while(!(TWCR & (1 << TWINT)));
	
	if ((TW_STATUS & 0xF8) != TW_MT_DATA_ACK){
		
		#ifdef DEBUG
		print("\n   |Error: Data -> ");
		phex(TWSR & 0xF8);
		phex(TW_MT_DATA_ACK);
		#endif
	}

}
/*
 * recive one byte of the I2C hardware
 */
uint8_t receive_i2c() {
	TWCR = (1 << TWINT) | (1 << TWEN);// | (1<<TWEA);
	while(!(TWCR & (1 << TWINT)));
	return TWDR;
}