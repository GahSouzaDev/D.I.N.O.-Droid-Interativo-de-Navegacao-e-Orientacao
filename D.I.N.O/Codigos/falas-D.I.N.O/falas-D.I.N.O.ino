//falas-D.I.N.O.
#include <Wire.h>

#define BUZZER 13         // Buzzer

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial
}

void loop() {
  if (Serial.available() > 0) {
    char comando = Serial.read(); // Lê o comando enviado via Serial

    switch (comando) {
      case '1':
        bipInicio();
        break;
      case '2':
        falaDino();
        break;
      case '3':
        // Função futura para o som 3
        break;
      case '4':
        // Função futura para o som 4
        break;
      case '5':
        // Função futura para o som 5
        break;
      case '6':
        // Função futura para o som 6
        break;
      case '7':
        // Função futura para o som 7
        break;
      case '8':
        // Função futura para o som 8
        break;
      case '9':
        // Função futura para o som 9
        break;
    }
  }
}
