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
#define FORMATO_LECTURA_EVOLUCIONES "%i;%[^;];%i;%[^;];%[^\n]\n"
#define ORIGEN 0
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int PARAMETROS_LEIDOS_AVISTAIENTOS = 6;
const int PARAMETROS_LEIDOS_EVOLUCIONES = 5;
const int COINCIDENCIA = 0;
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
	size_t cantidad = lista_elementos(elemento->pokemones);
    particular_pokemon_t* aux = NULL;
    size_t i;
    bool valido = false;

    if(cantidad > 0){
        i = cantidad -1;
        valido = true;
    }

    if(valido){
        for(; i > 0; i--){
            aux = (particular_pokemon_t*)lista_elemento_en_posicion(elemento->pokemones, i);
            lista_borrar_de_posicion(elemento->pokemones, i);
            free(aux);
        }
        if(i == 0){
            aux = (particular_pokemon_t*)lista_elemento_en_posicion(elemento->pokemones, 0);
            lista_borrar_de_posicion(elemento->pokemones, 0);
            free(aux);
        }
    }
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

    if(strlen(entrenador) > 0){
        strcpy(pokedex->nombre_entrenador, entrenador);
    }else{
        strcpy(pokedex->nombre_entrenador, "unknown");
    }
    pokedex->pokemones = arbol_crear(comparar_cosas, destructor_de_cosas);
    pokedex->ultimos_capturados = NULL;
    pokedex->ultimos_vistos = NULL;
    return pokedex;
}
/////////////////////////////////////////////////////////AUXILIARES AVISTAR////////////////////////////////////////////////////////////////////
void leer_avistamientos(int* leido, int* numero_especie, char* nombre_especie, char* descripcion_especie, char* nombre_pokemon, int* nivel_pokemon, char* capturado, FILE* avistamientostxt){
    (*leido) = fscanf(avistamientostxt, FORMATO_LECTURA_AVISTAMIENTOS, numero_especie, nombre_especie, descripcion_especie, nombre_pokemon, nivel_pokemon, capturado);
}

void revisar_estado_estructuras(pokedex_t* pokedex){
    if(pokedex->ultimos_capturados == NULL){
        pokedex->ultimos_capturados = lista_crear(); ///ESTO UNA PILA
    }
    if(pokedex->ultimos_vistos == NULL){
        pokedex->ultimos_vistos = lista_crear(); ///ESTO ES UNA COLA
    }
}

void insertar_pokemon_en_especie(pokedex_t* pokedex, especie_pokemon_t* especie_leida, particular_pokemon_t* pokemon_leido, bool* inserto_pokemon){
    especie_pokemon_t* especie_en_pokedex;
    especie_en_pokedex = (especie_pokemon_t*)arbol_buscar(pokedex->pokemones, especie_leida);
    if(especie_en_pokedex == NULL){ ///INSERTO LA ESPECIE EN EL ARBOL SI NO ESTA
        lista_insertar(especie_leida->pokemones, pokemon_leido);
        arbol_insertar(pokedex->pokemones, especie_leida);
        *inserto_pokemon = true;
    }else{ ///LIBERO LA LISTA DE LA ESPECIE QUE CREE SI YA ESTA EN EL ARBOL Y AGREGO EL POKEMON A LA UBICADA EN EL ARBOL
        lista_insertar(especie_en_pokedex->pokemones, pokemon_leido);
        lista_destruir(especie_leida->pokemones);
        free(especie_leida);
        *inserto_pokemon = true;
    }
}

void encolar_pokemon_ultimos_vistos(lista_t* cola, particular_pokemon_t* pokemon_leido, bool* inserto_en_cola){
    if(lista_encolar(cola, pokemon_leido) == EXITO){ ///INSERTO POKEMON EN LA COLA DE VISTOS
        *inserto_en_cola = true;
    }
}

