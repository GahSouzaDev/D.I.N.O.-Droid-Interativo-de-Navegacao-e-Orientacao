#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Definições para os servos
#define SERVO_MIN_PULSE 112  // Posição mínima do pulso
#define SERVO_MAX_PULSE 512  // Posição máxima do pulso

// Números dos servos (agora nas portas 12, 13, 14 e 15)
#define SERVO_12 12
#define SERVO_13 13
#define SERVO_14 14
#define SERVO_15 15

// Variáveis para armazenar a posição dos servos
int servoPosition_12 = 90;
int servoPosition_13 = 90;
int servoPosition_14 = 90;
int servoPosition_15 = 90;

int moveSpeed = 20; // Velocidade padrão

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50); // Frequência de 50 Hz para servos

  // Inicializa os servos na posição 90 graus
  setServoAngle(SERVO_12, 90);
  setServoAngle(SERVO_13, 90);
  setServoAngle(SERVO_14, 90);
  setServoAngle(SERVO_15, 90);

  Serial.println("Sistema pronto. Envie comandos no formato 'sX angulo'. Exemplo: s12 50");
}

void loop() {
  // Verifica se há algum dado no Serial
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim(); // Remove espaços em branco extras

    // Verifica se é um comando de velocidade
    if (input.startsWith("speed ")) {
      moveSpeed = input.substring(6).toInt(); // Obtém a nova velocidade
      Serial.print("Velocidade ajustada para: ");
      Serial.println(moveSpeed);
    }

    // Comando para mover os servos
    else if (input.startsWith("s12 ")) {
      int angle = input.substring(4).toInt();
      moveServoSmoothly(SERVO_12, angle, moveSpeed);
    } 
    else if (input.startsWith("s13 ")) {
      int angle = input.substring(4).toInt();
      moveServoSmoothly(SERVO_13, angle, moveSpeed);
    } 
    else if (input.startsWith("s14 ")) {
      int angle = input.substring(4).toInt();
      moveServoSmoothly(SERVO_14, angle, moveSpeed);
    } 
    else if (input.startsWith("s15 ")) {
      int angle = input.substring(4).toInt();
      moveServoSmoothly(SERVO_15, angle, moveSpeed);
    }
  }
  delay(20);
}

// Função para mover o servo para o ângulo especificado
void setServoAngle(int servoNum, int angle) {
  int pulse = map(angle, 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE);
  pwm.setPWM(servoNum, 0, pulse);
}

// Função para mover o servo suavemente
void moveServoSmoothly(int servoNum, int targetAngle, int speed) {
  int *servoPosition;

  // Define qual variável de posição usar com base no número do servo
  if (servoNum == SERVO_12) {
    servoPosition = &servoPosition_12;
  } else if (servoNum == SERVO_13) {
    servoPosition = &servoPosition_13;
  } else if (servoNum == SERVO_14) {
    servoPosition = &servoPosition_14;
  } else if (servoNum == SERVO_15) {
    servoPosition = &servoPosition_15;
  }

  // Movimenta o servo de forma suave até o ângulo desejado
  while (*servoPosition != targetAngle) {
    if (*servoPosition < targetAngle) {
      *servoPosition = min(*servoPosition + speed, targetAngle);
    } else if (*servoPosition > targetAngle) {
      *servoPosition = max(*servoPosition - speed, targetAngle);
    }
    
    // Atualiza o ângulo do servo
    setServoAngle(servoNum, *servoPosition);
    delay(20); // Atraso para controlar a velocidade do movimento
  }
}
