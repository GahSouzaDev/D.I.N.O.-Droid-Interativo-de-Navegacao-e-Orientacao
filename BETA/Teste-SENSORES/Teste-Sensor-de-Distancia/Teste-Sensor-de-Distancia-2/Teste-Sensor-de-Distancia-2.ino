#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Definições para os pulsos do servo
#define SERVO_MIN_PULSE 112 // Pulso mínimo para o servo
#define SERVO_MAX_PULSE 512 // Pulso máximo para o servo

// Inicialização do driver PWM
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Pinos do sensor ultrassônico
const int trigPin = 4;
const int echoPin = 5;

// Pinos dos LEDs
const int ledVerde = 14;
const int ledAmarelo = 27;
const int ledVermelho = 26;

// Parâmetros do servo
const int servoChannel = 1; // Canal do servo no PCA9685
int angulo = 100; // Posição inicial do servo
int direcao = 1; // 1 para aumentar o ângulo, -1 para diminuir

// Variáveis para distância
long duracao;
int distancia;

// Função para converter ângulo em pulsos para o servo
int anguloParaPulso(int angulo) {
  int pulso = map(angulo, 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE);
  return pulso;
}

void setup() {
  // Inicialização do driver PWM
  pwm.begin();
  pwm.setPWMFreq(50); // Frequência de 50 Hz para controle de servos

  // Configuração dos pinos do sensor ultrassônico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Configuração dos pinos dos LEDs
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);

  // Inicializa o monitor serial
  Serial.begin(9600);

  // Move o servo para a posição inicial
  pwm.setPWM(servoChannel, 0, anguloParaPulso(angulo));
  delay(1000); // Tempo para estabilizar na posição inicial
}

void loop() {
  // Gera um pulso no pino TRIG do sensor ultrassônico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Leitura do tempo de resposta do ECHO
  duracao = pulseIn(echoPin, HIGH);

  // Calcula a distância em centímetros
  distancia = duracao * 0.034 / 2;

  // Imprime a distância e o ângulo no monitor serial
  Serial.print("Angulo: ");
  Serial.print(angulo);
  Serial.print(" graus, Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  // Controle dos LEDs com base na distância
  if (distancia > 60) {
    // Distância maior que 30 cm - LED Verde aceso
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, LOW);
  } else if (distancia > 30 && distancia <= 60) {
    // Distância entre 10 cm e 30 cm - LED Amarelo aceso
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVermelho, LOW);
  } else {
    // Distância menor que 10 cm - LED Vermelho piscando
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, HIGH);
  }

  // Atualiza o ângulo do servo para criar o efeito de sonar
  angulo += direcao * 5; // Muda o ângulo na velocidade de 3 graus

  // Verifica os limites do movimento do servo
  if (angulo >= 190) {
    direcao = -1; // Inverte a direção para voltar para 10 graus
  } else if (angulo <= 10) {
    direcao = 1; // Inverte a direção para ir até 190 graus
  }

  // Move o servo para o novo ângulo
  pwm.setPWM(servoChannel, 0, anguloParaPulso(angulo));

  // Pausa para dar tempo ao servo e ao sensor
  delay(100);
}
