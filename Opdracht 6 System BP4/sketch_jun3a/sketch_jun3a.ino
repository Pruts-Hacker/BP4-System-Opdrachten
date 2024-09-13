#include <Servo.h>

Servo servoMotor;  // Creëer een Servo-object voor de aansturing van de servo

// Pin configuraties
const int SERVO_PIN = 9;         // Servo is aangesloten op pin 9
const int BUTTON_PIN = 2;        // Drukknop is aangesloten op pin 2
const int X_AXIS_PIN = A3;       // X-as van de joystick is aangesloten op analoge pin A3 (momenteel niet gebruikt)
const int Y_AXIS_PIN = A2;       // Y-as van de joystick is aangesloten op analoge pin A2

// Joystick grenzen
const int Y_POSITION_UPPER_THRESHOLD = 300;  // Drempelwaarde voor joystick omhoog
const int Y_POSITION_LOWER_THRESHOLD = 700;  // Drempelwaarde voor joystick omlaag

// Servo hoeken
const int MAX_SERVO_ANGLE = 120;  // Maximale hoek van de servo (120 graden)
const int MIN_SERVO_ANGLE = 0;    // Minimale hoek van de servo (0 graden)

// Delays in milliseconden
const int SHORT_DELAY = 10;       // Korte vertraging (voor vloeiende beweging)
const int MEDIUM_DELAY = 15;      // Middellange vertraging (voor knoprespons)
const int LONG_DELAY = 500;       // Lange vertraging (pauze bij volledig bewegen)

// Huidige servo positie
int currentServoPosition = 0;  // Houdt de huidige positie van de servo bij

void setup() {
  // Seriële communicatie voor debugging
  Serial.begin(9600);

  // Servo motor initialisatie
  servoMotor.attach(SERVO_PIN);  // Koppel de servo aan pin 9
  servoMotor.write(currentServoPosition);  // Zet de beginpositie van de servo op 0 graden

  // Pin modes instellen
  pinMode(X_AXIS_PIN, INPUT);     // X-as van de joystick als input
  pinMode(Y_AXIS_PIN, INPUT);     // Y-as van de joystick als input
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Drukknop als input met interne pull-up weerstand
}

void loop() {
  // Joystick controle
  checkJoystick();  // Controleer de positie van de joystick

  // Drukknop controle
  if (isButtonPressed()) {  // Controleer of de drukknop is ingedrukt
    handleButtonPress();  // Als de knop is ingedrukt, voer de bijbehorende functie uit
  }
}

// Functie om de joystick positie te controleren en de servo aan te passen
void checkJoystick() {
  int yPosition = readJoystickYAxis();  // Lees de Y-as positie van de joystick

  // Joystick omhoog bewogen
  if (isJoystickUp(yPosition) && !isServoAtMaxAngle()) {  // Als de joystick omhoog is en de servo niet op de maximale hoek staat
    moveServoUp();  // Beweeg de servo omhoog
  } 
  // Joystick omlaag bewogen
  else if (isJoystickDown(yPosition) && !isServoAtMinAngle()) {  // Als de joystick omlaag is en de servo niet op de minimale hoek staat
    moveServoDown();  // Beweeg de servo omlaag
  }
}

// Functie om de joystick Y-as te lezen
int readJoystickYAxis() {
  return analogRead(Y_AXIS_PIN);  // Lees de analoge waarde van de Y-as van de joystick
}

// Functie om te controleren of de joystick omhoog is bewogen
bool isJoystickUp(int yPosition) {
  return yPosition < Y_POSITION_UPPER_THRESHOLD;  // Controleer of de Y-as positie kleiner is dan de drempelwaarde voor omhoog
}

// Functie om te controleren of de joystick omlaag is bewogen
bool isJoystickDown(int yPosition) {
  return yPosition > Y_POSITION_LOWER_THRESHOLD;  // Controleer of de Y-as positie groter is dan de drempelwaarde voor omlaag
}

// Functie om te controleren of de servo aan de maximale hoek staat
bool isServoAtMaxAngle() {
  return currentServoPosition >= MAX_SERVO_ANGLE;  // Controleer of de huidige positie gelijk is aan of groter is dan de maximale hoek
}

// Functie om te controleren of de servo aan de minimale hoek staat
bool isServoAtMinAngle() {
  return currentServoPosition <= MIN_SERVO_ANGLE;  // Controleer of de huidige positie gelijk is aan of kleiner is dan de minimale hoek
}

// Functie om de servo omhoog te bewegen
void moveServoUp() {
  currentServoPosition += 2;  // Verhoog de servo positie met 2 graden
  servoMotor.write(currentServoPosition);  // Beweeg de servo naar de nieuwe positie
  delay(SHORT_DELAY);  // Voeg een korte vertraging toe voor vloeiende beweging
}

// Functie om de servo omlaag te bewegen
void moveServoDown() {
  currentServoPosition -= 2;  // Verlaag de servo positie met 2 graden
  servoMotor.write(currentServoPosition);  // Beweeg de servo naar de nieuwe positie
  delay(SHORT_DELAY);  // Voeg een korte vertraging toe voor vloeiende beweging
}

// Functie om te controleren of de drukknop is ingedrukt
bool isButtonPressed() {
  return digitalRead(BUTTON_PIN) == LOW;  // Controleer of de drukknop is ingedrukt (LOW betekent ingedrukt omdat de pull-up weerstand is ingeschakeld)
}

// Functie die wordt aangeroepen wanneer de drukknop is ingedrukt
void handleButtonPress() {
  // Beweeg de servo van de minimale naar de maximale hoek
  for (int angle = MIN_SERVO_ANGLE; angle <= MAX_SERVO_ANGLE; angle += 2) {
    servoMotor.write(angle);  // Zet de servo naar de nieuwe hoek
    delay(MEDIUM_DELAY);  // Voeg een vertraging toe voor een vloeiende beweging
  }
  
  delay(LONG_DELAY);  // Wacht een halve seconde nadat de servo de maximale hoek heeft bereikt

  // Beweeg de servo terug van de maximale naar de minimale hoek
  for (int angle = MAX_SERVO_ANGLE; angle >= MIN_SERVO_ANGLE; angle -= 2) {
    servoMotor.write(angle);  // Zet de servo naar de nieuwe hoek
    delay(MEDIUM_DELAY);  // Voeg een vertraging toe voor een vloeiende beweging
  }
}