void apilar_pokemon_capturados(lista_t* pila, particular_pokemon_t* pokemon_leido, bool* inserto_en_pila){
    if(pokemon_leido->capturado == true){
        if(lista_apilar(pila, pokemon_leido) == EXITO){ ///INSERTO POKEMON EN LA PILA DE CAPTURADOS
            *inserto_en_pila = true;
        }
    }
}
/////////////////////////////////////////////////////////POKEDEX AVISTAR////////////////////////////////////////////////////////////////////
int pokedex_avistar(pokedex_t* pokedex, char ruta_archivo[MAX_RUTA]){
    if(!pokedex) return ERROR;   
    FILE* avistamientostxt = fopen(ruta_archivo, "r");
    if(!avistamientostxt) return ERROR;
        
    especie_pokemon_t* especie_leida;
    particular_pokemon_t* pokemon_leido;
    bool problemas_lectura = false, inserto_pokemon = false, inserto_en_pila = false, inserto_en_cola = false, problemas_insercion = false;
    int leido = 0, estado = EXITO, numero_especie = 0, nivel_pokemon = 0;
    char nombre_especie[MAX_NOMBRE], descripcion_especie[MAX_DESCRIPCION], nombre_pokemon[MAX_NOMBRE], capturado = '0';

    leer_avistamientos(&leido, &numero_especie, nombre_especie, descripcion_especie, nombre_pokemon, &nivel_pokemon, &capturado, avistamientostxt);
    if(leido != PARAMETROS_LEIDOS_AVISTAIENTOS){
        problemas_lectura = true;
    }
    while(leido == PARAMETROS_LEIDOS_AVISTAIENTOS && !problemas_lectura && !problemas_insercion){
        especie_leida = crear_especie(numero_especie, nombre_especie, descripcion_especie);
        pokemon_leido = crear_pokemon(nombre_pokemon, nivel_pokemon, capturado);
        revisar_estado_estructuras(pokedex);
        insertar_pokemon_en_especie(pokedex, especie_leida, pokemon_leido, &inserto_pokemon);
        encolar_pokemon_ultimos_vistos(pokedex->ultimos_vistos, pokemon_leido, &inserto_en_cola);
        apilar_pokemon_capturados(pokedex->ultimos_capturados, pokemon_leido, &inserto_en_pila);
        if((!inserto_en_cola && !inserto_en_pila) || !inserto_pokemon){
            problemas_insercion = true;
        } ///VERIFICO QUE TODO FUNCIONO    
        leer_avistamientos(&leido, &numero_especie, nombre_especie, descripcion_especie, nombre_pokemon, &nivel_pokemon, &capturado, avistamientostxt); ///VUELVO A LEER
        if(leido != PARAMETROS_LEIDOS_AVISTAIENTOS){
            problemas_lectura = true;
        }
    }
    fclose(avistamientostxt); ///CIERRO EL ARCHIVO
    if(problemas_insercion){ ///VERIFICO SI HUBO ERRORES DE INSERCION
        estado = ERROR;
    }
    return estado;
}
/////////////////////////////////////////////////////////AUXILIARES EVOLUCIONAR////////////////////////////////////////////////////////////////////
void leer_evoluciones(int* leido, int* numero_especie_original, char* nombre_especie_nueva, char* descripcion_especie_nueva, char* nombre_pokemon, int* numero_especie_nueva, FILE* evolucionestxt){
    (*leido) = fscanf(evolucionestxt, FORMATO_LECTURA_EVOLUCIONES, numero_especie_original, nombre_pokemon, numero_especie_nueva, nombre_especie_nueva, descripcion_especie_nueva);
}

particular_pokemon_t* buscar_pokemon_a_evolucionar(especie_pokemon_t* especie_en_pokedex, bool* pokemon_encontrado, size_t* posicion_pokemon, size_t* i, particular_pokemon_t pokemon_leido){
    particular_pokemon_t* pokemon_aux;
    size_t cantidad;
    cantidad = lista_elementos(especie_en_pokedex->pokemones);
    while((*i) < cantidad && !(*pokemon_encontrado)){
        pokemon_aux = (particular_pokemon_t*)lista_elemento_en_posicion(especie_en_pokedex->pokemones, *i);
        if(strcmp(pokemon_aux->nombre, pokemon_leido.nombre) == COINCIDENCIA){
            if(pokemon_aux->capturado){
                *pokemon_encontrado = true;
                *posicion_pokemon = (*i);
            }
        }
        (*i)++;
    }
    return pokemon_aux;
}

