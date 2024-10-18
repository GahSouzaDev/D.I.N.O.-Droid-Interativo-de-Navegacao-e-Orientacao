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
int minPosition[4] = {90, 10, 90, 50};    // Posições mínimas
int initialPosition[4] = {125, 100, 120, 80}; // Posições iniciais
int maxPosition[4] = {160, 190, 150, 140}; // Posições máximas
int currentPosition[4] = {125, 100, 130, 80}; // Posições atuais

//S0 = Servo de elevação(base) min=90 media=125 max=160
//S1 = Servo de posição(horizontal) min=10 media=100 max=190
//S2 = Servo da antena(antena) min=90 media=120 max=150
//S3 = Servo de posição(vertical) min=50 media=80 max=140

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
    processRequest(request);

    // Responde ao cliente com a página HTML estilizada
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html; charset=utf-8");
    client.println("Connection: close");
    client.println();
    client.println("<!DOCTYPE HTML>");
    client.println("<html lang=\"pt-BR\">");
    client.println("<head>");
    client.println("<title>Controle CABEÇA DROID</title>");
    client.println("<style>");
    client.println("body { font-family: Arial, sans-serif; text-align: center; background-color: #f0f0f0; margin: 0; padding: 0; }");
    client.println("h1 { font-size: 70px; color: #333; }");
    client.println("button { padding: 30px 60px; font-size: 40px; margin: 10px; cursor: pointer; }");
    client.println(".b1 { background-color: #FFD700; color: #000; }");
    client.println(".b2 { background-color: #90EE90; color: #000; }");
    client.println(".b3 { background-color: #FF6347; color: #000; }");
    client.println("</style>");
    client.println("</head>");
    client.println("<body>");
    client.println("<h1>Controle Cabeça DROID</h1>");
    
    // Botões para controle dos servos s0 a s3
    client.println("<h2>Servo s0</h2>");
    client.println("<button class=\"b1\" onclick=\"location.href='/s0=1'\">Máximo</button>");
    client.println("<button class=\"b2\" onclick=\"location.href='/s0=2'\">Inicial</button>");
    client.println("<button class=\"b3\" onclick=\"location.href='/s0=3'\">Mínimo</button>");

    client.println("<h2>Servo s1</h2>");
    client.println("<button class=\"b1\" onclick=\"location.href='/s1=1'\">Esquerda</button>");
    client.println("<button class=\"b2\" onclick=\"location.href='/s1=2'\">Inicial</button>");
    client.println("<button class=\"b3\" onclick=\"location.href='/s1=3'\">Direita</button>");

    client.println("<h2>Servo s3</h2>");
    client.println("<button class=\"b1\" onclick=\"location.href='/s3=1'\">Alto</button>");
    client.println("<button class=\"b2\" onclick=\"location.href='/s3=2'\">Inicial</button>");
    client.println("<button class=\"b3\" onclick=\"location.href='/s3=3'\">Baixo</button>");

    client.println("<h2>Servo s2</h2>");
    client.println("<button class=\"b1\" onclick=\"location.href='/s2=1'\">Máximo</button>");
    client.println("<button class=\"b2\" onclick=\"location.href='/s2=2'\">Inicial</button>");
    client.println("<button class=\"b3\" onclick=\"location.href='/s2=3'\">Mínimo</button>");

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

  if (request.indexOf("/s0=1") != -1) { servoNum = 0; targetAngle = minPosition[0]; }
  else if (request.indexOf("/s0=2") != -1) { servoNum = 0; targetAngle = initialPosition[0]; }
  else if (request.indexOf("/s0=3") != -1) { servoNum = 0; targetAngle = maxPosition[0]; }
  else if (request.indexOf("/s1=1") != -1) { servoNum = 1; targetAngle = maxPosition[1]; }
  else if (request.indexOf("/s1=2") != -1) { servoNum = 1; targetAngle = initialPosition[1]; }
  else if (request.indexOf("/s1=3") != -1) { servoNum = 1; targetAngle = minPosition[1]; }
  else if (request.indexOf("/s2=1") != -1) { servoNum = 2; targetAngle = maxPosition[2]; }
  else if (request.indexOf("/s2=2") != -1) { servoNum = 2; targetAngle = initialPosition[2]; }
  else if (request.indexOf("/s2=3") != -1) { servoNum = 2; targetAngle = minPosition[2]; }
  else if (request.indexOf("/s3=1") != -1) { servoNum = 3; targetAngle = maxPosition[3]; }
  else if (request.indexOf("/s3=2") != -1) { servoNum = 3; targetAngle = initialPosition[3]; }
  else if (request.indexOf("/s3=3") != -1) { servoNum = 3; targetAngle = minPosition[3]; }

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
