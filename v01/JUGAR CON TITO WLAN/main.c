#include<LPC214x.h>
#include <stdio.h>
#include <string.h>
#include "serial.h"

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

typedef struct
{
    int res;
    int cont;
    int id;
} jugador;

int movimiento(jugador *, int,int);
void mostrar_leds(void);
void configTimer(void);
int esperar_mov(void);
void realizar_movimiento(void);
//interrupciones
void timer(void) __irq;


jugador p1, p2;
int  tabla[3][3],esperar,tomar_boton,boton_apretado_mov,boton_apretado_sustr;







int main()
{
	/*int i, boton[9] = {boton0,boton1,boton2,boton3,boton4,boton5,boton6,boton7,boton8};
	int led1[9] = {led11,led12,led13,led14,led15,led16,led17,led18,led19};
	int led2[9] = {led21,led22,led23,led24,led25,led26,led27,led28,led29};*/
	
	
	int i,j,mine_cond;
	char recibir[1];
	
		
	PINSEL0 = 0x00000005;				// P0.0 Y P0.1 PARA UART, RESTO GPIO
	PINSEL1 = 0x00000000;				// GPIO
	IODIR0  = 0xFFFFF800;				// BOTONES ENTRADA, LEDS SALIDA
	IODIR1  = 0xFFFFFF00;	
	IO0CLR = 0xFFFFFFFF; 				// LIMPIO TODAS LAS SALIDAS
	IO1CLR = 0xFFFFFFFF;
	configTimer();
	configExcepcion();
		
	
	
	
  p1.cont = 3;
  p2.cont = 3;
  p1.id = 1;
  p2.id = 2;
  esperar = 1;
  //---inicializo la tabla---//
  for(i=0; i<3; i++)
  {
	  for(j=0; j<3; j++)
		  tabla[i][j] = 0;
  }

	/*espero que me indiquen comienzo de juego */
	do{
		scanf("%c",recibir);
	}while(strcmp(recibir,"czo"));
	
  /* espero msj de rs232 que indique mi estado (servidor o cliente)*/
	do{
		scanf("%c", recibir);
	}while(strcmp(recibir,"server") || strcmp(recibir,"client"));
	
	if(strcmp(recibir,"server"))
		mine_cond = 1;
	else
		mine_cond = 2;
	
	
	if(mine_cond == 1)
		realizar_movimiento();
	else
		scanf("%c",recibir);
	
	
}

void realizar_movimiento()
{
	int i,j;
	do{
			if(p1.cont >= 1)
			{
				boton_apretado_mov= esperar_mov();
				p1.res = movimiento(&p1,boton_apretado_mov,-1);
				
				/*envio el movimiento si es correcto */
				if(p1.res != 2)
					printf("%c",(char) boton_apretado_mov);
				
				/* Verifica si es victoria */
				if(p1.res == 1)
				{
					/* envio victoria propia */
					printf("victoria");
					
					/* muestro leds de victoria propia */
					for(i = 0; i<3;i++){
						for(j=0;j<3;j++)
							tabla[i][j]=1;
					}
						mostrar_leds();
						//habilito interrupcion timer0
						VICIntEnable |= 0x00000010;
						// Inicio el TIMER0
						T0TCR = 0x01;
						while(esperar){}
					
				}
			}
			else
			{
				boton_apretado_sustr = esperar_mov();
				boton_apretado_mov= esperar_mov();
				p1.res = movimiento(&p1,boton_apretado_mov,boton_apretado_sustr);
					
				/*envio el movimiento si es correcto */
				if(p1.res != 2)
					printf("%c",(char) boton_apretado_mov);
				
				/*Verifico victoria */
				if(p1.res == 1)
				{
					for(i = 0; i<3;i++){
						for(j=0;j<3;j++)
							tabla[i][j]=1;
					}
						mostrar_leds();
						//habilito interrupcion timer0
						VICIntEnable |= 0x00000010;
						// Inicio el TIMER0
						T0TCR = 0x01;
						while(esperar){}
				}
			}
	}
	while(p1.res == 2);
	p1.cont--;if(p1.cont < 1) p1.cont = 0;
	
}


