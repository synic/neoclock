#define PIXELS 60
#define NEOPIXEL_PIN 9
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
#define DIAGNOSTIC_BRIGHTNESS 90
#define MINUTE_MARKER_BRIGHTNESS_RATIO 0.20
#define COMMON_GROUND 0
#define HOUR_BUTTON 2
#define MINUTE_BUTTON 1
#define BRIGHTNESS_BUTTON 3
#define MODE_BUTTON 4
#define ROTATE 0
#define COLOR_SCHEME_COUNT 11
#define MODES_PER_SCHEME 3
#define MODE_HANDS_ONLY 0
#define MODE_HANDS_WITH_FIFTHS 1
#define MODE_HANDS_WITH_ALL_MARKERS 2
#define MINUTE_LED_COUNT 2
#define HOUR_LED_COUNT 1
#define SECOND_LED_COUNT 18

#include <FastLED.h>
#include <Wire.h>
#include <RTClib.h>
#include <EEPROM.h>

class SerialWrapper
{
private:
    bool initialized = false;

    void ensureInitialized()
    {
        if (!initialized)
        {
            Serial.begin(9600); // More reliable baud rate for Metro
            delay(2000);        // Longer delay for Metro's USB serial to stabilize
            Serial.println();
            Serial.println("Serial initialized");
            initialized = true;
        }
    }

public:
    void print(const char *str)
    {
        ensureInitialized();
        Serial.print(str);
        Serial.flush(); // Ensure data is sent
    }

    void println(const char *str)
    {
        ensureInitialized();
        Serial.println(str);
        Serial.flush(); // Ensure data is sent
    }

    void print(int val)
    {
        ensureInitialized();
        Serial.print(val);
        Serial.flush(); // Ensure data is sent
    }

    void println(int val)
    {
        ensureInitialized();
        Serial.println(val);
        Serial.flush(); // Ensure data is sent
    }

    void print(byte val, int format)
    {
        ensureInitialized();
        Serial.print(val, format);
        Serial.flush(); // Ensure data is sent
    }

    void println(byte val, int format)
    {
        ensureInitialized();
        Serial.println(val, format);
        Serial.flush(); // Ensure data is sent
    }
};

SerialWrapper Debug;

class LEDStrip
{
private:
    CRGB *leds;
    CRGB *pixelHistory;
    bool *pixelDirty;
    const uint16_t pixelCount;
    uint8_t currentBrightness;

public:
    LEDStrip(uint16_t numPixels) : pixelCount(numPixels)
    {
        leds = new CRGB[pixelCount];
        pixelHistory = new CRGB[pixelCount];
        pixelDirty = new bool[pixelCount];
        currentBrightness = 255;

        for (uint16_t i = 0; i < pixelCount; i++)
        {
            pixelHistory[i] = CRGB::Black;
            pixelDirty[i] = false;
        }
    }

    ~LEDStrip()
    {
        delete[] leds;
        delete[] pixelHistory;
        delete[] pixelDirty;
    }

    void setPixelColor(uint16_t n, CRGB color, bool saveToHistory = true)
    {
        if (saveToHistory)
        {
            pixelHistory[n] = color;
            pixelDirty[n] = true;
        }
        leds[n] = color;
    }

    CRGB getPixelColor(uint16_t n)
    {
        return leds[n];
    }

    CRGB getPixelHistory(uint16_t n)
    {
        return pixelHistory[n];
    }

    void show()
    {
        FastLED.show();
    }

    void clear()
    {
        for (uint16_t i = 0; i < pixelCount; i++)
        {
            pixelDirty[i] = false;
            pixelHistory[i] = CRGB::Black;
        }
        FastLED.clear();
    }

    void begin()
    {
        FastLED.setBrightness(currentBrightness);
    }

    void setBrightness(uint8_t b)
    {
        currentBrightness = b;
        FastLED.setBrightness(b);
    }

    uint8_t getBrightness()
    {
        return currentBrightness;
    }

    uint16_t numPixels()
    {
        return pixelCount;
    }

    // Helper function to convert RGB values to CRGB
    static CRGB Color(uint8_t r, uint8_t g, uint8_t b)
    {
        return CRGB(r, g, b);
    }

    CRGB *getLeds()
    {
        return leds;
    }
};

LEDStrip strip(PIXELS);
RTC_DS3231 RTC;

