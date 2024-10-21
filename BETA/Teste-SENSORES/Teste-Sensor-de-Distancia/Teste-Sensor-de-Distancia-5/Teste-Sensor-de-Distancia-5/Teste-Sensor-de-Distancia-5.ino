#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Configurações de Wi-Fi
const char* ssid = "NomeDoSeuWifi"; // Substitua pelo seu SSID
const char* password = "SenhaDoSeuWifi"; // Substitua pela sua senha

// Criação do servidor na porta 80
WebServer server(80);

// Configurações do sensor ultrassônico
const int trigPin = 4; // Pino do trigger
const int echoPin = 5; // Pino do echo

// Inicialização do driver PWM
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
const int servoChannel = 1; // Canal do servo no PCA9685

// Parâmetros do servo
int anguloServo = 0; 
int anguloHaste = -90; // Ângulo inicial da haste
int direcao = 1; // 1 para aumentar, -1 para diminuir

// HTML simples para a página do radar
const char* htmlRadar = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Radar ESP32</title>
  <style>
    body { font-family: Arial, sans-serif; text-align: center; }
    #radar { width: 300px; height: 150px; background: lightgray; border-radius: 150px 150px 0 0; position: relative; overflow: hidden; }
    .line { width: 2px; height: 150px; background: red; position: absolute; bottom: 0; transform-origin: bottom; left: 50%; margin-left: -1px; }
  </style>
</head>
<body>
  <h1>Radar ESP32</h1>
  <div id="radar">
    <div class="line" id="line" style="transform: rotate(-90deg);"></div>
  </div>
  <p>Distância: <span id="distance">0</span> cm</p>
  <script>
    setInterval(() => {
      fetch('/data').then(response => response.json()).then(data => {
        document.getElementById("line").style.transform = `rotate(${data.angle}deg)`;
        document.getElementById("distance").innerText = data.distance;
      });
    }, 100);
  </script>
</body>
</html>
)rawliteral";

// Função para lidar com a requisição da página principal
void handleRoot() {
  server.send(200, "text/html", htmlRadar);
}

// Função para lidar com a requisição de dados (ângulo e distância)
void handleData() {
  // Mede a distância usando o sensor ultrassônico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  // Formata os dados em JSON
  String jsonData = "{\"angle\":" + String(anguloHaste) + ",\"distance\":" + String(distance) + "}";
  server.send(200, "application/json", jsonData);
}

void setup() {
  Serial.begin(9600);
  WiFi.softAP(ssid, password);
  Serial.println("Acessar http://192.168.4.1 para visualizar o radar");

  // Configuração dos pinos do sensor ultrassônico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Inicialização do driver PWM
  pwm.begin();
  pwm.setPWMFreq(50); // Frequência de 50 Hz para controle de servos

  // Move o servo para a posição inicial
  pwm.setPWM(servoChannel, 0, anguloParaPulso(anguloServo));

  // Roteamento de requisições
  server.on("/", handleRoot);
  server.on("/data", handleData);

  // Inicia o servidor
  server.begin();
}

void loop() {
  // Trata as requisições do servidor
  server.handleClient();

  // Atualiza o ângulo do servo
  anguloServo += direcao * 3; // Incremento do ângulo do servo

  // Verifica os limites do movimento do servo
  if (anguloServo >= 180) {
    anguloServo = 180;
    anguloHaste = 90; // Atualiza o ângulo da haste
    direcao = -1; // Inverte a direção
  } else if (anguloServo <= 0) {
    anguloServo = 0;
    anguloHaste = -90; // Atualiza o ângulo da haste
    direcao = 1; // Inverte a direção
  }

  // Move o servo para o novo ângulo
  pwm.setPWM(servoChannel, 0, anguloParaPulso(anguloServo));

  // Atualiza o ângulo da haste para sincronia
  anguloHaste = map(anguloServo, 0, 180, -90, 90);

  // Pausa para dar tempo ao servo e ao sensor
  delay(100);
}

// Função para converter ângulo em pulsos para o servo
int anguloParaPulso(int angulo) {
  int pulso = map(angulo, 0, 180, 112, 512); // Mapeia ângulos para pulsos
  return pulso;
}
