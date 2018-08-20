/*
 * pcf8574.h
 *
 *  Created on: Apr 28, 2017
 *      Author: sanchayan
 */

#ifndef PCF8574_H_
#define PCF8574_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <libsoc_i2c.h>

/* PCF8574 I2C Address on Pioneer 600 */
#define PCF8574_ADDRESS		0x20

i2c* pcf8574_init(uint8_t i2c_bus, uint8_t i2c_address);
int pcf8574_free(i2c *i2c);
uint8_t pcf8574_port_read(i2c *i2c);
size_t pcf8574_port_read_buf(i2c *i2c, void *buf, size_t len);
void pcf8574_port_write(i2c *i2c, uint8_t value);
size_t pcf8574_port_write_buf(i2c *i2c, void *buf, size_t len);
bool pcf8574_gpio_read(i2c *i2c, uint8_t num);
void pcf8574_gpio_write(i2c *i2c, uint8_t num, bool value);

#endif /* PCF8574_H_ */
