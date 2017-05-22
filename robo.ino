// Programa : Controle de motor CC com o L293D
// Autor : Arduino e Cia

#include <stdio.h>
#include "TimerOne.h"

int Motor1_1 = 2; //Ligado ao pino 2 do L293D
int Motor1_2 = 3; //Ligado ao pino 3 do L293D
int Motor2_1 = 4; //Ligado ao pino 4 do L293D
int Motor2_2 = 5; //Ligado ao pino 5 do L293D
int Veloc_1 = 6; //Ligado ao pino 6 do L293D
int Veloc_2 = 7; //Ligado ao pino 7 do L293D

const int Infra_rec = A5;

int sensorValue = 0;
int sentido = 0; // 0 direita, 1 esquerda
int blocktime=0;
int turning=0;

void Int_Timer() {
  sensorValue = analogRead(Infra_rec) - 100;        // Faz a leitura do LDR e converte em 8 bits
  Serial.print(sensorValue);
  Serial.print("\n");
  if (turning==1)
     blocktime ++;
  
  if (blocktime >= 75)
      {blocktime =0;
      turning=0;
      }
}


/*if (pisca)                                          // Pisca o LED a cada 1 seg, se necessario
  digitalWrite(ledPin, digitalRead(ledPin) ^ 1);
  else
  digitalWrite (ledPin, LOW);*/

void setup() {
  Timer1.initialize(200);                // Inicializacao da interrupcao por tempo
  Timer1.attachInterrupt(Int_Timer);
  Serial.begin(9600);

  //Define os pinos como saida
  pinMode(Motor1_1, OUTPUT);
  pinMode(Motor1_2, OUTPUT);
  pinMode(Motor2_1, OUTPUT);
  pinMode(Motor2_2, OUTPUT);
  pinMode(Veloc_1, OUTPUT);
  pinMode(Veloc_2, OUTPUT);
}

void loop() {
  //Define a velocidade de rotacao
  int velocidade = 150;
  analogWrite(Veloc_1, velocidade);
  analogWrite(Veloc_2, velocidade);

  if (sensorValue <= 20)
    gira_frente();

  else{
      if(blocktime< 25)
      {
        gira_esquerda();
        turning=1;
      }
       if(blocktime> 25)
      {
        gira_direita();
     }
  }
}

void gira_frente() {
  digitalWrite(Motor1_1, LOW);
  digitalWrite(Motor1_2, HIGH);

  digitalWrite(Motor2_1, HIGH);
  digitalWrite(Motor2_2, LOW);
}

void gira_tras() {
  digitalWrite(Motor1_1, HIGH);
  digitalWrite(Motor1_2, LOW);

  digitalWrite(Motor2_1, LOW);
  digitalWrite(Motor2_2, HIGH);
}

void para_motor() {
  digitalWrite(Motor1_1, LOW);
  digitalWrite(Motor1_2, LOW);

  digitalWrite(Motor2_1, LOW);
  digitalWrite(Motor2_2, LOW);
  delay(2000);
}

void gira_direita() {
  digitalWrite(Motor1_1, HIGH);
  digitalWrite(Motor1_2, LOW);

  digitalWrite(Motor2_1, HIGH);
  digitalWrite(Motor2_2, LOW);
}

void gira_esquerda() {
  digitalWrite(Motor1_1, LOW);
  digitalWrite(Motor1_2, HIGH);

  digitalWrite(Motor2_1, LOW);
  digitalWrite(Motor2_2, HIGH);
}

/* referencias :
  https://www.arduino.cc/documents/datasheets/L293D.pdf
  http://www.arduinoecia.com.br/2014/04/controle-de-motor-cc-com-o-l293d-ponte-h.html*/
