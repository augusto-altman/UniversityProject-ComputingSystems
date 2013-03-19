#include<LPC214x.h>
#include <stdio.h>
#include <string.h>
#include "serial.h"

//interrupciones
//configuraciones
void configExcepcion(void);
//variables globales

//interrupciones

int main()
{
	/*int i, boton[9] = {boton0,boton1,boton2,boton3,boton4,boton5,boton6,boton7,boton8};
	int led1[9] = {led11,led12,led13,led14,led15,led16,led17,led18,led19};
	int led2[9] = {led21,led22,led23,led24,led25,led26,led27,led28,led29};*/
	

	char recibir[1];
	
		
	PINSEL0 = 0x00000005;				// P0.0 Y P0.1 PARA UART, RESTO GPIO
	PINSEL1 = 0x00000000;				// GPIO
	IODIR0  = 0xFFFFF800;				// BOTONES ENTRADA, LEDS SALIDA
	IODIR1  = 0xFFFFFF00;	
	IO0CLR = 0xFFFFFFFF; 				// LIMPIO TODAS LAS SALIDAS
	IO1CLR = 0xFFFFFFFF;
	configExcepcion();
		
	
	
	scanf("%c",recibir);
	printf("%c",recibir[0]);
}
void configExcepcion()
{
	VICIntSelect = 0x00000000;			//timer 0 como IRQ
	VICIntEnable = 0x00000010;			//habilito la interrupcion por timer0
}
