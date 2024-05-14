const int ButtonPin = 2; // De schakelaar of drukknop zit op Pin 2.
const int LedPin = 11; // De LED zit op Pin 11.
int ButtonState = 0; // Een variabele voor de status van de schakelaar of knop.
int LastButtonState = LOW; // Een variabele om de vorige status van de knop bij te houden.
bool LampOn = false; // Een variabele om de toestand van het lampje bij te houden.

void setup() {
  pinMode(LedPin, OUTPUT); // De LED Pin is een uitgang. 
  pinMode(ButtonPin, INPUT); // De knop Pin is een ingang.
}

void loop() {
  ButtonState = digitalRead(ButtonPin); // Lees de status van de schakelaar of knop.

  if (ButtonState == HIGH && LastButtonState == LOW) { // Als de knop van laag naar hoog gaat (ingedrukt wordt):
    delay(50); // Voeg een vertraging van 50 ms toe om debounce-effecten te verminderen.
    LampOn = !LampOn; // Toggle de toestand van het lampje.
  }

  if (LampOn) { // Als het lampje aan moet zijn:
    digitalWrite(LedPin, HIGH); // Zet de LED aan.
  } else { // Zo niet..
    digitalWrite(LedPin, LOW); // Zet de LED uit.
  }

  LastButtonState = ButtonState; // Bewaar de huidige ButtonState voor de volgende iteratie.
}