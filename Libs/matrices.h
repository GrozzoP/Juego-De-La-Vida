#ifndef MATRICES_H_INCLUDED
#define MATRICES_H_INCLUDED

#define FILAS 40
#define COLS 40
#define VIVA '*'
#define MUERTA '.'

int numeroAleatorio(int minNum, int maxNum);
void juego(char juego[][COLS]);
void inicioJuego(char juego[][COLS]);
void inicioMatriz(char juego[][COLS]);
void actualizarJuego(char juego[][COLS]);
void actualizarMatriz(char juego[][COLS]);
int contarVecinas(char juego[][COLS], int fila, int col);
void mostrarJuego(char juego[][COLS]);
void patronBloque(char juego[][COLS]);
void patronPlaneador(char juego[][COLS]);
void patronParpadeador(char juego[][COLS]);
void patronSapo(char juego[][COLS]);
void patronFaro(char juego[][COLS]);
void canionPlaneador(char juego[][COLS]);


#endif // MATRICES_H_INCLUDED
