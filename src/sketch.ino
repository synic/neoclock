#include <Adafruit_NeoPixel.h> 
#include <Wire.h>
#include <math.h>

#include "RTClib.h"
#include "RoundClock.h"

// constants
const uint8_t PIXELS = 24;
const uint8_t NEO_PIN = 13;
const unsigned int SYNC_MAX = 18000; // 5 hours

// other variables
RTC_DS1307 RTC;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXELS, 
    NEO_PIN, NEO_GRB + NEO_KHZ800);
boolean syncLoop = true;
unsigned int loopCount = 0;
RoundClock *clock = new RoundClock();
 
void setup () {
    Serial.begin(9600);
    Wire.begin();
    RTC.begin();
    strip.begin();
    strip.show();
 
    if (! RTC.isrunning()) {
        Serial.println("RTC is NOT running!");
        // following line sets the RTC to the date & time this 
        // sketch was compiled
        RTC.adjust(DateTime(__DATE__, __TIME__));
    }

    for(int i = 0; i < PIXELS; i++) {
        clock->add(i);
    }
    
    clock->done();
}

void clearStrip() {
    for(int i = 0; i < PIXELS; i++) {
        strip.setPixelColor(i, 1, 0, 1);
    }
}

long mapRange(double x, double in_min, double in_max, double out_min,
    double out_max) {
    return round((x - in_min) * (out_max - out_min) / (in_max - in_min) +
        out_min);
}

void fadeIn(int start, int count, int endPercent) {
    int add = (count / (float)endPercent) * (float)endPercent;
    Serial.print("add: ");
    Serial.println(add);
    int brightness = add;

    while(count > 0) {
        int led = clock->back(start, count);
        Serial.println(brightness);
        strip.setPixelColor(led, brightness / 2, 0, brightness);
        strip.show();
        delay(20);
        count--;
        brightness += add;
    }
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
    long minutes = mapRange(value, 0, 60, 0, PIXELS);
    long start = minutes;

    for(int i = 0; i < 2; i++) {
        strip.setPixelColor(minutes, 0, 20, 0);
        minutes = clock->back(start, i + 1);
    }

    value = now.hour() % 12;
    int hours = round(value * 2);
    strip.setPixelColor(hours, 10, 0, 0);
    
    strip.show();
    delay(200);
    
    value = now.second();
    long seconds = mapRange(value, 0, 60, 0, PIXELS);
    fadeIn(seconds, 5, 200);

    delay(1000 - 200 - 20 * 4);
    loopCount++;
    if(loopCount >= SYNC_MAX) {
        syncLoop = true;
    }
}
