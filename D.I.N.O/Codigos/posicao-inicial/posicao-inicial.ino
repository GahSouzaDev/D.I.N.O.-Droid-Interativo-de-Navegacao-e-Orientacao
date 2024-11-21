//D.I.N.O.
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_MIN_PULSE 112 // Pulso mínimo para o servo
#define SERVO_MAX_PULSE 512 // Pulso máximo para o servo

//----CABEÇA----//
//Pescoço
int PescocoMin = 90, PescocoMed = 120, PescocoMax = 160;

//Rotação da cabeça
int RotacaoCabecaMed = 100; 
//Rotação para DIREITA
int RotacaoCabecaDirMax = 0, RotacaocabecaDirMed = 50;
//Rotação para ESQUERDA
int RotacaoCabecaEsqMax = 150, RotacaoCabecaEspMed = 200;

//Antenas
int AntenasMed = 120, AntenasMax = 150, AntenasMin = 90;

//Elevação da cabeça
int ElevacaoMed = 75;
//Cabeça para BAIXO
int ElevacaoBaixoMed = 57.5, ElevacaoBaixoMax = 40;
//Cabeça para CIMA
int ElevacaoCimaMed = 92.5, ElevacaoCimaMax = 130;

//---PERNAS---//
//          ESQUEDA                  DIREITA   

//Rotação  
//                        MEDIA   
int RotacaoPernaEsqMed1 = 90, RotacaoPernaDirMed1 = 90;
int RotacaoPernaEsqMed2 = 90, RotacaoPernaDirMed2 = 105;
//                 Rotação para dentro
int RotacaoPernaEsqMin1 = 60, RotacaoPernaDirMin1 = 60;
int RotacaoPernaEsqMin2 = 120, RotacaoPernaDirMin2 = 135;
//                  Rotação para fora
int RotacaoPernaEsqMax1 = 120, RotacaoPernaDirMax1 = 120;
int RotacaoPernaEsqMax2 = 60, RotacaoPernaDirMax2 = 75;

//COXA (Parte superior da perna)
//                        MEDIA   
int MoveCoxaEsqMed1 = 120, MoveCoxaDirMed1 = 65;
int MoveCoxaEsqMed2 = 120, MoveCoxaDirMed2 = 75;
//             Rotação para dentro
int MoveCoxaEsqMin1 = 135, MoveCoxaDirMin1 = 50;
int MoveCoxaEsqMin2 = 135, MoveCoxaDirMin2 = 60;
//              Rotação para fora
int MoveCoxaEsqMax1 = 105, MoveCoxaDirMax1 = 80;
int MoveCoxaEsqMax2 = 105, MoveCoxaDirMax2 = 90;

//PANTURRILHA (Parte de baixo da perna)
//                        MEDIA   
int MovePantEsqMed1 = 95, MovePantDirMed1 = 90;
int MovePantEsqMed2 = 105, MovePantDirMed2 = 90;
//              Rotação para dentro
int MovePantEsqMin1 = 105, MovePantDirMin1 = 70;
int MovePantEsqMin2 = 115, MovePantDirMin2 = 80;
//               Rotação para fora
int MovePantEsqMax1 = 85, MovePantDirMax1 = 90;
int MovePantEsqMax2 = 95, MovePantDirMax2 = 100;

//Exemplo da sequencia a ser seguida!
int initialPosition[16] =   
{
  PescocoMed, 
  RotacaoCabecaMed, 
  AntenasMed, 
  ElevacaoMed,  
  
  RotacaoPernaDirMed1,RotacaoPernaDirMed2,
  RotacaoPernaEsqMed1,RotacaoPernaEsqMed2,   

  MoveCoxaEsqMax1, MoveCoxaEsqMax2,
  MoveCoxaDirMax1, MoveCoxaDirMax2,

  MovePantDirMax1, MovePantDirMax2,
  MovePantEsqMax1, MovePantEsqMax2
};


// Definição dos pinos
#define LED_ESP32 2       // LED integrado no ESP32

#define OLHO_ESQUERDO 14  // Olho esquerdo
#define OLHO_DIREITO 12   // Olho direito
// Define o brilho dos OLHOS (0 a 255)
int brilho = 10; // Você pode ajustar isso conforme necessário

#define LED_VERMELHO 32     // LED vermelho
#define LED_AMARELO 26     // LED amarelo
#define LED_VERDE 33      // LED verde
#define LED_AZUL 27       // LED azul

#define BUZZER 13         // Buzzer
         
void setup() {
  
  pwm.begin();
  pwm.setPWMFreq(50); // Configura a frequência para 50Hz

  for (int i = 0; i < 16; i++) {
    moveServo(i, initialPosition[i]);
  }
  // Configuração dos pinos como saídas
  pinMode(LED_ESP32, OUTPUT);
  pinMode(OLHO_ESQUERDO, OUTPUT);
  pinMode(OLHO_DIREITO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Sequência de LEDs coloridos
  sequenciaLEDs();

  bipBuzzer();

}

void loop() {

  // Piscar olhos de forma natural
  piscarOlhos();

}