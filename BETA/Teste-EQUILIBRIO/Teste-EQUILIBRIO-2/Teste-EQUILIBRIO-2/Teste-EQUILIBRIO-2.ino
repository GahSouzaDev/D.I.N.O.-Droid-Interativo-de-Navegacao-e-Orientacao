#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
Adafruit_MPU6050 mpu;

// Configurações do servo
#define SERVO_MIN_PULSE 102  // Posição mínima do pulso
#define SERVO_MAX_PULSE 512  // Posição máxima do pulso
#define SERVO_NUM 0          // Servo a ser controlado (porta 0)

int minPosition = 80;       // Posição mínima do servo
int maxPosition = 160;      // Posição máxima do servo
int initialPosition = 120;   // Posição inicial do servo
int servoPosition = initialPosition; // Posição atual do servo
int moveSpeed = 3;          // Velocidade do movimento

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50); // Frequência de 50 Hz para servos

  // Inicializa o MPU6050
  if (!mpu.begin()) {
    Serial.println("Falha ao inicializar o MPU6050!");
    while (3);
  }

  // Inicializa o servo na posição inicial
  pwm.setPWM(SERVO_NUM, 0, map(initialPosition, 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE));
}

void loop() {
  // Lê as leituras do acelerômetro
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Define a posição alvo com base no eixo Z do acelerômetro
  int targetPosition = initialPosition; // Posição padrão do servo

  // Condições para ajustar a posição do servo
  if (a.acceleration.z < -10) {
    targetPosition = maxPosition; // Mover para a posição máxima
  } else if (a.acceleration.z > 10) {
    targetPosition = minPosition; // Mover para a posição mínima
  } else {
    // Mapeia a posição do servo com base na leitura do eixo Z
    targetPosition = map(a.acceleration.z, -10, 10, minPosition, maxPosition);
  }

  // Mover servo de forma suave para a posição alvo
  moveServoSmoothly(SERVO_NUM, targetPosition, moveSpeed);

  delay(40); // Atraso para evitar sobrecarga na CPU
}

void moveServoSmoothly(int servoNum, int targetAngle, int speed) {
  // Incrementa ou decrementa a posição do servo em pequenos passos
  if (servoPosition < targetAngle) {
    servoPosition = min(servoPosition + speed, targetAngle);
  } else if (servoPosition > targetAngle) {
    servoPosition = max(servoPosition - speed, targetAngle);
  }

  // Converter o ângulo para o pulso e mover o servo
  int targetPulse = map(servoPosition, 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE);
  pwm.setPWM(servoNum, 0, targetPulse); // Mover o servo para a posição atual
}
