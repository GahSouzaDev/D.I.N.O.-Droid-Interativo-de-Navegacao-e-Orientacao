//D.I.N.O.
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_MIN_PULSE 112 // Pulso mínimo para o servo
#define SERVO_MAX_PULSE 512 // Pulso máximo para o servo

int minPosition[16] = {60, 5, 90, 40, 60, 120, 60, 135, 135, 135, 50, 60, 70, 80, 105, 115};       // Posições mínimas
int initialPosition[16] = {115, 100, 120, 75, 90, 90, 90, 105, 120, 120, 65, 75, 80, 90, 95, 105}; // Posições iniciais
int maxPosition[16] = {160, 195, 150, 130, 120, 60, 120, 75, 105, 105, 80, 90, 90, 100, 85, 95};   // Posições máximas
int currentPosition[16] = {115, 100, 120, 75, 90, 90, 90, 105, 120, 120, 65, 75, 80, 90, 95, 105}; // Posições atuais

// Definição dos pinos
#define LED_ESP32 2       // LED integrado no ESP32
#define OLHO_ESQUERDO 14  // Olho esquerdo
#define OLHO_DIREITO 12   // Olho direito
#define LED_VERMELHO 32   // LED vermelho
#define LED_AMARELO 26    // LED amarelo
#define LED_VERDE 33      // LED verde
#define LED_AZUL 27       // LED azul
#define BUZZER 34         // Buzzer

void moveServo(int servoNum, int targetAngle) {
  int startPulse = map(currentPosition[servoNum], 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE);
  int endPulse = map(targetAngle, 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE);

  if (startPulse < endPulse) {
    for (int pos = startPulse; pos <= endPulse; pos++) {
      pwm.setPWM(servoNum, 0, pos);
      delay(4);
    }
  } else {
    for (int pos = startPulse; pos >= endPulse; pos--) {
      pwm.setPWM(servoNum, 0, pos);
      delay(4);
    }
  }
  currentPosition[servoNum] = targetAngle;
}

// Função para piscar os olhos
void piscarOlhos() {
  digitalWrite(OLHO_ESQUERDO, HIGH);
  digitalWrite(OLHO_DIREITO, HIGH);
  delay(80);
  digitalWrite(OLHO_ESQUERDO, LOW);
  digitalWrite(OLHO_DIREITO, LOW);
  delay(150);
  digitalWrite(OLHO_ESQUERDO, HIGH);
  digitalWrite(OLHO_DIREITO, HIGH);
  delay(2000);
  digitalWrite(OLHO_ESQUERDO, LOW);
  digitalWrite(OLHO_DIREITO, LOW);
  delay(180);
  digitalWrite(OLHO_ESQUERDO, HIGH);
  digitalWrite(OLHO_DIREITO, HIGH);
  delay(3500);
  digitalWrite(OLHO_ESQUERDO, LOW);
  digitalWrite(OLHO_DIREITO, LOW);
  delay(150);
  digitalWrite(OLHO_ESQUERDO, HIGH);
  digitalWrite(OLHO_DIREITO, HIGH);
  delay(60);
  digitalWrite(OLHO_ESQUERDO, LOW);
  digitalWrite(OLHO_DIREITO, LOW);
  delay(200);
  digitalWrite(OLHO_ESQUERDO, HIGH);
  digitalWrite(OLHO_DIREITO, HIGH);
  delay(2500);
  digitalWrite(OLHO_ESQUERDO, LOW);
  digitalWrite(OLHO_DIREITO, LOW);
  delay(100);
  digitalWrite(OLHO_ESQUERDO, HIGH);
  digitalWrite(OLHO_DIREITO, HIGH);
  delay(1800);
  digitalWrite(OLHO_ESQUERDO, LOW);
  digitalWrite(OLHO_DIREITO, LOW);
  delay(100);
}

// Função para a sequência de LEDs
void sequenciaLEDs() {
  digitalWrite(LED_VERMELHO, HIGH);
  delay(200);
  digitalWrite(LED_AMARELO, HIGH);
  delay(200);
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_VERDE, HIGH);
  delay(200);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_AZUL, HIGH);
  delay(200);
  digitalWrite(LED_VERDE, LOW);
  delay(200);
  digitalWrite(LED_AZUL, LOW);
}

// Função para os bips no buzzer
void bipBuzzer() {
  tone(BUZZER, 1000);
  delay(300);
  noTone(BUZZER);
  delay(50);
  tone(BUZZER, 1500);
  delay(300);
  noTone(BUZZER);
}

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50); // Configura a frequência para 50Hz

  for (int i = 0; i < 16; i++) {
    moveServo(i, initialPosition[i]);
  }
  
  pinMode(LED_ESP32, OUTPUT);
  pinMode(OLHO_ESQUERDO, OUTPUT);
  pinMode(OLHO_DIREITO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  sequenciaLEDs();
  bipBuzzer();
}

void processCommand(char command) {
  switch (command) {
    case '1':
      moveServo(0, initialPosition[0]);
      moveServo(1, initialPosition[1]);
      break;
    case '2':
      moveServo(0, minPosition[0]);
      moveServo(1, maxPosition[1]);
      break;
    case '3':
      moveServo(0, minPosition[0]);
      moveServo(1, maxPosition[1]);
      break;
    default:
      return;
  }
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();
    processCommand(command);
  }
  delay(50);
}
