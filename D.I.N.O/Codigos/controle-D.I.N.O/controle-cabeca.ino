void controleCabeca(char command) {
  int servos[16];        // Array para armazenar os índices dos servos que queremos mover.
  int targetAngles[16];   // Array para armazenar os ângulos de destino desses servos.

  switch (command) {
    case '2':
      servos[0] = 0;                      // Define o servo de índice 0.
      targetAngles[0] = initialPosition[0]; // Define o ângulo de destino para o servo 0 com a posição inicial.
      
      servos[1] = 1;                      // Define o servo de índice 1.
      targetAngles[1] = initialPosition[1]; // Define o ângulo de destino para o servo 1 com a posição inicial.
      
      moveServosTogether(servos, targetAngles, 2); // Move os dois servos (0 e 1) para as posições definidas.
      break;

    case '1':
      servos[0] = 0;                      // Define o servo de índice 0.
      targetAngles[0] = initialPosition[0];     // Define o ângulo de destino para o servo 0 na posição mínima.
      
      servos[1] = 1;                      // Define o servo de índice 1.
      targetAngles[1] = minPosition[1];     // Define o ângulo de destino para o servo 1 na posição mínima.
      
      moveServosTogether(servos, targetAngles, 2); // Move os dois servos (0 e 1) para as posições definidas.
      break;

    case '3':
      servos[0] = 0;                      // Define o servo de índice 0.
      targetAngles[0] = initialPosition[0];     // Define o ângulo de destino para o servo 0 na posição mínima.
      
      servos[1] = 1;                      // Define o servo de índice 1.
      targetAngles[1] = maxPosition[1];     // Define o ângulo de destino para o servo 1 na posição máxima.
      
      moveServosTogether(servos, targetAngles, 2); // Move os dois servos (0 e 1) para as posições definidas.
      break;

    default:
      return; // Retorna sem fazer nada se o comando não for reconhecido.
  }
}
