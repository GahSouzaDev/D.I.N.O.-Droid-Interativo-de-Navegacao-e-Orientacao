#include <Arduino.h>

#include "PiscaLED.h"

PiscaLED::PiscaLED(int pino1, int pino2) {
  pinMode(pino1, OUTPUT);
  pinMode(pino2, OUTPUT);
  pino1_ = pino1;
  pino2_ = pino2;
}

void PiscaLED::piscar() {
  digitalWrite(pino1_, HIGH);
  digitalWrite(pino2_, LOW);
  delay(750); // Ajuste o tempo de delay conforme necessário
  digitalWrite(pino1_, LOW);
  digitalWrite(pino2_, HIGH);
  delay(750);
}