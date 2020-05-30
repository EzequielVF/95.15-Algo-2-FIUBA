#include "batallas.h"
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define FORMATO_LECTURA_ARCHIVO "%[^;];%[^;];%i;%i;%i;%[^;];%i;%i;%i;%[^;];%i;%i;%i\n"
#define NOMBRE_ENT_DERROTADOR "perdedores"
#define POKEMONES_X_ENTRENADOR 3
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int ENTREADORES_MIN = 2;
const int PARAMETROS_LEIDOS = 13;
const int COINCIDENCIA = 0;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Recibe un entrenador_t un vector de pokemones y la direcion de un archivo abierto y
 * lo lee y deposita lo que lee en la variables pasadas por referencia.
 */
void leer_archivo(int* leido, entrenador_t *entrenador_leido, pokemon_t pokemon_leido[], FILE* entrenadores){
    (*leido) = fscanf(entrenadores, FORMATO_LECTURA_ARCHIVO, entrenador_leido->nombre, 
        pokemon_leido[0].nombre, &pokemon_leido[0].fuerza, &pokemon_leido[0].agilidad, &pokemon_leido[0].inteligencia, 
        pokemon_leido[1].nombre, &pokemon_leido[1].fuerza, &pokemon_leido[1].agilidad, &pokemon_leido[1].inteligencia, 
        pokemon_leido[2].nombre, &pokemon_leido[2].fuerza, &pokemon_leido[2].agilidad, &pokemon_leido[2].inteligencia);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 */
torneo_t* torneo_crear(char *ruta_archivo){
    torneo_t* torneo = NULL;
    entrenador_t entrenador_leido;
    pokemon_t pokemon_leido[POKEMONES_X_ENTRENADOR];
    int leido = 0;
    bool problemas_memoria = false;
    bool problema_archivo = false;
    size_t cantidad = 0;

    FILE* entrenadorestxt = fopen(ruta_archivo,"r");
    if(entrenadorestxt){
        torneo = malloc(sizeof(torneo_t));
        if(torneo != NULL){
            torneo->cantidad_entrenadores = 0;
            torneo->ronda = 0;
            torneo->entrenadores = NULL;
            leer_archivo(&leido, &entrenador_leido, pokemon_leido, entrenadorestxt);
            if(leido != PARAMETROS_LEIDOS){
                problemas_memoria = true;
            }
            while((leido == PARAMETROS_LEIDOS)&&(!problemas_memoria)&&(!problema_archivo)){
                torneo->cantidad_entrenadores++;
                cantidad++;
                torneo->entrenadores = realloc(torneo->entrenadores, cantidad*sizeof(entrenador_t));
                if(torneo->entrenadores != NULL){
                    strcpy(torneo->entrenadores[cantidad-1].nombre, entrenador_leido.nombre);
                    torneo->entrenadores[cantidad-1].pokemones = malloc(POKEMONES_X_ENTRENADOR*sizeof(pokemon_t));
                    if(torneo->entrenadores[cantidad-1].pokemones != NULL){
                        for(int i = 0; i < POKEMONES_X_ENTRENADOR; i++){
                            strcpy(torneo->entrenadores[cantidad-1].pokemones[i].nombre, pokemon_leido[i].nombre);
                            torneo->entrenadores[cantidad-1].pokemones[i].fuerza = pokemon_leido[i].fuerza;
                            torneo->entrenadores[cantidad-1].pokemones[i].agilidad = pokemon_leido[i].agilidad;
                            torneo->entrenadores[cantidad-1].pokemones[i].inteligencia = pokemon_leido[i].inteligencia;
                        }
                        leer_archivo(&leido, &entrenador_leido, pokemon_leido, entrenadorestxt);
                    }else{
                        problemas_memoria = true;
                        perror("Problemas con la asignacion de memoria para pokemones.");
                    }
                }else{
                    problemas_memoria = true;
                    perror("Prolema con el agrandamiento de la memoria para entrenadores.");
                }
            }
        }else{
           problemas_memoria = true;
           perror("Problemas con la asignacion de memoria para el torneo.");
        }
    }else{
        problema_archivo = true;
        perror("Problemas con la apertura del archivo de entrenadores.");
    }
    if((!problemas_memoria)&&(!problema_archivo)){
        fclose(entrenadorestxt);
        return torneo;
    }else if ((problemas_memoria)&&(!problema_archivo)){
        fclose(entrenadorestxt);
        torneo_destruir(torneo);
        return NULL;
    }else{
        return NULL;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 */
void torneo_destruir(torneo_t* torneo){
    if(torneo != NULL){
        if(torneo->cantidad_entrenadores > 0){
            for(int i = (torneo->cantidad_entrenadores); i>0; i--){
                free(torneo->entrenadores[i-1].pokemones);
            }
            free(torneo->entrenadores);
        }
        free(torneo);  
    } 
     
    
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Recibe dos booleanos por referencia y determina si puede jugar o no, y si participara una cantidad
 * par o impar de entrenadores.
 */
void definir_parametros_torneo(bool *se_puede_jugar, bool *cantidad_par, int entrenadores, int (*ganador_batalla)(entrenador_t* ,entrenador_t*)){
    if((entrenadores >= ENTREADORES_MIN)&&((*ganador_batalla) != NULL)){
        (*se_puede_jugar) = true;
    }
    if(entrenadores % 2 == 0){
        (*cantidad_par) = true;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Recibe un puntero a torneo y la cantidad de entrenadores y desplaza hacia el final a los entrenadores que perdieron. (Metodo: Burbujeo)
 */
void mover_perdedores_alfinal(torneo_t* torneo, int entrenadores){
    entrenador_t swap;
    for(int i = 1; i < entrenadores; i++){
        for(int j = 0; j < entrenadores-i; j++){
            if(strcmp((torneo->entrenadores[j].nombre), NOMBRE_ENT_DERROTADOR) == COINCIDENCIA){
                swap = torneo->entrenadores[j];
                torneo->entrenadores[j] = torneo->entrenadores[j+1];
                torneo->entrenadores[j+1] = swap;
            }                
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Recibe un puntero a torneo y un contador, cambia el nombredel entrenador que perdio el duelo y libera la memoria reservada para sus pokemones.
 */
void cambiar_nombre_perdedor(torneo_t* torneo, int contador){
    strcpy(torneo->entrenadores[contador].nombre, NOMBRE_ENT_DERROTADOR);
    free(torneo->entrenadores[contador].pokemones);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Recibe un puntero a torneo,la cantidad de entrenadores y un booleano que dice si la cantidad es par o no, y actualiza la nueva cantidad de 
 * entrenadores activos en el torneo.
 */
void actualizar_cant_entrenadores(torneo_t* torneo, int* entrenadores, bool cantidad_par){
    if(cantidad_par){
        (*entrenadores) = (*entrenadores)/2;
        torneo->cantidad_entrenadores = (*entrenadores);
    }else{
        (*entrenadores) = (((*entrenadores)-1)/2)+1;
        torneo->cantidad_entrenadores = (*entrenadores);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 */
int torneo_jugar_ronda(torneo_t* torneo, int (*ganador_batalla)(entrenador_t* ,entrenador_t*)){
    int contador = 0;
    int resultado = 0;
    int entrenadores;
    int resultado_ronda = 0;
    bool se_puede_jugar = false;
    bool cantidad_par = false;
    if(torneo != NULL){
        entrenadores = torneo->cantidad_entrenadores;
        definir_parametros_torneo(&se_puede_jugar, &cantidad_par, entrenadores, ganador_batalla);
    }
    
    if(se_puede_jugar){
        while(contador < entrenadores-1){
            resultado = ganador_batalla(&(torneo->entrenadores[contador]), &(torneo->entrenadores[contador+1]));
            if(resultado == 0){
                cambiar_nombre_perdedor(torneo, contador+1);
            }else{
                cambiar_nombre_perdedor(torneo, contador);
            }
            contador+=2;
        }
        mover_perdedores_alfinal(torneo, entrenadores);
        actualizar_cant_entrenadores(torneo, &entrenadores, cantidad_par);
        torneo->entrenadores = realloc(torneo->entrenadores, (size_t)entrenadores*sizeof(entrenador_t));
        if(torneo->entrenadores == NULL){
            perror("Error en el realloc");
        }
        resultado_ronda = EXITO;
        torneo->ronda++;
    }else{
        resultado_ronda = ERROR;
    }
    return resultado_ronda;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 */
void torneo_listar(torneo_t* torneo, void (*formatear_entrenador)(entrenador_t*)){
    if((torneo != NULL)&&( *formatear_entrenador != NULL)){
        for(int contador = 0; contador<(torneo->cantidad_entrenadores); contador++){
            formatear_entrenador(&(torneo->entrenadores[contador]));
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////