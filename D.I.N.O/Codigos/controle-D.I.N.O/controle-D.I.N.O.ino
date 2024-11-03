//D.I.N.O.
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_MIN_PULSE 112 // Pulso mínimo para o servo
#define SERVO_MAX_PULSE 512 // Pulso máximo para o servo

int minPosition[16] = {90, 0, 90, 40, 60, 120, 60, 135, 135, 135, 50, 60, 70, 80, 105, 115};
int initialPosition[16] = {130, 100, 120, 75, 90, 90, 90, 105, 120, 120, 65, 75, 80, 90, 95, 105};
int maxPosition[16] = {160, 190, 150, 130, 120, 60, 120, 75, 105, 105, 80, 90, 90, 100, 85, 95};
int currentPosition[16] = {130, 100, 120, 75, 90, 90, 90, 105, 120, 120, 65, 75, 80, 90, 95, 105};

//S0, S1, S2 E S3 CABEÇA
//S4, S5, S6 E S7 ROTAÇÃO PERNAS
//S8, S9, S10 E S11 
//S12, S13, S14 E S15

#define LED_ESP32 2       
#define OLHO_ESQUERDO 14  
#define OLHO_DIREITO 12   
#define LED_VERMELHO 32    
#define LED_AMARELO 26    
#define LED_VERDE 33   
#define LED_AZUL 27       
#define BUZZER 34         

void moveServosTogether(int servos[], int targetAngles[], int numServos) {
  bool movement = true;
  while (movement) {
    movement = false;
    for (int i = 0; i < numServos; i++) {
      int startPulse = map(currentPosition[servos[i]], 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE);
      int endPulse = map(targetAngles[i], 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE);

      if (currentPosition[servos[i]] < targetAngles[i]) {
        currentPosition[servos[i]]++;
        pwm.setPWM(servos[i], 0, map(currentPosition[servos[i]], 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE));
        movement = true;
      } else if (currentPosition[servos[i]] > targetAngles[i]) {
        currentPosition[servos[i]]--;
        pwm.setPWM(servos[i], 0, map(currentPosition[servos[i]], 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE));
        movement = true;
      }
    }
    delay(20); // Pequeno atraso para controlar a velocidade do movimento simultâneo
  }
}

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50);

  for (int i = 0; i < 16; i++) {
    currentPosition[i] = initialPosition[i];
    pwm.setPWM(i, 0, map(initialPosition[i], 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE));
  }

  pinMode(LED_ESP32, OUTPUT);
  pinMode(OLHO_ESQUERDO, OUTPUT);
  pinMode(OLHO_DIREITO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();

    // Chama a função de controle da cabeça ou das pernas com base no comando
    controleCabeca(command);  // Comandos para a cabeça
    controlePernas(command);   // Comandos para as pernas
  }
  delay(100);
}