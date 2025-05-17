#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <RTClib.h>
#include <EEPROM.h>

class NeoPixelStrip {
private:
    Adafruit_NeoPixel& strip;
    uint32_t* pixelHistory;
    bool* pixelDirty;
    const uint16_t pixelCount;

public:
    NeoPixelStrip(Adafruit_NeoPixel& _strip) : 
        strip(_strip), 
        pixelCount(_strip.numPixels()) {
        pixelHistory = new uint32_t[pixelCount];
        pixelDirty = new bool[pixelCount];
        for(uint16_t i = 0; i < pixelCount; i++) {
            pixelHistory[i] = 0;
            pixelDirty[i] = false;
        }
    }

    ~NeoPixelStrip() {
        delete[] pixelHistory;
        delete[] pixelDirty;
    }

    void setPixelColor(uint16_t n, uint32_t c, bool saveToHistory = true) {
        if(saveToHistory) {
            pixelHistory[n] = c;
            pixelDirty[n] = true;
        }
        strip.setPixelColor(n, c);
    }

    uint32_t getPixelColor(uint16_t n) {
        return strip.getPixelColor(n);
    }

    uint32_t getPixelHistory(uint16_t n) {
        return pixelHistory[n];
    }

    void show() {
        strip.show();
    }

    void clear() {
        for(uint16_t i = 0; i < pixelCount; i++) {
            pixelDirty[i] = false;
        }
        strip.clear();
    }

    void begin() {
        strip.begin();
    }

    void setBrightness(uint8_t b) {
        strip.setBrightness(b);
    }

    uint8_t getBrightness() {
        return strip.getBrightness();
    }

    uint16_t numPixels() {
        return pixelCount;
    }
};

#define PIXELS 60
#define PIN 9
#define BRIGHTNESS_LEVELS 5
#define DEFAULT_BRIGHTNESS_LEVEL 3
#define EEPROM_BRIGHTNESS_ADDR 0
#define EEPROM_MODE_ADDR 1
#define EEPROM_COLOR_SCHEME_ADDR 2
#define MINUTE_RATE_LIMIT 20
#define HOUR_RATE_LIMIT 100
#define SETTING_RATE_LIMIT 500
#define INDICATOR_DURATION 700
#define MAX_BRIGHTNESS 200
#define SYNC_MAX 3600
#define DIAGNOSTIC_BRIGHTNESS 20
#define MINUTE_MARKER_BRIGHTNESS_RATIO 0.20

#define COMMON_GROUND 10
#define HOUR_BUTTON 14
#define MINUTE_BUTTON 16
#define BRIGHTNESS_BUTTON 15
#define MODE_BUTTON 18

#define ROTATE 0

#define COLOR_SCHEME_COUNT 11
#define MODES_PER_SCHEME 3

#define MODE_HANDS_ONLY 0
#define MODE_HANDS_WITH_FIFTHS 1
#define MODE_HANDS_WITH_ALL_MARKERS 2

#define MINUTE_LED_COUNT 2
#define HOUR_LED_COUNT 1
#define SECOND_LED_COUNT 18

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXELS, PIN, NEO_GRB + NEO_KHZ800);
NeoPixelStrip ledStrip(strip);
RTC_DS3231 RTC;

uint32_t OFF_COLOR = strip.Color(0, 0, 0);
uint32_t ERROR_COLOR = strip.Color(255, 32, 32);
uint32_t I2C_ERROR_COLOR = strip.Color(0, 255, 128);
uint32_t BUTTON_ERROR_COLOR = strip.Color(128, 0, 128);
uint32_t RTC_ERROR_COLOR = strip.Color(255, 0, 0);
uint32_t WARNING_COLOR = strip.Color(255, 128, 0);
uint32_t SUCCESS_COLOR = strip.Color(0, 255, 0);

struct ColorScheme {
    uint32_t markerColor;
    uint32_t hourColor;
    uint32_t minuteColor;
    uint32_t secondColor;
};

