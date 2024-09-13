void setup()
{
  pinMode(12, OUTPUT); //configureer pin 12 als output
  pinMode(11, OUTPUT); //configureer pin 11 als output
}


void loop() {
  // Roep de functies aan om beide LEDs te laten knipperen
  FlashLeft(30); // Knipperen van linker LED met een interval van 30 milliseconden
  FlashRight(30); // Knipperen van rechter LED met een interval van 30 milliseconden
}

// Functie om de linker LED te laten knipperen
void FlashLeft(int tijd) {
  for (int i = 13; i >= 6; i--) { // Loop door de pinnen van 13 tot 6
    digitalWrite(i, HIGH); // Zet de huidige pin aan
    delay(tijd); // Wacht voor de opgegeven tijd
    digitalWrite(i, LOW); // Zet de huidige pin uit
    delay(tijd); // Wacht voor de opgegeven tijd voordat de volgende pin wordt ingeschakeld
  }
}

// Functie om de rechter LED te laten knipperen
void FlashRight(int tijd) {
  for (int i = 6; i <= 13; i++) { // Loop door de pinnen van 6 tot 13
    digitalWrite(i, HIGH); // Zet de huidige pin aan
    delay(tijd); // Wacht voor de opgegeven tijd
    digitalWrite(i, LOW); // Zet de huidige pin uit
    delay(tijd); // Wacht voor de opgegeven tijd voordat de volgende pin wordt ingeschakeld
  }
}