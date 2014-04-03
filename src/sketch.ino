#include <Adafruit_NeoPixel.h> 
#include <Wire.h>
#include <math.h>

#include "RTClib.h"
#include "LinkedList.h"

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
LinkedList *list = new LinkedList();
 
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
        //RTC.adjust(DateTime(__DATE__, __TIME__));
    }

    for(int i = 0; i < PIXELS; i++) {
        list->add(i);
    }
    
    list->done();
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

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    
    clearStrip();

    uint8_t value = now.minute();
    long minutes = mapRange(value, 0, 60, 0, PIXELS);
    strip.setPixelColor(minutes, 0, 80, 0);
    
    value = now.hour() % 12;
    uint8_t hours = value * 2;
    strip.setPixelColor(hours, 80, 0, 0);
    
    strip.show();
    delay(200);
    
    value = now.second();
    long seconds = mapRange(value, 0, 60, 0, PIXELS);
    strip.setPixelColor(seconds, 50, 0, 80);
    strip.show();

    delay(800);
    loopCount++;
    if(loopCount >= SYNC_MAX) {
        syncLoop = true;
    }
}