const ColorScheme colorSchemes[COLOR_SCHEME_COUNT] = {
    // Default - Purple markers, green/blue hands
    {
        strip.Color(51, 0, 51),    // marker
        strip.Color(153, 204, 0),   // hour
        strip.Color(0, 159, 255),   // minute
        strip.Color(0, 0, 255)     // second
    },
    // Sunset - Orange markers, blue/teal hands
    {
        strip.Color(255, 128, 0),  // marker
        strip.Color(0, 128, 255),  // hour
        strip.Color(0, 255, 255),  // minute
        strip.Color(0, 128, 128)   // second
    },
    // Forest - Green markers, red/pink hands
    {
        strip.Color(0, 128, 0),    // marker
        strip.Color(255, 0, 0),    // hour
        strip.Color(255, 0, 128),  // minute
        strip.Color(128, 0, 64)    // second
    },
    // Ocean - Teal markers, orange/yellow hands
    {
        strip.Color(0, 128, 128),  // marker
        strip.Color(255, 128, 0),  // hour
        strip.Color(255, 255, 0),  // minute
        strip.Color(128, 128, 0)   // second
    },
    // Royal - Gold markers, purple/blue hands
    {
        strip.Color(255, 215, 0),  // marker
        strip.Color(128, 0, 255),  // hour
        strip.Color(0, 0, 255),    // minute
        strip.Color(64, 0, 128)    // second
    },
    // Neon - Pink markers, cyan/green hands
    {
        strip.Color(255, 0, 255),  // marker
        strip.Color(0, 255, 255),  // hour
        strip.Color(0, 255, 128),  // minute
        strip.Color(0, 128, 255)   // second
    },
    // Autumn - Brown markers, sky blue/light blue hands
    {
        strip.Color(139, 69, 19),  // marker
        strip.Color(135, 206, 235),// hour
        strip.Color(173, 216, 230),// minute
        strip.Color(176, 224, 230) // second
    },
    // Winter - Silver markers, deep blue/light blue hands
    {
        strip.Color(192, 192, 192),// marker
        strip.Color(0, 0, 139),    // hour
        strip.Color(0, 0, 205),    // minute
        strip.Color(0, 0, 255)     // second
    },
    // Fire - Red markers, orange/yellow hands
    {
        strip.Color(255, 0, 0),    // marker
        strip.Color(255, 128, 0),  // hour
        strip.Color(255, 255, 0),  // minute
        strip.Color(255, 200, 0)   // second
    },
    // Mint - Mint markers, teal/blue hands
    {
        strip.Color(152, 255, 152),// marker
        strip.Color(0, 128, 128),  // hour
        strip.Color(0, 0, 255),    // minute
        strip.Color(0, 64, 128)    // second
    },
    // Lavender - Purple markers, pink/red hands
    {
        strip.Color(230, 230, 250),// marker
        strip.Color(255, 192, 203),// hour
        strip.Color(255, 0, 0),    // minute
        strip.Color(128, 0, 0)     // second
    }
};

const uint8_t brightnessLevels[] = {
    20,    // Level 0: Night mode
    40,    // Level 1: Very dim
    60,    // Level 2: Dim
    102,   // Level 4: Medium-low
    153,   // Level 5: Medium
    200    // Level 7: Full brightness 
};

uint8_t BUTTON_PINS[] = {HOUR_BUTTON, MINUTE_BUTTON, BRIGHTNESS_BUTTON, MODE_BUTTON};
uint8_t lastButtonState[4] = {HIGH, HIGH, HIGH, HIGH};
unsigned long lastActionTime[4] = {0, 0, 0, 0};
unsigned long lastClearTime = 0;
unsigned long lastColorSchemeTime = 0;
unsigned long colorSchemeButtonPressTime = 0;
bool colorSchemeButtonsPressed = false;
bool modeButtonPressed = false;
bool brightnessButtonPressed = false;
unsigned long modeButtonPressTime = 0;
unsigned long brightnessButtonPressTime = 0;
unsigned long lastButtonReleaseTime = 0;
bool buttonsRecentlyReleased = false;

DateTime now;
DateTime previousReading;
unsigned long lastSecondMillis = 0;
unsigned long lastCheck = 0;
boolean rtcWorking = false;
boolean rtcDiagnosticMode = true;
boolean syncLoop = true;
int loopCount = 0;

uint8_t fallbackHour = 12;
uint8_t fallbackMinute = 0;
uint8_t fallbackSecond = 0;

