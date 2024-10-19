#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <WiFi.h>

const char* ssid = "DROID";
const char* password = "12345678";

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_MIN_PULSE 150 // Pulso mínimo para o servo
#define SERVO_MAX_PULSE 600 // Pulso máximo para o servo

int minPosition[4] = {90, 10, 90, 50};       // Posições mínimas
int initialPosition[4] = {125, 100, 120, 80}; // Posições iniciais
int maxPosition[4] = {160, 190, 150, 130};   // Posições máximas
int currentPosition[4] = {125, 100, 120, 80}; // Posições atuais

WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50); // Configura a frequência para 50Hz

  WiFi.softAP(ssid, password); // Inicia o ponto de acesso Wi-Fi

  server.begin(); // Inicia o servidor
  Serial.println("Servidor iniciado");
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

void inicio(WiFiClient& client) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html; charset=utf-8");
  client.println("Connection: close");
  client.println();

  client.println("<!DOCTYPE HTML>");
  client.println("<html lang=\"pt-BR\">");
  client.println("<head>");
  client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
  client.println("<title>Página Inicial</title>");
  client.println("<style>");
  client.println("body { font-family: Arial, sans-serif; text-align: center; background-color: #f0f0f0; margin: 0; margin-top: 100px; padding: 0; }");
  client.println(".button { font-size: 50px; padding: 15px 30px; margin: 10px; font-weight: bold; border: none; cursor: pointer; }");
  client.println(".cabeça { background-color: #FFD700; color: #000; }");
  client.println(".text-autoria { font-size: 15px; color: #808080; margin-top: 150px; }");
  client.println("</style>");
  client.println("</head>");
  client.println("<body>");
  client.println("<h1>Bem-vindo ao Controle do DROID D.I.N.O.</h1>");
  client.println("<p>Escolha um servo para controlar:</p>");

  for (int i = 0; i < 4; i++) {
    client.print("<button class=\"button\" onclick=\"location.href='/servo");
    client.print(i);
    client.println("'\"><strong>Servo ");
    client.print(i);
    client.println("</strong></button><br>");
  }

  client.println("<p class=\"text-autoria\">Projeto criado por:<br>Emerson Gabriel Souza<br>www.gahsouza.com.br</p>");
  client.println("</body></html>");
}

void controleServo(WiFiClient& client, int servoNum) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html; charset=utf-8");
  client.println("Connection: close");
  client.println();

  client.println("<!DOCTYPE HTML>");
  client.println("<html lang=\"pt-BR\">");
  client.println("<head>");
  client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
  client.println("<title>Controle do Servo</title>");
  client.println("<style>");
  client.println("body { font-family: Arial, sans-serif; text-align: center; background-color: #f0f0f0; margin: 0; padding: 0; }");
  client.println(".button { font-size: 35px; padding: 15px 30px; margin: 10px; font-weight: bold; border: none; cursor: pointer; }");
  client.println("</style>");
  client.println("</head>");
  client.println("<body>");
  client.print("<h1>Controle do Servo ");
  client.print(servoNum);
  client.println("</h1>");
  client.println("<p>Escolha uma posição:</p>");

  client.print("<button class=\"button\" onclick=\"location.href='/servo");
  client.print(servoNum);
  client.println("/min'\">Posição Mínima</button><br>");

  client.print("<button class=\"button\" onclick=\"location.href='/servo");
  client.print(servoNum);
  client.println("/inicial'\">Posição Inicial</button><br>");

  client.print("<button class=\"button\" onclick=\"location.href='/servo");
  client.print(servoNum);
  client.println("/max'\">Posição Máxima</button><br>");

  // Adiciona o botão "Voltar"
  client.println("<br><button class=\"button\" onclick=\"location.href='/'\">Voltar</button>");

  client.println("<p class=\"text-autoria\">Projeto criado por:<br>Emerson Gabriel Souza<br>www.gahsouza.com.br</p>");
  client.println("</body></html>");
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;

  String request = client.readStringUntil('\r');
  client.flush();

  for (int i = 0; i < 4; i++) {
    if (request.indexOf("/servo" + String(i)) != -1) {
      if (request.indexOf("/min") != -1) {
        moveServo(i, minPosition[i]);
      } else if (request.indexOf("/inicial") != -1) {
        moveServo(i, initialPosition[i]);
      } else if (request.indexOf("/max") != -1) {
        moveServo(i, maxPosition[i]);
      }
      controleServo(client, i);
      return;
    }
  }

  inicio(client);

  delay(1);
  client.stop();
}
