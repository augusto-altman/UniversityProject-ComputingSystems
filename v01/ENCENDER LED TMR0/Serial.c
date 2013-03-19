#include <LPC21xx.H>                     /* definición de registros               */

#define CR     0x0D


void init_serial (void)  {               /* inicialización del puerto       */
  PINSEL0 = 0x00000005;                  /* configuración de pines RxD0 y TxD0 */
  U0LCR = 0x83;                          /* 8 bits, sin paridad, 1 Stop bit    */
  U0DLL = 0x14;                            /* 9600 Baud Rate @ 15MHz VPB Clock  */
  U0LCR = 0x03;                          /* DLAB = 0                          */
}


/* implementación de putchar (invocada por printf())    */
int sendchar (unsigned char  ch)  { /* escribe un caracter en el puerto serie    */

  if (ch == '\n')  {		//si el caracter es'\n' envía CR=0x0D=d'13' enter(ascii)
    while (!(U0LSR & 0x20));		//espera a que el registro de salida esté vacío
    U0THR = CR;                          /* envía CR */
  }
  while (!(U0LSR & 0x20));
  return (U0THR = ch);
}


int getkey (void)  {           /* lee el caracter actual en el puerto serie   */
  while (!(U0LSR & 0x01));		//espera a que el caracter esté disponible para ser leído
  return (U0RBR);
}





