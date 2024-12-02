#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_MIN_PULSE 112 // Pulso mínimo para o servo
#define SERVO_MAX_PULSE 512 // Pulso máximo para o servo

// ----CABEÇA---- //
// Pescoço
int PescocoMin = 90, PescocoMed = 120, PescocoMax = 160;

// Rotação da cabeça
int RotacaoCabecaMed = 100;
// Rotação para DIREITA
int RotacaoCabecaDirMax = 0, RotacaocabecaDirMed = 50;
// Rotação para ESQUERDA
int RotacaoCabecaEsqMax = 200, RotacaoCabecaEspMed = 150;

// Antenas
int AntenasMed = 120, AntenasMax = 150, AntenasMin = 90;

// Elevação da cabeça
int ElevacaoMed = 75;
// Cabeça para BAIXO
int ElevacaoBaixoMed = 57.5, ElevacaoBaixoMax = 40;
// Cabeça para CIMA
int ElevacaoCimaMed = 92.5, ElevacaoCimaMax = 130;

// ---PERNAS--- //
// ESQUERDA
// Rotação
int RotacaoPernaEsqMed1 = 90, RotacaoPernaDirMed1 = 90;
int RotacaoPernaEsqMed2 = 90, RotacaoPernaDirMed2 = 105;
int RotacaoPernaEsqMin1 = 60, RotacaoPernaDirMin1 = 60;
int RotacaoPernaEsqMin2 = 120, RotacaoPernaDirMin2 = 135;
int RotacaoPernaEsqMax1 = 120, RotacaoPernaDirMax1 = 120;
int RotacaoPernaEsqMax2 = 60, RotacaoPernaDirMax2 = 75;

// Coxa
int MoveCoxaEsqMed1 = 120, MoveCoxaDirMed1 = 65;
int MoveCoxaEsqMed2 = 120, MoveCoxaDirMed2 = 75;
int MoveCoxaEsqMin1 = 135, MoveCoxaDirMin1 = 50;
int MoveCoxaEsqMin2 = 135, MoveCoxaDirMin2 = 60;
int MoveCoxaEsqMax1 = 105, MoveCoxaDirMax1 = 80;
int MoveCoxaEsqMax2 = 105, MoveCoxaDirMax2 = 90;

// Panturrilha
int MovePantEsqMed1 = 95, MovePantDirMed1 = 90;
int MovePantEsqMed2 = 105, MovePantDirMed2 = 90;
int MovePantEsqMin1 = 105, MovePantDirMin1 = 70;
int MovePantEsqMin2 = 115, MovePantDirMin2 = 80;
int MovePantEsqMax1 = 85, MovePantDirMax1 = 90;
int MovePantEsqMax2 = 95, MovePantDirMax2 = 100;

// Posições
int initialPosition[16] = {
  PescocoMin, RotacaoCabecaMed, AntenasMed, ElevacaoMed,  
  RotacaoPernaDirMed1, RotacaoPernaDirMed2, RotacaoPernaEsqMed1, RotacaoPernaEsqMed2,   
  MoveCoxaEsqMax1, MoveCoxaEsqMax2, MoveCoxaDirMax1, MoveCoxaDirMax2,
  MovePantDirMax1, MovePantDirMax2, MovePantEsqMax1, MovePantEsqMax2
};

int currentPosition[16] = {
  PescocoMin, RotacaoCabecaMed, AntenasMed, ElevacaoMed,  
  RotacaoPernaDirMed1, RotacaoPernaDirMed2, RotacaoPernaEsqMed1, RotacaoPernaEsqMed2,   
  MoveCoxaEsqMax1, MoveCoxaEsqMax2, MoveCoxaDirMax1, MoveCoxaDirMax2,
  MovePantDirMax1, MovePantDirMax2, MovePantEsqMax1, MovePantEsqMax2
};

