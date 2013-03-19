#include <stdlib.h>
#include <stdio.h>

void show_tabla(int**);
int movimiento(int,int,int**);

int main()
{
    int i, j, **tabla, res1, res2;

    tabla = (int**) malloc(sizeof(int*) * 3);
    for(i=0; i<3; i++)
    {
        tabla[i] = (int*) malloc(sizeof(int) * 3);
        for(j=0; j<3; j++)
            tabla[i][j] = 0;
    }

    show_tabla(tabla);printf("\n \n \n");

    while(1)
    {
        do
        {
            printf("Jugador 1: "); scanf("%d", &i); printf("\n");
            res1 = movimiento(1,i,tabla);
            if(res1 == 1)
            {
                printf("EL JUGADOR 1 ES EL GANADOR!!! \n");
                exit(0);
            }
        }
        while(res1 == 2);

        do
        {
            printf("Jugador 2: "); scanf("%d", &i); printf("\n");
            res2 = movimiento(2,i,tabla);
            if(res2 == 1)
            {
                printf("EL JUGADOR 2 ES EL GANADOR!!! \n");
                exit(0);
            }
        }
        while(res2 == 2);
    }
}

int movimiento(int jugador, int codigo, int **tabla)
{
    int fila, columna, i, j, win=0;

    if(codigo >=0 && codigo <=8) //Se valida que el jugador no haya ingresado un alor fuera de la tabla
    {
        fila = codigo/3;
        columna = codigo - fila*3;
        if(tabla[fila][columna] == 0) //Se valida que el jugador no haya colocado la ficha donde ya habia una
            tabla[fila][columna] = jugador;
        else
        {
            printf("Error, no puede colocar una ficha ahi! \n");
            return 2; //Retorna error
        }
    }
    else
    {
        printf("Error, coloque un numero del 0 al 8! \n");
        return 2; //Retorna error
    }

    //CHECKEO DE FILAS
    for(i=0; i<3 && !win; i++)
    {
        win = 1;
        for(j=0; j<3 && win; j++)
        {
            if(tabla[i][j] != jugador)
                win = 0;
        }
    }

    //CHECKEO DE COLUMNAS
    for(i=0; i<3 && !win; i++)
    {
        win = 1;
        for(j=0; j<3 && win; j++)
        {
            if(tabla[j][i] != jugador)
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
            if(tabla[j][j] != jugador)
                win_d1 = 0;

            if(tabla[j][2-j] != jugador)
                win_d2 = 0;

            win = win_d1 || win_d2;
        }
    }

    show_tabla(tabla); //Quitar esta linea cuando pasemos el codigo a ARM!!!!!!!
    printf("\n"); //Quitar esta linea cuando pasemos el codigo a ARM!!!!!!!

    return win;
}

void show_tabla(int **tabla) //Quitar esta funcion cuando pasemos el codigo a ARM!!!!!!!
{
    int i, j;
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
            printf("%d ", tabla[i][j]);
        printf("\n");
    }
}