CRGB OFF_COLOR = CRGB::Black;
CRGB ERROR_COLOR = CRGB(255, 32, 32);
CRGB I2C_ERROR_COLOR = CRGB(0, 255, 128);
CRGB BUTTON_ERROR_COLOR = CRGB(128, 0, 128);
CRGB RTC_ERROR_COLOR = CRGB(255, 0, 0);
CRGB WARNING_COLOR = CRGB(255, 128, 0);

struct ColorScheme
{
    CRGB markerColor;
    CRGB hourColor;
    CRGB minuteColor;
    CRGB secondColor;
};

const ColorScheme colorSchemes[COLOR_SCHEME_COUNT] = {
    // Default - Purple markers, green/blue hands
    {
        CRGB(51, 0, 51),   // marker
        CRGB(153, 204, 0), // hour
        CRGB(0, 159, 255), // minute
        CRGB(0, 0, 255)    // second
    },
    // Sunset - Orange markers, blue/teal hands
    {
        CRGB(255, 128, 0), // marker
        CRGB(0, 128, 255), // hour
        CRGB(0, 255, 255), // minute
        CRGB(0, 128, 128)  // second
    },
    // Forest - Green markers, red/pink hands
    {
        CRGB(0, 128, 0),   // marker
        CRGB(255, 0, 0),   // hour
        CRGB(255, 0, 128), // minute
        CRGB(128, 0, 64)   // second
    },
    // Ocean - Teal markers, orange/yellow hands
    {
        CRGB(0, 128, 128), // marker
        CRGB(255, 128, 0), // hour
        CRGB(255, 255, 0), // minute
        CRGB(128, 128, 0)  // second
    },
    // Royal - Gold markers, purple/blue hands
    {
        CRGB(255, 215, 0), // marker
        CRGB(128, 0, 255), // hour
        CRGB(0, 0, 255),   // minute
        CRGB(64, 0, 128)   // second
    },
    // Neon - Pink markers, cyan/green hands
    {
        CRGB(255, 0, 255), // marker
        CRGB(0, 255, 255), // hour
        CRGB(0, 255, 128), // minute
        CRGB(0, 128, 255)  // second
    },
    // Autumn - Brown markers, sky blue/light blue hands
    {
        CRGB(139, 69, 19),   // marker
        CRGB(135, 206, 235), // hour
        CRGB(173, 216, 230), // minute
        CRGB(176, 224, 230)  // second
    },
    // Winter - Silver markers, deep blue/light blue hands
    {
        CRGB(192, 192, 192), // marker
        CRGB(0, 0, 139),     // hour
        CRGB(0, 0, 205),     // minute
        CRGB(0, 0, 255)      // second
    },
    // Fire - Red markers, orange/yellow hands
    {
        CRGB(255, 0, 0),   // marker
        CRGB(255, 128, 0), // hour
        CRGB(255, 255, 0), // minute
        CRGB(255, 200, 0)  // second
    },
    // Mint - Mint markers, teal/blue hands
    {
        CRGB(152, 255, 152), // marker
        CRGB(0, 128, 128),   // hour
        CRGB(0, 0, 255),     // minute
        CRGB(0, 64, 128)     // second
    },
    // Lavender - Purple markers, pink/red hands
    {
        CRGB(230, 230, 250), // marker
        CRGB(255, 192, 203), // hour
        CRGB(255, 0, 0),     // minute
        CRGB(128, 0, 0)      // second
    }};

