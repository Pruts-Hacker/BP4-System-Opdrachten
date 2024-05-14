#include <Servo.h>

Servo servo; 
int x_key = A1; // Pin voor de X-as van de joystick
int y_key = A0; // Pin voor de Y-as van de joystick
int button_key = 2; // Pin voor de drukknop van de joystick
int x_pos; //Variabele voor de positie van de X-as van de joystick
int y_pos; // Variabele voor de positie van de Y-as van de joystick
int servo_pin = 9; //Pin voor de ServoMotor 
int initial_position = 0; // Beginspositie van de servo

void setup() {
  Serial.begin(9600);
  servo.attach(servo_pin); // Sluit de servo aan op de servo_pin
  servo.write(initial_position); // Beginpositie van de servo
  pinMode(x_key, INPUT); // Stel de X-as van de joystick in als input
  pinMode(y_key, INPUT); // Stel de Y-as van de joystick in als input
  pinMode(button_key, INPUT_PULLUP); // Drukknop pin als input met interne pull-up weerstand
}

void loop() {
  LeftRight(); // Roep de functie LeftRight() aan

  // Controleer of de drukknop wordt ingedrukt
  if (digitalRead(button_key) == LOW) {
    Pressed(); // Roep de functie Pressed() aan
  }
}

void LeftRight() {
  x_pos = analogRead(x_key);
  y_pos = analogRead(y_key);

  if (y_pos < 300) { // Als de joystick naar boven wordt gedrukt
    if (initial_position < 120) { // Controleer of de maximale positie niet overschreden wordt
      initial_position += 2; // Verhoog de hoek van de servo met 2 graden
      servo.write(initial_position); // Stuur de servo naar de nieuwe positie
      delay(10);
    }
  } else if (y_pos > 700) { // Als de joystick naar beneden wordt gedrukt
    if (initial_position > 0) { // Controleer of de minimale positie niet overschreden wordt
      initial_position -= 2; // Verlaag de hoek van de servo met 2 graden
      servo.write(initial_position); // Stuur de servo naar de nieuwe positie
      delay(10);
    }
  }
}

void Pressed() {
  // Draai de servo van 0 naar 120 graden en keer dan terug naar 0 graden
  for (int angle = 0; angle <= 120; angle += 2) {
    servo.write(angle); // Stuur de servo naar de huidige hoek
  }
  delay(500); // Wacht 0.5 seconden voordat de servo terugkeert naar de beginpositie
  // Keer terug naar de beginpositie (0 graden)
  servo.write(0);
  delay(15); // Voeg een kleine vertraging toe voor stabiliteit
}