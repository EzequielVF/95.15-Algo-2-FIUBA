#include "pokedex.h"
#include "lista.h"
#include "abb.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define ERROR -1
#define EXITO 0
#define FORMATO_LECTURA_AVISTAMIENTOS "%i;%[^;];%[^;];%[^;];%i;%c\n"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int PARAMETROS_LEIDOS = 6;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
especie_pokemon_t* crear_especie(int numero, char* nombre, char* descripcion){
    especie_pokemon_t* aux = malloc(sizeof(especie_pokemon_t));
    if(!aux)
        return NULL;

    aux->numero = numero;
    strcpy(aux->nombre, nombre);
    strcpy(aux->descripcion, descripcion);
    aux->pokemones = lista_crear();

    return aux;
}

particular_pokemon_t* crear_pokemon(char* nombre, int nivel, char capturado){
    particular_pokemon_t* aux = malloc(sizeof(particular_pokemon_t));
    if(!aux)
        return NULL;

    strcpy(aux->nombre, nombre);
    aux->nivel = nivel;
    if(capturado == 'S'){
        aux->capturado = true;
    }else{
        aux->capturado = false;
    }
    return aux;
}

int comparar_cosas(void* elemento1, void* elemento2){
	if(!elemento1 || !elemento2)
		return 0;

	if(((especie_pokemon_t*)elemento1)->numero > ((especie_pokemon_t*)elemento2)->numero )
		return 1;
	
	if(((especie_pokemon_t*)elemento1)->numero < ((especie_pokemon_t*)elemento2)->numero )
		return -1;
	
	return 0;
}

void destruir_cosa(especie_pokemon_t* elemento){
	lista_destruir(elemento->pokemones);
    free(elemento);
}

void destructor_de_cosas(void* elemento){
	if(!elemento)
		return;
	
	destruir_cosa((especie_pokemon_t*)elemento);
}
///////////////////////////////////////////////////////FUNCIONES BASICAS///////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////CREAR POKEDEX//////////////////////////////////////////////////////////////////////
pokedex_t* pokedex_crear(char entrenador[MAX_NOMBRE]){
    pokedex_t* pokedex = NULL;
    pokedex = malloc(sizeof(pokedex_t));

    if(!pokedex)
        return NULL;

    strcpy(pokedex->nombre_entrenador, entrenador);
    pokedex->pokemones = NULL;
    pokedex->ultimos_capturados = NULL;
    pokedex->ultimos_vistos = NULL;
    return pokedex;
}
/////////////////////////////////////////////////////////POKEDEX AVISTAR////////////////////////////////////////////////////////////////////
void leer_archivo(int* leido, int* numero_especie, char* nombre_especie, char* descripcion_especie, char* nombre_pokemon, int* nivel_pokemon, char* capturado, FILE* avistamientostxt){
    (*leido) = fscanf(avistamientostxt, FORMATO_LECTURA_AVISTAMIENTOS, numero_especie, nombre_especie, descripcion_especie, nombre_pokemon, nivel_pokemon, capturado);
}

void revisar_estado_estructuras(pokedex_t* pokedex){
    if(pokedex->pokemones == NULL){
        pokedex->pokemones = arbol_crear(comparar_cosas, destructor_de_cosas);
    }
    if(pokedex->ultimos_capturados == NULL){
        pokedex->ultimos_capturados = lista_crear(); ///ESTO UNA PILA
    }
    if(pokedex->ultimos_vistos == NULL){
        pokedex->ultimos_vistos = lista_crear(); ///ESTO ES UNA COLA
    }
}

void insertar_pokemon_en_especie(pokedex_t* pokedex, especie_pokemon_t* especie_leida, particular_pokemon_t* pokemon_leido, bool* flag_liberar_especie, bool* inserto_pokemon){
    especie_pokemon_t* especie_en_pokedex;
    especie_en_pokedex = (especie_pokemon_t*)arbol_buscar(pokedex->pokemones, especie_leida);
    if(especie_en_pokedex == NULL){ ///INSERTO LA ESPECIE EN EL ARBOL SI NO ESTA
        lista_insertar(especie_leida->pokemones, pokemon_leido);
        arbol_insertar(pokedex->pokemones, especie_leida);
        *inserto_pokemon = true;
    }else{ ///LIBERO LA LISTA DE LA ESPECIE QUE CREE SI YA ESTA EN EL ARBOL Y AGREGO EL POKEMON A LA UBICADA ENEL ARBOL
        lista_insertar(especie_en_pokedex->pokemones, pokemon_leido);
        lista_destruir(especie_leida->pokemones);
        *flag_liberar_especie = true;
        *inserto_pokemon = true;
    }
}

