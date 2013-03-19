#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    int res;
    int cont;
    int id;
} jugador;

void show_tabla(int**);
int movimiento(jugador*,int,int**);

int main()
{
    int i, j, **tabla;
    jugador p1, p2;
    p1.cont = p2.cont = 3; p1.id = 1; p2.id = 2;

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
            if(p1.cont >= 1)
            {
                printf("Jugador 1: "); scanf("%d", &i); printf("\n");
                p1.res = movimiento(&p1,i,tabla);
                if(p1.res == 1)
                {
                    printf("EL JUGADOR 1 ES EL GANADOR!!! \n");
                    exit(0);
                }
            }
        }
        while(p1.res == 2);
        p1.cont--;if(p1.cont < 1) p1.cont = 0;

        do
        {
            if(p2.cont >= 1)
            {
                printf("Jugador 2: "); scanf("%d", &i); printf("\n");
                p2.res = movimiento(&p2,i,tabla);
                if(p2.res == 1)
                {
                    printf("EL JUGADOR 1 ES EL GANADOR!!! \n");
                    exit(0);
                }
            }
        }
        while(p2.res == 2);
        p2.cont--;if(p2.cont < 1) p2.cont = 0;
    }
}

int movimiento(jugador *p, int codigo, int **tabla)
{
    int fila, columna, i, j, win=0;

    //VALIDACIONES
    if(codigo >=0 && codigo <=8) //Se valida que el jugador no haya ingresado un alor fuera de la tabla
    {
        fila = codigo/3;
        columna = codigo - fila*3;
        if(tabla[fila][columna] == 0) //Se valida que el jugador no haya colocado la ficha donde ya habia una
            tabla[fila][columna] = p->id;
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
