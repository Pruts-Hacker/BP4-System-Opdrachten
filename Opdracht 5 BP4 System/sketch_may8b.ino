#include <Servo.h>

Servo myServo;  // Definieer een Servo object

const int buttonPin1 = 6;  // Pin van de eerste drukknop
const int buttonPin2 = 3;  // Pin van de tweede drukknop
int servo_pin = 11; // Pin voor de ServoMotor

void setup() {
  myServo.attach(servo_pin);  // Sluit de servomotor aan op servo_pin
  myServo.write(0);    // beginpositie van de servomotor
  
  pinMode(buttonPin1, INPUT);  // Configureer de eerste drukknop pin als input
  pinMode(buttonPin2, INPUT);  // Configureer de tweede drukknop pin als input

}

void loop() {
 ButtonPressed() ;// aanroepen van de ButtonPressed functie
}

void ButtonPressed(){
   int buttonState1 = digitalRead(buttonPin1);  // Lees de staat van de eerste drukknop
  int buttonState2 = digitalRead(buttonPin2);  // Lees de staat van de tweede drukknop
  
  if (buttonState1 == HIGH && buttonState2 == HIGH) {
    MoveServo(120, 1000);  // Draai de servomotor naar 120° in 1s
    delay(2000);  // Wacht 2 seconden voordat de servo naar 0 graden gaat
    MoveServo(0, 1000);  // Draai de servomotor terug naar 0° in 1s
  } else if (buttonState1 == HIGH) {
    MoveServo(120, 1000);  // Draai de servomotor naar 120° in 1s
    MoveServo(0, 1000);  // Draai de servomotor terug naar 0° in 1s
  } else if (buttonState2 == HIGH) {
    MoveServo(120, 500);  // Draai de servomotor naar 120° in 0.5s
    MoveServo(0, 1000);  // Draai de servomotor terug naar 0° in 1s
  }
}
void MoveServo(int angle, int duration) {
  int initialAngle = myServo.read();  // Huidige positie van de servomotor
  int finalAngle = angle;  // Gewenste positie van de servomotor
  
  float step = (finalAngle - initialAngle) / (float)duration;  // Bepaal de stapgrootte op basis van de gewenste duur

  
  // Beweeg de servomotor naar de gewenste positie
  for (int i = 0; i <= duration; i++) {
    myServo.write(initialAngle + step * i);
    delay(1);
  }
}