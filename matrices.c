#include "Libs/matrices.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int numeroAleatorio(int minNum, int maxNum)
{
    srand(time(NULL));
    return rand() % (maxNum - minNum + 1) + minNum;
}

// ----- CONFIGURACION BASICA ----- //

// Rellenar la matriz al comenzar el juego
void inicioMatriz(char juego[][COLS])
{
    int i, j;

    for(i = 0; i < FILAS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            juego[i][j] = MUERTA;
        }
    }

}

// Mostrar la generacion actual del juego
void mostrarJuego(char juego[][COLS])
{
    int i, j;

    for(i = 0; i < FILAS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            juego[i][j] == VIVA ? printf(" %c ", VIVA) : printf("  ");
        }
        printf("\n");
    }
}

int contarVecinas(char juego[][COLS], int fila, int col)
{
    int i, j, cont = 0;

    for(i = fila - 1; i <= fila + 1; i++)
    {
        for(j = col - 1; j <= col + 1; j++)
        {
            // Se cuenta solo si esta dentro de la matriz, y exceptuando el centro (celula a analizar)
            if((i >= 0 && j >= 0) && !(i == fila && j == col))
                // Si la celula en particular esta viva o en el proximo turno va a morir, cuenta como vecina
                // La segunda condicion es logica, ya que si "en la proxima generacion va a morir", significa
                // que en la actual generacion, esa celula esta VIVA.
                if(juego[i][j] == VIVA || juego[i][j] == 'M')
                    cont++;
        }
    }

    //printf("\nSUMA POSICION (%d, %d): %d", fila, col, cont);

    return cont;
}

// Modificar el 'estado futuro' de las celulas en base al estado actual
void actualizarJuego(char juego[][COLS])
{
    int i, j, vecinas;

    for(i = 0; i < FILAS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            vecinas = contarVecinas(juego, i, j);

            // Si una 'celda' tiene 3 celulas vecinas, en la proxima generacion va a nacer
            if(juego[i][j] == MUERTA && vecinas == 3)
                juego[i][j] = 'N';

            // Si una celula tiene mas de 3 vecinos, uno o ninguno, en la proxima generacion muere
            else if(juego[i][j] == VIVA && (vecinas > 3 || vecinas <= 1))
                juego[i][j] = 'M';
        }
    }
}

// Una vez ya analizada como sera la proxima generacion, se reemplaza cada condicion futura
// por su simbolo correspondiente. Si nace, entonces sera el simbolo de la celula viva,
// si va a morir, sera reemplazado por el simbolo de la celula muerta
void actualizarMatriz(char juego[][COLS])
{
    int i, j;

    for(i = 0; i < FILAS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            if(juego[i][j] == 'N')
                juego[i][j] = VIVA;

            else if(juego[i][j] == 'M')
                juego[i][j] = MUERTA;
        }
    }
}

// ----- PATRONES ----- //

// Bloque estatico que se genera en el medio del mapa
void patronBloque(char juego[][COLS])
{
    juego[FILAS / 2][COLS / 2] = VIVA;
    juego[FILAS / 2][(COLS / 2) + 1] = VIVA;
    juego[(FILAS / 2) + 1][COLS / 2] = VIVA;
    juego[(FILAS / 2) + 1][(COLS / 2) + 1] = VIVA;
}

void patronPlaneador(char juego[][COLS]){
    int fila, columna, i;

    fila = numeroAleatorio(0, FILAS - 3);
    columna = numeroAleatorio(0, COLS - 3);

    srand(time(NULL));

    for(i=columna;i<columna+3;i++){
        juego[fila][i] = VIVA;
    }

    juego[fila + 1][columna] = VIVA;
    juego[fila + 2][columna + 1] = VIVA;
}

void patronParpadeador(char juego[][COLS])
{
    int fila, columna, i;
    srand(time(NULL));

    fila = numeroAleatorio(0, FILAS - 5);
    columna = numeroAleatorio(0, COLS - 5);

    for(i = columna; i < columna + 3; i++)
    {
        juego[fila][i] = VIVA;
    }
}

void patronSapo(char juego[][COLS])
{
    int fila, columna, i;
    srand(time(NULL));

    fila = numeroAleatorio(0, FILAS - 1);
    columna = numeroAleatorio(0, COLS - 1);

    for(i = 0; i < 3; i++)
    {
        juego[fila][columna + i] = VIVA;
    }

    fila++;
    columna--;

    for(i = 0; i < 3; i++)
    {
        juego[fila][columna + i] = VIVA;
    }
}

// ----- INICIO JUEGO----- //

void inicioJuego(char juego[][COLS])
{
    inicioMatriz(juego);
    patronSapo(juego);
}

void juego(char juego[][COLS])
{
    mostrarJuego(juego);
    actualizarJuego(juego);
    actualizarMatriz(juego);
}
