#include <WiFi.h>
#include <WebServer.h>

// Definir o nome e a senha da rede Wi-Fi que o ESP32 irá criar
const char *ssid = "D.I.N.O."; // Nome da rede Wi-Fi
const char *password = "123456789";  // Senha da rede Wi-Fi

// Criação do servidor web na porta 80
WebServer server(80);

// HTML da página que será servida
const char* htmlContent = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-br">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Dino com Olhos Piscando</title>
    <style>
        body {
            font-family: 'Courier New', Courier, monospace;
            text-align: center;
        }

        /* Definir a animação de piscar (olhos fechando e abrindo) */
        @keyframes piscar {
            0%, 100% {
                r: 10; /* Olhos abertos */
            }
            50% {
                r: 0; /* Olhos fechados */
            }
        }

        /* Aplicar a animação aos dois olhos ao mesmo tempo */
        .olhos {
            animation: piscar 2s infinite; /* Animação que repete indefinidamente */
        }
    </style>
</head>
<body>
    <h1>Dino INICIO</h1>
    <svg xmlns="http://www.w3.org/2000/svg" width="300" height="500" viewBox="0 0 300 500">
        <!-- Pernas -->
        <rect x="40" y="360" width="40" height="120" fill="gray" stroke="black" stroke-width="2" />
        <rect x="220" y="360" width="40" height="120" fill="gray" stroke="black" stroke-width="2" />
        
        <!-- Corpo -->
        <rect x="50" y="255" width="200" height="120" fill="silver" stroke="black" stroke-width="2" />
        
        <!-- Pescoço -->
        <rect x="120" y="180" width="60" height="75" fill="gray" stroke="black" stroke-width="2" />
        
        <!-- Cabeça -->
        <rect x="60" y="100" width="180" height="80" fill="silver" stroke="black" stroke-width="2" />
        
        <!-- Antenas -->
        <rect x="50" y="10" width="10" height="100" fill="black" />
        <rect x="240" y="10" width="10" height="100" fill="black" />
             
        <!-- Olhos -->
        <circle cx="120" cy="140" r="15" fill="black"  />
        <circle cx="180" cy="140" r="15" fill="black"  />
        <circle cx="120" cy="140" r="12" fill="white" 
        class="olhos"/>
        <circle cx="180" cy="140" r="12" fill="white"
        class="olhos" />

        <!-- Pés -->
        <rect x="30" y="475" width="60" height="20" fill="black" />
        <rect x="210" y="475" width="60" height="20" fill="black" />
    </svg>
</body>
</html>
)rawliteral";

// Função que será chamada quando a página for acessada
void handleRoot() {
  server.send(200, "text/html", htmlContent); // Envia o conteúdo HTML
}

void setup() {
  Serial.begin(115200);
  
  // Inicializa o ESP32 como Access Point
  WiFi.softAP(ssid, password);  // Cria a rede Wi-Fi
  
  Serial.println();
  Serial.print("IP do ESP32: ");
  Serial.println(WiFi.softAPIP()); // Mostra o IP para acessar a página

  // Define a função de resposta para a raiz
  server.on("/", HTTP_GET, handleRoot);
  
  // Inicia o servidor
  server.begin();
}

void loop() {
  server.handleClient(); // Aguarda e processa as requisições HTTP
}
