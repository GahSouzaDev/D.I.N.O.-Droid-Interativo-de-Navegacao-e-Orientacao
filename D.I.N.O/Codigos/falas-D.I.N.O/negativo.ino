// Função para os bips no buzzer
void negativo() {
  
  // Primeira parte "uh" - tom descendente e volume caindo
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