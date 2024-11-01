// Função para o som de SOS em Morse
void ajuda() {

  // SOS: ... --- ...
  // "S" = ... (3 bips curtos)
  for (int i = 0; i < 3; i++) {
    tone(BUZZER, 400); // Tom curto
    analogWrite(BUZZER, volumeBase);
    delay(150); // Duração do bip curto
    noTone(BUZZER);
    delay(80); // Pausa entre bips curtos
  }

  delay(100); // Pausa mais longa antes do próximo sinal

  // "O" = --- (3 bips longos)
  for (int i = 0; i < 3; i++) {
    tone(BUZZER, 400); // Tom longo
    analogWrite(BUZZER, volumeBase);
    delay(300); // Duração do bip longo
    noTone(BUZZER);
    delay(80); // Pausa entre bips longos
  }

  delay(100); // Pausa mais longa antes do próximo sinal

  // "S" = ... (3 bips curtos) novamente
  for (int i = 0; i < 3; i++) {
    tone(BUZZER, 400); // Tom curto
    analogWrite(BUZZER, volumeBase);
    delay(150); // Duração do bip curto
    noTone(BUZZER);
    delay(80); // Pausa entre bips curtos
  }

  noTone(BUZZER); // Desliga o buzzer ao final
}
