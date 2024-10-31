// Função para piscar os olhos como olhos humanos
void piscarOlhos() {
  // Acende os olhos com o brilho definido
  analogWrite(OLHO_ESQUERDO, brilho);
  analogWrite(OLHO_DIREITO, brilho);
  delay(80); // Mantém os olhos abertos por um curto tempo

  // Apaga os olhos
  analogWrite(OLHO_ESQUERDO, 0);
  analogWrite(OLHO_DIREITO, 0);
  delay(150); // Pisca rápido, imitando o piscar humano

  // Mantém os olhos acesos por um tempo maior
  analogWrite(OLHO_ESQUERDO, brilho);
  analogWrite(OLHO_DIREITO, brilho);
  delay(3000);

  // Pisca de novo
  analogWrite(OLHO_ESQUERDO, 0);
  analogWrite(OLHO_DIREITO, 0);
  delay(180);

  // Mantém os olhos acesos por um tempo maior
  analogWrite(OLHO_ESQUERDO, brilho);
  analogWrite(OLHO_DIREITO, brilho);
  delay(3500);

  // Pisca de novo
  analogWrite(OLHO_ESQUERDO, 0);
  analogWrite(OLHO_DIREITO, 0);
  delay(150);

  // Mantém os olhos acesos por um tempo maior
  analogWrite(OLHO_ESQUERDO, brilho);
  analogWrite(OLHO_DIREITO, brilho);
  delay(60);

  // Pisca de novo
  analogWrite(OLHO_ESQUERDO, 0);
  analogWrite(OLHO_DIREITO, 0);
  delay(140);

  // Mantém os olhos acesos por um tempo maior
  analogWrite(OLHO_ESQUERDO, brilho);
  analogWrite(OLHO_DIREITO, brilho);
  delay(2500);

  // Pisca de novo
  analogWrite(OLHO_ESQUERDO, 0);
  analogWrite(OLHO_DIREITO, 0);
  delay(100);

  // Mantém os olhos acesos por um tempo maior
  analogWrite(OLHO_ESQUERDO, brilho);
  analogWrite(OLHO_DIREITO, brilho);
  delay(3500);

  // Pisca de novo
  analogWrite(OLHO_ESQUERDO, 0);
  analogWrite(OLHO_DIREITO, 0);
  delay(80);
}
