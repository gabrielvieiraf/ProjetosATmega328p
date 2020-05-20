/*
 * TestadorDS18B20.c
 *
 * Criado em: 20/05/2020 10:42:39
 * Author : Gabriel Vieira Flores
 */ 

#include "Utilitarios.h"
#include "_1wire.h"
#include "LCD.h"

unsigned char digitos[tam_vetor];

int main()
{
	unsigned char temp_LSB;
	unsigned int valor_temp;
	
	DDRD = 0xFF; //PORTD como saída
	DDRB = 0xFF; //PORTB como saída
	inic_LCD_4bits(); //inicializa o LCD
		
	while(1)
	{
		reset_1w();						//reset do sensor (a resposta de presença é retornada mas não avaliada).
		escreve_byte_1w(0xCC);			//comando para pular ROM (só 1 dispositivo no barramento).
		escreve_byte_1w(0x44);			//manda iniciar a conversão
		alimenta_1w();					
		reset_1w();
		escreve_byte_1w(0xCC);
		escreve_byte_1w(0xBE);			//avisa que quer ler a memória
		
		temp_LSB = le_byte_1w();		//só interesse em ler os dois bytes da temperatura
		
		//conversão do número lido para um valor inteiro sem vírgula (temp_LSB*10/2)
		valor_temp = 5*temp_LSB;		//retirar a virgula do número e converte, cada bit LSB vale 0,5°C
		//Para uso do DS18B20 a fórmula deve ser alterada.
		
		ident_num(valor_temp,digitos);
		cmd_LCD(0x85,0);
		cmd_LCD(digitos[3],1);
		cmd_LCD(0x86,0);
		cmd_LCD(digitos[2],1);
		cmd_LCD(0x88,0);
		cmd_LCD(digitos[1],1);
		cmd_LCD(0x8A,0);
		cmd_LCD(',',0);
		cmd_LCD(0x8B,0);
		cmd_LCD(digitos[0],1);
		cmd_LCD(0x8D,0);
		cmd_LCD(176,1);
		cmd_LCD(0x8E,0);
		cmd_LCD('C',1);
	}
}
