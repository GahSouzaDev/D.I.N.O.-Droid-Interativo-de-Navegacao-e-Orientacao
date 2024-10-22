#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Definições para os servos
#define SERVO_MIN_PULSE 102  // Posição mínima do pulso
#define SERVO_MAX_PULSE 512  // Posição máxima do pulso

// Números dos servos
#define SERVO_4 4
#define SERVO_5 5
#define SERVO_6 6
#define SERVO_7 7

// Variáveis para armazenar a posição dos servos
int servoPosition_4 = 90;
int servoPosition_5 = 90;
int servoPosition_6 = 90;
int servoPosition_7 = 90;

int moveSpeed = 20; // Velocidade padrão

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50); // Frequência de 50 Hz para servos

  // Inicializa os servos na posição 90 graus
  setServoAngle(SERVO_4, 110);
  setServoAngle(SERVO_5, 90);
  setServoAngle(SERVO_6, 90);
  setServoAngle(SERVO_7, 100);

  Serial.println("Sistema pronto. Envie comandos no formato 'sX angulo'. Exemplo: s4 50");
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
    else if (input.startsWith("s4 ")) {
      int angle = input.substring(3).toInt();
      moveServoSmoothly(SERVO_4, angle, moveSpeed);
    } 
    else if (input.startsWith("s5 ")) {
      int angle = input.substring(3).toInt();
      moveServoSmoothly(SERVO_5, angle, moveSpeed);
    } 
    else if (input.startsWith("s6 ")) {
      int angle = input.substring(3).toInt();
      moveServoSmoothly(SERVO_6, angle, moveSpeed);
    } 
    else if (input.startsWith("s7 ")) {
      int angle = input.substring(3).toInt();
      moveServoSmoothly(SERVO_7, angle, moveSpeed);
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
  if (servoNum == SERVO_4) {
    servoPosition = &servoPosition_4;
  } else if (servoNum == SERVO_5) {
    servoPosition = &servoPosition_5;
  } else if (servoNum == SERVO_6) {
    servoPosition = &servoPosition_6;
  } else if (servoNum == SERVO_7) {
    servoPosition = &servoPosition_7;
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
