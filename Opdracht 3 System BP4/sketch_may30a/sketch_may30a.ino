// Definieert de pin waar de LED is aangesloten
const int LED_PIN = 10;

// Definieert de pin waar de knop is aangesloten
const int BUTTON_PIN = 6;

// Definieert de vertragingstijd voor het "debouncen" van de knop
const int DEBOUNCE_DELAY = 50;  // 50 milliseconden om ruis van de knop te voorkomen

// Variabele om de huidige toestand van de LED op te slaan (aan/uit)
bool ledState = false;

// Variabele om de huidige meting van de knop op te slaan
int buttonReading;

// Variabele om de vorige toestand van de knop op te slaan
int lastButtonState = LOW;  // Beginwaarde is LOW (knop niet ingedrukt)

void setup() {
    // Zet de LED pin als een output (om stroom te leveren aan de LED)
    pinMode(LED_PIN, OUTPUT);

    // Zet de knop pin als een input, met een ingebouwde pull-up weerstand
    // Dit betekent dat de pin standaard HIGH is, en naar LOW gaat als de knop wordt ingedrukt
    pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
    // Lees de huidige toestand van de knop (hoog of laag)
    buttonReading = digitalRead(BUTTON_PIN);

    // Controleer of de toestand van de knop is veranderd sinds de laatste loop
    if (buttonReading != lastButtonState) {

        // Als de knop net is ingedrukt (van HIGH naar LOW gegaan)
        if (buttonReading == LOW) {
            // Wissel de toestand van de LED (als deze aan is, zet uit en vice versa)
            ledState = !ledState;
        }

        // Wacht een korte tijd om het "debounce"-effect te voorkomen
        // Dit voorkomt dat mechanische ruis of trillingen van de knop 
        // worden geïnterpreteerd als meerdere drukken
        delay(DEBOUNCE_DELAY);
    }

    // Sla de huidige toestand van de knop op voor de volgende loop
    lastButtonState = buttonReading;

    // Schakel de LED aan of uit, afhankelijk van de toestand van de 'ledState' variabele
    digitalWrite(LED_PIN, ledState ? HIGH : LOW);
}