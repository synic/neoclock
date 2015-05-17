#ifndef _AOLIB_H_
#define _AOLIB_H_

#include <stdint.h>

void delay(volatile uint64_t delay);
void systick_handler(void);

#endif