const uint8_t brightnessLevels[] = {
    20,  // Level 0: Night mode
    40,  // Level 1: Very dim
    60,  // Level 2: Dim
    102, // Level 4: Medium-low
    153, // Level 5: Medium
    200  // Level 7: Full brightness
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

enum SettingMode
{
    SETTING_BRIGHTNESS,
    SETTING_MODE,
    SETTING_COLOR_SCHEME
};

SettingMode currentSettingMode = SETTING_BRIGHTNESS;

void resetToDefaults()
{
    currentBrightnessLevel = DEFAULT_BRIGHTNESS_LEVEL;
    currentMode = MODE_HANDS_WITH_FIFTHS;
    currentColorScheme = 0;
    brightnessChanged = true;
    modeChanged = true;
    saveSettings();
}

void setup()
{
    FastLED.addLeds<WS2812B, NEOPIXEL_PIN, GRB>(strip.getLeds(), PIXELS);
    strip.begin();
    strip.clear();
    strip.show();

    pinMode(COMMON_GROUND, OUTPUT);
    digitalWrite(COMMON_GROUND, LOW);

    for (uint8_t i = 0; i < 4; i++)
    {
        pinMode(BUTTON_PINS[i], INPUT_PULLUP);
    }

    uint8_t storedBrightness = EEPROM.read(EEPROM_BRIGHTNESS_ADDR);
    if (storedBrightness < sizeof(brightnessLevels) / sizeof(brightnessLevels[0]))
    {
        currentBrightnessLevel = storedBrightness;
    }
    else
    {
        currentBrightnessLevel = DEFAULT_BRIGHTNESS_LEVEL;
        EEPROM.write(EEPROM_BRIGHTNESS_ADDR, currentBrightnessLevel);
    }

    uint8_t storedMode = EEPROM.read(EEPROM_MODE_ADDR);
    if (storedMode < MODES_PER_SCHEME)
    {
        currentMode = storedMode;
    }
    else
    {
        currentMode = MODE_HANDS_WITH_FIFTHS;
        EEPROM.write(EEPROM_MODE_ADDR, currentMode);
    }

    uint8_t storedColorScheme = EEPROM.read(EEPROM_COLOR_SCHEME_ADDR);
    if (storedColorScheme < COLOR_SCHEME_COUNT)
    {
        currentColorScheme = storedColorScheme;
    }
    else
    {
        currentColorScheme = 0;
        EEPROM.write(EEPROM_COLOR_SCHEME_ADDR, currentColorScheme);
    }

    strip.setBrightness(DIAGNOSTIC_BRIGHTNESS);
    for (int i = 0; i < PIXELS; i++)
    {
        strip.setPixelColor(i, LEDStrip::Color(51, 0, 51), false);
        strip.show();
        delayAndCheckButtons(4);
    }
    for (int i = 0; i < PIXELS; i++)
    {
        strip.setPixelColor(i, OFF_COLOR, false);
        strip.show();
        delayAndCheckButtons(4);
    }

    runRTCDiagnostics();

    for (uint8_t i = 0; i < 4; i++)
    {
        if (digitalRead(BUTTON_PINS[i]) != HIGH)
        {
            strip.setBrightness(DIAGNOSTIC_BRIGHTNESS);
            for (int j = 0; j < PIXELS; j++)
            {
                strip.setPixelColor(j, BUTTON_ERROR_COLOR, false);
            }
            strip.show();
            delayAndCheckButtons(100);
            for (int i = 0; i < PIXELS; i++)
            {
                strip.setPixelColor(i, OFF_COLOR, false);
            }
            strip.show();
        }
    }

    if (!rtcWorking)
    {
        Debug.println("RTC not working, using fallback time");
        fallbackHour = 12;
        fallbackMinute = 0;
        fallbackSecond = 0;
        now = DateTime(2020, 1, 1, fallbackHour, fallbackMinute, fallbackSecond);
        previousReading = now;
    }
    else
    {
        now = RTC.now();
        previousReading = now;
    }

    lastSecondMillis = millis();

    updateBrightness();
    renderClockFace();
}

void runRTCDiagnostics()
{
    // Start with a clean I2C bus
    Wire.end();
    delay(100);

    // Initialize with very slow clock
    Wire.begin();
    Wire.setClock(10000); // 10kHz
    delay(100);

    int deviceCount = 0;
    byte error;

    // First do a basic I2C scan
    for (byte address = 1; address < 127; address++)
    {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        delay(5); // Small delay between addresses

        if (error == 0)
        {
            deviceCount++;
        }
    }

    if (deviceCount == 0)
    {
        Debug.println("No I2C devices found in initial scan!");
        showDiagnosticPattern(I2C_ERROR_COLOR);
        rtcWorking = false;
        return;
    }

    // Try to read the seconds register first (simplest operation)
    Wire.beginTransmission(0x68);
    Wire.write(0x00); // Seconds register
    error = Wire.endTransmission();
    delay(10); // Longer delay after write

    if (error == 0)
    {
        if (Wire.requestFrom((uint8_t)0x68, (uint8_t)1) == 1)
        {
            byte seconds = Wire.read();

            // Now try to read control register
            Wire.beginTransmission(0x68);
            Wire.write(0x07); // Control register
            error = Wire.endTransmission();
            delay(10);

            if (error == 0)
            {
                if (Wire.requestFrom((uint8_t)0x68, (uint8_t)1) == 1)
                {
                    byte control = Wire.read();

                    // Check if oscillator is running
                    if (control & 0x80)
                    {
                        Debug.println("Oscillator is stopped!");
                        // Try to start the oscillator
                        Wire.beginTransmission(0x68);
                        Wire.write(0x07);
                        Wire.write(control & 0x7F); // Clear bit 7
                        error = Wire.endTransmission();
                        delay(10);

                        if (error == 0)
                        {
                            Debug.println("Oscillator started");
                        }
                    }
                }
            }
        }
    }
    else
    {
        Debug.print("Failed to communicate with DS1307, error: ");
        Debug.println(error);
        showDiagnosticPattern(I2C_ERROR_COLOR);
        rtcWorking = false;
        return;
    }

    // Now try to initialize the RTC
    if (!RTC.begin())
    {
        Debug.println("RTC initialization failed!");
        showDiagnosticPattern(RTC_ERROR_COLOR);
        rtcWorking = false;
        return;
    }

    rtcWorking = true;
}

void showDiagnosticPattern(CRGB color)
{
    static bool rtcErrorShown = false;
    uint8_t oldBrightness = strip.getBrightness();
    strip.setBrightness(DIAGNOSTIC_BRIGHTNESS);

    Debug.print("Showing diagnostic pattern: ");
    if (color == ERROR_COLOR)
        Debug.println("ERROR");
    else if (color == I2C_ERROR_COLOR)
        Debug.println("I2C ERROR");
    else if (color == RTC_ERROR_COLOR)
        Debug.println("RTC ERROR");
    else if (color == WARNING_COLOR)
        Debug.println("WARNING");

    for (int i = 0; i < PIXELS; i++)
    {
        strip.setPixelColor(i, OFF_COLOR, false);
    }
    strip.show();
    delay(250);

    if (color == ERROR_COLOR)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int i = 0; i < PIXELS; i++)
            {
                strip.setPixelColor(i, (i % 2 == 0) ? ERROR_COLOR : OFF_COLOR, false);
            }
            strip.show();
            delay(250);
            for (int i = 0; i < PIXELS; i++)
            {
                strip.setPixelColor(i, (i % 2 == 1) ? ERROR_COLOR : OFF_COLOR, false);
            }
            strip.show();
            delay(250);
        }
    }
    else if (color == I2C_ERROR_COLOR)
    {
        for (int i = 0; i < PIXELS; i++)
        {
            strip.setPixelColor(i, OFF_COLOR, false);
            strip.setPixelColor((i + 1) % PIXELS, I2C_ERROR_COLOR, false);
            strip.show();
            delay(20);
        }
    }
    else if (color == RTC_ERROR_COLOR && !rtcErrorShown)
    {
        rtcErrorShown = true;
        for (int i = 0; i < PIXELS; i++)
        {
            strip.setPixelColor(i, OFF_COLOR, false);
        }
        strip.show();
        delay(250);

        for (int i = 0; i < PIXELS; i++)
        {
            strip.setPixelColor(i, OFF_COLOR, false);
            strip.setPixelColor((i + 1) % PIXELS, RTC_ERROR_COLOR, false);
            strip.show();
            delay(20);
        }

        for (int i = 0; i < PIXELS; i++)
        {
            strip.setPixelColor(i, OFF_COLOR, false);
        }
        strip.show();
        delay(250);
    }
    else if (color == WARNING_COLOR)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int i = 0; i < PIXELS; i++)
            {
                strip.setPixelColor(i, OFF_COLOR, false);
                strip.setPixelColor((i + 1) % PIXELS, WARNING_COLOR, false);
                strip.setPixelColor((i + 2) % PIXELS, WARNING_COLOR, false);
                strip.show();
                delay(2);
            }
        }
    }

    strip.setBrightness(oldBrightness);
}

