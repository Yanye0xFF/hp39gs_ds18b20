#include <hpsys.h>
#include "user_main.h"

extern unsigned int *__exit_stk_state;
extern int _exit_save(unsigned int *ptr);
extern void __exit_cleanup();

unsigned __display_buf;

void _start(void) {
	volatile unsigned *LCDSADDR1 = (unsigned *)0x7300014;
	__display_buf = (*LCDSADDR1 & 0xffff) * 2 + 0x7f00000;

	unsigned state_buffer[4], lcd_buffer[17];
	__exit_stk_state = state_buffer;

	sys_intOff();
	sys_lcdsave(lcd_buffer);

	if (_exit_save((unsigned *)state_buffer)) {
		user_init();
		__exit_cleanup();
	}

	sys_lcdrestore(lcd_buffer);
	sys_intOn();
}
