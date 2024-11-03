//S4, S5, S6 E S7 ROTAÇÃO PERNAS
//S8, S9, S10 E S11 
//S12, S13, S14 E S15
void controlePernas(char command) {
  int servos[16];        // Array para armazenar os índices dos servos que queremos mover.
  int targetAngles[16];   // Array para armazenar os ângulos de destino desses servos.

  switch (command) {
    case 'q':
      servos[0] = 0;                      // Define o servo de índice 0.
      targetAngles[0] = initialPosition[0]; // Define o ângulo de destino para o servo 0 com a posição inicial.
      
      servos[1] = 1;                      // Define o servo de índice 1.
      targetAngles[1] = initialPosition[1]; // Define o ângulo de destino para o servo 1 com a posição inicial.
      
      moveServosTogether(servos, targetAngles, 2); // Move os dois servos (0 e 1) para as posições definidas.
      break;

    case 'w':
      servos[0] = 0;                      // Define o servo de índice 0.
      targetAngles[0] = minPosition[0];     // Define o ângulo de destino para o servo 0 na posição mínima.
      
      servos[1] = 1;                      // Define o servo de índice 1.
      targetAngles[1] = minPosition[1];     // Define o ângulo de destino para o servo 1 na posição mínima.
      
      moveServosTogether(servos, targetAngles, 2); // Move os dois servos (0 e 1) para as posições definidas.
      break;

    case 'e':
      servos[0] = 0;                      // Define o servo de índice 0.
      targetAngles[0] = minPosition[0];     // Define o ângulo de destino para o servo 0 na posição mínima.
      
      servos[1] = 1;                      // Define o servo de índice 1.
      targetAngles[1] = maxPosition[1];     // Define o ângulo de destino para o servo 1 na posição máxima.
      
      moveServosTogether(servos, targetAngles, 2); // Move os dois servos (0 e 1) para as posições definidas.
      break;

    default:
      return; // Retorna sem fazer nada se o comando não for reconhecido.
  }
}
