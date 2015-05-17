#include "main.h"

// colors
const uint32_t OFF_COLOR = 131074L; // ws2812_color(2, 0, 2);
const uint32_t FIVE_COLOR = 1114129L; // ws2812_color(17, 0, 17);
const uint32_t MINUTES_COLOR = 13721L; // ws2812_color(0, 53, 153);
const uint32_t HOURS_COLOR = 3368448L; // ws2812_color(51, 102, 0);
const uint32_t NOON_COLOR = 4587590L; // ws2812_color(70, 0, 70);

// number of LEDS for each "hand"
const uint8_t MINUTES_LEDS = 2;
const uint8_t HOURS_LEDS = 1;
const uint8_t SECONDS_LEDS = 18;
const uint8_t MAX_BRIGHTNESS = 60;
const uint16_t FADE_TIME = 500;
const uint16_t HOUR_BUTTON = GPIO_Pin_1;
const uint16_t MINUTE_BUTTON = GPIO_Pin_2;
const uint16_t BUTTONS[] = {GPIO_Pin_1, GPIO_Pin_2};

const uint8_t PIXELS = 60;
const uint8_t ROTATE = 6;
const uint16_t SYNC_MAX = 3600; // one hour
const uint16_t FADE_PAUSE = 500;


// other variables
RTC_TimeTypeDef RTC_TimeStructure;
uint8_t sync_loop = 0;
uint32_t loop_count = 0;
uint32_t current_colors[60];
uint32_t start_millis = 0;
volatile uint64_t counter = 0;
volatile uint64_t delay_ms = 0;


void systick_handler(void) {
    counter++;
    if(delay_ms > 0) {
        delay_ms --;
    }
}

uint8_t constrain(uint8_t value, uint8_t min, uint8_t max) {
    if(value < min) value = min;
    else if(value > max) value = max;
    return value;
}

uint8_t forward(uint8_t pos, uint8_t count) {
    pos += count % PIXELS;
    if(pos > 59) pos -= 60;
    return pos;
}


uint8_t backward(uint8_t pos_, uint8_t count) {
    int8_t pos = pos_;
    pos -= count % PIXELS;
    if(pos < 0) pos += 60;
    return pos;
}

void clear_strip() {
    uint8_t i;

    for(i = 0; i < PIXELS; i++) {
        uint8_t pixel = forward(i, ROTATE * 5);
        uint32_t color = OFF_COLOR;

        if(i % 5 == 0) {
            color = FIVE_COLOR;
        }

        current_colors[pixel] = color;

        ws2812_set_color_single(pixel, color);
    }

    uint8_t noon = forward(0, ROTATE * 5);

    ws2812_set_color_single(noon, NOON_COLOR);
    current_colors[noon] = NOON_COLOR;
}

uint32_t map_range(double x, double in_min, double in_max, double out_min,
    double out_max) {
    return round((x - in_min) * (out_max - out_min) / (in_max - in_min) +
        out_min);
}


/**
 * Blends two colors.
 *
 * This code was borrowed from Kevin Alford - https://github.com/zeroeth
 */
uint32_t blend(uint32_t color1, uint32_t color2) {
    uint8_t r1, g1, b1;
    uint8_t r2, g2, b2;

    r1 = (uint8_t)(color1 >> 16);
    g1 = (uint8_t)(color1 >> 8);
    b1 = (uint8_t)(color1 >> 0);

    r2 = (uint8_t)(color2 >> 16);
    g2 = (uint8_t)(color2 >> 8);
    b2 = (uint8_t)(color2 >> 0);

    return ws2812_color(constrain(r1 + r2, 0, 255),
        constrain(g1 + g2, 0, 255), constrain(b1 + b2, 0, 255));
}

void fade_in(uint8_t start, uint8_t count, uint8_t _end) {
    uint8_t add = (float)_end / count;
    uint8_t brightness = add;
    uint16_t _delay = (uint16_t)(FADE_TIME / (double)count - 1);

    uint8_t first = 1;
    while(count > 0) {
        uint8_t led = backward(start, count);
        uint32_t color = ws2812_color(brightness, 0, brightness / 2);

        set_color(led, color, 0);

        if(!first) {
            uint8_t newled = backward(led, 2);
            ws2812_set_color_single(newled, current_colors[newled]);
            if(count == 1) {
                newled = backward(led, 1);
                ws2812_set_color_single(newled, current_colors[newled]);
            }
        }
        ws2812_show();
        delay(_delay);
        count--;
        brightness += add;
        first = 0;
    }
}