void checkRTCStatus()
{
    static uint8_t failCount = 0;

    if (millis() - lastCheck > 10000)
    {
        lastCheck = millis();

        if (rtcWorking)
        {
            DateTime current = RTC.now();

            boolean timeChanged = (current.second() != previousReading.second()) ||
                                  (current.minute() != previousReading.minute());

            boolean validTime = (current.year() >= 2000) &&
                                (current.month() >= 1 && current.month() <= 12) &&
                                (current.day() >= 1 && current.day() <= 31);

            if (!timeChanged || !validTime)
            {
                failCount++;

                if (failCount >= 3)
                {
                    rtcWorking = false;
                    Debug.println("RTC failed after multiple attempts");

                    fallbackHour = previousReading.hour();
                    fallbackMinute = previousReading.minute();
                    fallbackSecond = previousReading.second();
                    lastSecondMillis = millis();

                    showDiagnosticPattern(ERROR_COLOR);
                }
            }
            else
            {
                failCount = 0;
                previousReading = current;
            }
        }
    }
}

void delayAndCheckButtons(uint16_t time)
{
    while (time > 20)
    {
        checkNeedToPerformAction();
        delay(20);
        time -= 20;
    }
    checkNeedToPerformAction();
    delay(time);
}

void checkNeedToPerformAction()
{
    if (digitalRead(HOUR_BUTTON) == LOW && digitalRead(BRIGHTNESS_BUTTON) == LOW)
    {
        if (millis() - lastClearTime >= SETTING_RATE_LIMIT)
        {
            clearEEPROM();
            resetToDefaults();
            lastClearTime = millis();
        }
        return;
    }

    if (digitalRead(MODE_BUTTON) == LOW)
    {
        if (millis() - lastActionTime[2] >= 50)
        {
            currentSettingMode = (SettingMode)((currentSettingMode + 1) % 3);
            showSettingIndicator(currentSettingMode);
            lastActionTime[2] = millis();
        }
        return;
    }

    if (digitalRead(BRIGHTNESS_BUTTON) == LOW)
    {
        if (millis() - lastActionTime[3] >= SETTING_RATE_LIMIT)
        {
            switch (currentSettingMode)
            {
            case SETTING_BRIGHTNESS:
                currentBrightnessLevel = (currentBrightnessLevel + 1) % (sizeof(brightnessLevels) / sizeof(brightnessLevels[0]));
                updateBrightness();
                brightnessChanged = true;
                saveSettings();
                break;

            case SETTING_MODE:
                currentMode = (currentMode + 1) % MODES_PER_SCHEME;
                modeChanged = true;
                saveSettings();
                renderClockFace();
                break;

            case SETTING_COLOR_SCHEME:
                currentColorScheme = (currentColorScheme + 1) % COLOR_SCHEME_COUNT;
                EEPROM.write(EEPROM_COLOR_SCHEME_ADDR, currentColorScheme);
                renderClockFace();
                break;
            }
            lastActionTime[3] = millis();
        }
        return;
    }

    for (uint8_t i = 0; i < 2; i++)
    {
        int reading = digitalRead(BUTTON_PINS[i]);

        if (reading == LOW)
        {
            unsigned long rateLimit = (i == 0) ? HOUR_RATE_LIMIT : MINUTE_RATE_LIMIT;

            if (millis() - lastActionTime[i] >= rateLimit)
            {
                performAction(BUTTON_PINS[i]);
                lastActionTime[i] = millis();
            }
        }

        lastButtonState[i] = reading;
    }
}

