#include<LPC214x.h>
#include <stdio.h>

//interrupciones
//configuraciones
void configExcepcion(void);
//variables globales

#define boton0  0x00000004
#define boton1  0x00000008
#define boton2	0x00000010
#define boton3	0x00000020
#define boton4	0x00000040
#define boton5	0x00000080
#define boton6	0x00000100
#define boton7	0x00000200
#define boton8	0x00000400

#define led11	0x00000800
#define led12	0x00001000
#define led13	0x00002000
#define led14 0x10000 // (p1.16)
#define led15	0x00008000
#define led16	0x20000 // (p1.17)
#define led17	0x40000 //(p1.18)
#define led18	0x00040000
#define led19	0x00080000

#define led21	0x00100000 // P0.20
#define led22	0x00200000 // P0.21
#define led23	0x00400000 // P0.22
#define led24 0x00800000 // P0.23
#define led25	0x02000000 // P0.25
#define led26	0x10000000 // P0.28
#define led27	0x20000000 // P0.29
#define led28	0x40000000 // P0.30
#define led29	0x80000000 // P0.31

int main()
{
	int i, boton[9] = {boton0,boton1,boton2,boton3,boton4,boton5,boton6,boton7,boton8};
	//int led1[9] = {led11,led12,led13,led14,led15,led16,led17,led18,led19};
	int led2[9] = {led21,led22,led23,led24,led25,led26,led27,led28,led29};
		
	
		
	PINSEL0 = 0x00000000;				//P0.6 como GPIO
	PINSEL1 = 0x00000000;				//P0.28 como ADC0
	IODIR0  = 0xFFF00000;				//P0.6 como salida
	IODIR1  = 0x00000000;				//P0.6 como salida
		
	configExcepcion();
	
	IO0SET = 0xFFFFFFFF;
	for(i=0;i<60000000;i++);
	
	while(1){
		for(i=0;i<9;i++){
			if(( IO0PIN & boton[i]) == boton[i]){
				IO0CLR = led2[i];
			}
			else{
				IO0SET = led2[i];
			}
		}
	}
}



void configExcepcion()
{
	VICIntSelect = 0x00000000;			//timer 0 como IRQ
	VICIntEnable = 0x00000000;			//DEHABILITO TODAS LAS INT
}
