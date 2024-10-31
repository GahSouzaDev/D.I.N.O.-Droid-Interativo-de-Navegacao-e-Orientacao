// Função para o robô "falar" o nome "Dino" com uma entonação contínua
void falaDino() {
  int volume = 25; // Volume fixo para o som

  // Início de "Di" com tom crescente para dar entonação
  for (int freq = 600; freq <= 900; freq += 10) {
    tone(BUZZER, freq);
    analogWrite(BUZZER, volume);
    delay(10); // Transição rápida para o tom subir como em "Di"
  }
  
  // Transição para "no" - tom mais grave com descida gradual
  for (int freq = 400; freq >= 300; freq -= 10) {
    tone(BUZZER, freq);
    analogWrite(BUZZER, volume);
    delay(30); // Duração um pouco mais longa para dar entonação de "noo"
  }

  noTone(BUZZER); // Desliga o buzzer ao final
}
