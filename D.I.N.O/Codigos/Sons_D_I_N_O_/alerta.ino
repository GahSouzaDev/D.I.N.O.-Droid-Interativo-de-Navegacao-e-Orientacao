// Função para o som da sirene "uiuiu"
void alerta() {

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
