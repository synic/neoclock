#ifndef __NEOCLOCK_MAIN_H
#define __NEOCLOCK_MAIN_H

#include <math.h>
#include <stdint.h>

#include "stm32f30x.h"
#include "timer.h"
#include "rtc.h"
#include "dma.h"
#include "gpio.h"
#include "ws2812.h"
#include "aolib.h"

extern const uint8_t PIXELS;
extern const uint8_t ROTATE;
extern const uint16_t SYNC_MAX; // one hour
extern const uint16_t FADE_PAUSE;

// colors
extern const uint32_t OFF_COLOR; // ws2812_color(2, 0, 2);
extern const uint32_t FIVE_COLOR; // ws2812_color(17, 0, 17); 
extern const uint32_t MINUTES_COLOR; // ws2812_color(0, 53, 153);
extern const uint32_t HOURS_COLOR; // ws2812_color(51, 102, 0);
extern const uint32_t NOON_COLOR; // ws2812_color(70, 0, 70);

// number of LEDS for each "hand"
extern const uint8_t MINUTES_LEDS;
extern const uint8_t HOURS_LEDS;
extern const uint8_t SECONDS_LEDS;
extern const uint8_t MAX_BRIGHTNESS;
extern const uint16_t FADE_TIME;
extern const uint16_t HOUR_BUTTON;
extern const uint16_t MINUTE_BUTTON;
extern const uint16_t BUTTONS[];

extern RTC_TimeTypeDef RTC_TimeStructure;
extern uint8_t sync_loop;
extern uint32_t loop_count;
extern uint32_t current_colors[];
extern uint32_t start_millis;
extern volatile uint64_t counter;
extern volatile uint64_t delay_ms;

// prototypes
uint8_t forward(uint8_t pos, uint8_t count);
uint8_t backward(uint8_t post, uint8_t count);
void clear_strip(void);
uint32_t map_range(double x, double in_min, double in_max, double out_min,
    double out_max);
uint32_t blend(uint32_t color1, uint32_t color2);
void fade_in(uint8_t start, uint8_t count, uint8_t end);
void set_color(uint8_t led, uint32_t color, uint8_t set_current);
void show_hours_minutes(void);
void advance(uint8_t button);
void clock_set_mode(void);
void check_set_mode(void);
uint8_t constrain(uint8_t value, uint8_t min, uint8_t max);
void systick_handler(void);

#endif
