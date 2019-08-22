#ifndef __GPIO_H__
#define __GPIO_H__

#define GPBCON ((unsigned int*) 0x07A00010)
#define GPBDAT ((unsigned int*) 0x07A00014)
#define GPBUP ((unsigned int*) 0x07A00018)

void output_set(unsigned char state);
unsigned char input_get();

void pull_up();
void pull_up_dis();

#endif
