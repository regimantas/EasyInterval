#include <EasyInterval.h>

const int pirPin = 2;
EasyInterval timer;

void setup() {
  Serial.begin(115200);
  pinMode(pirPin, INPUT);
}

void loop() {
  if (digitalRead(pirPin) == HIGH) {
    unsigned long dt = timer.get();  // laikas nuo paskutinio get (ir reset)
    Serial.print("Praėjo nuo paskutinio HIGH: ");
    Serial.print(dt);
    Serial.println(" ms");
    delay(100); // debounce
  }
}
