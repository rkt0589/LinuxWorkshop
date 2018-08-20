/*
 * pcf8574.c
 * PCF8574 IO expander helper functions using libsoc API.
 *
 * libsoc i2c API Documentation: http://jackmitch.github.io/libsoc/c/i2c/#i2c
 *
 * Copyright (C) 2017 - BhuvanChandra DV <bhuvanchandradv@gmail.com>
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "pcf8574.h"

i2c* pcf8574_init(uint8_t i2c_bus, uint8_t i2c_address)
{
	i2c *i2c = libsoc_i2c_init(i2c_bus, i2c_address);

	if (i2c == NULL) {
		perror("libsoc_i2c_init failed");
		return i2c;
	}

	return i2c;
}

int pcf8574_free(i2c *i2c)
{
	return libsoc_i2c_free(i2c);
}

uint8_t pcf8574_port_read(i2c *i2c)
{
	uint8_t res;

	if (libsoc_i2c_read(i2c, &res, 1))
		return 0;

	return res;
}

size_t pcf8574_port_read_buf(i2c *i2c, void *buf, size_t len)
{
	uint8_t *_buf = (uint8_t *)buf;

	if (!len || !buf)
		return 0;

	if (libsoc_i2c_read(i2c, _buf, len))
		return 0;

	return len;
}

size_t pcf8574_port_write_buf(i2c *i2c, void *buf, size_t len)
{
	uint8_t *_buf = (uint8_t *)buf;

	if (!len || !buf)
		return 0;

	if (libsoc_i2c_write(i2c, _buf, len))
		return 0;

	return len;
}

void pcf8574_port_write(i2c *i2c, uint8_t value)
{
	libsoc_i2c_write(i2c, &value, 1);
}

bool pcf8574_gpio_read(i2c *i2c, uint8_t num)
{
	return (bool)((pcf8574_port_read(i2c) >> num) & 1);
}

void pcf8574_gpio_write(i2c *i2c, uint8_t num, bool value)
{
    uint8_t bit = (uint8_t)!value << num;
    uint8_t mask = ~(1 << num);

    pcf8574_port_write (i2c, (pcf8574_port_read(i2c) & mask) | bit);
}
