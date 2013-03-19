#include<LPC214x.h>
#include <stdio.h>


//interrupciones

//configuraciones


void configExcepcion(void);
//variables globales


int main()
{
	int i;
	PINSEL0 = 0x00000000;				//P0.6 como GPIO
	PINSEL1 = 0x00000000;				//
	IODIR0  = 0xFFFFFFFF;				//P0.6 como salida
	
	configExcepcion();
		
		while(1){
			
	for(i=0;i<7500000;i++);
		if( (IO0PIN & 0X00020000) == 0X00020000)
			IO0CLR |=  0X00020000;
		else
			IO0SET |=  0X00020000;

	}
	
}





void configExcepcion()
{
	VICIntSelect = 0x00000000;			//timer 0 como IRQ
	VICIntEnable = 0x00000000;			//habilito la interrupcion por timer0
}


