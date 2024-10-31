// Função para os bips no buzzer
void bipBuzzer() {
  tone(BUZZER, 1000); // Primeiro bip com frequência de 1000 Hz
  delay(300);
  noTone(BUZZER);

  delay(50); // Pausa rápida entre os bips

  tone(BUZZER, 1500); // Segundo bip com frequência de 1500 Hz
  delay(300);
  noTone(BUZZER);
}