#ifndef MATRICES_H_INCLUDED
#define MATRICES_H_INCLUDED

#define FILAS 40
#define COLS 40
#define VIVA '*'
#define MUERTA '.'
char** construirMat(unsigned fila, unsigned col);
int numeroAleatorio(int minNum, int maxNum);
void juego(char **juego);
void inicioJuego(char **juego);
void inicioMatriz(char **juego);
void actualizarJuego(char **juego);
void actualizarMatriz(char **juego);
int contarVecinas(char **juego, int fila, int col);
void mostrarJuego(char **juego);
void patronBloque(char **juego);
void patronPlaneador(char **juego);
void patronParpadeador(char **juego);
void patronSapo(char **juego);
void patronFaro(char **juego);
void canionPlaneador(char **juego);

#endif // MATRICES_H_INCLUDED
