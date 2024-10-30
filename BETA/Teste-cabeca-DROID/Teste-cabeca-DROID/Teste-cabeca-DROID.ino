#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Configurações do servo
#define SERVO_MIN_PULSE 112  // Posição mínima do pulso
#define SERVO_MAX_PULSE 512  // Posição máxima do pulso

// Configurações de ângulos dos servos
int minPosition[4] = {100, 0, 90, 50};    // Posições mínimas
int initialPosition[4] = {140, 100, 130, 80}; // Posições iniciais
int maxPosition[4] = {170, 180, 150, 140}; // Posições máximas
int currentPosition[4] = {140, 100, 130, 80}; // Posições atuais

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50);  // Frequência de 50 Hz para servos

  // Inicializa os servos suavemente nas posições iniciais
  for (int i = 0; i < 4; i++) {
    int targetPulse = map(initialPosition[i], 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE);
    pwm.setPWM(i, 0, targetPulse);
    currentPosition[i] = initialPosition[i]; // Atualiza a posição atual para a posição inicial
  }
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();
    processCommand(command);
  }
  delay(50); // Pequeno atraso para evitar sobrecarga na CPU
}

void processCommand(char command) {
  int servoNum = -1;
  int targetAngle;

  switch (command) {
    case '1': servoNum = 0; targetAngle = maxPosition[0]; break;
    case '2': servoNum = 0; targetAngle = initialPosition[0]; break;
    case '3': servoNum = 0; targetAngle = minPosition[0]; break;
    case 'q': servoNum = 1; targetAngle = minPosition[1]; break;
    case 'w': servoNum = 1; targetAngle = initialPosition[1]; break;
    case 'e': servoNum = 1; targetAngle = maxPosition[1]; break;
    case 'a': servoNum = 2; targetAngle = maxPosition[2]; break;
    case 's': servoNum = 2; targetAngle = initialPosition[2]; break;
    case 'd': servoNum = 2; targetAngle = minPosition[2]; break;
    case 'z': servoNum = 3; targetAngle = minPosition[3]; break;
    case 'x': servoNum = 3; targetAngle = initialPosition[3]; break;
    case 'c': servoNum = 3; targetAngle = maxPosition[3]; break;
    default: return; // Comando inválido, sai da função
  }

  if (servoNum != -1) {
    moveServo(servoNum, targetAngle);
  }
}

void moveServo(int servoNum, int targetAngle) {
  int startPulse = map(currentPosition[servoNum], 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE);
  int endPulse = map(targetAngle, 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE);

  if (startPulse < endPulse) {
    for (int pos = startPulse; pos <= endPulse; pos++) {
      pwm.setPWM(servoNum, 0, pos);
      delay(5); // Atraso para suavizar o movimento
    }
  } else {
    for (int pos = startPulse; pos >= endPulse; pos--) {
      pwm.setPWM(servoNum, 0, pos);
      delay(5); // Atraso para suavizar o movimento
    }
  }

  currentPosition[servoNum] = targetAngle; // Atualiza a posição atual
}
