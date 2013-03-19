#include<LPC214x.h>
#include <stdio.h>


//interrupciones
void timer(void) __irq;
//configuraciones
void configTimer(void);

void configExcepcion(void);
//variables globales


int main()
{
	PINSEL0 = 0x00000000;				//P0.6 como GPIO
	PINSEL1 = 0x00000000;				//P0.28 como ADC0
	IODIR0  = 0x00020000;				//P0.6 como salida
		
	configTimer();
	configExcepcion();
		
		
	T0TCR = 0x01;

	
	while(1);
}

void timer() __irq
{
	
	if( (IO0PIN & 0X00020000) == 0X00020000)
		IO0CLR |=  0X00020000;
	else
		IO0SET |=  0X00020000;

	
	VICVectAddr = 0x00000000;
	T0IR = 0x01;
}




void configExcepcion()
{
	VICVectAddr0 = (unsigned) timer;
	VICVectCntl0 =  0x24;
	VICIntSelect = 0x00000000;			//timer 0 como IRQ
	VICIntEnable = 0x00000010;			//habilito la interrupcion por timer0
}

void configTimer()
{
	T0CTCR 	= 0x00;								
	T0TCR  	= 0x02;
	T0IR		=	0x01;
	T0PR		=	0;  
	T0MCR		=	0x03;
	T0MR0		=	3000000;
}
