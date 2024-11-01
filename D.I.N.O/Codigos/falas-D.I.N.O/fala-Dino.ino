// Função para o robô "falar" o nome "Dino" com uma entonação contínua e dinâmica
void falaDino() {
  int volumeBase = 25; // Volume base para o som

  // Início de "Di" com tom crescente e ajuste dinâmico de volume
  for (int freq = 600; freq <= 900; freq += 10) {
    int volume = map(freq, 600, 900, volumeBase, volumeBase + 20); // Aumenta o volume conforme a frequência
    tone(BUZZER, freq);
    analogWrite(BUZZER, volume);
    delay(15); // Transição um pouco mais suave
  }
  
  // Pequena pausa entre as sílabas para maior clareza
  noTone(BUZZER);
  delay(50);

  // Transição para "no" - tom mais grave e volume decrescente para criar uma entonação suave
  for (int freq = 400; freq >= 300; freq -= 5) {
    int volume = map(freq, 300, 400, volumeBase, volumeBase - 10); // Diminui o volume junto com a frequência
    tone(BUZZER, freq);
    analogWrite(BUZZER, volume);
    delay(35); // Duração mais longa para dar o efeito de "noo"
  }

  noTone(BUZZER); // Desliga o buzzer ao final
}
