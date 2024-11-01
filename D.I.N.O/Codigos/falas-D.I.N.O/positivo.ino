// Função para o som de confirmação no buzzer
void positivo() {
  
  // Primeira parte do "ta" - tom ascendente e volume aumentando
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