void performAction(uint8_t buttonPin)
{
    if (rtcWorking)
    {
        DateTime oldTime = now;

        if (buttonPin == HOUR_BUTTON)
        {
            uint8_t hour = now.hour() + 1;
            if (hour >= 24)
                hour = 0;
            now = DateTime(now.year(), now.month(), now.day(), hour,
                           now.minute(), now.second());
        }
        else if (buttonPin == MINUTE_BUTTON)
        {
            uint8_t minute = now.minute() + 1;
            if (minute > 59)
                minute = 0;
            now = DateTime(now.year(), now.month(), now.day(), now.hour(),
                           minute, now.second());
        }
        else if (buttonPin == BRIGHTNESS_BUTTON)
        {
            currentBrightnessLevel = (currentBrightnessLevel + 1) % (sizeof(brightnessLevels) / sizeof(brightnessLevels[0]));
            updateBrightness();
            brightnessChanged = true;
            saveSettings();
        }
        else if (buttonPin == MODE_BUTTON)
        {
            currentMode = (currentMode + 1) % MODES_PER_SCHEME;
            modeChanged = true;
            saveSettings();
        }

        if (buttonPin == HOUR_BUTTON || buttonPin == MINUTE_BUTTON)
        {
            RTC.adjust(now);
            delay(10);

            DateTime verify = RTC.now();
            if (verify.hour() != now.hour() || verify.minute() != now.minute())
            {
                Debug.println("RTC adjustment failed!");
                showDiagnosticPattern(ERROR_COLOR);
                now = oldTime;
            }
        }
    }
    else
    {
        if (buttonPin == HOUR_BUTTON)
        {
            fallbackHour++;
            if (fallbackHour >= 24)
                fallbackHour = 0;
        }
        else if (buttonPin == MINUTE_BUTTON)
        {
            fallbackMinute++;
            if (fallbackMinute >= 60)
                fallbackMinute = 0;
        }
        else if (buttonPin == BRIGHTNESS_BUTTON)
        {
            currentBrightnessLevel = (currentBrightnessLevel + 1) % (sizeof(brightnessLevels) / sizeof(brightnessLevels[0]));
            updateBrightness();
            brightnessChanged = true;
            saveSettings();
        }
        else if (buttonPin == MODE_BUTTON)
        {
            currentMode = (currentMode + 1) % MODES_PER_SCHEME;
            modeChanged = true;
            saveSettings();
        }

        now = DateTime(2020, 1, 1, fallbackHour, fallbackMinute, fallbackSecond);
    }

    strip.clear();
    strip.show();
    renderClockFace();
    delay(100);
}

