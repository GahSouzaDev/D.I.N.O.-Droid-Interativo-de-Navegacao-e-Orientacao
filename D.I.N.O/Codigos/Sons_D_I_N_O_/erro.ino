// Função para o som de raiva
void erro() {

  // Primeira parte - frequências alternadas e volume forte para um tom agressivo
  for (int i = 0; i < random(3, 7); i++) {
    tone(BUZZER, 700); // Frequência inicial alta e intensa
    analogWrite(BUZZER, volumeBase);
    delay(50); // Tom curto e forte
    noTone(BUZZER);

    delay(20); // Pausa curta para criar uma oscilação "nervosa"

    tone(BUZZER, 600); // Frequência ligeiramente menor para dar variação
    analogWrite(BUZZER, volumeBase - 5); // Volume um pouco menor para contraste
    delay(50); // Outra curta duração
    noTone(BUZZER);

    delay(20); // Pausa curta entre as partes para um efeito de "grunhido"
  }

  // Parte final - tom mais grave e prolongado para finalizar o som de raiva
  tone(BUZZER, 400);
  analogWrite(BUZZER, volumeBase - 10);
  delay(150); // Duração maior para o encerramento
  noTone(BUZZER); // Desliga o buzzer ao final
}