void mover_pokemon_de_especie_a_especie(pokedex_t* pokedex, especie_pokemon_t* especie_en_pokedex, particular_pokemon_t* pokemon_nuevo, especie_pokemon_t* especie_nueva, especie_pokemon_t* especie_a_evolucionar_en_pokedex, bool* inserto_pokemon, bool* problemas_asignacion, size_t posicion_pokemon, particular_pokemon_t* pokemon_aux){
    if(!especie_a_evolucionar_en_pokedex){ ///INSERTO LA ESPECIE EN EL ARBOL SI NO ESTA
        lista_insertar(especie_nueva->pokemones, pokemon_nuevo);
        arbol_insertar(pokedex->pokemones, especie_nueva);
        *inserto_pokemon = true;
    }else{ ///LIBERO LA ESPECIE QUE CREE Y AGREGO EL POKEMON A LA UBICADA EN EL ARBOL
        lista_insertar(especie_a_evolucionar_en_pokedex->pokemones, pokemon_nuevo);
        lista_destruir(especie_nueva->pokemones);
        free(especie_nueva);
        *inserto_pokemon = true;
    }
    if(!(*inserto_pokemon)){
        *problemas_asignacion = true;
    }else{
        lista_borrar_de_posicion(especie_en_pokedex->pokemones, posicion_pokemon);
        free(pokemon_aux);
    } 
}
/////////////////////////////////////////////////////////POKEDEX EVOLUCIONAR////////////////////////////////////////////////////////////////////
int pokedex_evolucionar(pokedex_t* pokedex, char ruta_archivo[MAX_RUTA]){
    if(!pokedex) return ERROR;
    FILE* evolucionestxt = fopen(ruta_archivo, "r");
    if(!evolucionestxt) return ERROR;
    
    especie_pokemon_t especie_base;
    particular_pokemon_t pokemon_leido;
    especie_pokemon_t* especie_en_pokedex;
    especie_pokemon_t* especie_a_evolucionar_en_pokedex;
    especie_pokemon_t* especie_nueva;
    particular_pokemon_t* pokemon_nuevo;
    particular_pokemon_t* pokemon_aux;
    int numero_especie_base = 0, numero_especie_nueva = 0, estado = EXITO, leido = 0;
    size_t posicion_pokemon = 0, i = 0;
    char nombre_especie_nueva[MAX_NOMBRE], descripcion_especie_nueva[MAX_DESCRIPCION], nombre_pokemon[MAX_NOMBRE];
    bool pokemon_encontrado = false, inserto_pokemon = false, problemas_asignacion = false, problemas_lectura = false;

    leer_evoluciones(&leido, &numero_especie_base, nombre_especie_nueva, descripcion_especie_nueva, nombre_pokemon, &numero_especie_nueva, evolucionestxt);
    while(leido == PARAMETROS_LEIDOS_EVOLUCIONES && !problemas_lectura){
        especie_base.numero = numero_especie_base;
        strcpy(pokemon_leido.nombre, nombre_pokemon);
        especie_en_pokedex = (especie_pokemon_t*)arbol_buscar(pokedex->pokemones, &especie_base);
        if(especie_en_pokedex){
            pokemon_aux = buscar_pokemon_a_evolucionar(especie_en_pokedex, &pokemon_encontrado, &posicion_pokemon, &i, pokemon_leido);
        }
        if(pokemon_encontrado){
            pokemon_nuevo = crear_pokemon(pokemon_aux->nombre, pokemon_aux->nivel, 'S');
            especie_nueva = crear_especie(numero_especie_nueva, nombre_especie_nueva, descripcion_especie_nueva);
            especie_a_evolucionar_en_pokedex = (especie_pokemon_t*)arbol_buscar(pokedex->pokemones, especie_nueva);
            mover_pokemon_de_especie_a_especie(pokedex, especie_en_pokedex, pokemon_nuevo, especie_nueva, especie_a_evolucionar_en_pokedex, &inserto_pokemon, &problemas_asignacion, posicion_pokemon, pokemon_aux);
        }
        inserto_pokemon = false;
        pokemon_encontrado = false;
        i = 0;
        leer_evoluciones(&leido, &numero_especie_base, nombre_especie_nueva, descripcion_especie_nueva, nombre_pokemon, &numero_especie_nueva, evolucionestxt); ///VUELVO A LEER NUEVAMENTE
        if(leido != PARAMETROS_LEIDOS_EVOLUCIONES){
            problemas_lectura = true;
        }
    }
    fclose(evolucionestxt); //CIERRO EL ARCHIVO
    if(problemas_asignacion) estado = ERROR; //ME FIJO SI HUBO ERRORES

    return estado;
}
/////////////////////////////////////////////////////////POKEDEX ULTIMOS CAPTURADOS////////////////////////////////////////////////////////////////////
void pokedex_ultimos_capturados(pokedex_t* pokedex){
    if(!pokedex) return;  
    size_t cantidad = lista_elementos(pokedex->ultimos_capturados);
    particular_pokemon_t* cosa = NULL;
    for(size_t i = (cantidad-1); i > 0; i--){
        cosa = (particular_pokemon_t*)lista_elemento_en_posicion(pokedex->ultimos_capturados, i);
        printf("%s-%i\n", cosa->nombre, cosa->nivel);
    }
    cosa = (particular_pokemon_t*)lista_elemento_en_posicion(pokedex->ultimos_capturados, ORIGEN);
    printf("%s-%i\n", cosa->nombre, cosa->nivel);
    lista_destruir(pokedex->ultimos_capturados);
}
/////////////////////////////////////////////////////////POKEDEX ULTIMOS VISTOS////////////////////////////////////////////////////////////////////
void pokedex_ultimos_vistos(pokedex_t* pokedex){
    if(!pokedex) return;  
    size_t cantidad = lista_elementos(pokedex->ultimos_vistos);
    particular_pokemon_t* cosa = NULL;
    for(size_t i = 0; i < cantidad; i++){
        cosa = (particular_pokemon_t*)lista_elemento_en_posicion(pokedex->ultimos_vistos, i);
        printf("%s-%i\n", cosa->nombre, cosa->nivel);
    }
    lista_destruir(pokedex->ultimos_vistos);
}
/////////////////////////////////////////////////////////AUXILIARES INFORMACION///////////////////////////////////////////////////////////////////
void buscar_pokemon(bool* pokemon_encontrado, particular_pokemon_t* pokemon_en_pokedex, particular_pokemon_t pokemon_leido, especie_pokemon_t* especie_en_pokedex){
    size_t i = 0, cantidad = lista_elementos(especie_en_pokedex->pokemones);
    while(i < cantidad && !(*pokemon_encontrado)){
        pokemon_en_pokedex = (particular_pokemon_t*)lista_elemento_en_posicion(especie_en_pokedex->pokemones, i);
        if(strcmp(pokemon_en_pokedex->nombre, pokemon_leido.nombre) == COINCIDENCIA){
            printf("%s-%s-%i\n", especie_en_pokedex->nombre, pokemon_en_pokedex->nombre, pokemon_en_pokedex->nivel);
            *pokemon_encontrado = true;
        }
        i++;
    } 
}

