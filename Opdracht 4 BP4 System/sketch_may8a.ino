const int PotPin = A3; // Pin voor de potentiometer
const int LedPins[] = {2, 4, 6, 8, 10, 12, 13}; // Pins voor de LEDs

void setup() {
  // LED-pinnen instellen als uitgangen
  for (int i = 0; i < 7; i++) {
    pinMode(LedPins[i], OUTPUT);
  }
}

void loop() {
  // Potentiometerwaarde lezen (0-1023)
  int potWaarde = analogRead(PotPin);
 
  // Potentiometerwaarde mappen naar aantal te branden LEDs (0-7)
  int Ledsnr = map(potWaarde, 0, 1023, 0, 7);
 
  // LEDs aansturen op basis van het aantal LEDs dat moet branden
  for (int i = 0; i < 7; i++) {
    if (i < Ledsnr) {
      digitalWrite(LedPins[i], HIGH); // LED aan
    } else {
      digitalWrite(LedPins[i], LOW); // LED uit
    }
  }
 
  delay(50); // Kleine vertraging voor zichtbaarheid van veranderingen
}