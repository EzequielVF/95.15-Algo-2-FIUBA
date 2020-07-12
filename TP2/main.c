#include "pokedex.h"
#include "lista.h"
#include "abb.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ERROR -1
#define EXITO 0
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void muestra_opciones_basicas(){
    printf(ANSI_COLOR_YELLOW"\t/***MENU***/\n");
    printf("\n\n");
    printf("Iniciar Pokedex (Tecla I)\n");
    printf("Salir del programa (Tecla S)\n");
    printf("Ayuda (Tecla H)\n");
    printf("/*********************************/\n"ANSI_COLOR_RESET);
}

void muestra_todas_las_opciones(){
    printf(ANSI_COLOR_CYAN"\t/***MENU***/\n");
    printf("\n\n");
    printf("Iniciar Pokedex (Tecla I)\n");
    printf("Guardar Pokedex (Tecla G)\n");
    printf("Salir del programa (Tecla S)\n");
    printf("Ayuda (Tecla H)\n");
    printf("Avistar pokemon (Tecla A)\n");
    printf("Evolucionar Pokemon (Tecla E)\n");
    printf("Capturas Recientes (Tecla C)\n");
    printf("Vistas recientes (Tecla V)\n");
    printf("Informacion especie (Tecla M)\n");
    printf("Informacion Pokemon (Tecla P)\n");
    printf("/*********************************/\n"ANSI_COLOR_RESET );
}