void updateFallbackTime()
{
    unsigned long currentMillis = millis();

    if (currentMillis - lastSecondMillis >= 1000)
    {
        lastSecondMillis = currentMillis;
        fallbackSecond++;

        if (fallbackSecond >= 60)
        {
            fallbackSecond = 0;
            fallbackMinute++;

            if (fallbackMinute >= 60)
            {
                fallbackMinute = 0;
                fallbackHour++;

                if (fallbackHour >= 24)
                {
                    fallbackHour = 0;
                }
            }
        }

        now = DateTime(2020, 1, 1, fallbackHour, fallbackMinute, fallbackSecond);
    }
}

void updateBrightness()
{
    strip.setBrightness(brightnessLevels[currentBrightnessLevel]);
    renderClockFace();
}

void saveSettings()
{
    if (brightnessChanged)
    {
        EEPROM.write(EEPROM_BRIGHTNESS_ADDR, currentBrightnessLevel);
        brightnessChanged = false;
    }
    if (modeChanged)
    {
        EEPROM.write(EEPROM_MODE_ADDR, currentMode);
        modeChanged = false;
    }
}

void renderClockFace()
{
    strip.clear();

    const ColorScheme &scheme = colorSchemes[currentColorScheme];

    // Draw clock face first (lowest priority)
    if (currentMode == MODE_HANDS_WITH_FIFTHS || currentMode == MODE_HANDS_WITH_ALL_MARKERS)
    {
        for (int i = 0; i < 60; i += 5)
        {
            strip.setPixelColor(i, scheme.markerColor);
        }
    }

    if (currentMode == MODE_HANDS_WITH_ALL_MARKERS)
    {
        uint8_t r = ((uint32_t)scheme.markerColor >> 16 & 0xFF) * MINUTE_MARKER_BRIGHTNESS_RATIO;
        uint8_t g = ((uint32_t)scheme.markerColor >> 8 & 0xFF) * MINUTE_MARKER_BRIGHTNESS_RATIO;
        uint8_t b = ((uint32_t)scheme.markerColor & 0xFF) * MINUTE_MARKER_BRIGHTNESS_RATIO;
        CRGB MINUTE_MARKER_COLOR = LEDStrip::Color(r, g, b);

        for (int i = 0; i < 60; i++)
        {
            if (i % 5 != 0)
            {
                strip.setPixelColor(i, MINUTE_MARKER_COLOR);
            }
        }
    }

    // Draw minute hand (medium priority)
    uint8_t minutes = now.minute();
    float percent = minutes / 60.0;
    minutes = forward(minutes, ROTATE * 5);
    uint8_t start = minutes;

    for (volatile uint8_t i = 0; i < MINUTE_LED_COUNT; i++)
    {
        strip.setPixelColor(minutes, scheme.minuteColor);
        minutes = seekBackward(start, i + 1);
    }

    // Draw hour hand last (highest priority)
    uint8_t hours = (now.hour() % 12) * 5;
    hours = forward(hours, ROTATE * 5);
    float hourPercent = (float)minutes / 60.0;
    hours += (uint8_t)(5.0 * hourPercent);
    start = hours;

    for (volatile uint8_t i = 0; i < HOUR_LED_COUNT; i++)
    {
        strip.setPixelColor(hours, scheme.hourColor);
        hours = seekBackward(start, i + 1);
    }

    strip.show();
}

