#include "SONS_DINO.h"

#define BUZZER_PIN 13
#define VOLUME_BASE 25

SONS_DINO dino(BUZZER_PIN, VOLUME_BASE);

void setup() {
    Serial.begin(9600);
    dino.begin(); // Inicializa o buzzer
}

void loop() {
    if (Serial.available() > 0) {
        char comando = Serial.read();
        switch (comando) {
            case '1':
                dino.confirmacao();
                break;
            case '2':
                dino.falaNome();
                break;
            case '3':
                dino.positivo();
                break;
            case '4':
                dino.negativo();
                break;
            case '5':
                dino.duvida();
                break;
            case '6':
                dino.erro();
                break;
            case '7':
                dino.ajuda();
                break;
            case '8':
                dino.alerta();
                break;
            case '9':
                dino.contente();
                break;
            default:
                Serial.println("Comando inválido!");
                break;
        }
    }
}