uint8_t currentBrightnessLevel = DEFAULT_BRIGHTNESS_LEVEL;
boolean brightnessChanged = false;
uint8_t currentColorScheme = 0;
uint8_t currentMode = MODE_HANDS_WITH_FIFTHS;
boolean modeChanged = false;

enum SettingMode {
    SETTING_BRIGHTNESS,
    SETTING_MODE,
    SETTING_COLOR_SCHEME
};

SettingMode currentSettingMode = SETTING_BRIGHTNESS;

void resetToDefaults() {
    currentBrightnessLevel = DEFAULT_BRIGHTNESS_LEVEL;
    currentMode = MODE_HANDS_WITH_FIFTHS;
    currentColorScheme = 0;
    brightnessChanged = true;
    modeChanged = true;
    saveSettings();
}

void setup() {
    Serial.begin(115200);
    Serial.println("Starting NeoClock...");
    
    strip.begin();
    ledStrip.begin();
    clearStrip();
    ledStrip.show();

    pinMode(COMMON_GROUND, OUTPUT);
    digitalWrite(COMMON_GROUND, LOW);
    
    for(uint8_t i = 0; i < 4; i++) {
        pinMode(BUTTON_PINS[i], INPUT_PULLUP);
    }
    
    uint8_t storedBrightness = EEPROM.read(EEPROM_BRIGHTNESS_ADDR);
    if(storedBrightness < sizeof(brightnessLevels)/sizeof(brightnessLevels[0])) {
        currentBrightnessLevel = storedBrightness;
    } else {
        currentBrightnessLevel = DEFAULT_BRIGHTNESS_LEVEL;
        EEPROM.write(EEPROM_BRIGHTNESS_ADDR, currentBrightnessLevel);
    }
    
    uint8_t storedMode = EEPROM.read(EEPROM_MODE_ADDR);
    if(storedMode < MODES_PER_SCHEME) {
        currentMode = storedMode;
    } else {
        currentMode = MODE_HANDS_WITH_FIFTHS;
        EEPROM.write(EEPROM_MODE_ADDR, currentMode);
    }

    uint8_t storedColorScheme = EEPROM.read(EEPROM_COLOR_SCHEME_ADDR);
    if(storedColorScheme < COLOR_SCHEME_COUNT) {
        currentColorScheme = storedColorScheme;
    } else {
        currentColorScheme = 0;
        EEPROM.write(EEPROM_COLOR_SCHEME_ADDR, currentColorScheme);
    }
    
    ledStrip.setBrightness(DIAGNOSTIC_BRIGHTNESS);
    for(int i = 0; i < PIXELS; i++) {
        ledStrip.setPixelColor(i, strip.Color(51, 0, 51));
        ledStrip.show();
        delayAndCheckButtons(5);
    }
    for(int i = 0; i < PIXELS; i++) {
        ledStrip.setPixelColor(i, OFF_COLOR);
        ledStrip.show();
        delayAndCheckButtons(5);
    }
    
    if(rtcDiagnosticMode) {
        Serial.println("Running RTC diagnostics...");
        runRTCDiagnostics();
    }
    
    for(uint8_t i = 0; i < 4; i++) {
        if(digitalRead(BUTTON_PINS[i]) != HIGH) {
            ledStrip.setBrightness(DIAGNOSTIC_BRIGHTNESS);
            for(int j = 0; j < PIXELS; j++) {
                ledStrip.setPixelColor(j, BUTTON_ERROR_COLOR);
            }
            ledStrip.show();
            delayAndCheckButtons(100);
            for(int i = 0; i < PIXELS; i++) {
                ledStrip.setPixelColor(i, OFF_COLOR);
            }
            ledStrip.show();
        }
    }
    
    if(!rtcWorking) {
        Serial.println("RTC not working, using fallback time");
        fallbackHour = 12;
        fallbackMinute = 0;
        fallbackSecond = 0;
        now = DateTime(2020, 1, 1, fallbackHour, fallbackMinute, fallbackSecond);
        previousReading = now;
    } else {
        Serial.println("RTC initialized successfully");
        now = RTC.now();
        previousReading = now;
    }
    
    lastSecondMillis = millis();
    
    updateBrightness();
    renderClockFace();
    Serial.println("Setup complete");
}

