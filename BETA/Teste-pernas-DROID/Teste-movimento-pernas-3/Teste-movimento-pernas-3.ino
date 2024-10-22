#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Definições para os servos
#define SERVO_MIN_PULSE 102  // Posição mínima do pulso
#define SERVO_MAX_PULSE 512  // Posição máxima do pulso

// Definições de ângulos para os servos
// Perna direita (portas 9 e 8)
#define SERVO_9_MAX 118
#define SERVO_9_MED 133
#define SERVO_9_MIN 148

#define SERVO_8_MAX 108
#define SERVO_8_MED 123
#define SERVO_8_MIN 138

// Perna esquerda (portas 11 e 10)
#define SERVO_11_MAX 100
#define SERVO_11_MED 85
#define SERVO_11_MIN 70

#define SERVO_10_MAX 90
#define SERVO_10_MED 75
#define SERVO_10_MIN 60

int moveSpeed = 20; // Velocidade padrão

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50); // Frequência de 50 Hz para servos

  // Inicializa todos os servos na posição média
  setServoAngle(9, SERVO_9_MED);
  setServoAngle(8, SERVO_8_MED);
  setServoAngle(11, SERVO_11_MED);
  setServoAngle(10, SERVO_10_MED);

  Serial.println("Sistema pronto. Envie comandos de 1 a 5 para mover as pernas sincronizadas.");
}

void loop() {
  // Verifica se há algum dado no Serial
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim(); // Remove espaços em branco extras

    if (input == "1") {
      // Coloca todas as pernas na posição máxima
      moveServoSmoothly(9, SERVO_9_MAX, moveSpeed);
      moveServoSmoothly(8, SERVO_8_MAX, moveSpeed);
      moveServoSmoothly(11, SERVO_11_MAX, moveSpeed);
      moveServoSmoothly(10, SERVO_10_MAX, moveSpeed);
    } 
    else if (input == "2") {
      // Coloca todas as pernas na posição média
      moveServoSmoothly(9, SERVO_9_MED, moveSpeed);
      moveServoSmoothly(8, SERVO_8_MED, moveSpeed);
      moveServoSmoothly(11, SERVO_11_MED, moveSpeed);
      moveServoSmoothly(10, SERVO_10_MED, moveSpeed);
    } 
    else if (input == "3") {
      // Coloca todas as pernas na posição mínima
      moveServoSmoothly(9, SERVO_9_MIN, moveSpeed);
      moveServoSmoothly(8, SERVO_8_MIN, moveSpeed);
      moveServoSmoothly(11, SERVO_11_MIN, moveSpeed);
      moveServoSmoothly(10, SERVO_10_MIN, moveSpeed);
    } 
    else if (input == "4") {
      // Coloca perna esquerda em máximo e perna direita em médio
      moveServoSmoothly(11, SERVO_11_MAX, moveSpeed);
      moveServoSmoothly(10, SERVO_10_MAX, moveSpeed);
      moveServoSmoothly(9, SERVO_9_MED, moveSpeed);
      moveServoSmoothly(8, SERVO_8_MED, moveSpeed);
    } 
    else if (input == "5") {
      // Coloca perna direita em máximo e perna esquerda em médio
      moveServoSmoothly(9, SERVO_9_MAX, moveSpeed);
      moveServoSmoothly(8, SERVO_8_MAX, moveSpeed);
      moveServoSmoothly(11, SERVO_11_MED, moveSpeed);
      moveServoSmoothly(10, SERVO_10_MED, moveSpeed);
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
  int currentPosition = targetAngle;  // Posição atual é a meta, você pode adaptar essa lógica para suavidade

  while (currentPosition != targetAngle) {
    if (currentPosition < targetAngle) {
      currentPosition = min(currentPosition + speed, targetAngle);
    } else if (currentPosition > targetAngle) {
      currentPosition = max(currentPosition - speed, targetAngle);
    }
    
    // Atualiza o ângulo do servo
    setServoAngle(servoNum, currentPosition);
    delay(20); // Atraso para controlar a velocidade do movimento
  }
}
