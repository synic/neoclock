#ifndef _NEOCLOCK_WS2812_H
#define _NEOCLOCK_WS2812_H

#include "stm32f30x.h"

struct __attribute__((aligned(4))) ws2812 {
    uint8_t num_leds;
    uint8_t brightness;
    uint8_t dma_buffer[100];
};

extern struct ws2812 strip;
extern const uint8_t PERIOD;
extern const uint8_t HIGH;
extern const uint8_t LOW;
extern const uint8_t RESET_LEN;

void ws2812_set_color(uint8_t led, uint8_t r, uint8_t g, uint8_t b);
void ws2812_set_color_single(uint8_t led, uint32_t c);
uint32_t ws2812_color(uint8_t r, uint8_t b, uint8_t g);
void ws2812_clear(void);
uint32_t wheel(char pos);
void ws2812_show(void);
void rainbow(uint32_t wait);

#endif
