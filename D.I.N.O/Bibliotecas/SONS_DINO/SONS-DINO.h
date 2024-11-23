#ifndef SONS_DINO_H
#define SONS_DINO_H

class SONS_DINO {
public:
    SONS_DINO(int buzzerPin, int volumeBase); // Construtor
    void begin();                            // Inicializa o buzzer
    void confirmacao();
    void falaNome();
    void positivo();
    void negativo();
    void duvida();
    void erro();
    void ajuda();
    void alerta();
    void contente();

private:
    int _buzzerPin;
    int _volumeBase;
};

#endif
