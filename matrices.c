#include "libs/matrices.h"
#include "libs/global.h"
#include <string.h>

void extraerValorNumerico(int* num, const char* cadena, const char* parametro) {
    char* delimitador = strchr(cadena, ':'), *cadenaNumero;
    size_t tamanioParametro;

    if (delimitador == NULL)
        return;

    tamanioParametro = delimitador - cadena;

    if(strncmp(cadena, parametro, tamanioParametro) != 0)
        return;

    cadenaNumero = delimitador + 1;

    *num = atoi(cadenaNumero);
}

void extraerValorCadena(char* valor, const char* cadena, const char* parametro) {
    char* delimitador = strchr(cadena, ':'), *aux;
    size_t tamanioParametro;

    if (delimitador == NULL)
        return;

    tamanioParametro = delimitador - cadena;

    if(strncmp(cadena, parametro, tamanioParametro) != 0)
        return;

    aux = delimitador + 1;

    while(*aux == ' ')
    {
        aux++;
    }

    while(*aux)
    {
        *valor = *aux;
        valor++; aux++;
    }

    *valor = '\0';
}

//---dibujo de matriz
void dibujarJuego(char**matriz,int fila, int columna,SDL_Rect fillRect,int posX, int posY,int alto, int ancho,SDL_Renderer* renderer){
   int i,j;
   int posIni;

   posIni = posX;

   for(i=0;i<fila;i++){
    for(j=0;j<columna;j++){
        if(matriz[i][j]==VIVA){
        SDL_SetRenderDrawColor(renderer, 0, 200+i, 0, 0);
        dibujarRectangulo(fillRect,posX,posY,alto,ancho,renderer);
       }
        if(matriz[i][j]==MUERTA){
        SDL_SetRenderDrawColor(renderer, 0, 50, 50, 0);
        dibujarRectangulo(fillRect,posX,posY,alto,ancho,renderer);
       }

       posX+=15;
    }
    posY+=15;
    posX = posIni;
   }
}


void dibujarRectangulo(SDL_Rect fillRect,int posX, int posY,int alto, int ancho,SDL_Renderer* renderer){
    fillRect.x = posX;
    fillRect.y = posY;
    fillRect.h = alto;
    fillRect.w = ancho;

    SDL_RenderFillRect(renderer, &fillRect);
}

//---matriz dinamica
char** construirMat(unsigned fila, unsigned col)
{
    char** mat = (char**)malloc(fila * sizeof(char*));
    if(!mat)
    {
        printf("\nError al asignar memoria.\n");
        return NULL;
    }
    int i;
    char **ini = mat;
    char **tmp;

    for(i = 0; i < fila; i++)
    {
        *(mat + i) = (char *)malloc(col * sizeof(char));
        if(!*(mat + i))
        {
            for(tmp = ini; tmp < mat + i; tmp++) //Liberamos toda la memoria hasta el punto actual
                free(*tmp);
            free(ini);
            printf("Error al asignar memoria.\n");
            return NULL;
        }
    }
    return ini;

}


int numeroAleatorio(int minNum, int maxNum)
{
    srand(time(NULL));
    return rand() % (maxNum - minNum + 1) + minNum;
}

// ----- CONFIGURACION BASICA ----- //

// Rellenar la matriz al comenzar el juego
void inicioMatriz(char **juego)
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
void mostrarJuego(char **juego)
{
    int i, j;

    for(i = 0; i < FILAS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            juego[i][j] == VIVA ? printf(" %c ", VIVA) : printf("   ");
        }
        printf("\n");
    }
}

int contarVecinas(char **juego, int fila, int col)
{
    int f, c, cont = 0, filaMin, filaMax, colMin, colMax;

    filaMin = (fila - 1) > 0 ? fila - 1 : 0;
    colMin = (col - 1) > 0 ? col - 1 : 0;
    filaMax = (fila + 1) == FILAS ? fila : fila + 1;
    colMax = (col + 1) == COLS ? col : col + 1;

    for(f = filaMin; f <= filaMax; f++)
    {
        for(c = colMin; c <= colMax; c++)
        {
            if((juego[f][c] == VIVA || juego[f][c] == 'M') && !(f == fila && c == col))
                cont++;
        }
    }

    //printf("\nSUMA POSICION (%d, %d): %d", fila, col, cont);
    return cont;
}


// Modificar el 'estado futuro' de las celulas en base al estado actual
void actualizarJuego(char **juego)
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
void actualizarMatriz(char **juego)
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
void patronBloque(char **juego)
{
    juego[FILAS / 2][COLS / 2] = VIVA;
    juego[FILAS / 2][(COLS / 2) + 1] = VIVA;
    juego[(FILAS / 2) + 1][COLS / 2] = VIVA;
    juego[(FILAS / 2) + 1][(COLS / 2) + 1] = VIVA;
}

