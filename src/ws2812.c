#include "ws2812.h"
#include "aolib.h"

struct ws2812 strip;

const uint8_t PERIOD = 59;
const uint8_t LOW = 17;
const uint8_t HIGH = 25;
const uint8_t RESET_LEN = 50;

void ws2812_set_color(uint8_t led, uint8_t r, uint8_t g, uint8_t b) {
    volatile uint32_t n = (led * 24);
    volatile uint8_t i;

    if(strip.brightness > 0) {
        r = (r * strip.brightness) >> 8;
        g = (g * strip.brightness) >> 8;
        b = (b * strip.brightness) >> 8;
    }

    for(i = 8; i-- > 0; n++) {
        strip.dma_buffer[n] = g & (1 << i) ? HIGH : LOW;
    }

    for(i = 8; i-- > 0; n++) {
        strip.dma_buffer[n] = r & (1 << i) ? HIGH : LOW;
    }

    for(i = 8; i-- > 0; n++) {
        strip.dma_buffer[n] = b & (1 << i) ? HIGH : LOW;
    }

}

void ws2812_set_color_single(uint8_t led, uint32_t c) {
    volatile uint8_t
        r = (uint8_t)(c >> 16),
        g = (uint8_t)(c >> 8),
        b = (uint8_t)(c);

    ws2812_set_color(led, r, g, b);
}

uint32_t ws2812_color(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

void ws2812_clear(void) {
    volatile uint16_t i;

    // initialize all the colors as off
    for(i = 0; i < strip.num_leds; i++) {
        ws2812_set_color(i, 0, 0, 0);
    }
}

uint32_t wheel(char pos) {
    if(pos < 85) {
        return ws2812_color(pos * 3, 255 - pos * 3, 0);
    }
    else if(pos < 170) {
        pos -= 85;
        return ws2812_color(255 - pos * 3, 0, pos * 3);
    }
    else {
        pos -= 170;
        return ws2812_color(0, pos * 3, 255 - pos * 3);
    }
}

void ws2812_show(void) {
    volatile uint16_t memaddr;
    volatile uint16_t buffersize;

    buffersize = (strip.num_leds * 24) + RESET_LEN;
    memaddr = (strip.num_leds * 24);

    while(memaddr < buffersize) {
        strip.dma_buffer[memaddr] = 0;
        memaddr++;
    }

    DMA_SetCurrDataCounter(DMA1_Channel2, buffersize - 1);
    DMA_Cmd(DMA1_Channel2, ENABLE);
    TIM_Cmd(TIM3, ENABLE);

    while(!DMA_GetFlagStatus(DMA1_FLAG_TC2));

    DMA_Cmd(DMA1_Channel2, DISABLE);
    TIM_Cmd(TIM3, DISABLE);
    DMA_ClearFlag(DMA1_FLAG_TC2);
}

void rainbow(uint32_t wait) {
    volatile uint16_t i, j;

    for(j = 0; j < 256 * 5; j++) {
        for(i = 0; i < strip.num_leds; i++) {
            ws2812_set_color_single(
                i, wheel(((i * 256 / strip.num_leds) + j) & 255));
        }
        ws2812_show();
        delay(wait);
    }
}