void set_color(uint8_t led, uint32_t color, uint8_t set_current) {
    if(color != OFF_COLOR) {
        if(current_colors[led] != OFF_COLOR) {
            color = blend(current_colors[led], color);
        }
    }

    if(set_current) {
        current_colors[led] = color;
    }

    ws2812_set_color_single(led, color);
}

void show_hours_minutes(void) {
    uint8_t minutes = RTC_TimeStructure.RTC_Minutes;
    float percent = minutes / 60.0;

    minutes = forward(minutes, ROTATE * 5);
    uint8_t start = minutes;

    uint8_t i;

    for(i = 0; i < MINUTES_LEDS; i++) {
        set_color(minutes, MINUTES_COLOR, 1);
        minutes = backward(start, i + 1);
    }

    uint8_t hours = (RTC_TimeStructure.RTC_Hours % 12) * 5;
    hours = forward(hours, ROTATE * 5);

    hours += (uint8_t)(5.0 * percent);
    start = hours;

    for(i = 0; i < HOURS_LEDS; i++) {
        set_color(hours, HOURS_COLOR, 1);
        hours = backward(start, i + 1);
    }

    ws2812_show();
}

void advance(uint8_t button) {
    if(button == HOUR_BUTTON) {
        uint8_t hour = RTC_TimeStructure.RTC_Hours + 1;
        if(hour >= 12) hour = 0;

        RTC_TimeStructure.RTC_Hours = hour;
    }
    else {
        uint8_t minute = RTC_TimeStructure.RTC_Minutes + 1;
        if(minute > 59) minute = 0;
        RTC_TimeStructure.RTC_Minutes = minute;
    }

    set_time(RTC_TimeStructure);

    clear_strip();
    ws2812_show();;
    show_hours_minutes();
    delay(200);
}

void clock_set_mode(void) {
    uint8_t i, button = 0;
    show_hours_minutes();
    delay(1000);
    clear_strip();
    uint64_t start_millis = counter;
    while(1) {
        for(i = 0; i < 2; i++) {
            button = BUTTONS[i];
            if(!GPIO_ReadInputDataBit(GPIOA, button)) {
                delay(90);
                if(!GPIO_ReadInputDataBit(GPIOA, button)) {
                    advance(BUTTONS[i]);
                    start_millis = counter;
                }
            }
        }

        if(counter - start_millis > 3000) {
            delay(1000);
            return;
        }
    }
}

void check_set_mode(void) {
    uint8_t i;
    uint16_t button;

    for(i = 0; i < 2; i++) {
        button = BUTTONS[i];
        if(!GPIO_ReadInputDataBit(GPIOA, button)) {
            delay(150);
            if(!GPIO_ReadInputDataBit(GPIOA, button)) {
                clock_set_mode();
                return;
            }
        }
    }
}
/*****************************************************************************/
//                                  MAIN LOOP                                //
/*****************************************************************************/
int main(void) {
    if(SysTick_Config(SystemCoreClock / 1000)) {
        while(1) { }
    }
    strip.num_leds = 60;
    strip.brightness = 0;

    setup_gpio();
    setup_rtc();
    setup_timer();
    setup_dma();

    GPIO_SetBits(GPIOB, GPIO_Pin_1);

    uint8_t current_seconds = 0, start = 0, seconds = 0;

    ws2812_clear();

    while(1) {
        // get the current time
        RTC_TimeStructInit(&RTC_TimeStructure);
        RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);

        current_seconds = RTC_TimeStructure.RTC_Seconds;

        if(sync_loop) {
            start = current_seconds;
            while(start == RTC_TimeStructure.RTC_Seconds) {
                RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
            }
            sync_loop = 0;
            loop_count = 0;
            current_seconds = RTC_TimeStructure.RTC_Seconds;
        }

        // set the brightness based on the current light input
        // TODO: this is a todo!

        clear_strip();
        check_set_mode();
        show_hours_minutes();

        seconds = RTC_TimeStructure.RTC_Seconds;
        seconds = forward(seconds, ROTATE * 5);

        fade_in(seconds, SECONDS_LEDS, MAX_BRIGHTNESS);

        start = current_seconds;
        while(start == RTC_TimeStructure.RTC_Seconds) {
            RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
        }

        loop_count++;

        if(loop_count > SYNC_MAX) {
            sync_loop = 1;
        }

    }

    return 0;
}

