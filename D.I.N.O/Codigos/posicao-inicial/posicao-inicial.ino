//D.I.N.O.
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_MIN_PULSE 112 // Pulso mínimo para o servo
#define SERVO_MAX_PULSE 512 // Pulso máximo para o servo

int minPosition[16] = {60, 5, 90, 40,60,120,60,135,140,140,50,60,70,80,105,115};       // Posições mínimas
int initialPosition[16] = {120, 100, 120, 75,90,90,90,105,125,125,65,75,80,90,95,105}; // Posições iniciais
int maxPosition[16] = {160, 195, 150, 130,120,60,120,75,110,110,80,90,90,100,85,95};   // Posições máximas
int currentPosition[16] = {120, 100, 120, 75,90,90,90,105,125,125,65,75,80,90,95,105}; // Posições atuais

// Definição dos pinos
#define LED_ESP32 2       // LED integrado no ESP32
#define OLHO_ESQUERDO 14  // Olho esquerdo
#define OLHO_DIREITO 12   // Olho direito
#define LED_VERMELHO 32      // LED vermelho
#define LED_AMARELO 26    // LED amarelo
#define LED_VERDE 33   // LED verde
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

// Função para piscar os olhos como olhos humanos
void piscarOlhos() {
  digitalWrite(OLHO_ESQUERDO, HIGH);
  digitalWrite(OLHO_DIREITO, HIGH);
  delay(80); // Mantém os olhos abertos por um curto tempo

  digitalWrite(OLHO_ESQUERDO, LOW);
  digitalWrite(OLHO_DIREITO, LOW);
  delay(150); // Pisca rápido, imitando o piscar humano

  digitalWrite(OLHO_ESQUERDO, HIGH);
  digitalWrite(OLHO_DIREITO, HIGH);
  delay(2000); // Mantém os olhos abertos por um tempo maior

  digitalWrite(OLHO_ESQUERDO, LOW);
  digitalWrite(OLHO_DIREITO, LOW);
  delay(180); // Pisca de novo

  digitalWrite(OLHO_ESQUERDO, HIGH);
  digitalWrite(OLHO_DIREITO, HIGH);
  delay(3500); // Mantém os olhos abertos por um tempo maior

  digitalWrite(OLHO_ESQUERDO, LOW);
  digitalWrite(OLHO_DIREITO, LOW);
  delay(150); // Pisca de novo

  digitalWrite(OLHO_ESQUERDO, HIGH);
  digitalWrite(OLHO_DIREITO, HIGH);
  delay(60); // Mantém os olhos abertos por um curto tempo

  digitalWrite(OLHO_ESQUERDO, LOW);
  digitalWrite(OLHO_DIREITO, LOW);
  delay(200); // Pisca de novo

  digitalWrite(OLHO_ESQUERDO, HIGH);
  digitalWrite(OLHO_DIREITO, HIGH);
  delay(2500); // Mantém os olhos abertos por um tempo maior

  digitalWrite(OLHO_ESQUERDO, LOW);
  digitalWrite(OLHO_DIREITO, LOW);
  delay(100); // Pisca de novo

  digitalWrite(OLHO_ESQUERDO, HIGH);
  digitalWrite(OLHO_DIREITO, HIGH);
  delay(1800); // Mantém os olhos abertos por um tempo maior

  digitalWrite(OLHO_ESQUERDO, LOW);
  digitalWrite(OLHO_DIREITO, LOW);
  delay(100); // Pisca de novo
}


// Função para a sequência de LEDs
void sequenciaLEDs() {
  digitalWrite(LED_VERMELHO, HIGH); // Liga o verde
  delay(200);

  digitalWrite(LED_AMARELO, HIGH); // Liga o amarelo
  delay(200);

  digitalWrite(LED_VERMELHO, LOW); // Apaga o verde
  digitalWrite(LED_VERDE, HIGH); // Liga o vermelho
  delay(200);

  digitalWrite(LED_AMARELO, LOW); // Apaga o amarelo
  digitalWrite(LED_AZUL, HIGH); // Liga o azul
  delay(200);

  digitalWrite(LED_VERDE, LOW); // Apaga o vermelho
  delay(200);

  digitalWrite(LED_AZUL, LOW); // Apaga o azul
}

// Função para os bips no buzzer
void bipBuzzer() {
  tone(BUZZER, 1000); // Primeiro bip com frequência de 1000 Hz
  delay(300);
  noTone(BUZZER);

  delay(50); // Pausa rápida entre os bips

  tone(BUZZER, 1500); // Segundo bip com frequência de 1500 Hz
  delay(300);
  noTone(BUZZER);
}

void setup() {
  
  pwm.begin();
  pwm.setPWMFreq(50); // Configura a frequência para 50Hz

  for (int i = 0; i < 16; i++) {
    moveServo(i, initialPosition[i]);
  }
  // Configuração dos pinos como saídas
  pinMode(LED_ESP32, OUTPUT);
  pinMode(OLHO_ESQUERDO, OUTPUT);
  pinMode(OLHO_DIREITO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);
  pinMode(BUZZER, OUTPUT);

 // Sequência de LEDs coloridos
  sequenciaLEDs();

  // Dois bips no buzzer
  bipBuzzer();

}

void loop() {

  // Piscar olhos de forma natural
  piscarOlhos();

}