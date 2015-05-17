#include "aolib.h"
#include "main.h"
#include <stdint.h>

void delay(volatile uint64_t delay) {
    delay_ms = delay;
    while(delay_ms > 0) { }
}
