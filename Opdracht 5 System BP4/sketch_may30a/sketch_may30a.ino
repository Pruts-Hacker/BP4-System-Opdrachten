#include <Servo.h>

// Definieer de pinnen voor de drukknoppen
// BUTTON_PIN_1 en BUTTON_PIN_2 zijn verbonden met digitale pinnen 8 en 6
const int BUTTON_PIN_1 = 8;
const int BUTTON_PIN_2 = 6;

// Debounce delay in milliseconden
// Deze vertraging voorkomt het verkeerd detecteren van meerdere drukken door mechanische ruis
const int DEBOUNCE_DELAY = 50;

// Standaard wachttijden in milliseconden
// DELAY_1 is 2000 ms (2 seconden) en DELAY_2 is 1 ms voor korte pauzes
const int DELAY_1 = 2000;
const int DELAY_2 = 1; 

// Definieer de hoeken voor de servo
// ANGLE_1 is 120 graden en ANGLE_2 is 0 graden
const int ANGLE_1 = 120;
const int ANGLE_2 = 0;

// Definieer de tijd (in milliseconden) die de servo nodig heeft om te draaien
// ROTATE_TIME_1 is 1000 ms (1 seconde), ROTATE_TIME_2 is 500 ms
const int ROTATE_TIME_1 = 1000;
const int ROTATE_TIME_2 = 500;

// Definieer de pin voor de servomotor
// SERVO_PIN is aangesloten op digitale pin 9
const int SERVO_PIN = 9;

// Maak een Servo object aan
Servo servoMotor;

void setup() {
    // Koppel de servomotor aan de opgegeven pin
    servoMotor.attach(SERVO_PIN);
    
    // Zet de beginpositie van de servomotor op 0 graden
    servoMotor.write(0); 
    
    // Zet de pinnen van de drukknoppen als input
    pinMode(BUTTON_PIN_1, INPUT);
    pinMode(BUTTON_PIN_2, INPUT);
}

void loop() {
    // Controleer of beide knoppen zijn ingedrukt
    if (checkButtons()) {
        delay(DEBOUNCE_DELAY); // Voorkom meerdere detecties door mechanische ruis
        return; // Sla de rest van de loop over als beide knoppen zijn ingedrukt
    }

    // Controleer de knoppen afzonderlijk
    individualButtons();
    delay(DEBOUNCE_DELAY); // Debounce na elke controle
}

// Functie om te controleren of beide knoppen zijn ingedrukt
bool checkButtons() {
    // Lees de status van beide knoppen (HIGH betekent ingedrukt)
    int buttonStatus1 = digitalRead(BUTTON_PIN_1);
    int buttonStatus2 = digitalRead(BUTTON_PIN_2);

    // Als beide knoppen zijn ingedrukt
    if (buttonStatus1 == HIGH && buttonStatus2 == HIGH) {
        // Draai de servo naar ANGLE_1 (120 graden) en wacht 1 seconde
        rotateServo(ANGLE_1, ROTATE_TIME_1);
        
        // Wacht 2 seconden
        delay(DELAY_1); 
        
        // Draai de servo terug naar ANGLE_2 (0 graden)
        rotateServo(ANGLE_2, ROTATE_TIME_1);
        
        // Geef aan dat beide knoppen zijn ingedrukt
        return true;
    }

    // Geef aan dat niet beide knoppen zijn ingedrukt
    return false;
}

// Functie om de knoppen afzonderlijk te controleren
void individualButtons() {
    // Lees de status van beide knoppen
    int buttonStatus1 = digitalRead(BUTTON_PIN_1);
    int buttonStatus2 = digitalRead(BUTTON_PIN_2);

    // Als de eerste knop is ingedrukt
    if (buttonStatus1 == HIGH) {
        // Draai de servo naar ANGLE_1 (120 graden) en dan terug naar ANGLE_2 (0 graden)
        rotateServo(ANGLE_1, ROTATE_TIME_1);
        rotateServo(ANGLE_2, ROTATE_TIME_1);
    } 
    // Als de tweede knop is ingedrukt
    else if (buttonStatus2 == HIGH) {
        // Draai de servo naar ANGLE_1 (120 graden) en dan terug naar ANGLE_2 (0 graden) met kortere rotatietijd
        rotateServo(ANGLE_1, ROTATE_TIME_2);
        rotateServo(ANGLE_2, ROTATE_TIME_2);
    }
}

// Functie om de servo naar een opgegeven hoek te draaien over een bepaalde tijd
void rotateServo(int angle, int duration) {
    // Lees de huidige positie van de servo
    int initialAngle = servoMotor.read();
    
    // Bereken de stapgrootte: het verschil tussen de huidige hoek en de doelhoek gedeeld door de tijd
    float step = float(angle - initialAngle) / float(duration);

    // Gebruik een lus om de servo geleidelijk naar de doelhoek te draaien
    for (int i = 0; i <= duration; i++) {
        // Verander de positie van de servo met kleine stappen
        servoMotor.write(initialAngle + step * i);
        
        // Wacht een korte tijd tussen elke stap om de beweging vloeiend te maken
        delay(DELAY_2);
    }
}