void runRTCDiagnostics() {
    Wire.begin();
    delay(100);
    
    byte error, address;
    int deviceCount = 0;
    
    Serial.println("Scanning I2C bus...");
    for(address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        
        if(error == 0) {
            deviceCount++;
            Serial.print("I2C device found at address 0x");
            if(address < 16) Serial.print("0");
            Serial.println(address, HEX);
        }
    }
    
    if(deviceCount == 0) {
        Serial.println("No I2C devices found!");
        showDiagnosticPattern(I2C_ERROR_COLOR);
        rtcWorking = false;
        return;
    }
    
    Serial.println("Initializing RTC...");
    if(!RTC.begin()) {
        Serial.println("RTC initialization failed!");
        showDiagnosticPattern(RTC_ERROR_COLOR);
        rtcWorking = false;
        return;
    }
    
    Wire.beginTransmission(0x68);
    Wire.write(0x00);
    Wire.endTransmission();
    
    Wire.requestFrom(0x68, 1);
    if(Wire.available()) {
        byte reg0 = Wire.read();
        if(reg0 & 0x80) {
            Serial.println("RTC stopped, adjusting time...");
            RTC.adjust(DateTime(__DATE__, __TIME__));
        }
    }
    
    Serial.println("RTC diagnostics passed");
    showDiagnosticPattern(SUCCESS_COLOR);
    rtcWorking = true;
}

void showDiagnosticResult(bool success, String message) {
    for(int i = 0; i < PIXELS; i++) {
        strip.setPixelColor(i, OFF_COLOR);
    }
    strip.show();
    delay(250);
    
    if(success) {
        for(int i = 0; i < PIXELS; i += 3) {
            strip.setPixelColor(i, SUCCESS_COLOR);
        }
    } else {
        for(int i = 0; i < PIXELS; i++) {
            strip.setPixelColor(i, ERROR_COLOR);
        }
    }
    strip.show();
    delay(1000);
}

void showDiagnosticPattern(uint32_t color) {
    static bool rtcErrorShown = false;
    uint8_t oldBrightness = strip.getBrightness();
    strip.setBrightness(DIAGNOSTIC_BRIGHTNESS);

    Serial.print("Showing diagnostic pattern: ");
    if(color == ERROR_COLOR) Serial.println("ERROR");
    else if(color == I2C_ERROR_COLOR) Serial.println("I2C ERROR");
    else if(color == RTC_ERROR_COLOR) Serial.println("RTC ERROR");
    else if(color == WARNING_COLOR) Serial.println("WARNING");
    else Serial.println("SUCCESS");
    
    for(int i = 0; i < PIXELS; i++) {
        strip.setPixelColor(i, OFF_COLOR);
    }
    strip.show();
    delay(250);

    if(color == ERROR_COLOR) {
        for(int j = 0; j < 3; j++) {
            for(int i = 0; i < PIXELS; i++) {
                strip.setPixelColor(i, (i % 2 == 0) ? ERROR_COLOR : OFF_COLOR);
            }
            strip.show();
            delay(250);
            for(int i = 0; i < PIXELS; i++) {
                strip.setPixelColor(i, (i % 2 == 1) ? ERROR_COLOR : OFF_COLOR);
            }
            strip.show();
            delay(250);
        }
    } else if(color == I2C_ERROR_COLOR) {
        for(int i = 0; i < PIXELS; i++) {
            strip.setPixelColor(i, OFF_COLOR);
            strip.setPixelColor((i + 1) % PIXELS, I2C_ERROR_COLOR);
            strip.show();
            delay(20);
        }
    } else if(color == RTC_ERROR_COLOR && !rtcErrorShown) {
        rtcErrorShown = true;
        for(int i = 0; i < PIXELS; i++) {
            strip.setPixelColor(i, OFF_COLOR);
        }
        strip.show();
        delay(250);
        
        for(int i = 0; i < PIXELS; i++) {
            strip.setPixelColor(i, OFF_COLOR);
            strip.setPixelColor((i + 1) % PIXELS, RTC_ERROR_COLOR);
            strip.show();
            delay(20);
        }
        
        for(int i = 0; i < PIXELS; i++) {
            strip.setPixelColor(i, OFF_COLOR);
        }
        strip.show();
        delay(250);
    } else if(color == WARNING_COLOR) {
        for(int j = 0; j < 3; j++) {
            for(int i = 0; i < PIXELS; i++) {
                strip.setPixelColor(i, OFF_COLOR);
                strip.setPixelColor((i + 1) % PIXELS, WARNING_COLOR);
                strip.setPixelColor((i + 2) % PIXELS, WARNING_COLOR);
                strip.show();
                delay(2);
            }
        }
    } else if(color == SUCCESS_COLOR) {
        rtcErrorShown = false;
        for(int j = 0; j < 2; j++) {
            for(int i = 0; i < PIXELS; i++) {
                strip.setPixelColor(i, OFF_COLOR);
            }
            strip.show();
            delay(100);
            
            for(int i = 0; i < PIXELS; i += 3) {
                strip.setPixelColor(i, SUCCESS_COLOR);
            }
            strip.show();
            delay(100);
            
            for(int i = 0; i < PIXELS; i++) {
                strip.setPixelColor(i, OFF_COLOR);
            }
            strip.show();
            delay(100);
        }
    }
    
    strip.setBrightness(oldBrightness);
}

