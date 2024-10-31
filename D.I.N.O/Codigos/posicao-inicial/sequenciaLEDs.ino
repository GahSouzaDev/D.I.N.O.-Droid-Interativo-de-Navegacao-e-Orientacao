// Função para a sequência de LEDs
void sequenciaLEDs() {
  digitalWrite(LED_VERMELHO, HIGH); // Liga o verde
  delay(100);

  digitalWrite(LED_AMARELO, HIGH); // Liga o amarelo
  delay(100);

  digitalWrite(LED_VERMELHO, LOW); // Apaga o verde
  digitalWrite(LED_VERDE, HIGH); // Liga o vermelho
  delay(100);

  digitalWrite(LED_AMARELO, LOW); // Apaga o amarelo
  digitalWrite(LED_AZUL, HIGH); // Liga o azul
  delay(100);

  digitalWrite(LED_VERDE, LOW); // Apaga o vermelho
  delay(100);

  digitalWrite(LED_AZUL, LOW); // Apaga o azul
}