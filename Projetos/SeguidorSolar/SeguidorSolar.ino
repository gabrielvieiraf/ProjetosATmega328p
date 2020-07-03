/*       PROJETO SEGUIDOR SOLAR:
CARLOS SPEROTTO, DIMAS ELIAS, GABRIEL FLORES
               IFSC 2019                   */
            
//DECLARANDO BIBLIOTECA PARA O MOTOR SERVO
#include <Servo.h>

//DECLARANDO OS PINOS ANALOGICOS.

#define pinLDR1  A1
#define pinLDR2  A0
#define pinLDR4  A2
#define pinLDR3  A3
#define pinServo  9

Servo servo1;
int angulomax = 130;
int angulomin = 50;
int Qtestes = 8; // Número de amostras antes de fazer o movimento.
int Passo = 0;

//CRIANDO VARIÁVEIS PARA ARMAZENAR OS VALORES LIDOS PELAS PORTAS ANALOGICAS.
//TODAS COMEÇAM EM ZERO PARA RESETAR, CASO TENHA UM VALOR ARMAZENADO NA MEMÓRIA DO ARDUINO.

void setup()
{
  //DEFININDO AS PORTAS ANALOGICAS COMO INPUT(ENTRADA), PARA LER A VARIAÇÃO DE LUMINOSIDADE DOS LDRs, EM UM INTERVALO DE 1024 VALORES.
  servo1.attach(pinServo);
  servo1.write(90);
  delay(100);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(pinLDR1, INPUT);
  pinMode(pinLDR2, INPUT);
  pinMode(pinLDR3, INPUT);
  pinMode(pinLDR4, INPUT);
}


void VerificaAngulo(LDR_A,LDR_B,pinLDR_A,pinLDR_B,tempo_delay) {
  LDR_A = 0; LDR_B = 0;
  for (int cont = 0; cont < Qtestes; cont++)
  {
    LDR_A += analogRead(pinLDR_A);
    LDR_B += analogRead(pinLDR_B);
    delay(tempo_delay);
  }
  LDR_A /= Qtestes;
  LDR_B /= Qtestes;
}

void AtivaPasso(){
	digitalWrite (Passo + 2, HIGH);
    delay(30);
    digitalWrite (Passo + 2, LOW);
    delay(30);
}

void ComparaAngulo(LDR_A,LDR_B,pinLDR1,pinLDR2,flag){
 while ((LDR_A - LDR_B) > 10)
  {
    angulo = servo1.read();
    if (flag==1) {
    if (((LDR_B - LDR_A) > 5) || (angulo == angulomax)) break;
    if (angulo < angulomax) {
      servo1.write(angulo + 1);
    }
    }
    else {
    if (((LDR1 - LDR2) > 5) || (angulo == angulomin)) break;
    if (angulo > angulomin) {
      servo1.write(angulo - 1);
    }
    }
    VerificaAngulo(LDR_A,LDR_B,pinLDR1,pinLDR2,10);
  }
}

void loop()
{
  int angulo = servo1.read();
  int LDR1;
  int LDR2;
  int LDR3;
  int LDR4;
  
  //CONTROLE DO MOTOR SERVO.
  VerificaAngulo(LDR1,LDR2,pinLDR1,pinLDR2,20);
  ComparaAngulo(LDR1,LDR2,pinLDR1,pinLDR2,1);
  VerificaAngulo(LDR1,LDR2,pinLDR1,pinLDR2,20);
  ComparaAngulo(LDR1,LDR2,pinLDR1,pinLDR2,0);

  // CONTROLE DO MOTOR DE PASSO.
  
  angulo = servo1.read();
  if (angulo > 90) 
  {
    VerificaAngulo(LDR3,LDR4,pinLDR3,pinLDR4,20);

    while ((LDR3 - LDR4) > 10)
    {
      if ((LDR4 - LDR3) > 5) {
        break;
      }

      Passo++;
      if (Passo == 4) {
        Passo = 0;
      }
      AtivaPasso();
      VerificaAngulo(LDR3,LDR4,pinLDR3,pinLDR4,10);
    }

    VerificaAngulo(LDR3,LDR4,pinLDR3,pinLDR4,20);

    while ((LDR4 - LDR3) > 10)
    {
      if ((LDR3 - LDR4) > 5) {
        break;
      }

      Passo--;
      if (Passo == -1) {
        Passo = 3;
      }
      AtivaPasso();
      VerificaAngulo(LDR3,LDR4,pinLDR3,pinLDR4,10);
    }
  }

  angulo = servo1.read();
  if (angulo < 90) {
      VerificaAngulo(LDR3,LDR4,pinLDR3,pinLDR4,20);
    while ((LDR3 - LDR4) > 10)
    {
      if ((LDR4 - LDR3) > 5) {
        break;
      }
      Passo--;
      if (Passo == -1) {
        Passo = 3;
      }
      AtivaPasso();
      VerificaAngulo(LDR3,LDR4,pinLDR3,pinLDR4,10);
    }
    
    VerificaAngulo(LDR3,LDR4,pinLDR3,pinLDR4,20);
    
    while ((LDR4 - LDR3) > 10)
    {
      if ((LDR3 - LDR4) > 5) {
        break;
      }
      Passo++;
      if (Passo == 4) {
        Passo = 0;
      }
      AtivaPasso();
      VerificaAngulo(LDR3,LDR4,pinLDR3,pinLDR4,10);
    }
  }
}
