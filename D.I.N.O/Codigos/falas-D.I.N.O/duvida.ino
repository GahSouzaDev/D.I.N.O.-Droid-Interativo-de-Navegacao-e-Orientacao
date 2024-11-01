// Função para o som de dúvida
void duvida() {

  // Primeira parte "hmm" - tom ligeiramente crescente e depois decrescente para criar um efeito de questionamento
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