void imprimir_pokemones_de_una_especie(bool* pokemon_encontrado, especie_pokemon_t* especie_en_pokedex){
    size_t i = 0, cantidad = lista_elementos(especie_en_pokedex->pokemones);
    particular_pokemon_t* cosa = NULL;
    printf("%s:\n", especie_en_pokedex->nombre);
    for(i = 0; i < cantidad; i++){
        cosa = (particular_pokemon_t*)lista_elemento_en_posicion(especie_en_pokedex->pokemones, i);
        printf("%s-%i\n", cosa->nombre, cosa->nivel);
    }
    *pokemon_encontrado = true;
}
/////////////////////////////////////////////////////////POKEDEX INFORMACION////////////////////////////////////////////////////////////////////
void pokedex_informacion(pokedex_t* pokedex, int numero_pokemon, char nombre_pokemon[MAX_NOMBRE]){
    if(!pokedex) return;  
    especie_pokemon_t especie_leida;
    particular_pokemon_t pokemon_leido;
    especie_pokemon_t* especie_en_pokedex = NULL;
    particular_pokemon_t* pokemon_en_pokedex = NULL;
    bool pokemon_encontrado = false, nombre_especifico = false;

    if(strlen(nombre_pokemon) > 0){
        nombre_especifico = true;
    }
    strcpy(pokemon_leido.nombre, nombre_pokemon);
    especie_leida.numero = numero_pokemon;
    especie_en_pokedex = (especie_pokemon_t*)arbol_buscar(pokedex->pokemones, &especie_leida);
    if(especie_en_pokedex){
        if(nombre_especifico){
            printf("%s-%i-%s\n", especie_en_pokedex->nombre, especie_en_pokedex->numero, especie_en_pokedex->descripcion);
            buscar_pokemon(&pokemon_encontrado, pokemon_en_pokedex, pokemon_leido, especie_en_pokedex);         
        }else{
            printf("%s-%i-%s\n", especie_en_pokedex->nombre, especie_en_pokedex->numero, especie_en_pokedex->descripcion);
            printf("Pokemones observados de esta especie:\n");
            imprimir_pokemones_de_una_especie(&pokemon_encontrado, especie_en_pokedex);
        }
    }
    if(!especie_en_pokedex || !pokemon_encontrado){
        printf("Especie o Pokemon desconocido\n");
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool escribir_elemento(void* elemento, void* extra){
	FILE* pokedextxt = (FILE*)extra;
	especie_pokemon_t* cosa = (especie_pokemon_t*)elemento;
    particular_pokemon_t* pokemon = NULL;
    char captura = 'a';
    size_t cantidad = 0;

	if(elemento){
        fprintf(pokedextxt, "E;%s;%i;%s\n", cosa->nombre, cosa->numero, cosa->descripcion);
        cantidad = lista_elementos(cosa->pokemones);
        for(size_t i = 0; i < cantidad; i++){
            pokemon = (particular_pokemon_t*)lista_elemento_en_posicion(cosa->pokemones, i);
            if(pokemon->capturado){
                captura = 'S';
            }else{
                captura = 'N';
            }
            fprintf(pokedextxt, "P;%s;%i;%c\n", pokemon->nombre, pokemon->nivel, captura);
        }
    }
	return false;
}

int pokedex_apagar(pokedex_t* pokedex){
    if(!pokedex) return ERROR;
    FILE* pokedextxt = fopen("pokedex.txt", "w");
    if(!pokedextxt) return ERROR;

    fprintf(pokedextxt, "%s\n", pokedex->nombre_entrenador);
    abb_con_cada_elemento(pokedex->pokemones, ABB_RECORRER_PREORDEN, escribir_elemento, pokedextxt);

    fclose(pokedextxt);
    return EXITO;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
pokedex_t* pokedex_prender(){
    pokedex_t* aux = NULL;
    especie_pokemon_t* especie_leida = NULL;
    especie_pokemon_t* especie_en_pokedex = NULL;
    particular_pokemon_t* pokemon_leido = NULL;
    char especie[MAX_NOMBRE];
    char pokemon[MAX_NOMBRE];
    char descripcion_especie[MAX_NOMBRE];
    char nombre[MAX_NOMBRE];
    char letra_indice = 'a';
    char capturado = 'a';
    int numero_especie = 0;
    int nivel_pokemon = 0;
    int leido = 0;

    FILE* pokedextxt = fopen("pokedex.txt", "r");
    if(!pokedextxt) return NULL;

    fscanf(pokedextxt, "%[^\n]\n", nombre);
    aux = pokedex_crear(nombre);
    leido = fscanf(pokedextxt, "%c;", &letra_indice);
    while(leido == 1){
        if(letra_indice == 'E'){
            fscanf(pokedextxt, "%[^;];%i;%[^\n]\n", especie, &numero_especie, descripcion_especie);
            especie_leida = crear_especie(numero_especie, especie, descripcion_especie);
            arbol_insertar(aux->pokemones, especie_leida);
        }else{
            fscanf(pokedextxt, "%[^;];%i;%c\n", pokemon, &nivel_pokemon, &capturado);
            pokemon_leido = crear_pokemon(pokemon, nivel_pokemon, capturado);
            especie_en_pokedex = (especie_pokemon_t*)arbol_buscar(aux->pokemones, especie_leida);
            lista_insertar(especie_en_pokedex->pokemones, pokemon_leido);
        }
        leido = fscanf(pokedextxt, "%c;", &letra_indice);
    }
    fclose(pokedextxt);
    return aux;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pokedex_destruir(pokedex_t* pokedex){
    if(!pokedex) return;
    if(pokedex->ultimos_capturados)
        lista_destruir(pokedex->ultimos_capturados);

    if(pokedex->ultimos_vistos)
        lista_destruir(pokedex->ultimos_vistos);
    
    arbol_destruir(pokedex->pokemones);
    free(pokedex);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(){
    /*pokedex_t* pokedex = NULL;
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
    pokedex_destruir(pokedex);*/
    /*int cantidad;
    especie_pokemon_t* especies[10];
    especie_pokemon_t* especies2[10];*/
    pokedex_t* pokedex = pokedex_crear("Ezequiel");
    if(pokedex_avistar(pokedex, "avistamientos.txt")== EXITO){
        printf("Perfecto\n");
    }else{
        printf("Error\n");
    }
    printf("%s\n", pokedex->nombre_entrenador);
    /*
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
    }*/
    pokedex_ultimos_capturados(pokedex);
    printf("\n\n");/*
    pokedex_ultimos_vistos(pokedex);
    printf("\n\n");
    pokedex_informacion(pokedex, 25, "");
    pokedex_apagar(pokedex);*/
    /*pokedex_t* pokedex = pokedex_prender();
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
    }*/
    pokedex_destruir(pokedex);
    return 0;
}