int esperar_mov()
{
	int i,boton[9] = {boton0,boton1,boton2,boton3,boton4,boton5,boton6,boton7,boton8};
	int boton_apretado=-1;
	tomar_boton = 1;
	esperar=1;

	while(tomar_boton)
	{
		for(i=0;i<9;i++)
		{
			if((IO0PIN & boton[i]) == boton[i])
			{
				//habilito interrupcion timer0
				VICIntEnable |= 0x00000010;
				// Inicio el TIMER0
				T0TCR = 0x01;
				while(esperar){}
			}
		}

	}

	if((IO0PIN & boton[0]) == boton[0]){
		boton_apretado = 0;}
	else if((IO0PIN & boton[1]) == boton[1]){
		boton_apretado = 1;}
	else if((IO0PIN & boton[2]) == boton[2])
			boton_apretado = 2;
	else if((IO0PIN & boton[3]) == boton[3])
			boton_apretado = 3;
	else if((IO0PIN & boton[4]) == boton[4])
			boton_apretado = 4;
	else if((IO0PIN & boton[5]) == boton[5])
			boton_apretado = 5;
	else if((IO0PIN & boton[6]) == boton[6])
			boton_apretado = 6;
	else if((IO0PIN & boton[7]) == boton[7])
			boton_apretado = 7;
	else if((IO0PIN & boton[8]) == boton[8])
			boton_apretado = 8;

	return boton_apretado;
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
T0MR0		=	750000;
}

void timer() __irq
{
	tomar_boton = esperar = 0;

	//deshabilito la interrupcion
	VICIntEnable &= 0x0;

	
	VICVectAddr = 0x00000000;
	T0IR = 0x01;
}


int movimiento(jugador *p, int codigo, int sustr)
{
    int fila_m, fila_s, columna_m, columna_s, i, j, win=0;

    //VALIDACIONES

    if(codigo >=0 && codigo <=8) //Se valida que el jugador no haya ingresado un alor fuera de la tabla
    {
        fila_m = codigo/3;
        columna_m = codigo - fila_m*3;
        if(tabla[fila_m][columna_m] != 0) //Se valida que el jugador no haya colocado la ficha donde ya habia una
        {
            // printf("Error, no puede colocar una ficha ahi! \n");-- enviar msj
            return 2; //Retorna error
        }
    }
    else
    {
      //  printf("Error, coloque un numero del 0 al 8! \n"); -- enviar msj
        return 2; //Retorna error
    }

    if(p->cont < 1)
    {
        fila_s = sustr/3;
        columna_s = sustr - fila_s*3;
        if(tabla[fila_s][columna_s] != p->id)
        {
           // printf("Error, no puede sacar esa ficha! \n"); -- enviar msj
            return 2;
        }
        if(!(codigo + 3 == sustr ||
           codigo - 3 == sustr ||
           codigo - 1 == sustr ||
           codigo + 1 == sustr ||
           codigo == 4 ||
           sustr == 4 ))
        {
           //  printf("Error, no puede realizar ese movimiento! \n"); -- enviar msj
            return 2;
        }

        tabla[fila_s][columna_s] = 0;
    }

    tabla[fila_m][columna_m] = p->id;
    //CHECKEO DE FILAS
    for(i=0; i<3 && !win; i++)
    {
        win = 1;
        for(j=0; j<3 && win; j++)
        {
            if(tabla[i][j] != p->id)
                win = 0;
        }
    }

    //CHECKEO DE COLUMNAS
    for(i=0; i<3 && !win; i++)
    {
        win = 1;
        for(j=0; j<3 && win; j++)
        {
            if(tabla[j][i] != p->id)
                win = 0;
        }
    }

    //CHECKEO DE DIAGONALES
    if(!win)
    {
        int win_d1 = 1, win_d2 = 1;
        win = 1;
        for(j=0; j<3 && win ; j++)
        {
            if(tabla[j][j] != p->id)
                win_d1 = 0;

            if(tabla[j][2-j] != p->id)
                win_d2 = 0;

            win = win_d1 || win_d2;
        }
    }


    mostrar_leds();

    return win;
}



void mostrar_leds()
{
	int i,j,jugador1[9] = {led11,led12,led13,led14,led15,led16,led17,led18,led19};
	int jugador2[9] = {led21,led22,led23,led24,led25,led26,led27,led28,led29};
	IO0CLR = 0xFFFFFFFF;
	IO1CLR = 0xFFFFFFFF;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(tabla[i][j]==1){
				if(!((3*i+j) == 3 || (3*i+j) == 5 || (3*i+j) == 6  ))
					IO0SET |= jugador1[3*i+j];
				else
					IO1SET |= jugador1[3*i+j];
			}
			if(tabla[i][j]==2)
				IO0SET |= jugador2[3*i+j];
		}
	}

}
