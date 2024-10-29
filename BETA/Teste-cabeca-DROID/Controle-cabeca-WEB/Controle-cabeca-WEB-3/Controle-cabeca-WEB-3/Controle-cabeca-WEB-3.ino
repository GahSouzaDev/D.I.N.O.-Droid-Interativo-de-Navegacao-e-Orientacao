#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <WiFi.h>

const char* ssid = "DROID";
const char* password = "12345678";

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_MIN_PULSE 112 // Pulso mínimo para o servo
#define SERVO_MAX_PULSE 512 // Pulso máximo para o servo

int minPosition[4] = {80, 5, 90, 40};       // Posições mínimas
int initialPosition[4] = {130, 100, 120, 75}; // Posições iniciais
int maxPosition[4] = {160, 195, 150, 130};   // Posições máximas
int currentPosition[4] = {130, 100, 120, 75}; // Posições atuais

//S0 = Servo de elevação(base) min=80 media=120 max=160
//S1 = Servo de posição(horizontal) min=10 media=100 max=190
//S2 = Servo da antena(antena) min=90 media=120 max=150
//S3 = Servo de posição(vertical) min=40 media=75 max=130

WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50); // Configura a frequência para 50Hz

  WiFi.softAP(ssid, password); // Inicia o ponto de acesso Wi-Fi

pinMode(14 ,OUTPUT);//Olho direito
pinMode(12 ,OUTPUT);//Olho esquerdo

pinMode(25 ,OUTPUT);//LED Azul
pinMode(33 ,OUTPUT);//LED Verde
pinMode(27 ,OUTPUT);//LED Amarelo
pinMode(26 ,OUTPUT);//LED Vermelho

pinMode(34 ,OUTPUT);//Buzzer

digitalWrite(14, HIGH);
digitalWrite(12,HIGH);

digitalWrite(25,LOW);
digitalWrite(33,LOW);
digitalWrite(27,LOW);
digitalWrite(26,LOW);

digitalWrite(34,LOW);

  server.begin(); // Inicia o servidor
  Serial.println("Servidor iniciado");

  // Inicializa os servos nas posições iniciais
  for (int i = 0; i < 4; i++) {
    moveServo(i, initialPosition[i]);
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
  client.println("<p class=\"text-autoria\">Projeto criado por:<br>Emerson Gabriel Souza<br>www.gahsouza.com.br</p>");
  client.println("</style>");
  client.println("</head>");
  client.println("<body>");
  client.println("<h1>Bem-vindo ao Controle do DROID D.I.N.O.</h1>");
  client.println("<p>Escolha uma parte para controlar:</p>");

  client.println("<button class=\"button\" onclick=\"location.href='/cabeca'\">Cabeça</button><br>");
  client.println("<button class=\"button\" onclick=\"location.href='/pernas'\">Pernas</button><br>");

  client.println("<p class=\"text-autoria\">Projeto criado por:<br>Emerson Gabriel Souza<br>www.gahsouza.com.br</p>");
  
  client.println("</body></html>");
}

void controleCabeca(WiFiClient& client) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html; charset=utf-8");
  client.println("Connection: close");
  client.println();

  client.println("<!DOCTYPE HTML>");
  client.println("<html lang=\"pt-BR\">");
  client.println("<head>");
  client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
  client.println("<title>Controle da Cabeça</title>");
  client.println("<style>");
  client.println("body { font-family: Arial, sans-serif; text-align: center; background-color: #f0f0f0; margin: 0; padding: 0; }");
  client.println(".button.b1 { font-size: 15px; padding: 5px 5px; margin: 5px; font-weight: bold; border: none; cursor: pointer; background-color: #FFD700; color: #000; }");
  client.println(".button.b2 { font-size: 15px; padding: 5px 5px; margin: 5px; font-weight: bold; border: none; cursor: pointer; background-color: #90EE90; color: #000; }");
  client.println(".button.b3 { font-size: 15px; padding: 5px 5px; margin: 5px; font-weight: bold; border: none; cursor: pointer; background-color: #FF6347; color: #000; }");
  client.println("</style>");
  client.println("</head>");
  client.println("<body>");
  client.println("<h1>Controle dos Servos da Cabeça</h1>");
  client.println("<p>Controle os servos juntos:</p>");

  for (int i = 0; i < 4; i++) {
    client.print("<p>Servo ");
    client.print(i);
    client.println("</p>");

    client.print("<button class=\"button.b1\" onclick=\"location.href='/servo");
    client.print(i);
    client.println("/min'\">Posição Mínima</button>");

    client.print("<button class=\"button.b2\" onclick=\"location.href='/servo");
    client.print(i);
    client.println("/inicial'\">Posição Inicial</button>");

    client.print("<button class=\"button.b3\" onclick=\"location.href='/servo");
    client.print(i);
    client.println("/max'\">Posição Máxima</button><br><br>");
  }

  // Adiciona o botão "Voltar"
  client.println("<br><button class=\"button\" onclick=\"location.href='/'\">Voltar</button>");

  client.println("</body></html>");
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;

  String request = client.readStringUntil('\r');
  client.flush();

  if (request.indexOf("/cabeca") != -1) {
    controleCabeca(client);
    return;
  }

  for (int i = 0; i < 4; i++) {
    if (request.indexOf("/servo" + String(i)) != -1) {
      if (request.indexOf("/min") != -1) {
        moveServo(i, minPosition[i]);
      } else if (request.indexOf("/inicial") != -1) {
        moveServo(i, initialPosition[i]);
      } else if (request.indexOf("/max") != -1) {
        moveServo(i, maxPosition[i]);
      }
      controleCabeca(client);
      return;
    }
  }

  inicio(client);

  delay(1);
  client.stop();
}
