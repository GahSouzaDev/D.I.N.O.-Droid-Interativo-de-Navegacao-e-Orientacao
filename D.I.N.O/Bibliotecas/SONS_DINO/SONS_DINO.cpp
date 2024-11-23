#include "SONS_DINO.h"
#include <Wire.h> // Mantém sua inclusão original, caso precise usar no futuro

// Construtor
SONS_DINO::SONS_DINO(int buzzerPin, int volumeBase) {
    _buzzerPin = buzzerPin;
    _volumeBase = volumeBase;
}

// Inicializa o buzzer
void SONS_DINO::begin() {
    pinMode(_buzzerPin, OUTPUT);
}

// Métodos
void SONS_DINO::confirmacao() {  
  tone(BUZZER, 261); // Primeiro bip com frequência de 1000 Hz
  analogWrite(BUZZER, volumeBase);
  delay(150);         // Duração do bip
  noTone(BUZZER);       // Para o som

  delay(50);          // Pausa rápida entre os bips

  tone(BUZZER, 329); // Segundo bip com frequência de 1500 Hz
  analogWrite(BUZZER, volumeBase);
  delay(150);         // Duração do bip
  noTone(BUZZER);        // Para o som

  delay(50);          // Pausa rápida entre os bips

  tone(BUZZER, 493); // Terceiro bip com frequência de 1500 Hz
  analogWrite(BUZZER, volumeBase);
  delay(150);         // Duração do bip
  noTone(BUZZER);        // Para o som

}

void SONS_DINO::falaNome() {
    tone(BUZZER, 500);
    analogWrite(BUZZER, volumeBase);
    delay(random(40, 70));
  // Início de "Di" com tom crescente e ajuste dinâmico de volume
  for (int freq = 600; freq <= 900; freq += 10) {
    int volume = map(freq, 600, 900, volumeBase, volumeBase + 20); // Aumenta o volume conforme a frequência
    tone(BUZZER, freq);
    analogWrite(BUZZER, volume);
    delay(random(5, 20)); // Transição um pouco mais suave
  }
    tone(BUZZER, 700);
    analogWrite(BUZZER, volumeBase);
    delay(random(40, 70));
  // Pequena pausa entre as sílabas para maior clareza
  noTone(BUZZER);
  delay(50);

  // Transição para "no" - tom mais grave e volume decrescente para criar uma entonação suave
  for (int freq = 400; freq >= 300; freq -= 5) {
    int volume = map(freq, 300, 400, volumeBase, volumeBase - 10); // Diminui o volume junto com a frequência
    tone(BUZZER, freq);
    analogWrite(BUZZER, volume);
    delay(random(5, 25)); // Duração mais longa para dar o efeito de "noo"
  }

  noTone(BUZZER); // Desliga o buzzer ao final
}

void SONS_DINO::positivo() {
     for (int freq = 500; freq <= 700; freq += 15) {
    int volume = map(freq, 500, 700, volumeBase, volumeBase + 30); // Aumenta o volume gradativamente
    tone(BUZZER, freq);
    analogWrite(BUZZER, volume);
    delay(random(5, 30)); // Transição rápida e animada
  }

  noTone(BUZZER); // Pausa entre as sílabas
  delay(50);

  // Segunda parte do "da" - tom ascendente final com volume mais forte
  for (int freq = 700; freq <= 900; freq += 20) {
    int volume = map(freq, 700, 900, volumeBase + 10, volumeBase + 35); // Volume mais alto para o final
    tone(BUZZER, freq);
    analogWrite(BUZZER, volume);
    delay(random(10, 30)); // Transição um pouco mais suave para fechar o som
  }

  noTone(BUZZER); // Desliga o buzzer ao final

}

void SONS_DINO::negativo() {
    for (int freq = 800; freq >= 600; freq -= 15) {
    int volume = map(freq, 600, 800, volumeBase - 5, volumeBase); // Volume diminui gradualmente
    tone(BUZZER, freq);
    analogWrite(BUZZER, volume);
    delay(random(5, 30)); // Transição suave
  }

  noTone(BUZZER); // Pausa entre as partes
  delay(50);

  // Segunda parte "oh" - tom descendente final para completar o efeito
  for (int freq = 600; freq >= 400; freq -= 10) {
    int volume = map(freq, 400, 600, volumeBase - 10, volumeBase - 5); // Volume ligeiramente mais baixo
    tone(BUZZER, freq);
    analogWrite(BUZZER, volume);
    delay(random(5, 20)); // Duração ligeiramente mais longa para um efeito de "oh"
  }

  noTone(BUZZER); // Desliga o buzzer ao final
}

