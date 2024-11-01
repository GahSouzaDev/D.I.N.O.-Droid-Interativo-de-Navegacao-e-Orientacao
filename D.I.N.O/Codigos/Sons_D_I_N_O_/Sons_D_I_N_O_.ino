//falas-D.I.N.O.
#include <Wire.h>

#define BUZZER 13         // Buzzer
int volumeBase = 25;      //0 - 255

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial
}

void loop() {
  if (Serial.available() > 0) {
    char comando = Serial.read(); // Lê o comando enviado via Serial

    switch (comando) {
      case '1':
        confirmacao();
        break;
      case '2':
        falaNome();
        break;
      case '3':
        positivo();
        break;
      case '4':
        negativo();
        break;
      case '5':
        duvida();
        break;
      case '6':
        erro();
        break;
      case '7':
        ajuda();
        break;
      case '8':
        alerta();
        break;
      case '9':
        contente();
        break;
    }
      delay(50);
  }

}
