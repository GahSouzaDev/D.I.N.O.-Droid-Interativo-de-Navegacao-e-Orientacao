#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
Adafruit_MPU6050 mpu;

// Configurações dos servos
#define SERVO_MIN_PULSE 102  // Posição mínima do pulso
#define SERVO_MAX_PULSE 512  // Posição máxima do pulso
#define SERVO_NUM_0 0        // Servo a ser controlado (porta 0)
#define SERVO_NUM_1 3        // Servo a ser controlado (porta 3)

int minPosition_0 = 80;      // Posição mínima do servo 0
int maxPosition_0 = 160;     // Posição máxima do servo 0
int initialPosition_0 = 120;  // Posição inicial do servo 0
int servoPosition_0 = initialPosition_0; // Posição atual do servo 0
int moveSpeed = 3;           // Velocidade do movimento

int minPosition_1 = 40;      // Posição mínima do servo 1
int maxPosition_1 = 130;     // Posição máxima do servo 1
int initialPosition_1 = 75;  // Posição inicial do servo 1
int servoPosition_1 = initialPosition_1; // Posição atual do servo 1

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50); // Frequência de 50 Hz para servos

  // Inicializa o MPU6050
  if (!mpu.begin()) {
    Serial.println("Falha ao inicializar o MPU6050!");
    while (1); // Corrigido para while(1) para evitar loop infinito
  }

  // Inicializa os servos nas posições iniciais
  pwm.setPWM(SERVO_NUM_0, 0, map(initialPosition_0, 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE));
  pwm.setPWM(SERVO_NUM_1, 0, map(initialPosition_1, 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE));
}

void loop() {
  // Lê as leituras do acelerômetro
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Define a posição alvo com base no eixo Z do acelerômetro para o servo 0
  int targetPosition_0 = initialPosition_0; // Posição padrão do servo 0

  // Condições para ajustar a posição do servo 0
  if (a.acceleration.z < -10) {
    targetPosition_0 = maxPosition_0; // Mover para a posição máxima
  } else if (a.acceleration.z > 10) {
    targetPosition_0 = minPosition_0; // Mover para a posição mínima
  } else {
    // Mapeia a posição do servo com base na leitura do eixo Z
    targetPosition_0 = map(a.acceleration.z, -10, 10, minPosition_0, maxPosition_0);
  }

  // Mover servo 0 de forma suave para a posição alvo
  moveServoSmoothly(SERVO_NUM_0, targetPosition_0, moveSpeed);

  // Definindo a posição alvo para o servo 1 (porta 3)
  int targetPosition_1 = initialPosition_1; // Posição padrão do servo 1

  // Condições para ajustar a posição do servo 1
  if (a.acceleration.z < -10) {
    targetPosition_1 = maxPosition_1; // Mover para a posição máxima
  } else if (a.acceleration.z > 10) {
    targetPosition_1 = minPosition_1; // Mover para a posição mínima
  } else {
    // Mapeia a posição do servo 1 com base na leitura do eixo Z
    targetPosition_1 = map(a.acceleration.z, -10, 10, minPosition_1, maxPosition_1);
  }

  // Mover servo 1 de forma suave para a posição alvo
  moveServoSmoothly(SERVO_NUM_1, targetPosition_1, moveSpeed);

  delay(40); // Atraso para evitar sobrecarga na CPU
}

void moveServoSmoothly(int servoNum, int targetAngle, int speed) {
  // Incrementa ou decrementa a posição do servo em pequenos passos
  if (servoNum == SERVO_NUM_0) {
    if (servoPosition_0 < targetAngle) {
      servoPosition_0 = min(servoPosition_0 + speed, targetAngle);
    } else if (servoPosition_0 > targetAngle) {
      servoPosition_0 = max(servoPosition_0 - speed, targetAngle);
    }

    // Converter o ângulo para o pulso e mover o servo 0
    int targetPulse = map(servoPosition_0, 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE);
    pwm.setPWM(servoNum, 0, targetPulse); // Mover o servo 0 para a posição atual
  } else if (servoNum == SERVO_NUM_1) {
    if (servoPosition_1 < targetAngle) {
      servoPosition_1 = min(servoPosition_1 + speed, targetAngle);
    } else if (servoPosition_1 > targetAngle) {
      servoPosition_1 = max(servoPosition_1 - speed, targetAngle);
    }

    // Converter o ângulo para o pulso e mover o servo 1
    int targetPulse = map(servoPosition_1, 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE);
    pwm.setPWM(servoNum, 0, targetPulse); // Mover o servo 1 para a posição atual
  }
}
 
