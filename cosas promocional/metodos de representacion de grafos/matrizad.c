#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "lista.h"

#define ENTRADA 0
#define COCINA 1
#define SALA 2
#define BANIO 3
#define JARDIN 4
#define CALABOZO 5
#define TERRAZA 6
#define TORTUTA 7

typedef struct{
    int* adyacencias;
    int cantidad;
}grafo_t;

grafo_t* grafo_crear(int cantidad_vertices){
    grafo_t* g = malloc(sizeof(grafo_t));
    if(!g) return NULL;

    g->cantidad = cantidad_vertices;
    g->adyacencias = calloc(cantidad_vertices*cantidad_vertices, sizeof(int));
    if(!(g->adyacencias)){
        free(g);
        return NULL;
    }
    return g;
}

void grafo_agregar_arista(grafo_t* g, int v0, int v1, int peso){
    int p0 = g->cantidad*v1+v0;
    int p1 = g->cantidad*v0+v1;
    g->adyacencias[p0] = peso;
    g->adyacencias[p1] = peso;
}

bool puedo_ir(grafo_t* g, int v0, int v1){
    int p0 = g->cantidad*v1+v0;
    return g->adyacencias[p0] != 0;
}
///////////////////////////////////////////////////////////////////////////////////////////
typedef struct elemento{
    int cosa;
}elemento_t;

elemento_t* crear_elemento(int cosa){
    elemento_t* e = malloc(sizeof(elemento_t));
    e->cosa = cosa;
    return e;
}

void liberar_elementos(elemento_t** elementos, int cantidad){
    for(int i = 0; i< cantidad; i++){
        free(elementos[i]);
    }
    free(elementos);
}
//////////////////////////////////////////////////////////////////////////////////////////
void dfs_rec(grafo_t* g, int v0, bool* visitados){
    visitados[v0] = true;
    printf("%i", v0);

    int fila = g->cantidad*v0;
    for(int i = 0; i < g->cantidad; i++){
        if((g->adyacencias[fila+i] != 0) && !visitados[i])
            dfs_rec(g, i, visitados);
    }
}

void grafo_dfs(grafo_t* g, int v0){
    bool visitados[g->cantidad];
    memset(visitados, 0, sizeof(visitados));
    dfs_rec(g, v0, visitados);
}

void grafo_dfs_pila(grafo_t* g, int v0){
    bool visitados[g->cantidad];
    bool apilados[g->cantidad];
    memset(visitados, 0, sizeof(visitados));
    memset(apilados, 0, sizeof(apilados));
    elemento_t** elementos = malloc(sizeof(elemento_t*)*g->cantidad);
    int fila = 0;
    lista_t* pila = lista_crear();
    elemento_t* aux;

    elementos[v0] = crear_elemento(v0);
    lista_apilar(pila, elementos[v0]);
    apilados[v0] = true;
    while(lista_vacia(pila) != true){
        aux = (elemento_t*)lista_ultimo(pila); //Mi pila al desapilar no devuelve el elemento :D
        lista_desapilar(pila);
        printf("%i", aux->cosa);
        visitados[aux->cosa] = true;
        fila = g->cantidad*(aux->cosa);
        for(int i = 0; i < g->cantidad; i++){
            if((g->adyacencias[fila+i] != 0) && !visitados[i] && !apilados[i]){
                elementos[i] = crear_elemento(i);
                lista_apilar(pila, elementos[i]);
                apilados[i] = true;

            }
        }
    }
    lista_destruir(pila);
    liberar_elementos(elementos, g->cantidad);
}
//////////////////////////////////////////////////////////////////////////////////////////
void grafo_bfs(grafo_t* g, int v0){
    bool visitados[g->cantidad];
    bool encolados[g->cantidad];
    memset(visitados, 0, sizeof(visitados));
    memset(encolados, 0, sizeof(encolados));
    elemento_t** elementos = malloc(sizeof(elemento_t*)*g->cantidad);
    int fila = 0;
    lista_t* cola = lista_crear();
    elemento_t* aux;
    
    elementos[v0] = crear_elemento(v0);
    lista_encolar(cola, elementos[v0]);
    encolados[v0] = true;
    while(lista_vacia(cola) != true){
        aux = (elemento_t*)lista_elemento_en_posicion(cola, 0); //Mi cola al desencolar no devuelve el elemento :D
        lista_desencolar(cola);
        printf("%i", aux->cosa);
        visitados[aux->cosa] = true;
        fila = g->cantidad*(aux->cosa);
        for(int i = 0; i < g->cantidad; i++){
            if((g->adyacencias[fila+i] != 0) && !visitados[i] && !encolados[i]){
                elementos[i] = crear_elemento(i);
                lista_encolar(cola, elementos[i]);
                encolados[i] = true;
            }
        }
    }
    lista_destruir(cola);
    liberar_elementos(elementos, g->cantidad);
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void mostrar_matriz(int* matriz, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%i\t", matriz[i+j*n]);   
        }
        printf("\n");
    }
}

void grafo_liberar(grafo_t* g){
    free(g->adyacencias);
    free(g);
}

int main(){
    grafo_t* g = grafo_crear(8);

    grafo_agregar_arista(g, ENTRADA, SALA, 1);
    grafo_agregar_arista(g, SALA, COCINA, 1);
    grafo_agregar_arista(g, SALA, BANIO, 1);
    grafo_agregar_arista(g, SALA, JARDIN, 1);
    grafo_agregar_arista(g, JARDIN, CALABOZO, 1);
    grafo_agregar_arista(g, JARDIN, TERRAZA, 1);
    grafo_agregar_arista(g, CALABOZO, TORTUTA, 1);
    grafo_agregar_arista(g, TERRAZA, BANIO, 1);
    /*
    printf("¿Puedo ir del calabozo a la entrada? %s\n", puedo_ir(g, CALABOZO, ENTRADA)?"SI":"NO");
    printf("¿Puedo ir de la sala a la entrada? %s\n", puedo_ir(g, SALA, ENTRADA)?"SI":"NO");
    printf("¿Puedo ir del calabozo a tortuta? %s\n", puedo_ir(g, CALABOZO, TORTUTA)?"SI":"NO");
    printf("¿Puedo ir de la sala al jardin? %s\n", puedo_ir(g, SALA, JARDIN)?"SI":"NO");
    printf("¿Puedo ir de la terraza al banio? %s\n", puedo_ir(g, TERRAZA, BANIO)?"SI":"NO");
    printf("¿Puedo ir de la sala a la terraza? %s\n", puedo_ir(g, SALA, TERRAZA)?"SI":"NO");
    */
    mostrar_matriz(g->adyacencias, g->cantidad);
    grafo_dfs(g, 0);
    printf("-->DFS DE STACK");
    printf("\n");
    grafo_dfs_pila(g, 0);
    printf("-->DFS CON PILA");
    printf("\n");
    grafo_bfs(g, 0);
    printf("-->BFS");
    printf("\n");
    
    grafo_liberar(g);
    return 0;
}