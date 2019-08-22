#include "gpio.h"

void output_set(unsigned char state) {
    //set output
    *GPBCON &= 0x1FFFCF;
	*GPBCON |= 0x10;
    *GPBDAT = (state) ? ((*GPBDAT) | 0x04) : ((*GPBDAT) & 0x0B);
}

unsigned char input_get() {
    //set input
    *GPBCON &= 0x1FFFCF;
    return (*GPBDAT & 0x4) >> 2;
}

void pull_up() {
    *GPBUP &= 0x04;
}

void pull_up_dis() {
    *GPBUP |= 0x04;
}
