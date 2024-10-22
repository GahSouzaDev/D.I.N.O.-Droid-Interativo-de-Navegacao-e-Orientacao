#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Cria o objeto para o controle do PCA9685
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Define os limites para os servos da perna direita (9 e 8)
#define S9_MAX 118
#define S9_MED 133
#define S9_MIN 148

#define S8_MAX 108
#define S8_MED 123
#define S8_MIN 138

// Define os limites para os servos da perna esquerda (11 e 10)
#define S11_MAX 100
#define S11_MED 85
#define S11_MIN 70

#define S10_MAX 90
#define S10_MED 75
#define S10_MIN 60

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50);  // Frequência de 50 Hz para os servos
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();  // Lê o comando enviado via serial

    switch (command) {
      case '1':
        // Coloca todos os servos na posição máxima
        pwm.setPWM(9, 0, pulseLength(S9_MAX));
        pwm.setPWM(8, 0, pulseLength(S8_MAX));
        pwm.setPWM(11, 0, pulseLength(S11_MAX));
        pwm.setPWM(10, 0, pulseLength(S10_MAX));
        break;

      case '2':
        // Coloca todos os servos na posição média
        pwm.setPWM(9, 0, pulseLength(S9_MED));
        pwm.setPWM(8, 0, pulseLength(S8_MED));
        pwm.setPWM(11, 0, pulseLength(S11_MED));
        pwm.setPWM(10, 0, pulseLength(S10_MED));
        break;

      case '3':
        // Coloca todos os servos na posição mínima
        pwm.setPWM(9, 0, pulseLength(S9_MIN));
        pwm.setPWM(8, 0, pulseLength(S8_MIN));
        pwm.setPWM(11, 0, pulseLength(S11_MIN));
        pwm.setPWM(10, 0, pulseLength(S10_MIN));
        break;

      case '4':
        // Coloca a perna esquerda no máximo e a perna direita na posição média
        pwm.setPWM(11, 0, pulseLength(S11_MAX));
        pwm.setPWM(10, 0, pulseLength(S10_MAX));
        pwm.setPWM(9, 0, pulseLength(S9_MED));
        pwm.setPWM(8, 0, pulseLength(S8_MED));
        break;

      case '5':
        // Coloca a perna direita no máximo e a perna esquerda na posição média
        pwm.setPWM(9, 0, pulseLength(S9_MAX));
        pwm.setPWM(8, 0, pulseLength(S8_MAX));
        pwm.setPWM(11, 0, pulseLength(S11_MED));
        pwm.setPWM(10, 0, pulseLength(S10_MED));
        break;

      case '6':
        // Coloca a perna esquerda no mínimo e a perna direita no máximo
        pwm.setPWM(11, 0, pulseLength(S11_MIN));
        pwm.setPWM(10, 0, pulseLength(S10_MIN));
        pwm.setPWM(9, 0, pulseLength(S9_MAX));
        pwm.setPWM(8, 0, pulseLength(S8_MAX));
        break;

      case '7':
        // Coloca a perna direita no mínimo e a perna esquerda no máximo
        pwm.setPWM(9, 0, pulseLength(S9_MIN));
        pwm.setPWM(8, 0, pulseLength(S8_MIN));
        pwm.setPWM(11, 0, pulseLength(S11_MAX));
        pwm.setPWM(10, 0, pulseLength(S10_MAX));
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
