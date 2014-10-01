#include "aolib.h"
#include <stdint.h>

void delay(volatile uint32_t delay) {
    delay *= 1000;

    while(delay--) {}
}