void encolar_pokemon_ultimos_vistos(lista_t* cola, particular_pokemon_t* pokemon_leido, bool* inserto_en_cola){
    if(lista_encolar(cola, pokemon_leido) == EXITO){ ///INSERTO POKEMON EN LA COLA DE VISTOS
        *inserto_en_cola = true;
    }
}

void apilar_pokemon_capturados(lista_t* cola, particular_pokemon_t* pokemon_leido, bool* inserto_en_pila){
    if(pokemon_leido->capturado == true){
        if(lista_apilar(cola, pokemon_leido) == EXITO){ ///INSERTO POKEMON EN LA PILA DE CAPTURADOS
            *inserto_en_pila = true;
        }
    }
}

int pokedex_avistar(pokedex_t* pokedex, char ruta_archivo[MAX_RUTA]){
    if(!pokedex) return ERROR;
        
    FILE* avistamientostxt = fopen(ruta_archivo, "r");
    if(!avistamientostxt) return ERROR;
        
    especie_pokemon_t* especie_leida;
    particular_pokemon_t* pokemon_leido;
    bool problemas_lectura = false;
    bool inserto_pokemon = false;
    bool inserto_en_pila = false;
    bool inserto_en_cola = false;
    bool problemas_insercion = false;
    bool flag_liberar_especie = false;
    int leido = 0;
    int estado = EXITO;
    int numero_especie = 0;
    int nivel_pokemon = 0;
    char nombre_especie[MAX_NOMBRE];
    char descripcion_especie[MAX_DESCRIPCION];
    char nombre_pokemon[MAX_NOMBRE];
    char capturado = '0';

    leer_archivo(&leido, &numero_especie, nombre_especie, descripcion_especie, nombre_pokemon, &nivel_pokemon, &capturado, avistamientostxt);
    if(leido != PARAMETROS_LEIDOS){
        problemas_lectura = true;
    }
    while(leido == PARAMETROS_LEIDOS && !problemas_lectura && !problemas_insercion){
        especie_leida = crear_especie(numero_especie, nombre_especie, descripcion_especie);
        pokemon_leido = crear_pokemon(nombre_pokemon, nivel_pokemon, capturado);
        revisar_estado_estructuras(pokedex);
        insertar_pokemon_en_especie(pokedex, especie_leida, pokemon_leido, &flag_liberar_especie, &inserto_pokemon);
        encolar_pokemon_ultimos_vistos(pokedex->ultimos_vistos, pokemon_leido, &inserto_en_cola);
        apilar_pokemon_capturados(pokedex->ultimos_capturados, pokemon_leido, &inserto_en_pila);
        if((!inserto_en_cola && !inserto_en_pila) || !inserto_pokemon){
            problemas_insercion = true;
        } ///VERIFICO QUE TODO FUNCIONO    
        if(flag_liberar_especie){
            free(especie_leida);
            flag_liberar_especie = false;
        }
        leer_archivo(&leido, &numero_especie, nombre_especie, descripcion_especie, nombre_pokemon, &nivel_pokemon, &capturado, avistamientostxt); ///VUELVO A LEER
        if(leido != PARAMETROS_LEIDOS){
            problemas_lectura = true;
        }
    }
    fclose(avistamientostxt); ///CIERRO EL ARCHIVO
    if(problemas_insercion){ ///VERIFICO SI HUBO ERRORES DE INSERCION
        estado = ERROR;
    }
    return estado;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(){
    int cantidad;
    especie_pokemon_t* especies[10];
    pokedex_t* pokedex = pokedex_crear("Ezequiel");
    if(pokedex_avistar(pokedex, "avistamientos.txt")== EXITO){
        printf("Perfecto\n");
    }else{
        printf("Error\n");
    }
    printf("%s\n", pokedex->nombre_entrenador);

    cantidad = arbol_recorrido_preorden(pokedex->pokemones, (void**)especies, 9);
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
    printf("nada solo para mirar con gdb\n");
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////