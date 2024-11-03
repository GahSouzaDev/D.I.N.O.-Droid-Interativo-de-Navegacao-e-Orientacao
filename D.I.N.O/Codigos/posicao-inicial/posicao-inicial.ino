//D.I.N.O.
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_MIN_PULSE 112 // Pulso mínimo para o servo
#define SERVO_MAX_PULSE 512 // Pulso máximo para o servo

int minPosition[16] = {80, 5, 90, 40,60,120,60,135,135,135,50,60,70,80,105,115};       // Posições mínimas
int initialPosition[16] = {120, 100, 120, 75,90,90,90,105,120,120,65,75,80,90,95,105}; // Posições iniciais
int maxPosition[16] = {160, 195, 150, 130,120,60,120,75,105,105,80,90,90,100,85,95};   // Posições máximas
int currentPosition[16] = {120, 100, 120, 75,90,90,90,105,120,120,65,75,80,90,95,105}; // Posições atuais

// Definição dos pinos
#define LED_ESP32 2       // LED integrado no ESP32

#define OLHO_ESQUERDO 14  // Olho esquerdo
#define OLHO_DIREITO 12   // Olho direito
// Define o brilho dos OLHOS (0 a 255)
int brilho = 10; // Você pode ajustar isso conforme necessário

#define LED_VERMELHO 32     // LED vermelho
#define LED_AMARELO 26     // LED amarelo
#define LED_VERDE 33      // LED verde
#define LED_AZUL 27       // LED azul

#define BUZZER 13         // Buzzer
         
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

  bipBuzzer();

}

void loop() {

  // Piscar olhos de forma natural
  piscarOlhos();

}