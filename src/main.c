#include "stm32f30x.h"
#include "timer.h"
#include "rtc.h"
#include "dma.h"
#include "gpio.h"
#include "ws2812.h"
#include "aolib.h"

int main(void) {
    SystemInit();

    setup_gpio();
    setup_timer();
    setup_dma();
    setup_rtc();

    strip.num_leds = 144;
    strip.brightness = 50;
  
    ws2812_set_color(89, 0, 0, 0);

    ws2812_clear();

    while(1) {
        rainbow(0);
    }

    return 0;
}

