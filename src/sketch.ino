#include <Adafruit_NeoPixel.h> 
#include <Wire.h>
#include <math.h>

#include "RTClib.h"
#include "RoundClock.h"

const uint8_t PIXELS = 24;
const uint8_t NEO_PIN = 13;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXELS, 
    NEO_PIN, NEO_GRB + NEO_KHZ800);

const uint16_t SYNC_MAX = 18000; // 5 hours
const uint16_t FADE_PAUSE = 500;

// colors
const uint32_t OFF_COLOR = strip.Color(1, 0, 1);
const uint32_t MINUTES_COLOR = strip.Color(0, 53, 153);  
const uint32_t HOURS_COLOR = strip.Color(51, 102, 0);

// number of LEDs for each hand
const uint8_t MINUTES_LEDS = 2;
const uint8_t HOURS_LEDS = 1;
const uint8_t SECONDS_LEDS = 18;
const uint8_t MAX_BRIGHTNESS = 60;

const uint16_t FADE_TIME = 500;

// other variables
RTC_DS1307 RTC;
boolean syncLoop = true;
uint32_t loopCount = 0;
RoundClock clock = RoundClock();
uint32_t *currentColors = new uint32_t[PIXELS] {0};
 
void setup () {
    Serial.begin(9600);
    Wire.begin();
    RTC.begin();
    strip.begin();
    strip.show();
 
    if(!RTC.isrunning()) {
        // following line sets the RTC to the date & time this 
        // sketch was compiled
        RTC.adjust(DateTime(__DATE__, __TIME__));
    }

    for(uint8_t i = 0; i < PIXELS; i++) {
        clock.add(i);
    }
    
    clock.done();
}

void clearStrip() {
    for(uint8_t i = 0; i < PIXELS; i++) {
        currentColors[i] = OFF_COLOR;
        strip.setPixelColor(i, OFF_COLOR);
    }

}

long mapRange(double x, double in_min, double in_max, double out_min,
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

    return strip.Color(constrain(r1 + r2, 0, 255),
        constrain(g1 + g2, 0, 255), constrain(b1 + b2, 0, 255));
}

void fadeIn(uint8_t start, uint8_t count, uint8_t _end) {
    uint8_t add = (float)_end / count;
    uint8_t brightness = add;
    uint16_t _delay = (uint16_t)(FADE_TIME / (double)count - 1); 
    Serial.println(_delay);

    uint8_t first = true;
    while(count > 0) {
        uint8_t led = clock.back(start, count);
        uint32_t color = strip.Color(brightness, 0, brightness / 2);
        
        setColor(led, color, false);

        if(!first) {
            uint8_t newled = clock.back(led, 2);
            strip.setPixelColor(newled, currentColors[newled]);
            if(count == 1) {
                newled = clock.back(led, 1);
                strip.setPixelColor(newled, currentColors[newled]);
            }
        }
        strip.show();
        delay(_delay);
        count--;
        brightness += add;
        first = false;
    }
}

void setColor(uint8_t led, uint32_t color, boolean setCurrent) {
    if(color != OFF_COLOR) {
        if(currentColors[led] != OFF_COLOR) {
            color = blend(currentColors[led], color);
        }
    }

    if(setCurrent) {
        currentColors[led] = color;
    }

    strip.setPixelColor(led, color);
} 

void setColor(uint8_t led, uint32_t color) {
    setColor(led, color, true);
}
 
void loop () {
    DateTime now = RTC.now();  

    // here we sync up the time so that each loop happens more-or-less at the
    // top of each second.
    if(syncLoop) {
        uint8_t start = now.second();
        while(now.second() == start) {
            now = RTC.now();
        }
        syncLoop = false;
    }

    clearStrip();

    uint8_t value = now.minute();
    uint8_t minutes = mapRange(value, 0, 60, 0, PIXELS);
    uint8_t start = minutes;

    for(uint8_t i = 0; i < MINUTES_LEDS; i++) {
        setColor(minutes, MINUTES_COLOR);
        minutes = clock.back(start, i + 1);
    }

    value = now.hour() % 12;
    uint8_t hours = round(value * 2);
    start = hours;

    for(uint8_t i = 0; i < HOURS_LEDS; i++) { 
        setColor(hours, HOURS_COLOR);
        hours = clock.back(start, i + 1); 
    }
    
    strip.show();
    
    value = now.second();
    uint8_t seconds = mapRange(value, 0, 60, 0, PIXELS);
    fadeIn(seconds, SECONDS_LEDS, MAX_BRIGHTNESS);

    delay(500);
    loopCount++;
    if(loopCount >= SYNC_MAX) {
        syncLoop = true;
    }
}