void moveServosTogether(int servos[], int targetAngles[], int numServos) {
  bool movement = true;
  while (movement) {
    movement = false;
    for (int i = 0; i < numServos; i++) {
      int startPulse = map(currentPosition[servos[i]], 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE);
      int endPulse = map(targetAngles[i], 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE);

      if (currentPosition[servos[i]] < targetAngles[i]) {
        currentPosition[servos[i]]++;
        pwm.setPWM(servos[i], 0, map(currentPosition[servos[i]], 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE));
        movement = true;
      } else if (currentPosition[servos[i]] > targetAngles[i]) {
        currentPosition[servos[i]]--;
        pwm.setPWM(servos[i], 0, map(currentPosition[servos[i]], 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE));
        movement = true;
      }
    }
    delay(10); // Pequeno atraso para controlar a velocidade do movimento simultâneo
  }
}

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50);

  for (int i = 0; i < 16; i++) {
    currentPosition[i] = initialPosition[i];
    pwm.setPWM(i, 0, map(initialPosition[i], 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE));
  }
}

//S4, S5, S6 E S7 ROTAÇÃO PERNAS
//S8, S9, S10 E S11 
//S12, S13, S14 E S15
void controlePernas(char command) {
  int servos[12];       // Array para armazenar os índices dos servos das pernas (2 para cada perna).
  int targetAngles[12]; // Array para armazenar os ângulos de destino desses servos.

  switch (command) {
    case 'w': // Inicial - posição central para ambas as pernas
      servos[0] = 4; targetAngles[0] = RotacaoPernaEsqMed1 // Rotações perna esquerda
      servos[1] = 5; targetAngles[1] = RotacaoPernaEsqMed2;
      servos[2] = 6; targetAngles[2] = RotacaoPernaDirMed1; // Rotações perna direita
      servos[3] = 7; targetAngles[3] = ERotacaoPernaDirMed1;

      servos[4] = 8; targetAngles[4] = MoveCoxaEsqMax1; // Rotações perna esquerda
      servos[5] = 9; targetAngles[5] = MoveCoxaEsqMax2;
      servos[6] = 10; targetAngles[6] = MoveCoxaDirMax1; // Rotações perna direita
      servos[7] = 11; targetAngles[7] = MoveCoxaDirMax2;

      servos[8] = 12; targetAngles[8] = MovePantDirMax1; // Rotações perna esquerda
      servos[9] = 13; targetAngles[9] = MovePantDirMax2;
      servos[10] = 14; targetAngles[10] = MovePantEsqMax1; // Rotações perna direita
      servos[11] = 15; targetAngles[11] = MovePantEsqMax2;
      moveServosTogether(servos, targetAngles, 12);
      break;

    case 'q': // Esquerda no mínimo, direita no máximo
      servos[0] = 4; targetAngles[0] = RotacaoPernaEsqMed1 // Rotações perna esquerda
      servos[1] = 5; targetAngles[1] = RotacaoPernaEsqMed2;
      servos[2] = 6; targetAngles[2] = RotacaoPernaDirMed1; // Rotações perna direita
      servos[3] = 7; targetAngles[3] = ERotacaoPernaDirMed1;

      servos[4] = 8; targetAngles[4] = MoveCoxaEsqMin1; // Rotações perna esquerda
      servos[5] = 9; targetAngles[5] = MoveCoxaEsqMin2;
      servos[6] = 10; targetAngles[6] = MoveCoxaDirMax1; // Rotações perna direita
      servos[7] = 11; targetAngles[7] = MoveCoxaDirMax2;

      servos[8] = 12; targetAngles[8] = MovePantDirMax1; // Rotações perna esquerda
      servos[9] = 13; targetAngles[9] = MovePantDirMax2;
      servos[10] = 14; targetAngles[10] = MovePantEsqMin1; // Rotações perna direita
      servos[11] = 15; targetAngles[11] = MovePantEsqMin2;
      moveServosTogether(servos, targetAngles, 12);
      break;

    case 'e': // Direita no mínimo, esquerda no máximo
      servos[0] = 4; targetAngles[0] = RotacaoPernaEsqMed1 // Rotações perna esquerda
      servos[1] = 5; targetAngles[1] = RotacaoPernaEsqMed2;
      servos[2] = 6; targetAngles[2] = RotacaoPernaDirMed1; // Rotações perna direita
      servos[3] = 7; targetAngles[3] = ERotacaoPernaDirMed1;

      servos[4] = 8; targetAngles[4] = MoveCoxaEsqMax1; // Rotações perna esquerda
      servos[5] = 9; targetAngles[5] = MoveCoxaEsqMax2;
      servos[6] = 10; targetAngles[6] = MoveCoxaDirMin1; // Rotações perna direita
      servos[7] = 11; targetAngles[7] = MoveCoxaDirMin2;

      servos[8] = 12; targetAngles[8] = MovePantDirMin1; // Rotações perna esquerda
      servos[9] = 13; targetAngles[9] = MovePantDirMin2;
      servos[10] = 14; targetAngles[10] = MovePantEsqMax1; // Rotações perna direita
      servos[11] = 15; targetAngles[11] = MovePantEsqMax2;
      moveServosTogether(servos, targetAngles, 12);
      break;

    case 'r': // Direita no mínimo, esquerda no máximo
      servos[0] = 4; targetAngles[0] = RotacaoPernaEsqMed1 // Rotações perna esquerda
      servos[1] = 5; targetAngles[1] = RotacaoPernaEsqMed2;
      servos[2] = 6; targetAngles[2] = RotacaoPernaDirMed1; // Rotações perna direita
      servos[3] = 7; targetAngles[3] = ERotacaoPernaDirMed1;

      servos[4] = 8; targetAngles[4] = MoveCoxaEsqMax1; // Rotações perna esquerda
      servos[5] = 9; targetAngles[5] = MoveCoxaEsqMax2;
      servos[6] = 10; targetAngles[6] = MoveCoxaDirMax1; // Rotações perna direita
      servos[7] = 11; targetAngles[7] = MoveCoxaDirMax2;

      servos[8] = 12; targetAngles[8] = MovePantDirMax1; // Rotações perna esquerda
      servos[9] = 13; targetAngles[9] = MovePantDirMax2;
      servos[10] = 14; targetAngles[10] = MovePantEsqMax1; // Rotações perna direita
      servos[11] = 15; targetAngles[11] = MovePantEsqMax2;
      moveServosTogether(servos, targetAngles, 12);

for (int i = 0; i < 8; i++) {

      servos[4] = 8; targetAngles[4] = MoveCoxaEsqMax1; // Rotações perna esquerda
      servos[5] = 9; targetAngles[5] = MoveCoxaEsqMax2;
      servos[6] = 10; targetAngles[6] = MoveCoxaDirMin1; // Rotações perna direita
      servos[7] = 11; targetAngles[7] = MoveCoxaDirMin2;

      servos[8] = 12; targetAngles[8] = MovePantDirMed1; // Rotações perna esquerda
      servos[9] = 13; targetAngles[9] = MovePantDirMed2;
      servos[10] = 14; targetAngles[10] = MovePantEsqMax1; // Rotações perna direita
      servos[11] = 15; targetAngles[11] = MovePantEsqMax2;
      moveServosTogether(servos, targetAngles, 8);
      delay(100);

      servos[0] = 4; targetAngles[0] = RotacaoPernaEsqMin1 // Rotações perna esquerda
      servos[1] = 5; targetAngles[1] = RotacaoPernaEsqMin2;
      servos[2] = 6; targetAngles[2] = RotacaoPernaDirMax1; // Rotações perna direita
      servos[3] = 7; targetAngles[3] = ERotacaoPernaDirMax1;
      moveServosTogether(servos, targetAngles, 4);

      servos[4] = 8; targetAngles[4] = MoveCoxaEsqMin1; // Rotações perna esquerda
      servos[5] = 9; targetAngles[5] = MoveCoxaEsqMin2;
      servos[6] = 10; targetAngles[6] = MoveCoxaDirMax1; // Rotações perna direita
      servos[7] = 11; targetAngles[7] = MoveCoxaDirMax2;

      servos[8] = 12; targetAngles[8] = MovePantDirMax1; // Rotações perna esquerda
      servos[9] = 13; targetAngles[9] = MovePantDirMax2;
      servos[10] = 14; targetAngles[10] = MovePantEsqMed1; // Rotações perna direita
      servos[11] = 15; targetAngles[11] = MovePantEsqMed2;
      moveServosTogether(servos, targetAngles, 8);
      delay(100);

      servos[0] = 4; targetAngles[0] = RotacaoPernaEsqMin1 // Rotações perna esquerda
      servos[1] = 5; targetAngles[1] = RotacaoPernaEsqMin2;
      servos[2] = 6; targetAngles[2] = RotacaoPernaDirMax1; // Rotações perna direita
      servos[3] = 7; targetAngles[3] = ERotacaoPernaDirMax1;
      moveServosTogether(servos, targetAngles, 4);
}

      servos[0] = 8; targetAngles[0] = MoveCoxaEsqMax1; // Rotações perna esquerda
      servos[1] = 9; targetAngles[1] = MoveCoxaEsqMax2;
      servos[2] = 10; targetAngles[2] = MoveCoxaDirMax1; // Rotações perna direita
      servos[3] = 11; targetAngles[3] = MoveCoxaDirMax2;

      servos[4] = 12; targetAngles[4] = MovePantDirMax1; // Rotações perna esquerda
      servos[5] = 13; targetAngles[5] = MovePantDirMax2;
      servos[6] = 14; targetAngles[6] = MovePantEsqMax1; // Rotações perna direita
      servos[7] = 15; targetAngles[7] = MovePantEsqMax2;
      moveServosTogether(servos, targetAngles, 8);
      break;

    default:
      return; // Comando inválido, não faz nada
  }
}


