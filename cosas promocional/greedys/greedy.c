#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "heap.h"

#define ENTRADA 0
#define COCINA 1
#define SALA 2
#define BANIO 3
#define JARDIN 4
#define CALABOZO 5
#define TERRAZA 6
#define TORTUTA 7
#define FIUBA 8
#define INFINITO 99999

typedef struct{
    int* adyacencias;
    int cantidad;
    bool dirigido;
}grafo_t;

grafo_t* grafo_crear(int cantidad_vertices, bool es_dirigido){
    grafo_t* g = malloc(sizeof(grafo_t));
    if(!g) return NULL;

    g->cantidad = cantidad_vertices;
    g->adyacencias = calloc(cantidad_vertices*cantidad_vertices, sizeof(int));
    if(!(g->adyacencias)){
        free(g);
        return NULL;
    }
    for(int i = 0; i < g->cantidad; i++){
        for(int j = 0; j < g->cantidad; j++){
            g->adyacencias[j*g->cantidad + i] = INFINITO;
            if(i == j)
                g->adyacencias[j*g->cantidad + i] = 0;
        }
    }
    g->dirigido = es_dirigido;
    return g;
}

void grafo_agregar_arista(grafo_t* g, int v0, int v1, int peso){
    int p0 = g->cantidad*v0+v1;
    int p1 = g->cantidad*v1+v0;
    g->adyacencias[p0] = peso;
    if(!g->dirigido){
        g->adyacencias[p1] = peso;
    }
}

bool puedo_ir(grafo_t* g, int v0, int v1){
    int p0 = g->cantidad*v0+v1;
    return g->adyacencias[p0] != 0;
}

void mostrar_matriz(int* matriz, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%i\t", matriz[i+j*n]);   
        }
        printf("\n");
    }
}
///////////////////////////////////////FLOYD///////////////////////////////////////////////////
void floyd(grafo_t* g){
    int matriz[g->cantidad * g->cantidad];
    memcpy(matriz, g->adyacencias, sizeof(matriz));
    mostrar_matriz(matriz, g->cantidad);
    
    for(int v0 = 0; v0<g->cantidad; v0++){
        for(int v1 = 0; v1<g->cantidad; v1++){
            for(int v2 = 0; v2<g->cantidad; v2++){
                int dv1v2 = matriz[v1*g->cantidad+v2];
                int dv1v0v2 = matriz[v1*g->cantidad+v0] + matriz[v0*g->cantidad+v2];
                if(dv1v0v2 < dv1v2)
                    matriz[v1*g->cantidad+v2] = dv1v0v2;
            }
        }
    }
    printf("\n");
    mostrar_matriz(matriz, g->cantidad);
}
///////////////////////////////////////DIJKSTRA/////////////////////////////////////////////////////
typedef struct{
   int distancia;
   int anterior; 
}caminodjkstra;

void mostrar_tabla(caminodjkstra* tabla, int n){
    for(int i = 0; i < n; i++){
        printf("V: %i\tD: %i\tA: %i\n", i, tabla[i].distancia, tabla[i].anterior);
    }
}

int buscar_menor_no_visitado(caminodjkstra* tabla, bool* visitados, grafo_t* g){
    int v0 = -1;
    int distancia = INFINITO;
    for(int i = 0; i < g->cantidad; i++){
        if(!visitados[i] && tabla[i].distancia < distancia){
            distancia = tabla[i].distancia;
            v0 = i;
        }
    }
    return v0;
}

void dijkstra_rec(grafo_t* g, bool* visitados, caminodjkstra* tabla){
    //1
    int v0 = buscar_menor_no_visitado(tabla, visitados, g);
    if(v0 < 0) return;
    //2
    visitados[v0] = true;
    //3
    int* adyacentes = g->adyacencias + g->cantidad*v0;
    for(int v1 = 0; v1<g->cantidad; v1++){
        if(v0 != v1 && !visitados[v1]){
            int dv0v1 = adyacentes[v1];
            int dv0 = tabla[v0].distancia;
            if(dv0+dv0v1 < tabla[v1].distancia){
                tabla[v1].distancia = dv0+dv0v1;
                tabla[v1].anterior = v0;
            }
        }
    }
    dijkstra_rec(g, visitados, tabla);
}

