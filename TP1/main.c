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
#define NOMBRE_ARCHIVO "entrenadores.csv"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int ENTRENADOR_1 = 0;
const int ENTRENADOR_2 = 1;
const int CANT_OPCIONES_RONDA = 6; 
const int IGUALES = 0;
const int POKEMONES_MAX = 3;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void definir_ganador_orden_alfabetico(entrenador_t* entrenador_1, entrenador_t* entrenador_2, int *ganador);
int por_inteligencia_del_equipo(entrenador_t* entrenador_1, entrenador_t* entrenador_2);
int por_fuerza_bruta(entrenador_t* entrenador_1, entrenador_t* entrenador_2);
int por_agilidad(entrenador_t* entrenador_1, entrenador_t* entrenador_2);
int por_promedio_pokemon1(entrenador_t* entrenador_1, entrenador_t* entrenador_2);
int por_promedio_pokemon2ypokemon_3(entrenador_t* entrenador_1, entrenador_t* entrenador_2);
int por_suma_habilidades_pokemon2(entrenador_t* entrenador_1, entrenador_t* entrenador_2);
void listar_por_inteligencia(entrenador_t* entrenador);
void listar_por_fuerza(entrenador_t* entrenador);
void listar_por_agilidad(entrenador_t* entrenador);
void listar_promedio_pokemon_1(entrenador_t* entrenador);
void listar_promedio_pokemon_2ypokemon_3(entrenador_t* entrenador);
void listar_suma_habilidades_pokemon2(entrenador_t* entrenador);
void definir_parametros_ronda(void (**formatear_entrenador)(entrenador_t*), int (**ganador_batalla)(entrenador_t* ,entrenador_t*));
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(){
    srand((unsigned)time(NULL));
    torneo_t* carmin = NULL;
    int resultado = 0;
    int (*ganador_batalla)(entrenador_t* ,entrenador_t*) =  NULL;
    void (*formatear_entrenador)(entrenador_t*) = NULL;
    bool ganador = false;

    carmin = torneo_crear(NOMBRE_ARCHIVO);
    
    if(carmin != NULL){
        if(carmin->cantidad_entrenadores == 0){
            printf(ANSI_COLOR_RED"\n\nDebido a la cuarentena no hubo inscriptos, el torneo se pospone hasta que termine la misma.\n\n"ANSI_COLOR_RESET);
        }
        while((carmin->cantidad_entrenadores>1)&&(!ganador)&&(resultado != ERROR)){
            definir_parametros_ronda(&formatear_entrenador, &ganador_batalla);
            torneo_listar(carmin, formatear_entrenador);
            resultado = torneo_jugar_ronda(carmin, ganador_batalla);
            if((carmin->cantidad_entrenadores < 2)){
                ganador = true;
            }
            if(resultado == 0){
                printf(ANSI_COLOR_RED"\n\tLa ronda %d se jugo correctamente, quedan %d entrenador/es.\n\n\n\n"ANSI_COLOR_RESET, carmin->ronda-1, carmin->cantidad_entrenadores);
            }else{
                printf("La ronda no pudo jugarse, 'Houston, tenemos un problema.'\n");
            }
            torneo_listar(carmin, formatear_entrenador);
            if(ganador){
                printf(ANSI_COLOR_RED"\n\n El entrenador %s es EL GANADOR del torneo Carmin\n\n"ANSI_COLOR_RESET, carmin->entrenadores[0].nombre);
            }
        }
        torneo_destruir(carmin);
    }else{
        printf("Debido a problemas tecnicos producidos por la llegada de Mewtwo se suspendio el torneo de Carmin hasta nuevo aviso, nuestras mas sinceras disculpas.\n");
    }
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Recibe dos entrenadores con sus campos completos y verifica quien se 
 * encuentra primero alfabeticamente para decidir el ganador.
 */
void definir_ganador_orden_alfabetico(entrenador_t* entrenador_1, entrenador_t* entrenador_2, int *ganador){
    if(strcmp(entrenador_1->nombre, entrenador_2->nombre) <= IGUALES){
        (*ganador) = ENTRENADOR_1;
    }else{
        (*ganador) = ENTRENADOR_2;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Recibe dos entrenadores con sus campos completos y compara cual suma mas puntos de inteligencia entre sus 3 pokemones, 
 * en caso de empate llama a definir_por_orden_alfabetico.
 * Devuelve 1 si el promedio mas alto es del entrenador 1 o -1 si el promedio mas alto es del entrenador 2.
 */
int por_inteligencia_del_equipo(entrenador_t* entrenador_1, entrenador_t* entrenador_2){
    int inteligencia_ent_1 = 0;
    int inteligencia_ent_2 = 0;
    int ganador;
    inteligencia_ent_1 = (entrenador_1->pokemones[0].inteligencia)+(entrenador_1->pokemones[1].inteligencia)+(entrenador_1->pokemones[2].inteligencia);
    inteligencia_ent_2 = (entrenador_2->pokemones[0].inteligencia)+(entrenador_2->pokemones[1].inteligencia)+(entrenador_2->pokemones[2].inteligencia);
    if(inteligencia_ent_1 > inteligencia_ent_2){
        ganador = ENTRENADOR_1;
    }else if(inteligencia_ent_1 < inteligencia_ent_2){
        ganador = ENTRENADOR_2;
    }else{
        definir_ganador_orden_alfabetico(entrenador_1, entrenador_2, &ganador);
    }
    return ganador;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Recibe dos entrenadores con sus campos completos y compara cual suma mas puntos de fuerza entre sus 3 pokemones, 
 * en caso de empate llama a definir_por_orden_alfabetico.
 * Devuelve 1 si el promedio mas alto es del entrenador 1 o -1 si el promedio mas alto es del entrenador 2.
 */
int por_fuerza_bruta(entrenador_t* entrenador_1, entrenador_t* entrenador_2){
    int fuerza_ent_1 = 0;
    int fuerza_ent_2 = 0;
    int ganador;
    fuerza_ent_1 = (entrenador_1->pokemones[0].fuerza)+(entrenador_1->pokemones[1].fuerza)+(entrenador_1->pokemones[2].fuerza);
    fuerza_ent_2 = (entrenador_2->pokemones[0].fuerza)+(entrenador_2->pokemones[1].fuerza)+(entrenador_2->pokemones[2].fuerza);
    if(fuerza_ent_1 > fuerza_ent_2){
        ganador = ENTRENADOR_1;
    }else if(fuerza_ent_1 < fuerza_ent_2){
        ganador = ENTRENADOR_2;
    }else{
        definir_ganador_orden_alfabetico(entrenador_1, entrenador_2, &ganador);
    }
    return ganador;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Recibe dos entrenadores con sus campos completos y compara cual suma mas puntos de agilidad entre sus 3 pokemones, 
 * en caso de empate llama a definir_por_orden_alfabetico.
 * Devuelve 1 si el promedio mas alto es del entrenador 1 o -1 si el promedio mas alto es del entrenador 2.
 */
int por_agilidad(entrenador_t* entrenador_1, entrenador_t* entrenador_2){
    int agilidad_ent_1 = 0;
    int agilidad_ent_2 = 0;
    int ganador;
    agilidad_ent_1 = (entrenador_1->pokemones[0].agilidad)+(entrenador_1->pokemones[1].agilidad)+(entrenador_1->pokemones[2].agilidad);
    agilidad_ent_2 = (entrenador_2->pokemones[0].agilidad)+(entrenador_2->pokemones[1].agilidad)+(entrenador_2->pokemones[2].agilidad);
    if(agilidad_ent_1 > agilidad_ent_2){
        ganador = ENTRENADOR_1;
    }else if(agilidad_ent_1 < agilidad_ent_2){
        ganador = ENTRENADOR_2;
    }else{
        definir_ganador_orden_alfabetico(entrenador_1, entrenador_2, &ganador);
    }
    return ganador;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Recibe dos entrenadores con sus campos completos y compara cual tiene el promedio mas alto de stats en el pokemon 1, 
 * en caso de empate llama a definir_por_orden_alfabetico.
 * Devuelve 1 si el promedio mas alto es del entrenador 1 o -1 si el promedio mas alto es del entrenador 2.
 */
int por_promedio_pokemon1(entrenador_t* entrenador_1, entrenador_t* entrenador_2){
    double promedio_entrenador1;
    double promedio_entrenador2;
    int ganador = 0;
    promedio_entrenador1 = ((entrenador_1->pokemones[0].inteligencia)+(entrenador_1->pokemones[0].agilidad)+(entrenador_1->pokemones[0].fuerza))/POKEMONES_MAX;
    promedio_entrenador2 = ((entrenador_2->pokemones[0].inteligencia)+(entrenador_2->pokemones[0].agilidad)+(entrenador_2->pokemones[0].fuerza))/POKEMONES_MAX;
    if(promedio_entrenador1 > promedio_entrenador2){
        ganador = ENTRENADOR_1;
    }else if(promedio_entrenador1 < promedio_entrenador2){
        ganador = ENTRENADOR_2;
    }else{
        definir_ganador_orden_alfabetico(entrenador_1, entrenador_2, &ganador);
    }
    return ganador;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Recibe dos entrenadores con sus campos completos y compara cual tiene el promedio mas alto de stats en el pokemon 2 y 3, 
 * en caso de empate llama a definir_por_orden_alfabetico.
 * Devuelve 1 si el promedio mas alto es del entrenador 1 o -1 si el promedio mas alto es del entrenador 2.
 */
int por_promedio_pokemon2ypokemon_3(entrenador_t* entrenador_1, entrenador_t* entrenador_2){
    double promedio_entrenador1;
    double promedio_entrenador2;
    int ganador = 0;
    promedio_entrenador1 = ((entrenador_1->pokemones[1].inteligencia)+(entrenador_1->pokemones[1].agilidad)+(entrenador_1->pokemones[1].fuerza)+
    (entrenador_1->pokemones[2].inteligencia)+(entrenador_1->pokemones[2].agilidad)+(entrenador_1->pokemones[2].fuerza))/(POKEMONES_MAX*2);
    promedio_entrenador2 = ((entrenador_2->pokemones[1].inteligencia)+(entrenador_2->pokemones[1].agilidad)+(entrenador_2->pokemones[1].fuerza)+
    (entrenador_2->pokemones[2].inteligencia)+(entrenador_2->pokemones[2].agilidad)+(entrenador_2->pokemones[2].fuerza))/(POKEMONES_MAX*2);
    if(promedio_entrenador1 > promedio_entrenador2){
        ganador = ENTRENADOR_1;
    }else if(promedio_entrenador1 < promedio_entrenador2){
        ganador = ENTRENADOR_2;
    }else{
        definir_ganador_orden_alfabetico(entrenador_1, entrenador_2, &ganador);
    }
    return ganador;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Recibe dos entrenadores con sus campos completos y compara cual suma mas puntos entre todas las stats de sus pokemones 2 y 3, 
 * en caso de empate llama a definir_por_orden_alfabetico.
 * Devuelve 1 si el promedio mas alto es del entrenador 1 o -1 si el promedio mas alto es del entrenador 2.
 */
int por_suma_habilidades_pokemon2(entrenador_t* entrenador_1, entrenador_t* entrenador_2){
    int total_habilidades_ent1;
    int total_habilidades_ent2;
    int ganador = 0;
    total_habilidades_ent1 = ((entrenador_1->pokemones[1].inteligencia)+(entrenador_1->pokemones[1].agilidad)+(entrenador_1->pokemones[1].fuerza));
    total_habilidades_ent2 = ((entrenador_2->pokemones[1].inteligencia)+(entrenador_2->pokemones[1].agilidad)+(entrenador_2->pokemones[1].fuerza));
    if(total_habilidades_ent1>total_habilidades_ent2){
        ganador = ENTRENADOR_1;
    }else if(total_habilidades_ent1>total_habilidades_ent2){
        ganador = ENTRENADOR_2;
    }else{
        definir_ganador_orden_alfabetico(entrenador_1, entrenador_2, &ganador);
    }
    return ganador;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Recibe un entrenador con sus campos completos y escribe por pantalla su campo nombre y nombre e inteligencia de cada componente en el campo pokemon. 
 */
void listar_por_inteligencia(entrenador_t* entrenador){
    printf(ANSI_COLOR_YELLOW"\tNombre: %s\nPokemon1: %s, y su inteligencia es %d\nPokemon2: %s, y su inteligencia es %d\nPokemon3; %s, y su inteligencia es %d\n\n"ANSI_COLOR_RESET, entrenador->nombre, 
    entrenador->pokemones[0].nombre, entrenador->pokemones[0].inteligencia, entrenador->pokemones[1].nombre, entrenador->pokemones[1].inteligencia, 
    entrenador->pokemones[2].nombre, entrenador->pokemones[2].inteligencia);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Recibe un entrenador con sus campos completos y escribe por pantalla su campo nombre y nombre y fuerza de cada componente en campo pokemon. 
 */
void listar_por_fuerza(entrenador_t* entrenador){
    printf(ANSI_COLOR_GREEN"\tNombre: %s\nPokemon1: %s, y su fuerza es %d\nPokemon2: %s, y su fuerza es %d\nPokemon3; %s, y su fuerza es %d\n\n"ANSI_COLOR_RESET, entrenador->nombre, 
    entrenador->pokemones[0].nombre, entrenador->pokemones[0].fuerza, entrenador->pokemones[1].nombre, entrenador->pokemones[1].fuerza, 
    entrenador->pokemones[2].nombre, entrenador->pokemones[2].fuerza);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Recibe un entrenador con sus campos completos y escribe por pantalla su campo nombre y nombre y agilidad de cada componente en campo pokemon.  
 */
void listar_por_agilidad(entrenador_t* entrenador){
    printf(ANSI_COLOR_CYAN"\tNombre: %s\nPokemon1: %s, y su agilidad es %d\nPokemon2: %s, y su agilidad es %d\nPokemon3: %s, y su agilidad es %d\n\n"ANSI_COLOR_RESET, entrenador->nombre, 
    entrenador->pokemones[0].nombre, entrenador->pokemones[0].agilidad, entrenador->pokemones[1].nombre, entrenador->pokemones[1].agilidad, 
    entrenador->pokemones[2].nombre, entrenador->pokemones[2].agilidad);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Recibe un entrenador con sus campos completos y escribe por pantalla el nombre del entrenador y nombre y promedio de las stats del pokemon 1. 
 */
void listar_promedio_pokemon_1(entrenador_t* entrenador){
    double promedio = (entrenador->pokemones[0].agilidad + entrenador->pokemones[0].fuerza + entrenador->pokemones[0].inteligencia)/POKEMONES_MAX;
    printf(ANSI_COLOR_BLUE"\tNombre: %s\nPokemon1: %s, y su promedio de habilidades es: %f\n\n"ANSI_COLOR_RESET, entrenador->nombre, entrenador->pokemones[0].nombre, promedio);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Recibe un entrenador con sus campos completos y escribe por pantalla nombre del entrenador, nombre pokemon 2 y pokemon 3 y el promedio de las stats de los pokemones 2 y 3. 
 */
void listar_promedio_pokemon_2ypokemon_3(entrenador_t* entrenador){
    double promedio = (((entrenador->pokemones[1].inteligencia)+(entrenador->pokemones[1].agilidad)+(entrenador->pokemones[1].fuerza)+
    (entrenador->pokemones[2].inteligencia)+(entrenador->pokemones[2].agilidad)+(entrenador->pokemones[2].fuerza))/(POKEMONES_MAX*2));
    printf(ANSI_COLOR_MAGENTA"\tNombre: %s\nPokemon1: %s\nPokemon2: %s\nEl promedio de habilidades de los dos en conjunto es: %f\n\n"ANSI_COLOR_RESET, entrenador->nombre, entrenador->pokemones[1].nombre, 
    entrenador->pokemones[2].nombre, promedio);   
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Recibe un entrenador con sus campos completos y escribe por pantalla nombre del entrenador y nombre y total de la suma de habilidades del pokemon 2. 
 */
void listar_suma_habilidades_pokemon2(entrenador_t* entrenador){
    int total = (entrenador->pokemones[1].inteligencia)+(entrenador->pokemones[1].agilidad)+(entrenador->pokemones[1].fuerza);
    printf("\tNombre: %s\nPokemon2: %s, y la suma de todas sus stats es; %d\n\n", entrenador->nombre, entrenador->pokemones[1].nombre, total);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Se encarga de asignarle a los punteros a funcion una tematica al azar en la que se
 * basara la ronda.
 */
void definir_parametros_ronda(void (**formatear_entrenador)(entrenador_t*), int (**ganador_batalla)(entrenador_t* ,entrenador_t*)){
    int opcion_elegida = (rand()%CANT_OPCIONES_RONDA);

    switch (opcion_elegida)
    {
        case 0:
            *ganador_batalla = &por_inteligencia_del_equipo;
            *formatear_entrenador = &listar_por_inteligencia;
            printf(ANSI_COLOR_RED"\n\tEsta ronda se definira por la inteligencia conjunta de los pokemones.\n\n"ANSI_COLOR_RESET);
            break;
    
        case 1:
            *ganador_batalla = &por_fuerza_bruta;
            *formatear_entrenador = &listar_por_fuerza;
            printf(ANSI_COLOR_RED"\n\tEsta ronda se definira por la fuerza conjunta de los pokemones.\n\n"ANSI_COLOR_RESET);
            break;
        case 2:
            *ganador_batalla = &por_agilidad;
            *formatear_entrenador = &listar_por_agilidad;
            printf(ANSI_COLOR_RED"\n\tEsta ronda se definira por la agilidad conjunta de los pokemones.\n\n"ANSI_COLOR_RESET);
            break;

        case 3:
            *ganador_batalla = &por_promedio_pokemon1;
            *formatear_entrenador = &listar_promedio_pokemon_1;
            printf(ANSI_COLOR_RED"\n\tEsta ronda se definira por el promedio de las stats del pokemon 1.\n\n"ANSI_COLOR_RESET);
            break;

        case 4:
            *ganador_batalla = &por_promedio_pokemon2ypokemon_3;
            *formatear_entrenador = &listar_promedio_pokemon_2ypokemon_3;
            printf(ANSI_COLOR_RED"\n\tEsta ronda se definira por el promedio de las stats del pokemon 2 y 3.\n\n"ANSI_COLOR_RESET);
            break;

        case 5:
            *ganador_batalla = &por_suma_habilidades_pokemon2;
            *formatear_entrenador = &listar_suma_habilidades_pokemon2;
            printf(ANSI_COLOR_RED"\n\tEsta ronda se definira por la suma de las stats del pokemon 2.\n\n"ANSI_COLOR_RESET);
            break;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////