void checkRTCStatus() {
    static uint8_t failCount = 0;
    
    if(millis() - lastCheck > 10000) {
        lastCheck = millis();
        
        if(rtcWorking) {
            DateTime current = RTC.now();
            
            boolean timeChanged = (current.second() != previousReading.second()) || 
                               (current.minute() != previousReading.minute());
                               
            boolean validTime = (current.year() >= 2000) && 
                            (current.month() >= 1 && current.month() <= 12) &&
                            (current.day() >= 1 && current.day() <= 31);
            
            if(!timeChanged || !validTime) {
                failCount++;
                
                if(failCount >= 3) {
                    rtcWorking = false;
                    
                    fallbackHour = previousReading.hour();
                    fallbackMinute = previousReading.minute();
                    fallbackSecond = previousReading.second();
                    lastSecondMillis = millis();
                    
                    showDiagnosticPattern(ERROR_COLOR);
                }
            } else {
                failCount = 0;
                previousReading = current;
            }
        }
    }
}

void delayAndCheckButtons(uint16_t time) {
    while(time > 20) {
        checkNeedToPerformAction();
        delay(20);
        time-=20;
    }
    checkNeedToPerformAction();
    delay(time);
}

void checkNeedToPerformAction() {
    static unsigned long lastButtonDebug = 0;
    if(millis() - lastButtonDebug >= 1000) {
        Serial.print("Button States - Hour: ");
        Serial.print(digitalRead(HOUR_BUTTON));
        Serial.print(" Minute: ");
        Serial.print(digitalRead(MINUTE_BUTTON));
        Serial.print(" Brightness: ");
        Serial.print(digitalRead(BRIGHTNESS_BUTTON));
        Serial.print(" Mode: ");
        Serial.println(digitalRead(MODE_BUTTON));
        lastButtonDebug = millis();
    }

    if(digitalRead(HOUR_BUTTON) == LOW && digitalRead(BRIGHTNESS_BUTTON) == LOW) {
        Serial.println("Hour + Brightness buttons pressed - Reset mode");
        if(millis() - lastClearTime >= SETTING_RATE_LIMIT) {
            Serial.println("Resetting to defaults");
            clearEEPROM();
            resetToDefaults();
            lastClearTime = millis();
        }
        return;
    }

    if(digitalRead(MODE_BUTTON) == LOW) {
        Serial.println("Mode button pressed");
        if(millis() - lastActionTime[2] >= 50) {
            currentSettingMode = (SettingMode)((currentSettingMode + 1) % 3);
            Serial.print("Setting mode changed to: ");
            switch(currentSettingMode) {
                case SETTING_BRIGHTNESS: Serial.println("Brightness"); break;
                case SETTING_MODE: Serial.println("Display Mode"); break;
                case SETTING_COLOR_SCHEME: Serial.println("Color Scheme"); break;
            }
            showSettingIndicator(currentSettingMode);
            lastActionTime[2] = millis();
        }
        return;
    }

    if(digitalRead(BRIGHTNESS_BUTTON) == LOW) {
        Serial.println("Brightness button pressed");
        if(millis() - lastActionTime[3] >= SETTING_RATE_LIMIT) {
            switch(currentSettingMode) {
                case SETTING_BRIGHTNESS:
                    currentBrightnessLevel = (currentBrightnessLevel + 1) % (sizeof(brightnessLevels)/sizeof(brightnessLevels[0]));
                    Serial.print("Brightness level changed to: ");
                    Serial.println(currentBrightnessLevel);
                    updateBrightness();
                    brightnessChanged = true;
                    saveSettings();
                    break;
                    
                case SETTING_MODE:
                    currentMode = (currentMode + 1) % MODES_PER_SCHEME;
                    Serial.print("Display mode changed to: ");
                    Serial.println(currentMode);
                    modeChanged = true;
                    saveSettings();
                    renderClockFace();
                    break;
                    
                case SETTING_COLOR_SCHEME:
                    currentColorScheme = (currentColorScheme + 1) % COLOR_SCHEME_COUNT;
                    Serial.print("Color scheme changed to: ");
                    Serial.println(currentColorScheme);
                    EEPROM.write(EEPROM_COLOR_SCHEME_ADDR, currentColorScheme);
                    renderClockFace();
                    break;
            }
            lastActionTime[3] = millis();
        }
        return;
    }

    for(uint8_t i = 0; i < 2; i++) {
        int reading = digitalRead(BUTTON_PINS[i]);
        
        if(reading != lastButtonState[i]) {
            Serial.print(i == 0 ? "Hour" : "Minute");
            Serial.print(" button state changed to: ");
            Serial.println(reading == LOW ? "LOW" : "HIGH");
        }
        
        if(reading == LOW) {
            unsigned long rateLimit = (i == 0) ? HOUR_RATE_LIMIT : MINUTE_RATE_LIMIT;
            
            if(millis() - lastActionTime[i] >= rateLimit) {
                Serial.print(i == 0 ? "Hour" : "Minute");
                Serial.println(" button pressed");
                performAction(BUTTON_PINS[i]);
                lastActionTime[i] = millis();
            }
        }
        
        lastButtonState[i] = reading;
    }
}

