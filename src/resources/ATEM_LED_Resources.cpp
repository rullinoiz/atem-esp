#include "ATEM_LED_Resources.h"

#ifdef DEBUG_LED_STRIP
#include "Arduino.h"
#endif

const CRGB color_led[8] = { CRGB::Black, CRGB::Red, CRGB::Lime, CRGB::Blue, CRGB::Yellow, CRGB::Fuchsia, CRGB::White, CRGB::Orange };

void ATEM_LED_Controller::begin(
        int* _numTallyLEDs, int* _numStatusLEDs,
        CRGBW* _tallyLEDs, CRGBW* _statusLED,
        bool* _neopixelsUpdated) {

    this->numTallyLEDs = _numTallyLEDs;
    this->numStatusLEDs = _numStatusLEDs;
    this->tallyLEDs = _tallyLEDs;
    this->statusLED = _statusLED;
    this->neopixelsUpdated = _neopixelsUpdated;
}

void ATEM_LED_Controller::setSTRIP(uint8_t color) {
    if (*this->numTallyLEDs > 0 && this->tallyLEDs[0] != color_led[color]) {
        for (int i = 0; i < *this->numTallyLEDs; i++) {
            this->tallyLEDs[i] = color_led[color];
        }
        *this->neopixelsUpdated = true;
#ifdef DEBUG_LED_STRIP
        Serial.println("Tally:  ");
        this->printLeds();
#endif
    }
}

void ATEM_LED_Controller::setStatusLED(uint8_t color) {
    if (*this->numStatusLEDs > 0 && this->statusLED[0] != color_led[color]) {
        for (int i = 0; i < *this->numStatusLEDs; i++) {
            this->statusLED[i] = color_led[color];
        }
        *this->neopixelsUpdated = true;
#ifdef DEBUG_LED_STRIP
        Serial.println("Status: ");
        printLeds();
#endif
    }
}

#ifdef DEBUG_LED_STRIP
void ATEM_LED_Controller::printLeds() {
    for (int i = 0; i < settings.neopixelsAmount; i++) {
        Serial.print(i);
        Serial.print(", RGB: ");
        Serial.print(leds[i].r);
        Serial.print(", ");
        Serial.print(leds[i].g);
        Serial.print(", ");
        Serial.println(leds[i].b);
    }
    Serial.println();
}
#endif