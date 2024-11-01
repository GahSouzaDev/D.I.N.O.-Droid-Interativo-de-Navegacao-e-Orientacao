// Função para os bips no buzzer
void bipInicio() {
  //261 Hz a 4000 Hz.
  // Ajuste o volume (0-255)
  tone(BUZZER, 261); // Primeiro bip com frequência de 1000 Hz
  analogWrite(BUZZER, 25);
  delay(150);         // Duração do bip
  noTone(BUZZER);       // Para o som

  delay(50);          // Pausa rápida entre os bips

  tone(BUZZER, 329); // Segundo bip com frequência de 1500 Hz
  analogWrite(BUZZER, 25);
  delay(150);         // Duração do bip
  noTone(BUZZER);        // Para o som

  delay(50);          // Pausa rápida entre os bips

  tone(BUZZER, 493); // Terceiro bip com frequência de 1500 Hz
  analogWrite(BUZZER, 25);
  delay(150);         // Duração do bip
  noTone(BUZZER);        // Para o som
}
//Dó (C4) - 261 Hz
//Ré (D4) - 293 Hz
//Mi (E4) - 329 Hz
//Fá (F4) - 349 Hz
//Sol (G4) - 392 Hz
//Lá (A4) - 440 Hz (Nota padrão de afinação)
//Si (B4) - 493 Hz
//Dó (C5) - 523 Hz