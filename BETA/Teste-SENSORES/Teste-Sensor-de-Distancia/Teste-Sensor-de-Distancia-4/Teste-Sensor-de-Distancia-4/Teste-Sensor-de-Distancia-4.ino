#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Definições para os pulsos do servo
#define SERVO_MIN_PULSE 112 // Pulso mínimo para o servo
#define SERVO_MAX_PULSE 512 // Pulso máximo para o servo

// Inicialização do driver PWM
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Pinos do sensor ultrassonico
const int trigPin = 4;
const int echoPin = 5;

// Pinos dos LEDs
const int ledVerde = 14;
const int ledAmarelo = 27;
const int ledVermelho = 26;

// Parâmetros do servo
const int servoChannel = 1; // Canal do servo no PCA9685
const int anguloInicial = 10; // Ângulo inicial do servo
const int anguloFinal = 190; // Ângulo final do servo
const int incremento = 10; // Incremento dos ângulos

// Variáveis para distância
long duracao;
int distancia;
int melhorAngulo = 0; // Armazena o ângulo com a maior distância
int maiorDistancia = 0; // Armazena a maior distância

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

  // Espera um segundo antes de começar a varredura
  delay(1000);
  
  // Move o servo para a posição inicial
  pwm.setPWM(servoChannel, 0, anguloParaPulso(anguloInicial));
  delay(1000); // Tempo para estabilizar na posição inicial

  // Realiza a varredura
  for (int angulo = anguloInicial; angulo <= anguloFinal; angulo += incremento) {
    // Move o servo para o ângulo atual
    pwm.setPWM(servoChannel, 0, anguloParaPulso(angulo));
    delay(500); // Aguarda o servo se mover

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

    // Atualiza a maior distância e o ângulo correspondente
    if (distancia > maiorDistancia) {
      maiorDistancia = distancia;
      melhorAngulo = angulo;
    }

    // Controle dos LEDs com base na distância
    if (distancia > 60) {
      digitalWrite(ledVerde, HIGH);
      digitalWrite(ledAmarelo, LOW);
      digitalWrite(ledVermelho, LOW);
    } else if (distancia > 30) {
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledAmarelo, HIGH);
      digitalWrite(ledVermelho, LOW);
    } else {
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledAmarelo, LOW);
      digitalWrite(ledVermelho, HIGH);
    }
  }

  // Após a varredura, exibe o ângulo com a maior distância
  Serial.print("Melhor angulo: ");
  Serial.print(melhorAngulo);
  Serial.print(" graus, com distancia: ");
  Serial.print(maiorDistancia);
  Serial.println(" cm");

  // Move o servo para o melhor ângulo encontrado
  pwm.setPWM(servoChannel, 0, anguloParaPulso(melhorAngulo));
  delay(1000); // Aguarda um segundo para estabilizar na nova posição
}

void loop() {
  // O loop está vazio, pois não queremos varreduras repetidas
}