void animateSecond(uint8_t start, uint8_t count, uint8_t _end)
{
    uint8_t add = (float)_end / count;
    uint8_t brightness = add;
    uint16_t _delay = (500 / count) - 1;

    while (count > 0)
    {
        uint8_t led = seekBackward(start, count);
        CRGB color = LEDStrip::Color(brightness, 0, brightness / 2);
        strip.setPixelColor(led, color, false);
        strip.show();
        delayAndCheckButtons(_delay);
        if (count > 1)
        {
            strip.setPixelColor(led, strip.getPixelHistory(led), false);
            strip.show();
        }
        count--;
        brightness += add;
    }
}

uint8_t forward(uint8_t value, uint8_t steps)
{
    return (value + steps) % 60;
}

uint8_t seekBackward(uint8_t pos_, uint8_t count)
{
    int8_t pos = pos_;
    pos -= count % PIXELS;
    if (pos < 0)
        pos += 60;
    return pos;
}

void loop()
{
    checkRTCStatus();

    if (rtcWorking)
    {
        now = RTC.now();

        if (syncLoop)
        {
            uint8_t start = now.second();
            while (now.second() == start)
            {
                now = RTC.now();
                checkNeedToPerformAction();
            }
            syncLoop = false;
            loopCount = 0;
        }
    }
    else
    {
        updateFallbackTime();
    }

    strip.clear();
    renderClockFace();

    bool anyButtonPressed = false;
    for (uint8_t i = 0; i < 4; i++)
    {
        if (digitalRead(BUTTON_PINS[i]) == LOW)
        {
            anyButtonPressed = true;
            break;
        }
    }

    if (!anyButtonPressed)
    {
        uint8_t seconds = now.second();
        seconds = forward(seconds, ROTATE * 5);
        animateSecond(seconds, SECOND_LED_COUNT, MAX_BRIGHTNESS);
    }

    delayAndCheckButtons(500);

    saveSettings();

    loopCount++;
    if (loopCount >= SYNC_MAX)
    {
        syncLoop = true;
    }
}

void clearEEPROM()
{
    for (int i = 0; i < 10; i++)
    {
        EEPROM.write(i, 0);
    }

    for (int i = 0; i < PIXELS; i++)
    {
        strip.setPixelColor(i, LEDStrip::Color(64, 0, 0), false);
    }
    strip.show();
    delay(800);

    strip.clear();
    strip.show();
    delay(700);
}

void showSettingIndicator(SettingMode kind)
{
    strip.clear();

    switch (kind)
    {
    case SETTING_BRIGHTNESS:
        for (int i = 0; i < PIXELS; i++)
        {
            uint8_t brightness = (i * 255) / (PIXELS / 4);
            if (brightness > 255)
                brightness = 255;
            brightness = brightness * 0.6; // Reduce to 60%
            strip.setPixelColor(i, LEDStrip::Color(brightness, brightness, 0), false);
        }
        break;

    case SETTING_MODE:
        for (int i = 0; i < PIXELS; i++)
        {
            if (i % 10 < 5)
            {
                uint8_t brightness = 255 * 0.6; // Reduce to 60%
                strip.setPixelColor(i, LEDStrip::Color(0, brightness, 0), false);
            }
        }
        break;

    case SETTING_COLOR_SCHEME:
        for (int i = 0; i < PIXELS; i++)
        {
            uint8_t hue = (i * 255) / PIXELS;
            uint8_t r, g, b;

            if (hue < 85)
            {
                r = hue * 3;
                g = 255 - hue * 3;
                b = 0;
            }
            else if (hue < 170)
            {
                hue -= 85;
                r = 255 - hue * 3;
                g = 0;
                b = hue * 3;
            }
            else
            {
                hue -= 170;
                r = 0;
                g = hue * 3;
                b = 255 - hue * 3;
            }

            // Reduce all colors to 60%
            r = r * 0.6;
            g = g * 0.6;
            b = b * 0.6;

            strip.setPixelColor(i, LEDStrip::Color(r, g, b), false);
        }
        break;
    }

    strip.show();
    delay(500);
    renderClockFace();
}
