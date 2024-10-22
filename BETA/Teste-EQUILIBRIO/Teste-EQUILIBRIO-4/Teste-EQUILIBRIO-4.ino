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
#define SERVO_NUM_2 6        // Novo Servo a ser controlado (porta 6)

int minPosition_0 = 90;      // Posição mínima do servo 0
int maxPosition_0 = 180;     // Posição máxima do servo 0
int initialPosition_0 = 130; // Posição inicial do servo 0
int servoPosition_0 = initialPosition_0; // Posição atual do servo 0

int minPosition_1 = 40;      // Posição mínima do servo 1
int maxPosition_1 = 130;     // Posição máxima do servo 1
int initialPosition_1 = 75;  // Posição inicial do servo 1
int servoPosition_1 = initialPosition_1; // Posição atual do servo 1

int minPosition_2 = 90;      // Posição mínima do novo servo 2
int maxPosition_2 = 150;     // Posição máxima do novo servo 2
int initialPosition_2 = 120; // Posição inicial do servo 2
int servoPosition_2 = initialPosition_2; // Posição atual do servo 2

int moveSpeed = 1;           // Velocidade do movimento

int olhoDireito = 12;
int olhoEsquerdo = 13;

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50); // Frequência de 50 Hz para servos
  
  pinMode(olhoDireito, OUTPUT);
  pinMode(olhoEsquerdo, OUTPUT);

  digitalWrite(olhoDireito, HIGH);
  digitalWrite(olhoEsquerdo, HIGH);
  
  // Inicializa o MPU6050
  if (!mpu.begin()) {
    Serial.println("Falha ao inicializar o MPU6050!");
    while (1);
  }

  // Inicializa os servos nas posições iniciais
  pwm.setPWM(SERVO_NUM_0, 0, map(initialPosition_0, 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE));
  pwm.setPWM(SERVO_NUM_1, 0, map(initialPosition_1, 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE));
  pwm.setPWM(SERVO_NUM_2, 0, map(initialPosition_2, 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE)); // Inicia servo 2
}

void loop() {
  // Lê as leituras do acelerômetro
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Controle do servo 0 (porta 0)
  int targetPosition_0 = initialPosition_0;
  if (a.acceleration.z < -4) {
    targetPosition_0 = maxPosition_0;
  } else if (a.acceleration.z > 4) {
    targetPosition_0 = minPosition_0;
  } else {
    targetPosition_0 = map(a.acceleration.z, -4, 4, minPosition_0, maxPosition_0);
  }
  moveServoSmoothly(SERVO_NUM_0, targetPosition_0, moveSpeed);

  // Controle do servo 1 (porta 3)
  int targetPosition_1 = initialPosition_1;
  if (a.acceleration.z < -4) {
    targetPosition_1 = maxPosition_1;
  } else if (a.acceleration.z > 4) {
    targetPosition_1 = minPosition_1;
  } else {
    targetPosition_1 = map(a.acceleration.z, -4, 4, minPosition_1, maxPosition_1);
  }
  moveServoSmoothly(SERVO_NUM_1, targetPosition_1, moveSpeed);

  // Controle do servo 2 (porta 6)
  int targetPosition_2 = initialPosition_2;
  if (a.acceleration.z < -4) {
    targetPosition_2 = maxPosition_2; // Posição 150 quando Z < -4
  } else if (a.acceleration.z > 4) {
    targetPosition_2 = minPosition_2; // Posição 90 quando Z > 4
  } else {
    targetPosition_2 = map(a.acceleration.z, -4, 4, minPosition_2, maxPosition_2);
  }
  moveServoSmoothly(SERVO_NUM_2, targetPosition_2, moveSpeed);

  delay(20);
}

void moveServoSmoothly(int servoNum, int targetAngle, int speed) {
  if (servoNum == SERVO_NUM_0) {
    if (servoPosition_0 < targetAngle) {
      servoPosition_0 = min(servoPosition_0 + speed, targetAngle);
    } else if (servoPosition_0 > targetAngle) {
      servoPosition_0 = max(servoPosition_0 - speed, targetAngle);
    }
    int targetPulse = map(servoPosition_0, 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE);
    pwm.setPWM(servoNum, 0, targetPulse);
  } else if (servoNum == SERVO_NUM_1) {
    if (servoPosition_1 < targetAngle) {
      servoPosition_1 = min(servoPosition_1 + speed, targetAngle);
    } else if (servoPosition_1 > targetAngle) {
      servoPosition_1 = max(servoPosition_1 - speed, targetAngle);
    }
    int targetPulse = map(servoPosition_1, 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE);
    pwm.setPWM(servoNum, 0, targetPulse);
  } else if (servoNum == SERVO_NUM_2) { // Adiciona controle do servo 2
    if (servoPosition_2 < targetAngle) {
      servoPosition_2 = min(servoPosition_2 + speed, targetAngle);
    } else if (servoPosition_2 > targetAngle) {
      servoPosition_2 = max(servoPosition_2 - speed, targetAngle);
    }
    int targetPulse = map(servoPosition_2, 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE);
    pwm.setPWM(servoNum, 0, targetPulse);
  }
}
