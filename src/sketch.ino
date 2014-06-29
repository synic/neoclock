#include <Adafruit_NeoPixel.h> 
#include <Wire.h>
#include <math.h>

#include "RTClib.h"
#include "RoundClock.h"

const uint8_t PIXELS = 60;
const uint8_t NEO_PIN = 6;
const uint8_t LIGHTSENSOR_PIN = A3;
const uint8_t ROTATE = 6;
const uint8_t HOUR_BUTTON = 3;
const uint8_t MINUTE_BUTTON = 4;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXELS, 
    NEO_PIN, NEO_GRB + NEO_KHZ800);

const uint16_t SYNC_MAX = 18000; // 5 hours
const uint16_t FADE_PAUSE = 500;

// colors
const uint32_t OFF_COLOR = strip.Color(2, 0, 2);
const uint32_t FIVE_COLOR = strip.Color(17, 0, 17);
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
const uint8_t BUTTONS[] = {HOUR_BUTTON, MINUTE_BUTTON};
boolean syncLoop = true;
uint32_t loopCount = 0;
RoundClock clock = RoundClock();
uint32_t *currentColors = new uint32_t[PIXELS] {0};
unsigned long startMillis = 0;
DateTime now;
 
void setup () {
    // set up pins
    pinMode(LIGHTSENSOR_PIN, INPUT);
    pinMode(HOUR_BUTTON, INPUT_PULLUP);
    pinMode(MINUTE_BUTTON, INPUT_PULLUP);

    Serial.begin(9600);
    Wire.begin();
    RTC.begin();
    strip.begin();
    strip.show();

    //Serial.println("Before setting clock");
 
    //RTC.adjust(DateTime(__DATE__, __TIME__));
    if(!RTC.isrunning()) {
        // following line sets the RTC to the date & time this 
        // sketch was compiled
        Serial.println("Setting clock from compile time.");
        RTC.adjust(DateTime(__DATE__, __TIME__));
    }

    //Serial.println(RTC.isrunning());

    for(uint8_t i = 0; i < PIXELS; i++) {
        clock.add(i);
    }
    
    clock.done();
}

void clearStrip() {
    for(uint8_t i = 0; i < PIXELS; i++) {
        uint32_t color = OFF_COLOR;

        if(i % 5 == 0) {
            color = FIVE_COLOR;
        }

        currentColors[i] = color;

        strip.setPixelColor(i, color);
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

void showHoursMinutes() {
    uint8_t minutes = now.minute();
    float percent = minutes / 60.0;

    minutes = clock.forward(minutes, ROTATE * 5);
    uint8_t start = minutes;

    for(volatile uint8_t i = 0; i < MINUTES_LEDS; i++) {
        setColor(minutes, MINUTES_COLOR);
        minutes = clock.back(start, i + 1);
    }

    uint8_t hours = (now.hour() % 12) * 5;
    hours = clock.forward(hours, ROTATE * 5);

    hours += 5 * percent;
    start = hours;

    for(volatile uint8_t i = 0; i < HOURS_LEDS; i++) { 
        setColor(hours, HOURS_COLOR);
        hours = clock.back(start, i + 1); 
    }

    strip.show();
}

void advance(uint8_t button) {
    if(button == HOUR_BUTTON) {
        uint8_t hour = now.hour() + 1;
        if(hour > 12) hour = 0;
        now = DateTime(now.year(), now.month(), now.day(), hour, 
            now.minute(), now.second());
    }
    else {
        uint8_t minute = now.minute() + 2;
        if(minute > 59) minute = 0;
        now = DateTime(now.year(), now.month(), now.day(), now.hour(), 
            minute, now.second());
    }

    RTC.adjust(now);
    showHoursMinutes();
}

void clockSetMode() {
    showHoursMinutes();
    delay(1000);
    clearStrip();
    startMillis = millis();

    while(1) {
        for(uint8_t i = 0; i < 2; i++) {
            if(digitalRead(BUTTONS[i]) == LOW) {
                delay(50);
                if(digitalRead(BUTTONS[i]) == LOW) {
                    advance(BUTTONS[i]);
                    startMillis = millis();
                }
            }
        }

        if(millis() - startMillis > 3000) {
            delay(500);
            return;
        }
    }
}

void checkSetMode() {
    return;
    for(uint8_t i = 0; i < 2; i++) {
        uint8_t button = BUTTONS[i];
        if(digitalRead(button) == LOW) {
            delay(50);
            if(digitalRead(button) == LOW) {
                clockSetMode();
                return;
            }
        }
    }
}
 
void loop() {
    now = RTC.now();  
    //Serial.println("Starting the loop...");

    // here we sync up the time so that each loop happens more-or-less at the
    // top of each second.
    if(syncLoop) {
        uint8_t start = now.second();
        while(now.second() == start) {
            now = RTC.now();
        }
        syncLoop = false;
    }

    int value = analogRead(LIGHTSENSOR_PIN);
    value = map(value, 1024, 0, 256, 50);
    strip.setBrightness(value);

    clearStrip();

    checkSetMode();

    showHoursMinutes();

    checkSetMode();

    uint8_t seconds = now.second();

    seconds = clock.forward(seconds, ROTATE * 5);

    fadeIn(seconds, SECONDS_LEDS, MAX_BRIGHTNESS);

    delay(500);

    loopCount++;

    if(loopCount >= SYNC_MAX) {
        syncLoop = true;
    }
}
