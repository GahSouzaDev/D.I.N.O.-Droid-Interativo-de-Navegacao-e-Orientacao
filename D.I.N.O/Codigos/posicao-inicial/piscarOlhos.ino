// Função para piscar os olhos como olhos humanos
void piscarOlhos() {

  // Ciclo de piscar
  for (int i = 0; i < 2; i++) { // Número de piscadas
    // Acende os olhos
    analogWrite(OLHO_ESQUERDO, 0);
    analogWrite(OLHO_DIREITO, 0);
    delay(random(60, 180)); // Mantém os olhos abertos por um tempo aleatório

    // Apaga os olhos
    analogWrite(OLHO_ESQUERDO, brilho);
    analogWrite(OLHO_DIREITO, brilho);
    delay(random(60, 180)); // Tempo de piscar, imitando o piscar humano
  }

  // Mantém os olhos acesos por tempo variável após as piscadas
  int tempoAbertos = random(2000, 4000); // Tempo que os olhos ficam abertos
  analogWrite(OLHO_ESQUERDO, brilho);
  analogWrite(OLHO_DIREITO, brilho);
  delay(tempoAbertos);

  // Pisca de forma dupla (exemplo de outra sequência)
  for (int j = 0; j < random(1, 4); j++) {
    analogWrite(OLHO_ESQUERDO, 0);
    analogWrite(OLHO_DIREITO, 0);
    delay(random(60, 180)); // Pisca rapidamente
    analogWrite(OLHO_ESQUERDO, brilho);
    analogWrite(OLHO_DIREITO, brilho);
    delay(random(2000, 4000)); // Mantém os olhos abertos por tempo variável
  }
}