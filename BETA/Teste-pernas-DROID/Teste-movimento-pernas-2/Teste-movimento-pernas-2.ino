#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Definições para os servos
#define SERVO_MIN_PULSE 112  // Posição mínima do pulso
#define SERVO_MAX_PULSE 512  // Posição máxima do pulso

// Números dos servos (agora nas portas 8, 9, 10 e 11)
#define SERVO_8 8
#define SERVO_9 9
#define SERVO_10 10
#define SERVO_11 11

// Variáveis para armazenar a posição dos servos
int servoPosition_8 = 90;
int servoPosition_9 = 90;
int servoPosition_10 = 90;
int servoPosition_11 = 90;

int moveSpeed = 20; // Velocidade padrão

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50); // Frequência de 50 Hz para servos

  // Inicializa os servos na posição 90 graus
  setServoAngle(SERVO_8, 90);
  setServoAngle(SERVO_9, 90);
  setServoAngle(SERVO_10, 90);
  setServoAngle(SERVO_11, 90);

  Serial.println("Sistema pronto. Envie comandos no formato 'sX angulo'. Exemplo: s8 50");
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
    else if (input.startsWith("s8 ")) {
      int angle = input.substring(3).toInt();
      moveServoSmoothly(SERVO_8, angle, moveSpeed);
    } 
    else if (input.startsWith("s9 ")) {
      int angle = input.substring(3).toInt();
      moveServoSmoothly(SERVO_9, angle, moveSpeed);
    } 
    else if (input.startsWith("s10 ")) {
      int angle = input.substring(4).toInt();
      moveServoSmoothly(SERVO_10, angle, moveSpeed);
    } 
    else if (input.startsWith("s11 ")) {
      int angle = input.substring(4).toInt();
      moveServoSmoothly(SERVO_11, angle, moveSpeed);
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
  if (servoNum == SERVO_8) {
    servoPosition = &servoPosition_8;
  } else if (servoNum == SERVO_9) {
    servoPosition = &servoPosition_9;
  } else if (servoNum == SERVO_10) {
    servoPosition = &servoPosition_10;
  } else if (servoNum == SERVO_11) {
    servoPosition = &servoPosition_11;
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
