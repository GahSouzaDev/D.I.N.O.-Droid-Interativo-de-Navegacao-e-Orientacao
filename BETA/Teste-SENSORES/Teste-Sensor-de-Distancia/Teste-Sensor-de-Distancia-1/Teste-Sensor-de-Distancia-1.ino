// Definições de pinos
const int trigPin = 4;
const int echoPin = 5;
const int ledVerde = 14;
const int ledAmarelo = 27;
const int ledVermelho = 26;

// Variáveis para distância
long duracao;
int distancia;

void setup() {
  // Configuração dos pinos
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // Gera um pulso no pino TRIG
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Leitura do tempo de resposta do ECHO
  duracao = pulseIn(echoPin, HIGH);
  
  // Calcula a distância em centímetros
  distancia = duracao * 0.034 / 2;

  // Imprime a distância no monitor serial
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  // Controle dos LEDs
  if (distancia > 60) {
    // Distância maior que 60 cm, acende o LED verde
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, LOW);
  } else if (distancia <= 60 && distancia > 30) {
    // Distância entre 30 cm e 60 cm, acende o LED amarelo
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVermelho, LOW);
  } else if (distancia <= 30 && distancia > 10) {
    // Distância entre 10 cm e 30 cm, acende o LED vermelho
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, HIGH);
  } else {
    // Distância menor ou igual a 10 cm, faz o LED vermelho piscar
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, HIGH);
    delay(150); // Pausa de 250ms com o LED aceso
    digitalWrite(ledVermelho, LOW);
    delay(150); // Pausa de 250ms com o LED apagado
  }

  // Pausa antes da próxima leitura
  delay(100);
}
