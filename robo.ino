/****************************************************************************
 * 
 *  EA076 C - Projeto 3 - robo.io
 *  Dimitri Reis        RA 145869
 *  Guilherme Frauches  RA 155591
 *
 *  Carrinho que ao encontrar um obstaculo, desvia
 *  
 ****************************************************************************/
#include <stdio.h>
#include "TimerOne.h"

/* Ligacao dos pinos no arduino*/ 
int Motor1_1 = 2;           // Controle do Motor 1
int Motor1_2 = 3;
int Motor2_1 = 4;           // Controle do Motor 2
int Motor2_2 = 5;
int Veloc_1 = 6;          
int Veloc_2 = 7;
const int Infra_rec = A5;   // Pino referente ao Receptor Infravermelho

int sensorValue = 0;        // Variavel que representa o valor lido do receptor

/* Realiza o tratamento da interrupção */
void Int_Timer() {
  sensorValue = analogRead(Infra_rec) ;        // Faz a leitura do Receptor
  Serial.print(sensorValue);
  Serial.print("\n");
}

void setup() {
  Timer1.initialize(200);               // Inicializacao da interrupcao por tempo
  Timer1.attachInterrupt(Int_Timer);
  Serial.begin(9600);

  pinMode(Motor1_1, OUTPUT);            // Define os pinos como saída
  pinMode(Motor1_2, OUTPUT);
  pinMode(Motor2_1, OUTPUT);
  pinMode(Motor2_2, OUTPUT);
  pinMode(Veloc_1, OUTPUT);
  pinMode(Veloc_2, OUTPUT);
}

void loop() {
  int velocidade = 150;                 // Define a velocidade de rotacao
  analogWrite(Veloc_1, velocidade);
  analogWrite(Veloc_2, velocidade);

  if(sensorValue>=135)                  // Muda o giro dos motores se tiver um obstaculo
    gira_frente();
  else
    gira_direita();
}

void gira_frente() {
  digitalWrite(Motor1_1, LOW);
  digitalWrite(Motor1_2, HIGH);

  digitalWrite(Motor2_1, HIGH);
  digitalWrite(Motor2_2, LOW);
}

void gira_direita() {
  digitalWrite(Motor1_1, HIGH);
  digitalWrite(Motor1_2, LOW);

  digitalWrite(Motor2_1, HIGH);
  digitalWrite(Motor2_2, LOW);
}

/* 
 * Referencias :
 * https://www.arduino.cc/documents/datasheets/L293D.pdf
 * http://www.arduinoecia.com.br/2014/04/controle-de-motor-cc-com-o-l293d-ponte-h.html
 */
