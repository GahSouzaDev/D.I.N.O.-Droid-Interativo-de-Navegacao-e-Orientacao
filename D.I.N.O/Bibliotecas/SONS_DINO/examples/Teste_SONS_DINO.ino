#include <SONS_DINO.h>

// Define o pino do buzzer e o volume base
SONS_DINO dino(13, 25);

void setup() {
    Serial.begin(9600); // Inicializa a comunicação serial
    dino.begin();       // Inicializa o buzzer
}

void loop() {
    if (Serial.available() > 0) {
        char comando = Serial.read(); // Lê o comando via Serial
        switch (comando) {
            case '1': dino.confirmacao(); break;
            case '2': dino.falaNome(); break;
            case '3': dino.positivo(); break;
            case '4': dino.negativo(); break;
            case '5': dino.duvida(); break;
            case '6': dino.erro(); break;
            case '7': dino.ajuda(); break;
            case '8': dino.alerta(); break;
            case '9': dino.contente(); break;
        }
    }
}
