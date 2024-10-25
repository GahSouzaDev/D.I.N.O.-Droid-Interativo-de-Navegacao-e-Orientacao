#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Cria o objeto para o controle do PCA9685
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Define os limites para os servos da perna direita (9 e 8)
#define S9_MAX 110
#define S9_MED 125
#define S9_MIN 140

#define S8_MAX 110
#define S8_MED 125
#define S8_MIN 140

// Define os limites para os servos da perna esquerda (11 e 10)
#define S11_MAX 90
#define S11_MED 75
#define S11_MIN 60

#define S10_MAX 80
#define S10_MED 65
#define S10_MIN 50

#define S13_MAX 100
#define S13_MED 90
#define S13_MIN 80

#define S12_MAX 90
#define S12_MED 80
#define S12_MIN 70

#define S15_MAX 95
#define S15_MED 105
#define S15_MIN 115

#define S14_MAX 85
#define S14_MED 95
#define S14_MIN 105

#define S4_MAX 120
#define S4_MED 90
#define S4_MIN 60

#define S5_MAX 60
#define S5_MED 90
#define S5_MIN 120

#define S6_MAX 120
#define S6_MED 90
#define S6_MIN 60

#define S7_MAX 75
#define S7_MED 105
#define S7_MIN 135

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
        pwm.setPWM(13, 0, pulseLength(S13_MAX));
        pwm.setPWM(12, 0, pulseLength(S12_MAX));
        pwm.setPWM(15, 0, pulseLength(S15_MAX));
        pwm.setPWM(14, 0, pulseLength(S14_MAX));
        break;

      case '2':
        // Coloca todos os servos na posição média
        pwm.setPWM(9, 0, pulseLength(S9_MED));
        pwm.setPWM(8, 0, pulseLength(S8_MED));
        pwm.setPWM(11, 0, pulseLength(S11_MED));
        pwm.setPWM(10, 0, pulseLength(S10_MED));
        pwm.setPWM(13, 0, pulseLength(S13_MED));
        pwm.setPWM(12, 0, pulseLength(S12_MED));
        pwm.setPWM(15, 0, pulseLength(S15_MED));
        pwm.setPWM(14, 0, pulseLength(S14_MED));
        break;

      case '3':
        // Coloca todos os servos na posição mínima
        pwm.setPWM(9, 0, pulseLength(S9_MIN));
        pwm.setPWM(8, 0, pulseLength(S8_MIN));
        pwm.setPWM(11, 0, pulseLength(S11_MIN));
        pwm.setPWM(10, 0, pulseLength(S10_MIN));
        pwm.setPWM(13, 0, pulseLength(S13_MIN));
        pwm.setPWM(12, 0, pulseLength(S12_MIN));
        pwm.setPWM(15, 0, pulseLength(S15_MIN));
        pwm.setPWM(14, 0, pulseLength(S14_MIN));
        break;        
        break;

      case '4':
        // Coloca a perna esquerda no máximo e a perna direita na posição média
        pwm.setPWM(11, 0, pulseLength(S11_MAX));
        pwm.setPWM(10, 0, pulseLength(S10_MAX));
        pwm.setPWM(9, 0, pulseLength(S9_MED));
        pwm.setPWM(8, 0, pulseLength(S8_MED));
        pwm.setPWM(13, 0, pulseLength(S13_MED));
        pwm.setPWM(12, 0, pulseLength(S12_MED));
        pwm.setPWM(15, 0, pulseLength(S15_MAX));
        pwm.setPWM(14, 0, pulseLength(S14_MAX));
        break;

      case '5':
        // Coloca a perna direita no máximo e a perna esquerda na posição média
        pwm.setPWM(9, 0, pulseLength(S9_MAX));
        pwm.setPWM(8, 0, pulseLength(S8_MAX));
        pwm.setPWM(11, 0, pulseLength(S11_MED));
        pwm.setPWM(10, 0, pulseLength(S10_MED));
        pwm.setPWM(13, 0, pulseLength(S13_MAX));
        pwm.setPWM(12, 0, pulseLength(S12_MAX));
        pwm.setPWM(15, 0, pulseLength(S15_MED));
        pwm.setPWM(14, 0, pulseLength(S14_MED));
        break;

      case '6':
        // Coloca a perna esquerda no mínimo e a perna direita no máximo
        pwm.setPWM(11, 0, pulseLength(S11_MIN));
        pwm.setPWM(10, 0, pulseLength(S10_MIN));
        pwm.setPWM(9, 0, pulseLength(S9_MAX));
        pwm.setPWM(8, 0, pulseLength(S8_MAX));
        pwm.setPWM(13, 0, pulseLength(S13_MAX));
        pwm.setPWM(12, 0, pulseLength(S12_MAX));
        pwm.setPWM(15, 0, pulseLength(S15_MIN));
        pwm.setPWM(14, 0, pulseLength(S14_MIN));
        break;

      case '7':
        // Coloca a perna direita no mínimo e a perna esquerda no máximo
        pwm.setPWM(9, 0, pulseLength(S9_MIN));
        pwm.setPWM(8, 0, pulseLength(S8_MIN));
        pwm.setPWM(11, 0, pulseLength(S11_MAX));
        pwm.setPWM(10, 0, pulseLength(S10_MAX));
        pwm.setPWM(13, 0, pulseLength(S13_MIN));
        pwm.setPWM(12, 0, pulseLength(S12_MIN));
        pwm.setPWM(15, 0, pulseLength(S15_MAX));
        pwm.setPWM(14, 0, pulseLength(S14_MAX));
        break;

        case '8':
        // Coloca a perna direita no mínimo e a perna esquerda no máximo
        pwm.setPWM(4, 0, pulseLength(S4_MIN));
        pwm.setPWM(5, 0, pulseLength(S5_MIN));
        pwm.setPWM(6, 0, pulseLength(S6_MAX));
        pwm.setPWM(7, 0, pulseLength(S7_MAX));        
        break;

        case '9':
        // Coloca a perna direita no mínimo e a perna esquerda no máximo
        pwm.setPWM(4, 0, pulseLength(S4_MAX));
        pwm.setPWM(5, 0, pulseLength(S5_MAX));
        pwm.setPWM(6, 0, pulseLength(S6_MIN));
        pwm.setPWM(7, 0, pulseLength(S7_MIN));        
        break;

        case '0':
        // Coloca a perna direita no mínimo e a perna esquerda no máximo
        pwm.setPWM(4, 0, pulseLength(S4_MED));
        pwm.setPWM(5, 0, pulseLength(S5_MED));
        pwm.setPWM(6, 0, pulseLength(S6_MED));
        pwm.setPWM(7, 0, pulseLength(S7_MED));        
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
