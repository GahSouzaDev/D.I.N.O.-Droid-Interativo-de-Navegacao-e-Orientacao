#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Cria o objeto para o controle do PCA9685
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Define os limites para os servos
#define S4_MIN 60
#define S4_MED 90
#define S4_MAX 120

#define S5_MIN 120
#define S5_MED 90
#define S5_MAX 60

#define S6_MIN 60
#define S6_MED 90
#define S6_MAX 120

#define S7_MIN 135
#define S7_MED 105
#define S7_MAX 75

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50);  // Frequência de 60 Hz para os servos
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();  // Lê o comando enviado via serial

    switch (command) {
      case '1':
        // Coloca os servos laterais na posição mínima
        pwm.setPWM(4, 0, pulseLength(S4_MIN));
        pwm.setPWM(5, 0, pulseLength(S5_MIN));
        // Coloca os servos de rotação na posição média
        pwm.setPWM(6, 0, pulseLength(S6_MIN));
        pwm.setPWM(7, 0, pulseLength(S7_MIN));
        break;

      case '2':
        // Coloca os servos laterais na posição média
        pwm.setPWM(4, 0, pulseLength(S4_MED));
        pwm.setPWM(5, 0, pulseLength(S5_MED));
        // Coloca os servos de rotação na posição média
        pwm.setPWM(6, 0, pulseLength(S6_MED));
        pwm.setPWM(7, 0, pulseLength(S7_MED));
        break;

      case '3':
        // Coloca os servos laterais na posição máxima
        pwm.setPWM(4, 0, pulseLength(S4_MAX));
        pwm.setPWM(5, 0, pulseLength(S5_MAX));
        // Coloca os servos de rotação na posição média
        pwm.setPWM(6, 0, pulseLength(S6_MAX));
        pwm.setPWM(7, 0, pulseLength(S7_MAX));
        break;

         case '4':
        // Coloca os servos laterais na posição máxima
        pwm.setPWM(4, 0, pulseLength(S4_MIN));
        pwm.setPWM(5, 0, pulseLength(S5_MIN));
        // Coloca os servos de rotação na posição média
        pwm.setPWM(6, 0, pulseLength(S6_MAX));
        pwm.setPWM(7, 0, pulseLength(S7_MAX));
        break;

         case '5':
        // Coloca os servos laterais na posição máxima
        pwm.setPWM(4, 0, pulseLength(S4_MAX));
        pwm.setPWM(5, 0, pulseLength(S5_MAX));
        // Coloca os servos de rotação na posição média
        pwm.setPWM(6, 0, pulseLength(S6_MIN));
        pwm.setPWM(7, 0, pulseLength(S7_MIN));
        break;

      default:
        // Não faz nada se o comando não for reconhecido
        break;
    }
  }
}

// Função para converter o valor do ângulo em comprimento de pulso PWM
int pulseLength(int angle) {
  int pulse = map(angle, 0, 180, 112, 512);
  return pulse;
}