int main(){
    pokedex_t* pokedex = NULL;
    bool menu_extendido = false;
    bool quiere_salir = false;
    char letra = 'a';
    char nombre_pokemon[MAX_NOMBRE];
    int especie = 0;
    int estado = 0;
    system("clear");
    while(!quiere_salir){
        if(!menu_extendido){
            muestra_opciones_basicas();
            scanf(" %c", &letra);
            while(letra != 'I' && letra != 'S' && letra != 'H'){
                printf(ANSI_COLOR_RED"La letra insertada no corresponde a una opcion valida, vuelva a intentarlo.\n"ANSI_COLOR_RESET);
                scanf(" %c", &letra);
            }
            system("clear");
            if(letra == 'H'){
                printf("\n");
                printf(ANSI_COLOR_YELLOW"/***********************************/\n"ANSI_COLOR_RESET);
            }else if(letra == 'I'){
                pokedex = pokedex_prender();
                menu_extendido = true;
                printf(ANSI_COLOR_YELLOW"/***********************************/\n"ANSI_COLOR_RESET);
            }else{
                pokedex_destruir(pokedex);
                quiere_salir = true;
            }
        }else{
            muestra_todas_las_opciones();
            scanf(" %c", &letra);
            while(letra != 'I' && letra != 'G' && letra != 'S' && letra != 'H' && letra != 'A'&& letra != 'E'&& letra != 'C'&& letra != 'V'&& letra != 'M'&& letra != 'P'){
                printf(ANSI_COLOR_RED"La letra insertada no corresponde a una opcion valida, vuelva a intentarlo.\n"ANSI_COLOR_RESET);
                scanf(" %c", &letra);
            }
            system("clear");
            if(letra == 'H'){
                /////////////////////////////////////////////////////////////////////////////////////
                printf("\n");
                printf(ANSI_COLOR_YELLOW"/***********************************/\n"ANSI_COLOR_RESET);
                /////////////////////////////////////////////////////////////////////////////////////
            }else if(letra == 'I'){
                /////////////////////////////////////////////////////////////////////////////////////
                pokedex = pokedex_prender();
                printf(ANSI_COLOR_YELLOW"/***********************************/\n"ANSI_COLOR_RESET);
                /////////////////////////////////////////////////////////////////////////////////////
            }else if(letra == 'S'){
                /////////////////////////////////////////////////////////////////////////////////////
                pokedex_destruir(pokedex);
                quiere_salir = true;
                /////////////////////////////////////////////////////////////////////////////////////
            }else if(letra == 'G'){
                /////////////////////////////////////////////////////////////////////////////////////
                estado = pokedex_apagar(pokedex);
                if(estado == EXITO){
                    printf(ANSI_COLOR_GREEN"Informacion guardada exitosamente!\n"ANSI_COLOR_RESET);
                    printf(ANSI_COLOR_YELLOW"/***********************************/\n"ANSI_COLOR_RESET);
                }else{
                    printf(ANSI_COLOR_RED"Error al guardar informacion!\n"ANSI_COLOR_RESET);
                    printf(ANSI_COLOR_YELLOW"/***********************************/\n"ANSI_COLOR_RESET);
                }
                /////////////////////////////////////////////////////////////////////////////////////
            }else if(letra == 'A'){
                /////////////////////////////////////////////////////////////////////////////////////
                estado = pokedex_avistar(pokedex, "avistamientos.txt");
                if(estado == EXITO){
                    printf(ANSI_COLOR_GREEN"Pokemones avistados correctamente!\n"ANSI_COLOR_RESET);
                    printf(ANSI_COLOR_YELLOW"/***********************************/\n"ANSI_COLOR_RESET);
                }else{
                    printf(ANSI_COLOR_RED"Error al avistar los pokemones!\n"ANSI_COLOR_RESET);
                    printf(ANSI_COLOR_YELLOW"/***********************************/\n"ANSI_COLOR_RESET);
                }
                /////////////////////////////////////////////////////////////////////////////////////
            }else if(letra == 'E'){
                /////////////////////////////////////////////////////////////////////////////////////
                estado = pokedex_evolucionar(pokedex, "evoluciones.txt");
                if(estado == EXITO){
                    printf(ANSI_COLOR_GREEN"Pokemones evolucionados exitosamente!\n"ANSI_COLOR_RESET);
                    printf(ANSI_COLOR_YELLOW"/***********************************/\n"ANSI_COLOR_RESET);
                }else{
                    printf(ANSI_COLOR_RED"Error al evolucionar los pokemones!\n"ANSI_COLOR_RESET);
                    printf(ANSI_COLOR_YELLOW"/***********************************/\n"ANSI_COLOR_RESET);
                }
                /////////////////////////////////////////////////////////////////////////////////////
            }else if(letra == 'C'){
                /////////////////////////////////////////////////////////////////////////////////////
                printf(ANSI_COLOR_GREEN"Ultimos pokemones capturados:\n"ANSI_COLOR_RESET);
                pokedex_ultimos_capturados(pokedex);
                printf(ANSI_COLOR_YELLOW"/***********************************/\n"ANSI_COLOR_RESET);
                /////////////////////////////////////////////////////////////////////////////////////
            }else if(letra == 'V'){
                /////////////////////////////////////////////////////////////////////////////////////
                printf(ANSI_COLOR_GREEN"Ultimos pokemones visto:\n"ANSI_COLOR_RESET);
                pokedex_ultimos_vistos(pokedex);
                printf(ANSI_COLOR_YELLOW"/***********************************/\n"ANSI_COLOR_RESET);
                /////////////////////////////////////////////////////////////////////////////////////
            }else if(letra == 'M'){
                /////////////////////////////////////////////////////////////////////////////////////
                printf(ANSI_COLOR_CYAN"Porfavor, escriba el numero de la especie de la que desea informacion:\n"ANSI_COLOR_RESET);
                scanf("%d", &especie);
                pokedex_informacion(pokedex, especie, "");
                printf(ANSI_COLOR_YELLOW"/***********************************/\n"ANSI_COLOR_RESET);
                /////////////////////////////////////////////////////////////////////////////////////
            }else if(letra == 'P'){
                /////////////////////////////////////////////////////////////////////////////////////
                printf(ANSI_COLOR_CYAN"Porfavor, escriba el numero de la especie de la que desea informacion:\n"ANSI_COLOR_RESET);
                scanf("%d", &especie);
                printf(ANSI_COLOR_CYAN"Ahora, escriba el nombre del pokemon del que busca informacion:\n"ANSI_COLOR_RESET);
                scanf("%s", nombre_pokemon);
                pokedex_informacion(pokedex, especie, nombre_pokemon);
                printf(ANSI_COLOR_YELLOW"/***********************************/\n"ANSI_COLOR_RESET);
                /////////////////////////////////////////////////////////////////////////////////////
            }
        }
    }
    return 0;
}