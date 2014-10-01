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
    setup_rtc();
    setup_timer();
    setup_dma();

    strip.num_leds = 60;
    strip.brightness = 50;
  
    ws2812_clear();

    uint8_t i;

    while(1) {
        //rainbow(0);
        for(i = 0; i < 20; i++) {
            ws2812_set_color(i, 25, 0, 25);
        }
        ws2812_show();
    }

    return 0;
}

