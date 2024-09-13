// Pin configuratie voor de potentiometer
// De potentiometer is aangesloten op analoge pin A0
const int POTENTIOMETER_PIN = A0;

// Debounce delay in milliseconden
// Een kleine vertraging tussen het lezen van de potentiometer om snelle veranderingen te voorkomen
const int DELAY_MS = 50;  // 50 milliseconden

// Pin-nummers voor de LEDs
// LEDs zijn aangesloten op digitale pinnen 2, 4, 6, 8, 10, 12, en 13
const int LED_PINS[] = {2, 4, 6, 8, 10, 12, 13};

// Berekent het aantal LEDs door de grootte van de array te delen door de grootte van één element
const int LED_COUNT = sizeof(LED_PINS) / sizeof(LED_PINS[0]);

// Minimale en maximale waarden voor de potentiometer
// De potentiometer geeft waarden tussen 0 (laagst) en 1023 (hoogst)
const int POT_MIN = 0;
const int POT_MAX = 1023;

// Index voor de eerste en laatste LED
const int LED_FIRST = 0;
const int LED_LAST = LED_COUNT;  // Aantal LEDs

void setup() {
    // Zet de LED-pinnen als output
    // De for-lus doorloopt elke LED-pin en stelt deze in als output
    for (int i = LED_FIRST; i < LED_LAST; i++) {
        pinMode(LED_PINS[i], OUTPUT);
    }
}

void loop() {
    // Lees de waarde van de potentiometer
    int potValue = readPotentiometer();

    // Map de potentiometerwaarde naar een aantal LEDs dat moet worden ingeschakeld
    int numLedsOn = mapPotValueToLedCount(potValue);

    // Update de LEDs: zet het juiste aantal LEDs aan
    updateLeds(numLedsOn);

    // Wacht een korte tijd voordat de loop opnieuw begint (debouncing)
    delay(DELAY_MS);
}

// Functie om de potentiometerwaarde te lezen
// Deze functie leest de analoge waarde van de potentiometer (0-1023)
int readPotentiometer() {
    return analogRead(POTENTIOMETER_PIN);
}

// Functie om de potentiometerwaarde te mappen naar het aantal LEDs dat moet branden
// De potentiometerwaarde (0-1023) wordt omgerekend naar een aantal LEDs (0-LED_COUNT)
int mapPotValueToLedCount(int potValue) {
    return map(potValue, POT_MIN, POT_MAX, LED_FIRST, LED_LAST);
}

// Functie om de LEDs bij te werken op basis van het aantal dat moet branden
// Zet de eerste 'numLedsOn' LEDs aan, de rest uit
void updateLeds(int numLedsOn) {
    for (int i = 0; i < LED_COUNT; i++) {
        // Als de huidige LED binnen het bereik van 'numLedsOn' ligt, zet deze aan
        // Anders, zet de LED uit
        digitalWrite(LED_PINS[i], i < numLedsOn ? HIGH : LOW);
    }
}