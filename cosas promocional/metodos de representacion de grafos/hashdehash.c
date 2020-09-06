#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "hash.h"

#define ENTRADA 0
#define COCINA 1
#define SALA 2
#define BANIO 3
#define JARDIN 4
#define CALABOZO 5
#define TERRAZA 6
#define TORTUTA 7

typedef struct{
    hash_t* v0;
}grafo_t;

grafo_t* grafo_crear(int cantidad_vertices){
    grafo_t* g = malloc(sizeof(grafo_t));
    if(!g) return NULL;

    g->v0 = hash_crear(NULL, 3);
    return g;
}
 
int* copiar_peso(int p){
    int* peso = malloc(sizeof(int));
    if(!peso)
        return NULL;

    *peso = p;
    return peso;
}

void grafo_agregar_arista(grafo_t* g, char* v0, char* v1, int peso){
    grafo_agregar_arista(g, v0, v1, peso);
    grafo_agregar_arista(g, v1, v0, peso);
}

void grafo_agregar_arista_aux(grafo_t* g, char* v0, char* v1, int peso){
    hash_t* hv1 = hash_obtener(g->v0, v0);
    if(!hv1){
        hv1 = hash_crear(NULL, 3);
        hash_insertar(g->v0, v0, hv1);
    }
    hash_insertar(hv1, v1, copiar_peso(peso));
}

int main(){
    grafo_t* g = grafo_crear();

    grafo_agregar_arista(g, "ENTRADA", "SALA", 1);
    grafo_agregar_arista(g, "SALA", "COCINA", 1);
    grafo_agregar_arista(g, "SALA", "BANIO", 1);
    grafo_agregar_arista(g, "SALA", "JARDIN", 1);
    grafo_agregar_arista(g, "JARDIN", "CALABOZO", 1);
    grafo_agregar_arista(g, "JARDIN", "TERRAZA", 1);
    grafo_agregar_arista(g, "CALABOZO", "TORTUTA", 1);
    grafo_agregar_arista(g, "TERRAZA", "BANIO", 1);
    return 0;
}