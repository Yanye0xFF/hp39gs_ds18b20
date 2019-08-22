#include "hp39kbd.h"

int get_key(void) {
	// wait until a key is pressed
	//while (!any_key_pressed);
    if (!any_key_pressed) {
        //about 0.125ms
        sys_waitRTCTicks(1);
        return KEY_EVENT_NULL;
    }
	// deal with the modifier keys
	if (comma_pressed) {
		return event_handler(4, 3);
	} else if (on_pressed) {
		return event_handler(4, 6);
	} else if (!any_normal_key_pressed) {
		return 0;
	}

	for (unsigned c = 0; c < 8; c++) {
		// set the current column pin to output, others inputs
		*GPGCON = (1 << 16 << c * 2) | 0xAAA9;
		delay(625);

		// skip this column if no key in it is pressed
		if (!any_key_pressed) {
			continue;
		}
		for (unsigned r = 0; r < 8; r++) {
			// check whether a row is active
			if (!(*GPGDAT & (1 << (r + 1)))) {
				// restore all column pins to output
				*GPGCON = 0x5555AAA9;
				delay(625);
				// return at the first detected key press
				return event_handler(c, r);
			}
		}
	}

	// the key was released before it could be captured, hence try again
	//return get_key();
	return KEY_EVENT_NULL;
}
