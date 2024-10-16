#include <stdio.h>
#include <string.h>
#include "libs/matrices.h"
#include "libs/global.h"

#define CELL_SIZE 16

// Defino las variables globales, para que de lo obtenido por argumento al main lo pueda usar en la biblioteca
int FILAS;
int COLS;

int main(int argc, char *argv[])
{
    //--configuracion de inicio de la matriz
    int i;
    int F, C, window_width, window_height;
    char* cad = malloc(TAM_CADENA);
    F = C = -1;

    for(i = 0; i < argc; i++)
    {
        printf("\nARGUMENTO %d: %s", i + 1, argv[i]);
        extraerValorNumerico(&F, argv[i], "max-filas");
        extraerValorNumerico(&C, argv[i], "max-columnas");
        extraerValorCadena(cad, argv[i], "patron");
    }

    printf("\nFILAS: %d", F);
    printf("\nCOLS: %d", C);
    printf("\nPATRON: %s", cad);

    if(F == -1 || C == -1)
        return -1;

    // Actualizo las variables globales
    FILAS = F;
    COLS = C;

    char **MJuego = construirMat(F, C);

    if(!MJuego)
        return 1;
    inicioJuego(MJuego, cad);
    //--
    unsigned char done;
    int k;

    int delay               = 100;//estaba en 100
    SDL_Window* window      = NULL; //objeto ventana
    SDL_Renderer* renderer  = NULL; //objeto lienzo
    SDL_Event e; //oyente
    SDL_Rect fillRect; //objeto de rectangulo

    // Establezco el ancho y alto de la ventana segun la cantidad de filas y columnas
    window_width = FILAS * CELL_SIZE;
    window_height = COLS * CELL_SIZE;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL No se ha podido inicializar! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    //crea ventana
    window = SDL_CreateWindow("Juego de la vida",
                                                SDL_WINDOWPOS_CENTERED,
                                                SDL_WINDOWPOS_CENTERED,
                                                window_width,
                                                window_height,
                                                SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("Error en la creacion de la ventana: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    //crea lienzo
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("No se ha podido crear el lienzo! SDL Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    //bucle principal
    while (!done){
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT ) {
                done = 1;
            }
        }

        SDL_SetRenderDrawColor(renderer, 110, 110, 200, 0xFF);//color fondo
        SDL_RenderClear(renderer); //limpia la pantalla

      //  SDL_SetRenderDrawColor(renderer, 0, 240, 50, 0);//establece color del prox elemento

        dibujarJuego(MJuego,FILAS,COLS,fillRect,10,10,10,10,renderer); //dibuja constantemente la matriz
        actualizarJuego(MJuego); //define las vivas y muertas
        actualizarMatriz(MJuego); // las cambia


        SDL_RenderPresent(renderer); //actualiza el lienzo
        k++;
        //SDL_UpdateWindowSurface(window);

        //Titulo/caption de la ventana//se puede agregar data aca
        SDL_SetWindowTitle(window, "Trabajo Practico"); // constantemente define el titulo
        SDL_Delay(delay); // establece el delay del juego

    }

    //destruyo todos los elementos creados
    //Observar ni mas ni menos que destructores, en la asignatura no inventamos nada!

    for(i=0;i<FILAS;i++)
        free(*(MJuego+i));
    free(MJuego);
    free(cad);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


