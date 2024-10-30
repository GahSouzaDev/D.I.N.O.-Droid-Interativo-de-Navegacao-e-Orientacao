//D.I.N.O.
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_MIN_PULSE 112 // Pulso mínimo para o servo
#define SERVO_MAX_PULSE 512 // Pulso máximo para o servo

int minPosition[16] = {50, 5, 90, 40,60,120,60,135,140,140,50,60,70,80,105,115};       // Posições mínimas
int initialPosition[16] = {100, 100, 120, 75,90,90,90,105,125,125,65,75,80,90,95,105}; // Posições iniciais
int maxPosition[16] = {160, 195, 150, 130,120,60,120,75,110,110,80,90,90,100,85,95};   // Posições máximas
int currentPosition[16] = {100, 100, 120, 75,90,90,90,105,125,125,65,75,80,90,95,105}; // Posições atuais

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

void setup() {
  
  pwm.begin();
  pwm.setPWMFreq(50); // Configura a frequência para 50Hz

  for (int i = 0; i < 16; i++) {
    moveServo(i, initialPosition[i]);
  }

pinMode(14 ,OUTPUT);//Olho direito
pinMode(12 ,OUTPUT);//Olho esquerdo

pinMode(25 ,OUTPUT);//LED Azul
pinMode(33 ,OUTPUT);//LED Verde
pinMode(27 ,OUTPUT);//LED Amarelo
pinMode(26 ,OUTPUT);//LED Vermelho

pinMode(34 ,OUTPUT);//Buzzer

digitalWrite(14, HIGH);
digitalWrite(12,LOW);

digitalWrite(25,LOW);
digitalWrite(33,LOW);
digitalWrite(27,LOW);
digitalWrite(26,LOW);

digitalWrite(34,LOW);

}

void loop() {
}