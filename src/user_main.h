#ifndef __USER_MAIN_H__
#define __USER_MAIN_H__

#include <kos.h>
#include "hp39kbd.h"
#include "key_event.h"
#include "ds18b20.h"
#include "displayer.h"

extern void _clear_screen();

int event_handler(unsigned col, unsigned row);

int user_init(void);

#endif