void patronPlaneador(char **juego)
{
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

void patronParpadeador(char **juego)
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

void patronSapo(char **juego)
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

void canionPlaneador(char **juego)
{
    int fila, columna;
  //  srand(time(NULL));

  //  fila = numeroAleatorio(0, FILAS - 9);
  //  columna = numeroAleatorio(0, COLS - 36);
    fila = 0;
    columna = 1;

    // Genera el primer bloque
    juego[fila + 5][columna + 1] = VIVA;
    juego[fila + 5][columna + 2] = VIVA;
    juego[fila + 6][columna + 1] = VIVA;
    juego[fila + 6][columna + 2] = VIVA;

    juego[fila + 3][columna + 13] = VIVA;
    juego[fila + 3][columna + 14] = VIVA;
    juego[fila + 4][columna + 12] = VIVA;
    juego[fila + 4][columna + 16] = VIVA;
    juego[fila + 5][columna + 11] = VIVA;
    juego[fila + 5][columna + 17] = VIVA;
    juego[fila + 6][columna + 11] = VIVA;
    juego[fila + 6][columna + 15] = VIVA;
    juego[fila + 6][columna + 17] = VIVA;
    juego[fila + 6][columna + 18] = VIVA;
    juego[fila + 7][columna + 11] = VIVA;
    juego[fila + 7][columna + 17] = VIVA;
    juego[fila + 8][columna + 12] = VIVA;
    juego[fila + 8][columna + 16] = VIVA;
    juego[fila + 9][columna + 13] = VIVA;
    juego[fila + 9][columna + 14] = VIVA;

    juego[fila + 1][columna + 25] = VIVA;
    juego[fila + 2][columna + 23] = VIVA;
    juego[fila + 2][columna + 25] = VIVA;
    juego[fila + 3][columna + 21] = VIVA;
    juego[fila + 3][columna + 22] = VIVA;
    juego[fila + 4][columna + 21] = VIVA;
    juego[fila + 4][columna + 22] = VIVA;
    juego[fila + 5][columna + 21] = VIVA;
    juego[fila + 5][columna + 22] = VIVA;
    juego[fila + 6][columna + 23] = VIVA;
    juego[fila + 6][columna + 25] = VIVA;
    juego[fila + 7][columna + 25] = VIVA;


    // Genera el segundo bloque
    juego[fila + 3][columna + 35] = VIVA;
    juego[fila + 3][columna + 36] = VIVA;
    juego[fila + 4][columna + 35] = VIVA;
    juego[fila + 4][columna + 36] = VIVA;
}

void patronFaro(char **juego)
{
    int fila, columna, i, j;
    srand(time(NULL));

    fila = numeroAleatorio(0, FILAS - 5);
    columna = numeroAleatorio(0, COLS - 4);

    for(i = 0; i < 2; i++)
    {
        for(j = 0; j < 2; j++)
        {
            if(i != 1 || j != 1)
                juego[fila + i][columna + j] = VIVA;
        }
    }

    fila += 2;
    columna += 2;

    for(i = 0; i < 2; i++)
    {
        for(j = 0; j < 2; j++)
        {
            if(i != 0 || j != 0)
                juego[fila + i][columna + j] = VIVA;
        }
    }
}
void patronOctagono(char** juego)
{
    int fila, columna, i, j;
    srand(time(NULL));

    fila = numeroAleatorio(0, FILAS - 6);
    columna = numeroAleatorio(0, COLS - 9);

    for (i = 0; i <= 7; i++)
    {
        j = (i <= 3) ? columna + 3 - i : columna + i - 4;
        juego[fila + i][j] = VIVA;
    }

    for (i = 0; i <= 7; i++)
    {
        j = (i <= 3) ? columna + 4 + i : columna + 11 - i;
        juego[fila + i][j] = VIVA;
    }
}
void patronPicante(char**juego)
{
    int fila, columna, i;
    srand(time(NULL));

    fila = numeroAleatorio(0, FILAS - 6);
    columna = numeroAleatorio(0, COLS - 9);

    juego[fila+2][columna+0] = VIVA;
    juego[fila+1][columna+1] = VIVA;
    juego[fila+3][columna+1] = VIVA;
    juego[fila+0][columna+2] = VIVA;
    juego[fila+4][columna+2] = VIVA;

    for(i = 0; i <= 4; i++)
    {
        juego[fila + i][columna + 3] = VIVA;
    }

    juego[fila+2][columna+8] = VIVA;
    juego[fila+1][columna+7] = VIVA;
    juego[fila+3][columna+7] = VIVA;
    juego[fila+0][columna+6] = VIVA;
    juego[fila+4][columna+6] = VIVA;

    for(i = 0; i <= 4; i++)
    {
        juego[fila + i][columna + 5] = VIVA;
    }
}

void patronPredecesor(char** juego){
    int fila, columna, i, j;
    srand(time(NULL));

    fila = numeroAleatorio(0, FILAS - 12);
    columna = numeroAleatorio(0, COLS - 12);

    for (i = 7; i <= 9; i++)
    {
        juego[fila + i][columna + 0] = VIVA;
        juego[fila + i][columna + 6] = VIVA;
    }

    for (j = 2; j <= 4; j++)
    {
        juego[fila + 5][columna + j] = VIVA;
        juego[fila + 11][columna + j] = VIVA;
    }

    juego[fila][columna + 9] = VIVA;
    juego[fila][columna + 10] = VIVA;

    for (i = 1; i <= 3; i++)
        juego[fila + i][columna + 8] = VIVA;

    juego[fila + 3][columna + 9] = VIVA;
    juego[fila + 3][columna + 10] = VIVA;
    juego[fila + 1][columna + 11] = VIVA;
    juego[fila + 2][columna + 11] = VIVA;
}

// ----- INICIO JUEGO----- //

void inicioJuego(char **juego, char* patron)
{
    inicioMatriz(juego);

   if(strcmpi(patron, "sapo") == 0)
        patronSapo(juego);

   else if(strcmpi(patron, "picante") == 0)
        patronPicante(juego);

   else if(strcmpi(patron, "octagono") == 0)
        patronOctagono(juego);

   else if(strcmpi(patron, "predecesor") == 0)
        patronPredecesor(juego);

   else
   {
       printf("\nComo no se eligio ninguna opcion correcta. Se mostrara el patron 'canion planeador'\n");
       canionPlaneador(juego);
   }
}

void juego(char **juego)
{
    mostrarJuego(juego);
    actualizarJuego(juego);
    actualizarMatriz(juego);
}
