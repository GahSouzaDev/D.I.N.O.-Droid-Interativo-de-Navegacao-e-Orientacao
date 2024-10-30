//D.I.N.O.
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_MIN_PULSE 112 // Pulso mínimo para o servo
#define SERVO_MAX_PULSE 512 // Pulso máximo para o servo

int minPosition[16] = {60, 5, 90, 40, 60, 120, 60, 135, 135, 135, 50, 60, 70, 80, 105, 115};
int initialPosition[16] = {115, 100, 120, 75, 90, 90, 90, 105, 120, 120, 65, 75, 80, 90, 95, 105};
int maxPosition[16] = {160, 195, 150, 130, 120, 60, 120, 75, 105, 105, 80, 90, 90, 100, 85, 95};
int currentPosition[16] = {115, 100, 120, 75, 90, 90, 90, 105, 120, 120, 65, 75, 80, 90, 95, 105};

#define LED_ESP32 2       
#define OLHO_ESQUERDO 14  
#define OLHO_DIREITO 12   
#define LED_VERMELHO 32    
#define LED_AMARELO 26    
#define LED_VERDE 33   
#define LED_AZUL 27       
#define BUZZER 34         

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

  pinMode(LED_ESP32, OUTPUT);
  pinMode(OLHO_ESQUERDO, OUTPUT);
  pinMode(OLHO_DIREITO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void processCommand(char command) {
  int servos[16];        // Array para armazenar os índices dos servos que queremos mover.
  int targetAngles[16];   // Array para armazenar os ângulos de destino desses servos.

  switch (command) {
    case '1':
      servos[0] = 0;                      // Define o servo de índice 0.
      targetAngles[0] = initialPosition[0]; // Define o ângulo de destino para o servo 0 com a posição inicial.
      
      servos[1] = 1;                      // Define o servo de índice 1.
      targetAngles[1] = initialPosition[1]; // Define o ângulo de destino para o servo 1 com a posição inicial.
      
      moveServosTogether(servos, targetAngles, 2); // Move os dois servos (0 e 1) para as posições definidas.
      break;

    case '2':
      servos[0] = 0;                      // Define o servo de índice 0.
      targetAngles[0] = minPosition[0];     // Define o ângulo de destino para o servo 0 na posição mínima.
      
      servos[1] = 1;                      // Define o servo de índice 1.
      targetAngles[1] = minPosition[1];     // Define o ângulo de destino para o servo 1 na posição mínima.
      
      moveServosTogether(servos, targetAngles, 2); // Move os dois servos (0 e 1) para as posições definidas.
      break;

    case '3':
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

void loop() {
  if (Serial.available()) {
    char command = Serial.read();
    processCommand(command);
  }
  delay(50);
}
