void setup()
{
  pinMode(12, OUTPUT); // configureer pin 12 als output
  pinMode(11, OUTPUT); // configureer pin 11 als output
}

void loop()
{
  
Flashing(1000); // aanroepen van de Flashing functie en een delay van 1 sec meegeven
  
}

void Flashing(int tijd)
{

digitalWrite(11, HIGH);
  delay(tijd); // wacht voor 1000 millisecond(s)
  digitalWrite(11, LOW);
  delay(tijd); // wacht voor 1000 millisecond(s)
  digitalWrite(12, HIGH);
  delay(tijd); // wacht voor 1000 millisecond(s)
  digitalWrite(12, LOW);
  delay(tijd); // wacht voor 1000 millisecond(s)

}
