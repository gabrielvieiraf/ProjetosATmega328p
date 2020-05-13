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

// SAÍDAS DO MOTOR DE PASSO
int IN2 = 2;
int IN3 = 3;
int IN4 = 4;
int IN5 = 5;
int Tempo = 30;

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

  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN5, OUTPUT);
  pinMode(pinLDR1, INPUT);
  pinMode(pinLDR2, INPUT);
  pinMode(pinLDR3, INPUT);
  pinMode(pinLDR4, INPUT);

}

void loop()
{
  int angulo = servo1.read();
  int LDR1 = 0;
  int LDR2 = 0;
  int LDR3;
  int LDR4;
  
  //CONTROLE DO MOTOR SERVO.
 
  for (int cont = 0; cont < Qtestes; cont++)
  {
    LDR1 += analogRead(pinLDR1);
    LDR2 += analogRead(pinLDR2);
    delay(20);
  }
  LDR1 /= Qtestes;
  LDR2 /= Qtestes;

  while ((LDR1 - LDR2) > 10)
  {
    angulo = servo1.read();
    if (((LDR2 - LDR1) > 5) || (angulo == angulomax)) break;
    if (angulo < angulomax) {
      servo1.write(angulo + 1);
    }

    LDR1 = 0; LDR2 = 0;
    for (int cont = 0; cont < Qtestes; cont++)
    {
      LDR1 += analogRead(pinLDR1);
      LDR2 += analogRead(pinLDR2);
      delay(10);
    }
    LDR1 /= Qtestes;
    LDR2 /= Qtestes;
  }

  LDR1 = 0; LDR2 = 0;
  for (int cont = 0; cont < Qtestes; cont++)
  {
    LDR1 += analogRead(pinLDR1);
    LDR2 += analogRead(pinLDR2);
    delay(20);
  }
  LDR1 /= Qtestes;
  LDR2 /= Qtestes;

  while ((LDR2 - LDR1) > 10)
  {
    angulo = servo1.read();
    if (((LDR1 - LDR2) > 5) || (angulo == angulomin)) break;
    if (angulo > angulomin) {
      servo1.write(angulo - 1);
    }

    LDR1 = 0; LDR2 = 0;
    for (int cont = 0; cont < Qtestes; cont++)
    {
      LDR1 += analogRead(pinLDR1);
      LDR2 += analogRead(pinLDR2);
      delay(10);
    }
    LDR1 /= Qtestes;
    LDR2 /= Qtestes;
  }

  // CONTROLE DO MOTOR DE PASSO.
  
  angulo = servo1.read();
  if (angulo > 90) 
  {
    LDR3 = 0; LDR4 = 0;
    for (int cont = 0; cont < Qtestes; cont++)
    {
      LDR3 += analogRead(pinLDR3);
      LDR4 += analogRead(pinLDR4);
      delay(20);
    }
    LDR3 /= Qtestes;
    LDR4 /= Qtestes;

    while ((LDR3 - LDR4) > 10)
    {
      if ((LDR4 - LDR3) > 5) {
        break;
      }

      Passo++;
      if (Passo == 4) {
        Passo = 0;
      }
      digitalWrite (Passo + 2, HIGH);
      delay(Tempo);
      digitalWrite (Passo + 2, LOW);
      delay(Tempo);

      LDR3 = 0; LDR4 = 0;
      for (int cont = 0; cont < Qtestes; cont++)
      {
        LDR3 += analogRead(pinLDR3);
        LDR4 += analogRead(pinLDR4);
        delay(10);
      }
      LDR3 /= Qtestes;
      LDR4 /= Qtestes;
    }

    LDR3 = 0; LDR4 = 0;
    for (int cont = 0; cont < Qtestes; cont++)
    {
      LDR3 += analogRead(pinLDR3);
      LDR4 += analogRead(pinLDR4);
      delay(20);
    }
    LDR3 /= Qtestes;
    LDR4 /= Qtestes;

    while ((LDR4 - LDR3) > 10)
    {
      if ((LDR3 - LDR4) > 5) {
        break;
      }

      Passo--;
      if (Passo == -1) {
        Passo = 3;
      }
      digitalWrite (Passo + 2, HIGH);
      delay(Tempo);
      digitalWrite (Passo + 2, LOW);
      delay(Tempo);

      LDR3 = 0; LDR4 = 0;
      for (int cont = 0; cont < Qtestes; cont++)
      {
        LDR3 += analogRead(pinLDR3);
        LDR4 += analogRead(pinLDR4);
        delay(10);
      }
      LDR3 /= Qtestes;
      LDR4 /= Qtestes;
    }
  }

  angulo = servo1.read();
  if (angulo < 90) {
    LDR3 = 0; LDR4 = 0;
    for (int cont = 0; cont < Qtestes; cont++)
    {
      LDR3 += analogRead(pinLDR3);
      LDR4 += analogRead(pinLDR4);
      delay(20);
    }
    LDR3 /= Qtestes;
    LDR4 /= Qtestes;

    while ((LDR3 - LDR4) > 10)
    {
      if ((LDR4 - LDR3) > 5) {
        break;
      }

      Passo--;
      if (Passo == -1) {
        Passo = 3;
      }
      digitalWrite (Passo + 2, HIGH);
      delay(Tempo);
      digitalWrite (Passo + 2, LOW);
      delay(Tempo);

      LDR3 = 0; LDR4 = 0;
      for (int cont = 0; cont < Qtestes; cont++)
      {
        LDR3 += analogRead(pinLDR3);
        LDR4 += analogRead(pinLDR4);
        delay(10);
      }
      LDR3 /= Qtestes;
      LDR4 /= Qtestes;
    }

    LDR3 = 0; LDR4 = 0;
    for (int cont = 0; cont < Qtestes; cont++)
    {
      LDR3 += analogRead(pinLDR3);
      LDR4 += analogRead(pinLDR4);
      delay(20);
    }
    LDR3 /= Qtestes;
    LDR4 /= Qtestes;

    while ((LDR4 - LDR3) > 10)
    {
      if ((LDR3 - LDR4) > 5) {
        break;
      }

      Passo++;
      if (Passo == 4) {
        Passo = 0;
      }
      digitalWrite (Passo + 2, HIGH);
      delay(Tempo);
      digitalWrite (Passo + 2, LOW);
      delay(Tempo);

      LDR3 = 0; LDR4 = 0;
      for (int cont = 0; cont < Qtestes; cont++)
      {
        LDR3 += analogRead(pinLDR3);
        LDR4 += analogRead(pinLDR4);
        delay(10);
      }
      LDR3 /= Qtestes;
      LDR4 /= Qtestes;
    }
  }
}