void controleCabeca(char command) {
  int servos[4];
  int targetAngles[4];

  switch (command) {
    case '2': // Pescoço e cabeça na posição inicial
      servos[0] = 0; targetAngles[0] = PescocoMed;
      servos[1] = 1; targetAngles[1] = RotacaoCabecaMed;
      moveServosTogether(servos, targetAngles, 2);
      break;

    case '1': // Cabeça rotaciona para a direita
      servos[0] = 0; targetAngles[0] = PescocoMin;
      servos[1] = 1; targetAngles[1] = RotacaoCabecaDirMax;
      moveServosTogether(servos, targetAngles, 2);
      break;

    case '3': // Cabeça rotaciona para a esquerda
      servos[0] = 0; targetAngles[0] = PescocoMax;
      servos[1] = 1; targetAngles[1] = RotacaoCabecaEsqMax;
      moveServosTogether(servos, targetAngles, 2);
      break;

    case '4': // Cabeça rotaciona para a esquerda
      servos[0] = 0; targetAngles[0] = PescocoMax;
      servos[1] = 1; targetAngles[1] = RotacaoCabecaEsqMax;
      moveServosTogether(servos, targetAngles, 2);
      delay(100);
      servos[0] = 0; targetAngles[0] = PescocoMin;
      servos[1] = 1; targetAngles[1] = RotacaoCabecaDirMax;
      moveServosTogether(servos, targetAngles, 2);
      delay(100);
      servos[0] = 0; targetAngles[0] = PescocoMax;
      servos[1] = 1; targetAngles[1] = RotacaoCabecaEsqMax;
      moveServosTogether(servos, targetAngles, 2);
      delay(100);
      servos[0] = 0; targetAngles[0] = PescocoMin;
      servos[1] = 1; targetAngles[1] = RotacaoCabecaDirMax;
      moveServosTogether(servos, targetAngles, 2);
      delay(100);
      break;

    default:
      return;
  }
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();
    controleCabeca(command);
    controlePernas(command); 
  }
  delay(100);
}
