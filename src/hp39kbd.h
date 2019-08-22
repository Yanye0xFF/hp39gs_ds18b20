#ifndef __HP39KBD_H__
#define __HP39KBD_H__

#include "user_main.h"
#include "key_event.h"
#include <hpsys.h>

// remapped addresses of registers
#define GPFDAT ((unsigned *)0x07A00054)
#define GPGCON ((unsigned *)0x07A00060)
#define GPGDAT ((unsigned *)0x07A00064)

// delay depends on cpu clock
// now cpu freq is 75Mhz
// 2.2us/tick
#define delay(t) { volatile unsigned int i = (t); while (i--); }

#define modifier_key_pressed(bit) ((*GPFDAT >> (bit)) & 1)
#define on_pressed    modifier_key_pressed(0)
#define comma_pressed modifier_key_pressed(4)
#define alpha_pressed modifier_key_pressed(5)
#define shift_pressed modifier_key_pressed(6)

#define any_normal_key_pressed ((*GPGDAT & 0xFE) != 0xFE)
#define any_key_pressed ( \
	any_normal_key_pressed || on_pressed || \
	comma_pressed || alpha_pressed || shift_pressed \
)

int get_key(void);

#endif