void performAction(uint8_t buttonPin) {
    if(rtcWorking) {
        DateTime oldTime = now;
        
        if(buttonPin == HOUR_BUTTON) {
            uint8_t hour = now.hour() + 1;
            if(hour >= 24) hour = 0;
            now = DateTime(now.year(), now.month(), now.day(), hour, 
                now.minute(), now.second());
            Serial.print("Hour adjusted to: ");
            Serial.println(hour);
        }
        else if(buttonPin == MINUTE_BUTTON) {
            uint8_t minute = now.minute() + 1;
            if(minute > 59) minute = 0;
            now = DateTime(now.year(), now.month(), now.day(), now.hour(), 
                minute, now.second());
            Serial.print("Minute adjusted to: ");
            Serial.println(minute);
        }
        else if(buttonPin == BRIGHTNESS_BUTTON) {
            currentBrightnessLevel = (currentBrightnessLevel + 1) % (sizeof(brightnessLevels)/sizeof(brightnessLevels[0]));
            Serial.print("Brightness level changed to: ");
            Serial.println(currentBrightnessLevel);
            updateBrightness();
            brightnessChanged = true;
            saveSettings();
        }
        else if(buttonPin == MODE_BUTTON) {
            currentMode = (currentMode + 1) % MODES_PER_SCHEME;
            Serial.print("Display mode changed to: ");
            Serial.println(currentMode);
            modeChanged = true;
            saveSettings();
        }
        
        if(buttonPin == HOUR_BUTTON || buttonPin == MINUTE_BUTTON) {
            RTC.adjust(now);
            delay(10);
            
            DateTime verify = RTC.now();
            if(verify.hour() != now.hour() || verify.minute() != now.minute()) {
                Serial.println("RTC adjustment failed!");
                showDiagnosticPattern(ERROR_COLOR);
                now = oldTime;
            } else {
                Serial.println("RTC adjustment successful");
            }
        }
    } else {
        if(buttonPin == HOUR_BUTTON) {
            fallbackHour++;
            if(fallbackHour >= 24) fallbackHour = 0;
            Serial.print("Fallback hour adjusted to: ");
            Serial.println(fallbackHour);
        }
        else if(buttonPin == MINUTE_BUTTON) {
            fallbackMinute++;
            if(fallbackMinute >= 60) fallbackMinute = 0;
            Serial.print("Fallback minute adjusted to: ");
            Serial.println(fallbackMinute);
        }
        else if(buttonPin == BRIGHTNESS_BUTTON) {
            currentBrightnessLevel = (currentBrightnessLevel + 1) % (sizeof(brightnessLevels)/sizeof(brightnessLevels[0]));
            Serial.print("Brightness level changed to: ");
            Serial.println(currentBrightnessLevel);
            updateBrightness();
            brightnessChanged = true;
            saveSettings();
        }
        else if(buttonPin == MODE_BUTTON) {
            currentMode = (currentMode + 1) % MODES_PER_SCHEME;
            Serial.print("Display mode changed to: ");
            Serial.println(currentMode);
            modeChanged = true;
            saveSettings();
        }
        
        now = DateTime(2020, 1, 1, fallbackHour, fallbackMinute, fallbackSecond);
    }

    clearStrip();
    strip.show();
    renderClockFace();
    delay(100);
}

