#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    int res;
    int cont;
    int id;
} jugador;

void show_tabla(int*);
int movimiento(jugador*,int,int,int*[3]);

int main()
{
    int i, j, tabla[3][3];
    jugador p1, p2;
    p1.cont = p2.cont = 3; p1.id = 1; p2.id = 2;


    for(i=0; i<3; i++)
    {
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
                p1.res = movimiento(&p1,i,-1,tabla);
                if(p1.res == 1)
                {
                    printf("EL JUGADOR 1 ES EL GANADOR!!! \n");
                    exit(0);
                }
            }
            else
            {
                printf("Jugador 1 - sustraer: "); scanf("%d", &j); printf("\n");
                printf("Jugador 1 - colocar: "); scanf("%d", &i); printf("\n");
                p1.res = movimiento(&p1,i,j,tabla);
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
                p2.res = movimiento(&p2,i,-1,tabla);
                if(p2.res == 1)
                {
                    printf("EL JUGADOR 2 ES EL GANADOR!!! \n");
                    exit(0);
                }
            }
            else
            {
                printf("Jugador 2 - sustraer: "); scanf("%d", &j); printf("\n");
                printf("Jugador 2 - colocar: "); scanf("%d", &i); printf("\n");
                p2.res = movimiento(&p2,i,j,tabla);
                if(p2.res == 1)
                {
                    printf("EL JUGADOR 2 ES EL GANADOR!!! \n");
                    exit(0);
                }
            }
        }
        while(p2.res == 2);
        p2.cont--;if(p2.cont < 1) p2.cont = 0;
    }
}

int movimiento(jugador *p, int codigo, int sustr, int *tabla)
{
    int fila_m, fila_s, columna_m, columna_s, i, j, win=0;

    //VALIDACIONES

    if(codigo >=0 && codigo <=8) //Se valida que el jugador no haya ingresado un alor fuera de la tabla
    {
        fila_m = codigo/3;
        columna_m = codigo - fila_m*3;
        if(tabla[fila_m][columna_m] != 0) //Se valida que el jugador no haya colocado la ficha donde ya habia una
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

    if(p->cont < 1)
    {
        fila_s = sustr/3;
        columna_s = sustr - fila_s*3;
        if(tabla[fila_s][columna_s] != p->id)
        {
            printf("Error, no puede sacar esa ficha! \n");
            return 2;
        }
        if(!(codigo + 3 == sustr ||
           codigo - 3 == sustr ||
           codigo - 1 == sustr ||
           codigo + 1 == sustr ||
           codigo == 4 ||
           sustr == 4 ))
        {
            printf("Error, no puede realizar ese movimiento! \n");
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

    show_tabla(tabla); //Quitar esta linea cuando pasemos el codigo a ARM!!!!!!!
    printf("\n"); //Quitar esta linea cuando pasemos el codigo a ARM!!!!!!!

    return win;
}

void show_tabla(int *tabla) //Quitar esta funcion cuando pasemos el codigo a ARM!!!!!!!
{
    int i, j;
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
            printf("%d ", tabla[i][j]);
        printf("\n");
    }
}
