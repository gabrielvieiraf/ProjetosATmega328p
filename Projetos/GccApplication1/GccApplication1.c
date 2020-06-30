/*
 * main.c
 *
 * Created: 20/06/2020 09:20:41
 * Author: Gabriel Vieira Flores
 */ 


#include "def_principais.h"
#include "LCD.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include "ds18b20.h"
unsigned char tempChar[2];

int main(void)
{
	DDRD = 0xFF;		//PORTD como saída para pastilha
	DDRB = 0xFF;		//PORTB como saída para display
    PORTC = 0xFE;     
    DDRC= 0x00;
	double tempC;
    
	sei();
         
	inic_LCD_4bits(); //inicializa o display
	
    while(1)
    {
		tempC = ds18b20_gettemp();
		
		cmd_LCD(0x81,0); // posição do cursor
		escreve_LCD("TESTE DE SONDAS:");//Escreve
	   
        cmd_LCD(0xC9,0);
        escreve_LCD("C");
		  
		if (tempC>40||tempC<8) {
			cmd_LCD(0xC5,0);
			cmd_LCD('X',1);
			cmd_LCD(0xC6,0);
			cmd_LCD('X',1);
			cmd_LCD(0x00,1);
		}
				
	    else {
			ident_num(tempC,tempChar);
			cmd_LCD(0x00,1);
			cmd_LCD(0xC5,0);
			cmd_LCD(tempChar[1],1);
			cmd_LCD(tempChar[0],1);
			cmd_LCD(0xc8,0);
			cmd_LCD(0b11011111,1);
		}
				  
		_delay_ms(100);
				
	}  


}



