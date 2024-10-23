#ifndef MATRICES_H_INCLUDED
#define MATRICES_H_INCLUDED
#include <stdio.h>
#include <time.h>

#include <unistd.h>
#include <conio.h>
#include <time.h>
#ifdef __MINGW32__
    #define SDL_MAIN_HANDLED
    #include <SDL_main.h>
#endif

#include <SDL2/SDL.h>

#define MAX_COLS 50
#define TAM_CADENA 20
#define VIVA '*'
#define MUERTA '.'
#define EXTRA 0

void extraerValorNumerico(int* num, const char* cadena, const char* parametro);
void extraerValorArchivo(char* valor, const char* cadena, const char* formato);
char** construirMat(unsigned fila, unsigned col);
void inicioJuego(char* nombreArchivo, char** juego, int FILAS, int COLS);
int numeroAleatorio(int minNum, int maxNum);
void inicioMatriz(char** juego, int FILAS, int COLS);
void actualizarJuego(char** juego, int FILAS, int COLS);
void actualizarMatriz(char** juego, int FILAS, int COLS);
int contarVecinas(char** juego, int fila, int col, int FILAS, int COLS);
void mostrarJuego(char** juego, int FILAS, int COLS);
void patronBloque(char** juego, int FILAS, int COLS);
void patronPlaneador(char** juego, int FILAS, int COLS);
void patronParpadeador(char** juego, int FILAS, int COLS);
void patronSapo(char** juego, int FILAS, int COLS);
void patronFaro(char** juego, int FILAS, int COLS);
void canionPlaneador(char** juego, int FILAS, int COLS);
void patronOctagono(char** juego, int FILAS, int COLS);
void patronPicante(char** jueg, int FILAS, int COLS);
void patronPredecesor(char** juego, int FILAS, int COLS);
int insertarPatron(char** juego, char* nombreArchivo, int FILAS, int COLS);
void tamanioPatron(char* nombreArchivo, int* FILAS, int* COLS);
void dibujarRectangulo(SDL_Rect fillRect,int posX, int posY,int alto, int ancho,SDL_Renderer* renderer);
void dibujarJuego(char**matriz,int fila, int columna,SDL_Rect fillRect,int posX, int posY,int alto, int ancho,SDL_Renderer* renderer);

#endif // MATRICES_H_INCLUDED
