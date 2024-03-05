//
// Created by Ollin Ruiz on 1/18/24.
//
#include "FastLED.h"
#include "FastLED_RGBW.h"

#if ESP32
//Define LED1 color pins
#ifndef PIN_RED1
#define PIN_RED1   32
#endif
#ifndef PIN_GREEN1
#define PIN_GREEN1 33
#endif
#ifndef PIN_BLUE1
#define PIN_BLUE1  25
#endif

//Define LED2 color pins
#ifndef PIN_RED2
#define PIN_RED2   26
#endif
#ifndef PIN_GREEN2
#define PIN_GREEN2 27
#endif
#ifndef PIN_BLUE2
#define PIN_BLUE2  14
#endif

#else // ESP8266
//Define LED1 color pins
#ifndef PIN_RED1
#define PIN_RED1    16 // D0
#endif
#ifndef PIN_GREEN1
#define PIN_GREEN1  4  // D2
#endif
#ifndef PIN_BLUE1
#define PIN_BLUE1   5  // D1
#endif

//Define LED2 color pins
#ifndef PIN_RED2
#define PIN_RED2    2  // D4
#endif
#ifndef PIN_GREEN2
#define PIN_GREEN2  14 // D5
#endif
#ifndef PIN_BLUE2
#define PIN_BLUE2   12 // D6
#endif
#endif

//Define LED colors
#define LED_OFF     0
#define LED_RED     1
#define LED_GREEN   2
#define LED_BLUE    3
#define LED_YELLOW  4
#define LED_PINK    5
#define LED_WHITE   6
#define LED_ORANGE  7

//FastLED
#ifndef TALLY_DATA_PIN
#if ESP32
#define TALLY_DATA_PIN    6
#elif ARDUINO_ESP8266_NODEMCU
#define TALLY_DATA_PIN    7
#else
#define TALLY_DATA_PIN    13 // D7
#endif
#endif

//Define states
#define STATE_STARTING                  0
#define STATE_CONNECTING_TO_WIFI        1
#define STATE_CONNECTING_TO_SWITCHER    2
#define STATE_RUNNING                   3

//Define modes of operation
#define MODE_NORMAL                     1
#define MODE_PREVIEW_STAY_ON            2
#define MODE_PROGRAM_ONLY               3
#define MODE_ON_AIR                     4

#define TALLY_FLAG_OFF                  0
#define TALLY_FLAG_PROGRAM              1
#define TALLY_FLAG_PREVIEW              2

//Define Neopixel status-LED options
#define NEOPIXEL_STATUS_FIRST           1
#define NEOPIXEL_STATUS_LAST            2
#define NEOPIXEL_STATUS_NONE            3

//Map "old" LED colors to CRGB colors
extern const CRGB color_led[8];

class ATEM_LED_Controller {
protected:
    int* numTallyLEDs{};
    int* numStatusLEDs{};
    CRGBW* tallyLEDs{};
    CRGBW* statusLED{};
    bool* neopixelsUpdated{};

public:
    inline ATEM_LED_Controller() = default;
    void setSTRIP(uint8_t color);
    void setStatusLED(uint8_t color);
    void begin(int*, int*, CRGBW*, CRGBW*, bool*);

#ifdef DEBUG_LED_STRIP
    void printLeds();
#endif
};