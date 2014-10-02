#include "stm32f30x.h"
#include "timer.h"
#include "rtc.h"
#include "dma.h"
#include "gpio.h"
#include "ws2812.h"
#include "aolib.h"

int main(void) {
    setup_gpio();
    setup_rtc();
    setup_timer();
    setup_dma();

    strip.num_leds = 60;
    strip.brightness = 30;
  
    ws2812_clear();

    while(1) {
        rainbow(0);
        delay(100);
    }

    return 0;
}

