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

#define TAM_CADENA 20
#define VIVA '*'
#define MUERTA '.'

void extraerValorNumerico(int* num, const char* cadena, const char* parametro);
void extraerValorCadena(char* valor, const char* cadena, const char* parametro);
char** construirMat(unsigned fila, unsigned col);
int numeroAleatorio(int minNum, int maxNum);
void juego(char** juego);
void inicioJuego(char** juego, char* patron);
void inicioMatriz(char** juego);
void actualizarJuego(char** juego);
void actualizarMatriz(char** juego);
int contarVecinas(char** juego, int fila, int col);
void mostrarJuego(char** juego);
void patronBloque(char** juego);
void patronPlaneador(char** juego);
void patronParpadeador(char** juego);
void patronSapo(char** juego);
void patronFaro(char** juego);
void canionPlaneador(char** juego);
void patronOctagono(char** juego);
void patronPicante(char** juego);
void patronPredecesor(char** juego);
void dibujarRectangulo(SDL_Rect fillRect,int posX, int posY,int alto, int ancho,SDL_Renderer* renderer);
void dibujarJuego(char**matriz,int fila, int columna,SDL_Rect fillRect,int posX, int posY,int alto, int ancho,SDL_Renderer* renderer);

#endif // MATRICES_H_INCLUDED
