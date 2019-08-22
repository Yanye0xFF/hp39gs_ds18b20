#ifndef __DISPLAYER_H__
#define __DISPLAYER_H__

#include "font.h"
#include <kos.h>
#include <stdint.h>

#define DISP_LINE 21
#define MENU_LINE 53
#define BUFFER_SIZE 8

#define CELSIUS 0
#define FAHRENHEIT 1

void display_temp(int16_t temp, uint8_t type);
void display_menu(uint8_t disp_type);

#endif
