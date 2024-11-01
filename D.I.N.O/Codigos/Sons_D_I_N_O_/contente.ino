// Função para o som de felicidade
void contente() {

  // Sequência de notas alegres
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
