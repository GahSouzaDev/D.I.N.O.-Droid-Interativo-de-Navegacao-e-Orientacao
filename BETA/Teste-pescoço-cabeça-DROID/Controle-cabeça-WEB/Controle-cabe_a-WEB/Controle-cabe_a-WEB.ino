#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <WiFi.h>

// Nome (SSID) e senha do ponto de acesso
const char* ssid = "DROID";    // Nome do ponto de acesso
const char* password = "12345678"; // Senha do ponto de acesso

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Configurações do servo
#define SERVO_MIN_PULSE 102  // Posição mínima do pulso
#define SERVO_MAX_PULSE 512  // Posição máxima do pulso

// Configurações de ângulos dos servos
int minPosition[4] = {100, 10, 90, 50};    // Posições mínimas
int initialPosition[4] = {140, 100, 130, 80}; // Posições iniciais
int maxPosition[4] = {170, 190, 150, 140}; // Posições máximas
int currentPosition[4] = {140, 100, 130, 80}; // Posições atuais

// Servidor web na porta 80
WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50);  // Frequência de 50 Hz para servos

  // Inicializa os servos suavemente nas posições iniciais
  for (int i = 0; i < 4; i++) {
    int targetPulse = map(initialPosition[i], 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE);
    pwm.setPWM(i, 0, targetPulse);
    
    currentPosition[i] = initialPosition[i]; // Atualiza a posição atual para a posição inicial
    
  }

  // Configura o ESP32 como ponto de acesso
  WiFi.softAP(ssid, password);
  Serial.println("Ponto de acesso criado");

  // Inicia o servidor web
  server.begin();
  Serial.println("Servidor web iniciado");
  Serial.print("Acesse http://192.168.4.1");
}

void loop() {
  // Verifica se há um cliente conectado
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Novo cliente conectado.");
    String request = client.readStringUntil('\r');
    Serial.println(request);
    //client.flush(); // Limpa o buffer do cliente

    // Processa a requisição para mover os servos
    processRequest(request);

    // Responde ao cliente com a página HTML estilizada
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html; charset=utf-8"); // Adiciona charset
    client.println("Connection: close");
    client.println();
    client.println("<!DOCTYPE HTML>");
    client.println("<html lang=\"pt-BR\">"); // Define o idioma como português do Brasil
    client.println("<head>");
    client.println("<title>Controle CABEÇA DROID</title>");
    // Estilo CSS
    client.println("<style>");
    client.println("body { font-family: Arial, sans-serif; text-align: center; background-color: #f0f0f0; margin: 0; padding: 0; }");
    client.println("h1 { font-size: 70px; color: #333; }");
    client.println("h2 { font-size: 50px; color: #333; }");
    client.println(".b1 { background-color: #FFFFE0; color: #333; }");
    client.println(".b2  { background-color: #90EE90; color: #333; }");
    client.println(".b3 { background-color: #FFCCCB; color: #333; }");
    client.println("button { padding: 30px 60px; font-size: 40px; margin: 10px; cursor: pointer; }");
    client.println("</style>");
    client.println("</head>");
    client.println("<body>");
    client.println("<h1>Controle Cabeça DROID</h1>");
    
    // Botões para controle dos servos
    client.println("<h2>Servo de Posição</h2>");
    client.println("<p><a href=\"/servo0=3\"><button class=\"b1\">Frente</button></a></p>");
    client.println("<p><a href=\"/servo0=2\"><button class=\"b2\">Meio</button></a></p>");
    client.println("<p><a href=\"/servo0=1\"><button class=\"b3\">Trás</button></a></p>");

    client.println("<h2>Servo de Direção</h2>");
    client.println("<p><a href=\"/servo1=a\"><button class=\"b1\">Esquerda</button></a></p>");
    client.println("<p><a href=\"/servo1=s\"><button class=\"b2\">Meio</button></a></p>");
    client.println("<p><a href=\"/servo1=d\"><button class=\"b3\">Direita</button></a></p>");

    client.println("<h2>Servo de Elevação</h2>");
    client.println("<p><a href=\"/servo3=q\"><button class=\"b1\">Cabeça Baixa</button></a></p>");
    client.println("<p><a href=\"/servo3=w\"><button class=\"b2\">Cabeça no Meio</button></a></p>");
    client.println("<p><a href=\"/servo3=e\"><button class=\"b3\">Cabeça Alta</button></a></p>");

    client.println("<h2>Servo Antena</h2>");
    client.println("<p><a href=\"/servo2=z\"><button class=\"b1\">Antena Alta</button></a></p>");
    client.println("<p><a href=\"/servo2=x\"><button class=\"b2\">Antena Meio</button></a></p>");
    client.println("<p><a href=\"/servo2=c\"><button class=\"b3\">Antena Baixa</button></a></p>");

    client.println("</body>");
    client.println("</html>");

    // Fecha a conexão com o cliente
    client.stop();
    Serial.println("Cliente desconectado.");
  }
}


void processRequest(String request) {
  int servoNum = -1;
  int targetAngle;

  // Identifica qual servo deve ser movido
  if (request.indexOf("/servo0=1") != -1) { servoNum = 0; targetAngle = maxPosition[0]; }
  else if (request.indexOf("/servo0=2") != -1) { servoNum = 0; targetAngle = initialPosition[0]; }
  else if (request.indexOf("/servo0=3") != -1) { servoNum = 0; targetAngle = minPosition[0]; }
  else if (request.indexOf("/servo1=a") != -1) { servoNum = 1; targetAngle = maxPosition[1]; }
  else if (request.indexOf("/servo1=s") != -1) { servoNum = 1; targetAngle = initialPosition[1]; }
  else if (request.indexOf("/servo1=d") != -1) { servoNum = 1; targetAngle = minPosition[1]; }
  else if (request.indexOf("/servo2=z") != -1) { servoNum = 2; targetAngle = minPosition[2]; }
  else if (request.indexOf("/servo2=x") != -1) { servoNum = 2; targetAngle = initialPosition[2]; }
  else if (request.indexOf("/servo2=c") != -1) { servoNum = 2; targetAngle = maxPosition[2]; }
  else if (request.indexOf("/servo3=q") != -1) { servoNum = 3; targetAngle = minPosition[3]; }
  else if (request.indexOf("/servo3=w") != -1) { servoNum = 3; targetAngle = initialPosition[3]; }
  else if (request.indexOf("/servo3=e") != -1) { servoNum = 3; targetAngle = maxPosition[3]; }

  // Move o servo se um comando válido foi encontrado
  if (servoNum != -1) {
    moveServo(servoNum, targetAngle);
  }
}

void moveServo(int servoNum, int targetAngle) {
  int startPulse = map(currentPosition[servoNum], 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE);
  int endPulse = map(targetAngle, 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE);

  if (startPulse < endPulse) {
    for (int pos = startPulse; pos <= endPulse; pos++) {
      pwm.setPWM(servoNum, 0, pos);
      delay(8); // Atraso para suavizar o movimento
    }
  } else {
    for (int pos = startPulse; pos >= endPulse; pos--) {
      pwm.setPWM(servoNum, 0, pos);
      delay(8); // Atraso para suavizar o movimento
    }
  }

  currentPosition[servoNum] = targetAngle; // Atualiza a posição atual
}