void dijkstra(grafo_t* g, int v0){
    bool visitados[g->cantidad];
    memset(visitados, 0, sizeof(visitados));

    caminodjkstra* tabla = malloc(sizeof(caminodjkstra)*g->cantidad);
    if(!tabla) return;

    for(int i = 0; i < g->cantidad; i++){
        tabla[i].distancia = INFINITO;
        tabla[i].anterior = -1;
    }
    tabla[v0].distancia = 0;

    //1. buscar el menor no visitado
    //2. buscar adyacentes y actualizar tabla
    //3. marcar como visitado
    //Repito
    dijkstra_rec(g, visitados, tabla);

    mostrar_tabla(tabla, g->cantidad);
}
/////////////////////////////////////PRIM///////////////////////////////////////////////////////////////
typedef struct{
    int v0, v1, distancia;
}arista_t;

arista_t* crear_arista(int v0, int v1, int peso){
    arista_t* a = malloc(sizeof(arista_t));
    if(!a) return NULL;

    a->v0 = v0;
    a->v1 = v1;
    a->distancia = peso;
    return a;
}

int comparar_aristas(const void *a, const void *b){
    arista_t* A0 = (arista_t*)a;
    arista_t* A1 = (arista_t*)b;
    return (A1->distancia - A0->distancia);
}

void prim(grafo_t* g, int v0){

    bool visitados[g->cantidad];
    memset(visitados, 0, sizeof(visitados));

    heap_t* h = heap_crear(comparar_aristas);
    do{
        visitados[v0] = true;
        int* adyacentes = g->adyacencias + g->cantidad*v0;
        for(int i = 0; i < g->cantidad; i++)
            if(adyacentes[i] != INFINITO && adyacentes[i] != 0)
                heap_encolar(h, crear_arista(v0, i, adyacentes[i]));

        arista_t* a = NULL;
        do{
            a = heap_desencolar(h);
        }while(a != NULL && visitados[a->v0] && visitados[a->v1]);

        if(!a) return;

        printf("%i -- %i\n", a->v1, a->v0);
        if(!visitados[a->v1])
            v0 = a->v1;
        else v0 = a->v0;
    }while(heap_cantidad(h) > 0);

    printf("\n");

    //1. Sacas a todas las aristas del grafo.
    //2. Agregas las aristas de v0 al heap.
    //3. Sacar arista del heap hasta encontrar una que no cree ciclos.
    //4. Mostrar la arista al grafo.
    //Repito

}
////////////////////////////////////////////////////////////////////////////////////////////////////
int main(){
    grafo_t* g = grafo_crear(9, false);

    grafo_agregar_arista(g, ENTRADA, SALA, 1);
    grafo_agregar_arista(g, SALA, COCINA, 2);
    grafo_agregar_arista(g, SALA, BANIO, 4);
    grafo_agregar_arista(g, SALA, JARDIN, 4);
    grafo_agregar_arista(g, JARDIN, CALABOZO, 7);
    grafo_agregar_arista(g, JARDIN, TERRAZA, 2);
    grafo_agregar_arista(g, CALABOZO, TORTUTA, 3);
    grafo_agregar_arista(g, TERRAZA, BANIO, 3);
    grafo_agregar_arista(g, ENTRADA, FIUBA, 8);
    grafo_agregar_arista(g, FIUBA, TORTUTA, 2);
    
    printf("Floyd");
    printf("\n");
    floyd(g);
    printf("Dijkstra");
    printf("\n");
    dijkstra(g, ENTRADA);
    printf("Prim");
    printf("\n");
    prim(g, ENTRADA);
    printf("\n");
    return 0;
}