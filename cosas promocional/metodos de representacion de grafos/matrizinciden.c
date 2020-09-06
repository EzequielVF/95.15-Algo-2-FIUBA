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
#define INFINITO 99999

typedef struct{
    int* adyacencias;
    int cantidad;
    int cant_aristas;
}grafo_t;

grafo_t* grafo_crear(int cantidad_vertices){
    grafo_t* g = malloc(sizeof(grafo_t));
    if(!g) return NULL;

    g->cantidad = cantidad_vertices;
    g->adyacencias = NULL;
    g->cant_aristas = 0;
    return g;
}

void grafo_agregar_arista(grafo_t* g, int v0, int v1, int peso){
    g->cant_aristas++;
    int* extra = NULL;
    extra = realloc(g->adyacencias, sizeof(int)*((g->cant_aristas)*(g->cantidad)));
    if(!extra) return;

    g->adyacencias = extra;
    if(!(g->adyacencias)){
        return;
    }
    int fila = (g->cant_aristas - 1) * g->cantidad;
    for(int i = 0; i< g->cantidad; i++){
        g->adyacencias[fila + i] = 0;
    }
    int p0 = (v0 + (g->cant_aristas-1)*(g->cantidad));
    int p1 = (v1 + (g->cant_aristas-1)*(g->cantidad));
    g->adyacencias[p0] = peso;
    g->adyacencias[p1] = peso;
}

void mostrar_matriz(int* matriz, int columnas, int aristas){
    for(int i = 0; i < aristas; i++){
        for(int j = 0; j < columnas; j++){
            printf("%i\t", matriz[i*aristas + j]);   
        }
        printf("\n");
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////
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
void grafo_bfs(grafo_t* g, int v0){
    bool visitados[g->cantidad];
    bool encolados[g->cantidad];
    memset(visitados, 0, sizeof(visitados));
    memset(encolados, 0, sizeof(encolados));
    elemento_t** elementos = malloc(sizeof(elemento_t*)*g->cantidad);
    int columna = 0;
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
        columna = aux->cosa;
        for(int i = 0; i < g->cant_aristas; i++){
            if(g->adyacencias[columna + g->cantidad*i] != 0){
                for(int j = 0; j < g->cantidad; j++){
                    if(j != columna && (g->adyacencias[j + g->cantidad*i] != 0)  && !visitados[j] && !encolados[j]){
                        elementos[j] = crear_elemento(j);
                        lista_encolar(cola, elementos[j]);
                        encolados[j] = true;
                    }
                }
            }
        }
    }
    lista_destruir(cola);
    liberar_elementos(elementos, g->cantidad);
}
//////////////////////////////////////////////////////////////////////////////////////////
void grafo_dfs(grafo_t* g, int v0){
    bool visitados[g->cantidad];
    bool apilados[g->cantidad];
    memset(visitados, 0, sizeof(visitados));
    memset(apilados, 0, sizeof(apilados));
    elemento_t** elementos = malloc(sizeof(elemento_t*)*g->cantidad);
    int columna = 0;
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
        columna = aux->cosa;
        for(int i = 0; i < g->cant_aristas; i++){
            if(g->adyacencias[columna + g->cantidad*i] != 0){
                for(int j = 0; j < g->cantidad; j++){
                    if(j != columna && (g->adyacencias[j + g->cantidad*i] != 0)  && !visitados[j] && !apilados[j]){
                        elementos[j] = crear_elemento(j);
                        lista_apilar(pila, elementos[j]);
                        apilados[j] = true;
                    }
                }
            }
        }
    }
    lista_destruir(pila);
    liberar_elementos(elementos, g->cantidad);
}
//////////////////////////////////////////////////////////////////////////////////////////
void destruir_grafo(grafo_t* g){
    free(g->adyacencias);
    free(g);
}
//////////////////////////////////////////////////////////////////////////////////////////
typedef struct matriz{
    int* adyacencias;
    int cantidad;
}matriz_t;

void agregar_arista_matriz(matriz_t* g, int v0, int v1, int peso){
    int p0 = g->cantidad*v1+v0;
    int p1 = g->cantidad*v0+v1;
    g->adyacencias[p0] = peso;
    g->adyacencias[p1] = peso;
}

void rellenar_matriz_con_elementos_en_incidencia(grafo_t* g, matriz_t* m){
    bool encontro_v0 = false;
    bool encontro_los_dos = false;
    int v0 = -1;
    int v1 = -1;
    int peso;

    for(int i = 0; i < g->cant_aristas; i++){
        for(int j = 0; j < g->cantidad; j++){
            if(encontro_v0 && g->adyacencias[i*g->cant_aristas + j] != 0){
                v1 = j;
                encontro_los_dos = true;
            }
            if((g->adyacencias[i*g->cant_aristas + j] != 0) && !encontro_v0){
                encontro_v0 = true;
                peso = g->adyacencias[i*g->cant_aristas + j];
                v0 = j;
            }
            if(encontro_los_dos){
                encontro_v0 = false;
                encontro_los_dos = false;
                agregar_arista_matriz(m, v0, v1, peso);
                break;
            }
        }
    }
}

matriz_t* transformar_matrizincidencia_matrizad(grafo_t* g){
    matriz_t* m = malloc(sizeof(matriz_t));
    if(!m) return NULL;

    m->cantidad = g->cantidad;
    m->adyacencias = calloc(m->cantidad*m->cantidad, sizeof(int));
    if(!(m->adyacencias)){
        free(m);
        return NULL;
    }
    //dejar_matriz_para_greedys(m);
    rellenar_matriz_con_elementos_en_incidencia(g, m);
    return m;
}

void mostrar_adyacencia(int* matriz, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%i\t", matriz[i+j*n]);   
        }
        printf("\n");
    }
}

void matriz_liberar(matriz_t* g){
    free(g->adyacencias);
    free(g);
}
//////////////////////////////////////////////////////////////////////////////////////////
int main(){
    grafo_t* g = grafo_crear(8);

    grafo_agregar_arista(g, ENTRADA, SALA, 1);
    grafo_agregar_arista(g, SALA, COCINA, 2);
    grafo_agregar_arista(g, SALA, BANIO, 4);
    grafo_agregar_arista(g, SALA, JARDIN, 4);
    grafo_agregar_arista(g, JARDIN, CALABOZO, 7);
    grafo_agregar_arista(g, JARDIN, TERRAZA, 2);
    grafo_agregar_arista(g, CALABOZO, TORTUTA, 3);
    grafo_agregar_arista(g, TERRAZA, BANIO, 3);

    mostrar_matriz(g->adyacencias, g->cantidad, g->cant_aristas);
    printf("\n");
    grafo_dfs(g, 0);
    printf("-->DFS");
    printf("\n");
    grafo_bfs(g, 0);
    printf("-->BFS");
    printf("\n");

    matriz_t* m;
    m = transformar_matrizincidencia_matrizad(g);
    printf("\n");
    printf("M.Incidencia-->M.Adyacencia");
    printf("\n");
    mostrar_adyacencia(m->adyacencias, m->cantidad);
    destruir_grafo(g);
    matriz_liberar(m);
    return 0;
}