void SONS_DINO::duvida() {
    for (int freq = 500; freq <= 550; freq += 10) {
    int volume = map(freq, 500, 550, volumeBase, volumeBase + 10); // Aumenta levemente o volume
    tone(BUZZER, freq);
    analogWrite(BUZZER, volume);
    delay(15); // Transição rápida para dar um toque de leveza
  }
  
  for (int freq = 550; freq >= 500; freq -= 10) {
    int volume = map(freq, 500, 550, volumeBase + 10, volumeBase); // Diminui o volume ao final
    tone(BUZZER, freq);
    analogWrite(BUZZER, volume);
    delay(15);
  }

  noTone(BUZZER); // Pausa entre as partes
  delay(50);

  // Segunda parte - tom curto e mais alto para simular uma inflexão de dúvida
  tone(BUZZER, 600);
  analogWrite(BUZZER, volumeBase + 15);
  delay(200); // Um som mais curto e mais agudo para o final
  noTone(BUZZER); // Desliga o buzzer ao final
}

void SONS_DINO::erro() {
    for (int i = 0; i < random(3, 7); i++) {
    tone(BUZZER, 700); // Frequência inicial alta e intensa
    analogWrite(BUZZER, volumeBase);
    delay(50); // Tom curto e forte
    noTone(BUZZER);

    delay(20); // Pausa curta para criar uma oscilação "nervosa"

    tone(BUZZER, 600); // Frequência ligeiramente menor para dar variação
    analogWrite(BUZZER, volumeBase - 5); // Volume um pouco menor para contraste
    delay(50); // Outra curta duração
    noTone(BUZZER);

    delay(20); // Pausa curta entre as partes para um efeito de "grunhido"
  }

  // Parte final - tom mais grave e prolongado para finalizar o som de raiva
  tone(BUZZER, 400);
  analogWrite(BUZZER, volumeBase - 10);
  delay(150); // Duração maior para o encerramento
  noTone(BUZZER); // Desliga o buzzer ao final
}

void SONS_DINO::ajuda() {
    for (int i = 0; i < 3; i++) {
    tone(BUZZER, 400); // Tom curto
    analogWrite(BUZZER, volumeBase);
    delay(150); // Duração do bip curto
    noTone(BUZZER);
    delay(80); // Pausa entre bips curtos
  }

  delay(100); // Pausa mais longa antes do próximo sinal

  // "O" = --- (3 bips longos)
  for (int i = 0; i < 3; i++) {
    tone(BUZZER, 400); // Tom longo
    analogWrite(BUZZER, volumeBase);
    delay(300); // Duração do bip longo
    noTone(BUZZER);
    delay(80); // Pausa entre bips longos
  }

  delay(100); // Pausa mais longa antes do próximo sinal

  // "S" = ... (3 bips curtos) novamente
  for (int i = 0; i < 3; i++) {
    tone(BUZZER, 400); // Tom curto
    analogWrite(BUZZER, volumeBase);
    delay(150); // Duração do bip curto
    noTone(BUZZER);
    delay(80); // Pausa entre bips curtos
  }

  noTone(BUZZER); // Desliga o buzzer ao final
}

void SONS_DINO::alerta() {
    for (int i = 0; i < 2; i++) {
  // Subida de frequência
  for (int freq = 300; freq <= 900; freq += 10) {
    tone(BUZZER, freq); // Aumenta a frequência
    analogWrite(BUZZER, volumeBase);
    delay(random(10, 30)); // Duração da nota
  }

  // Descida de frequência
  for (int freq = 900; freq >= 300; freq -= 10) {
    tone(BUZZER, freq); // Diminui a frequência
    analogWrite(BUZZER, volumeBase);
    delay(random(10, 30)); // Duração da nota
  }
    // Subida de frequência
 
  }

  noTone(BUZZER); // Desliga o buzzer ao final
}

void SONS_DINO::contente() {
     int notas[] = { 261, 293, 329, 349, 392, 440, 493, 523 }; // Notas de Dó a Dó (C4 a C5)

  // Tocar as notas em uma sequência ascendente
  for (int i = 0; i < sizeof(notas) / sizeof(notas[0]); i++) {
    tone(BUZZER, notas[i]); // Toca a nota
    analogWrite(BUZZER, volumeBase); // Define o volume
    delay(random(100, 300)); // Duração de cada nota
    noTone(BUZZER); // Para o som
    delay(random(30, 70)); // Pausa breve entre as notas
  }

  // Repetir a sequência para dar um efeito de alegria
  for (int i = sizeof(notas) / sizeof(notas[0]) - 1; i >= 0; i--) {
    tone(BUZZER, notas[i]); // Toca a nota em ordem decrescente
    analogWrite(BUZZER, volumeBase); // Define o volume
    delay(random(100, 300)); // Duração de cada nota
    noTone(BUZZER); // Para o som
    delay(random(30, 70)); // Pausa breve entre as notas
  }

  noTone(BUZZER); // Desliga o buzzer ao final
}
