#ifndef __DS18B20_H__
#define __DS18B20_H__

#include "gpio.h"
#include "hp39kbd.h"

#define uint8 unsigned char

void os_delay_us(unsigned int us);

uint8 ds18b20_init();

void ds18b20_write_byte(uint8 data);
uint8 ds18b20_read_byte();

void ds18b20_convert_temp();
void ds18b20_read_temp_cmd();

short ds18b20_read_temp();
unsigned int ds18b20_read_rom_id();
#endif