void updateFallbackTime() {
    unsigned long currentMillis = millis();
    
    if(currentMillis - lastSecondMillis >= 1000) {
        lastSecondMillis = currentMillis;
        fallbackSecond++;
        
        if(fallbackSecond >= 60) {
            fallbackSecond = 0;
            fallbackMinute++;
            
            if(fallbackMinute >= 60) {
                fallbackMinute = 0;
                fallbackHour++;
                
                if(fallbackHour >= 24) {
                    fallbackHour = 0;
                }
            }
        }
        
        now = DateTime(2020, 1, 1, fallbackHour, fallbackMinute, fallbackSecond);
    }
}

void updateBrightness() {
    strip.setBrightness(brightnessLevels[currentBrightnessLevel]);
    renderClockFace();
}

void saveSettings() {
    if(brightnessChanged) {
        EEPROM.write(EEPROM_BRIGHTNESS_ADDR, currentBrightnessLevel);
        brightnessChanged = false;
    }
    if(modeChanged) {
        EEPROM.write(EEPROM_MODE_ADDR, currentMode);
        modeChanged = false;
    }
}

void clearStrip() {
    ledStrip.clear();
}

void renderClockFace() {
    clearStrip();
    
    const ColorScheme& scheme = colorSchemes[currentColorScheme];
    
    // Draw clock face first (lowest priority)
    if(currentMode == MODE_HANDS_WITH_FIFTHS || currentMode == MODE_HANDS_WITH_ALL_MARKERS) {
        for(int i = 0; i < 60; i += 5) {
            ledStrip.setPixelColor(i, scheme.markerColor);
        }
    }
    
    if(currentMode == MODE_HANDS_WITH_ALL_MARKERS) {
        uint8_t r = ((uint32_t)scheme.markerColor >> 16 & 0xFF) * MINUTE_MARKER_BRIGHTNESS_RATIO;
        uint8_t g = ((uint32_t)scheme.markerColor >> 8 & 0xFF) * MINUTE_MARKER_BRIGHTNESS_RATIO;
        uint8_t b = ((uint32_t)scheme.markerColor & 0xFF) * MINUTE_MARKER_BRIGHTNESS_RATIO;
        uint32_t MINUTE_MARKER_COLOR = strip.Color(r, g, b);

        for(int i = 0; i < 60; i++) {
            if(i % 5 != 0) {
                ledStrip.setPixelColor(i, MINUTE_MARKER_COLOR);
            }
        }
    }
    
    // Draw minute hand (medium priority)
    uint8_t minutes = now.minute();
    float percent = minutes / 60.0;
    minutes = forward(minutes, ROTATE * 5);
    uint8_t start = minutes;

    for(volatile uint8_t i = 0; i < MINUTE_LED_COUNT; i++) {
        ledStrip.setPixelColor(minutes, scheme.minuteColor);
        minutes = seekBackward(start, i + 1);
    }

    // Draw hour hand last (highest priority)
    uint8_t hours = (now.hour() % 12) * 5;
    hours = forward(hours, ROTATE * 5);
    float hourPercent = (float)minutes / 60.0;
    hours += (uint8_t)(5.0 * hourPercent);
    start = hours;

    for(volatile uint8_t i = 0; i < HOUR_LED_COUNT; i++) { 
        ledStrip.setPixelColor(hours, scheme.hourColor);
        hours = seekBackward(start, i + 1); 
    }

    ledStrip.show();
}

