//D.I.N.O.
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_MIN_PULSE 112 // Pulso mínimo para o servo
#define SERVO_MAX_PULSE 512 // Pulso máximo para o servo

//----CABEÇA----//
//Pescoço
int PescocoMin = 90, PescocoMed = 130, PescocoMax = 160;

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
int MoveCoxaEsqMed1 = 90, MoveCoxaDirMed1 = 90;
int MoveCoxaEsqMed2 = 90, MoveCoxaDirMed2 = 105;
//                 Rotação para dentro
int MoveCoxaEsqMin1 = 60, MoveCoxaDirMin1 = 60;
int MoveCoxaEsqMin2 = 120, MoveCoxaDirMin2 = 135;
//                  Rotação para fora
int MoveCoxaEsqMax1 = 120, MoveCoxaDirMax1 = 120;
int MoveCoxaEsqMax2 = 60, MoveCoxaDirMax2 = 75;

//PANTURRILHA (Parte de baixo da perna)
//                        MEDIA   
int MovePantEsqMed1 = 90, MovePantDirMed1 = 90;
int MovePantEsqMed2 = 90, MovePantDirMed2 = 105;
//                 Rotação para dentro
int MovePantEsqMin1 = 60, MovePantDirMin1 = 60;
int MovePantEsqMin2 = 120, MovePantDirMin2 = 135;
//                  Rotação para fora
int MovePantEsqMax1 = 120, MovePantDirMax1 = 120;
int MovePantEsqMax2 = 60, MovePantDirMax2 = 75;

int minPosition[16] =       {PescocoMin, 0, 90, 40,   60,120,60,135,    135,135,50,60,70,80,105,115};      
//int initialPosition[16] =        {130, 100, 120, 75,  90,90,90,105,120,120,65,75,80,90,95,105}; 
int initialPosition[16] =   {PescocoMed, 100, 120, 75,  RotacaoPernaDirMed1,RotacaoPernaDirMed2,RotacaoPernaEsqMed1,RotacaoPernaEsqMed2,   105,105,80,90,90,100,85,95}; 
int maxPosition[16] =       {PescocoMax, 190, 150, 130, 120,60,120,75,  105,105,80,90,90,100,85,95};   
//int currentPosition[16] =        {130, 100, 120, 75,  90,90,90,105,120,120,65,75,80,90,95,105}; // Posições atuais
int currentPosition[16] =    {PescocoMed, 100, 120, 75,  RotacaoPernaDirMed1,RotacaoPernaDirMed2,RotacaoPernaEsqMed1,RotacaoPernaEsqMed2,   105,105,80,90,90,100,85,95}; // Posições atuais

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