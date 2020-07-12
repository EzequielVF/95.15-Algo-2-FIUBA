#include "pokedex.h"
#include "lista.h"
#include "abb.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void muestra_opciones_basicas(){
    printf("\t/***MENU***/\n");
    printf("\n\n");
    printf("Iniciar Pokedex (Tecla I)\n");
    printf("Salir del programa (Tecla S)\n");
    printf("Ayuda (Tecla H)\n");
    printf("/*********************************/\n");
}

void muestra_todas_las_opciones(){
    printf("\t/***MENU***/\n");
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
    printf("/*********************************/\n");
}

void mostrar_menu(pokedex_t* pokedex, bool* menu_extendido, bool* quiere_salir){
    char letra = 'a';
    
    while(!(*quiere_salir) && !(*menu_extendido)){
        muestra_opciones_basicas();
        scanf("%c", &letra);
        while(letra != 'I' && letra != 'S' && letra != 'H'){
            printf("q carajos?");
            printf("La letra insertada no corresponde a una opcion valida, vuelva a intentarlo.\n");
            scanf("%c", &letra);
        }
        if(letra == 'H'){
            printf("\n");
        }else if(letra == 'I'){
            pokedex_prender(pokedex);
            *menu_extendido = true;
        }else{
            *quiere_salir = true;
        }
    }
}

void mostrar_menu_desbloqueado(pokedex_t* pokedex, bool* quiere_salir){
    char letra = 'a';
    char nombre_pokemon[MAX_NOMBRE];
    bool letra_valida = false;
    int especie = 0;

    while(!(*quiere_salir)){
        muestra_todas_las_opciones();
        scanf("%c", &letra);
        if(letra == 'I' || letra == 'G' || letra == 'S' || letra == 'H' || letra == 'A'|| letra == 'E'|| letra == 'C'|| letra == 'V'|| letra == 'M'|| letra == 'P'){
            letra_valida = true;
        }
        while(!letra_valida){
            printf("La letra insertada no corresponde a una opcion valida, vuelva a intentarlo.\n");
            scanf("%c", &letra);
            if(letra == 'I' || letra == 'G' || letra == 'S' || letra == 'H' || letra == 'A'|| letra == 'E'|| letra == 'C'|| letra == 'V'|| letra == 'M'|| letra == 'P'){
                letra_valida = true;
            }
        }
        if(letra == 'H'){
            printf("\n");
        }else if(letra == 'I'){
            pokedex_prender(pokedex);
        }else if(letra == 'S'){
            *quiere_salir = true;
        }else if(letra == 'G'){
            pokedex_apagar(pokedex);
        }else if(letra == 'A'){
            pokedex_avistar(pokedex, "avistamientos.txt");
        }else if(letra == 'E'){
            pokedex_evolucionar(pokedex, "evoluciones.txt");
        }else if(letra == 'C'){
            pokedex_ultimos_capturados(pokedex);
        }else if(letra == 'V'){
            pokedex_ultimos_vistos(pokedex);
        }else if(letra == 'M'){
            printf("Porfavor, escriba el numero de la especie de la que desea informacion:\n");
            scanf("%d", &especie);
            pokedex_informacion(pokedex, especie, "");
        }else if(letra == 'P'){
            printf("Porfavor, escriba el numero de la especie de la que desea informacion:\n");
            scanf("%d", &especie);
            printf("Ahora, escriba el nombre del pokemon del que busca informacion:\n");
            scanf("%s", nombre_pokemon);
            pokedex_informacion(pokedex, especie, nombre_pokemon);
        }

    }
}

int main(){
    pokedex_t* pokedex = NULL;
    bool menu_extendido = false;
    bool quiere_salir = false;
    
    while(!quiere_salir){
        if(!menu_extendido){
            mostrar_menu(pokedex, &menu_extendido, &quiere_salir);
        }
        if(!quiere_salir && menu_extendido){
            mostrar_menu_desbloqueado(pokedex, &quiere_salir);
        }
    }
    pokedex_destruir(pokedex);
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 /*int cantidad;
    especie_pokemon_t* especies[10];
    especie_pokemon_t* especies2[10];
    pokedex_t* pokedex = pokedex_crear("Ezequiel");
    if(pokedex_avistar(pokedex, "avistamientos.txt")== EXITO){
        printf("Perfecto\n");
    }else{
        printf("Error\n");
    }
    printf("%s\n", pokedex->nombre_entrenador);
    
    cantidad = arbol_recorrido_preorden(pokedex->pokemones, (void**)especies, 10);
    for(int i=0;i<cantidad;i++){
        printf("%i-", especies[i]->numero);
        printf("Niveles de pokemones en la lista: ");
        for(size_t j=0;j<lista_elementos(especies[i]->pokemones);j++){
            printf("%i-", (*(particular_pokemon_t*)lista_elemento_en_posicion(especies[i]->pokemones, j)).nivel);
        }
        printf("\n\n");
    }
    for(size_t j=0;j<lista_elementos(pokedex->ultimos_vistos);j++){
            printf("%s-", (*(particular_pokemon_t*)lista_elemento_en_posicion(pokedex->ultimos_vistos, j)).nombre);
            printf("%i-", (*(particular_pokemon_t*)lista_elemento_en_posicion(pokedex->ultimos_vistos, j)).nivel);
    }
    printf("\n\n");
    for(size_t j=0;j<lista_elementos(pokedex->ultimos_capturados);j++){
            printf("%s-", (*(particular_pokemon_t*)lista_elemento_en_posicion(pokedex->ultimos_capturados, j)).nombre);
            printf("%i-", (*(particular_pokemon_t*)lista_elemento_en_posicion(pokedex->ultimos_capturados, j)).nivel);
    }
	printf("\n");
    if(pokedex_evolucionar(pokedex, "evoluciones.txt")== EXITO){
        printf("Perfecto\n");
    }
    cantidad = arbol_recorrido_preorden(pokedex->pokemones, (void**)especies2, 10);
    for(int i=0;i<cantidad;i++){
        printf("%i-", especies2[i]->numero);
        printf("Niveles de pokemones en la lista: ");
        for(size_t j=0;j<lista_elementos(especies2[i]->pokemones);j++){
            printf("%i-", (*(particular_pokemon_t*)lista_elemento_en_posicion(especies2[i]->pokemones, j)).nivel);
        }
        printf("\n\n");
    }
    pokedex_ultimos_capturados(pokedex);
    printf("\n\n");
    pokedex_ultimos_vistos(pokedex);
    printf("\n\n");
    pokedex_informacion(pokedex, 25, "");
    pokedex_apagar(pokedex);
    pokedex_t* pokedex = pokedex_prender();
    int cantidad;
    especie_pokemon_t* especies[12];
    cantidad = arbol_recorrido_preorden(pokedex->pokemones, (void**)especies, 12);
    for(int i=0;i<cantidad;i++){
        printf("%i-", especies[i]->numero);
        printf("Niveles de pokemones en la lista: ");
        for(size_t j=0;j<lista_elementos(especies[i]->pokemones);j++){
            printf("%i-", (*(particular_pokemon_t*)lista_elemento_en_posicion(especies[i]->pokemones, j)).nivel);
        }
        printf("\n\n");
    }
    pokedex_destruir(pokedex);*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////