void animateSecond(uint8_t start, uint8_t count, uint8_t _end) {
    uint8_t add = (float)_end / count;
    uint8_t brightness = add;
    uint16_t _delay = (500 / count) - 1;

    while(count > 0) {
        uint8_t led = seekBackward(start, count);
        uint32_t color = strip.Color(brightness, 0, brightness / 2);
        ledStrip.setPixelColor(led, color, false);
        ledStrip.show();
        delayAndCheckButtons(_delay);
        if(count > 1) {
            ledStrip.setPixelColor(led, ledStrip.getPixelHistory(led), false);
            ledStrip.show();
        }
        count--;
        brightness += add;
    }
}

uint8_t forward(uint8_t value, uint8_t steps) {
    return (value + steps) % 60;
}

uint8_t seekBackward(uint8_t pos_, uint8_t count) {
    int8_t pos = pos_; 
    pos -= count % PIXELS;
    if(pos < 0) pos += 60;
    return pos;
}

void loop() {
    checkRTCStatus();
    
    if(rtcWorking) {
        now = RTC.now();  

        if(syncLoop) {
            uint8_t start = now.second();
            while(now.second() == start) {
                now = RTC.now();
                checkNeedToPerformAction();
            }
            syncLoop = false;
            loopCount = 0;
        }
    } else {
        updateFallbackTime();
    }

    clearStrip();
    renderClockFace();

    bool anyButtonPressed = false;
    for(uint8_t i = 0; i < 4; i++) {
        if(digitalRead(BUTTON_PINS[i]) == LOW) {
            anyButtonPressed = true;
            break;
        }
    }

    if(!anyButtonPressed) {
        uint8_t seconds = now.second();
        seconds = forward(seconds, ROTATE * 5);
        animateSecond(seconds, SECOND_LED_COUNT, MAX_BRIGHTNESS);
    }
    
    delayAndCheckButtons(500);

    saveSettings();

    loopCount++;
    if(loopCount >= SYNC_MAX) {
        syncLoop = true;
    }
}

void clearEEPROM() {
    for(int i = 0; i < 10; i++) {
        EEPROM.write(i, 0);
    }
    
    for(int i = 0; i < PIXELS; i++) {
        strip.setPixelColor(i, strip.Color(64, 0, 0));
    }
    strip.show();
    delay(800);
    
    clearStrip();
    strip.show();
    delay(700);
}

void showSettingIndicator(SettingMode kind) {
    clearStrip();
    
    switch(kind) {
        case SETTING_BRIGHTNESS:
            for(int i = 0; i < PIXELS; i++) {
                uint8_t brightness = (i * 255) / (PIXELS / 4);
                if(brightness > 255) brightness = 255;
                strip.setPixelColor(i, strip.Color(brightness, brightness, 0));
            }
            break;
            
        case SETTING_MODE:
            for(int i = 0; i < PIXELS; i++) {
                if(i % 10 < 5) {
                    strip.setPixelColor(i, strip.Color(0, 255, 0));
                }
            }
            break;
            
        case SETTING_COLOR_SCHEME:
            for(int i = 0; i < PIXELS; i++) {
                uint8_t hue = (i * 255) / PIXELS;
                uint8_t r, g, b;
                
                if(hue < 85) {
                    r = hue * 3;
                    g = 255 - hue * 3;
                    b = 0;
                } else if(hue < 170) {
                    hue -= 85;
                    r = 255 - hue * 3;
                    g = 0;
                    b = hue * 3;
                } else {
                    hue -= 170;
                    r = 0;
                    g = hue * 3;
                    b = 255 - hue * 3;
                }
                
                strip.setPixelColor(i, strip.Color(r, g, b));
            }
            break;
    }
    
    strip.show();
    delay(500);
    renderClockFace();
}
