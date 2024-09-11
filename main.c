#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "Libs/matrices.h"

#define ITERACIONES 40

int main()
{
    char MJuego[FILAS][COLS];
    int indice = 0;

    inicioJuego(MJuego);
    while(indice < ITERACIONES)
    {
        juego(MJuego);
        system("Pause");
        system("cls");
        indice++;
    }
    return 0;
}
