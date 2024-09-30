#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "Libs/matrices.h"

#define ITERACIONES 40

int main()
{
    char **MJuego = construirMat(FILAS, COLS);
    if(!MJuego)
        return 1;
    int i=0;

    inicioJuego(MJuego);
    while(i < ITERACIONES)
    {
        juego(MJuego);
        system("Pause");
        system("cls");
        i++;
    }

    // Liberar memoria dinámica asignada (IMPORTANTE)
    for(i=0;i<FILAS;i++)
        free(*(MJuego+i));

    free(MJuego);

    return 0;
}
