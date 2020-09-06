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
#define DESCONOCIDA 9999
#define INFINITO 99999

typedef struct nodo{
    struct nodo* sig;
    int identidad;
    int peso;
}nodo_t;

typedef struct{
    nodo_t** vector;
    int cantidad;
}grafo_t;

nodo_t* crear_nodo(){
    nodo_t* nodito = malloc(sizeof(nodo_t));
    if(!nodito) return NULL;

    nodito->identidad = DESCONOCIDA;
    nodito->sig = NULL;
    return nodito;
} 

grafo_t* crear_grafo(int tamanio){
    grafo_t* grafito = malloc(sizeof(grafo_t));
    if(!grafito) return NULL;

    nodo_t** vector = malloc(sizeof(nodo_t*)*tamanio);
    if(!vector){
        free(grafito);
        return NULL;
    }
    grafito->vector = vector;
    grafito->cantidad = tamanio;
    for(int i = 0; i< tamanio; i++){
        grafito->vector[i] = crear_nodo();
    }
    return grafito;
}

void agregar_nodo(nodo_t* nodo, int v1, int peso){
    if(nodo->sig == NULL){
        nodo->sig = crear_nodo();
        nodo->sig->identidad = v1;
        nodo->sig->peso = peso;
        return;
    }
    if(nodo->sig != NULL){
        if(nodo->sig->identidad == v1){
            return;
        }else{
            agregar_nodo(nodo->sig, v1, peso);
        }
    }
}

void grafo_agregar_arista(grafo_t* g, int v0, int v1, int peso){
    bool esta_v0 = false;
    bool esta_v1 = false;
    int posicion_v0 = 0;
    int posicion_v1 = 0;

    for(int i = 0; i<g->cantidad; i++){
        if(g->vector[i]->identidad == v0){
            esta_v0 = true;
            posicion_v0 = i;
        }
        if(g->vector[i]->identidad == v1){
            esta_v1 = true;
            posicion_v1 = i;
        }
    }
    if(!esta_v0){
        for(int i = 0; i<g->cantidad; i++){
            if(g->vector[i]->identidad == DESCONOCIDA){
                g->vector[i]->identidad = v0;
                g->vector[i]->sig = crear_nodo();
                g->vector[i]->sig->identidad = v1;
                g->vector[i]->peso = 0;
                g->vector[i]->sig->peso = peso;
                break;
            }
        }
    }
    if(!esta_v1){
        for(int i = 0; i<g->cantidad; i++){
            if(g->vector[i]->identidad == DESCONOCIDA){
                g->vector[i]->identidad = v1;
                g->vector[i]->sig = crear_nodo();
                g->vector[i]->sig->identidad = v0;
                g->vector[i]->peso = 0;
                g->vector[i]->sig->peso = peso;
                break;
            }
        }
    }
    if(esta_v0){
        agregar_nodo(g->vector[posicion_v0], v1, peso);
    }
    if(esta_v1){
        agregar_nodo(g->vector[posicion_v1], v0, peso);
    }
}

void printear_todos_siguientes(nodo_t* n){
    if(n->sig){
        printf("-->%i", n->sig->identidad);
        printear_todos_siguientes(n->sig);
    }
    if(!(n->sig)){
        printf("\n");
    }  
}

void mostrar_grafo(grafo_t* g){
    for(int i = 0; i < g->cantidad; i++){
        printf("%i",g->vector[i]->identidad);
        printear_todos_siguientes(g->vector[i]);
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
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
void encolador_de_siguientes(nodo_t* nodo, bool* encolados, elemento_t** elementos, lista_t* cola, bool* visitados){
    if(nodo != NULL && !visitados[nodo->identidad] && !encolados[nodo->identidad]){
        elementos[nodo->identidad] = crear_elemento(nodo->identidad);
        lista_encolar(cola, elementos[nodo->identidad]);
        encolados[nodo->identidad] = true;
    }   
    if(nodo)
        encolador_de_siguientes(nodo->sig, encolados, elementos, cola, visitados); 
}

void grafo_bfs(grafo_t* g, int v0){
    bool visitados[g->cantidad];
    bool encolados[g->cantidad];
    memset(visitados, 0, sizeof(visitados));
    memset(encolados, 0, sizeof(encolados));
    elemento_t** elementos = malloc(sizeof(elemento_t*)*g->cantidad);
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
        encolador_de_siguientes(g->vector[aux->cosa]->sig, encolados, elementos, cola, visitados);
    }
    lista_destruir(cola);
    liberar_elementos(elementos, g->cantidad);
}
//////////////////////////////////////////////////////////////////////////////////////////
void apilador_de_siguientes(nodo_t* nodo, bool* apilados, elemento_t** elementos, lista_t* pila, bool* visitados){
    if(nodo != NULL && !visitados[nodo->identidad] && !apilados[nodo->identidad]){
        elementos[nodo->identidad] = crear_elemento(nodo->identidad);
        lista_apilar(pila, elementos[nodo->identidad]);
        apilados[nodo->identidad] = true;
    }   
    if(nodo)
        apilador_de_siguientes(nodo->sig, apilados, elementos, pila, visitados); 
}

void grafo_dfs(grafo_t* g, int v0){
    bool visitados[g->cantidad];
    bool apilados[g->cantidad];
    memset(visitados, 0, sizeof(visitados));
    memset(apilados, 0, sizeof(apilados));
    elemento_t** elementos = malloc(sizeof(elemento_t*)*g->cantidad);
    lista_t* pila = lista_crear();
    elemento_t* aux;

    elementos[v0] = crear_elemento(v0);
    lista_encolar(pila, elementos[v0]);
    apilados[v0] = true;
    while(lista_vacia(pila) != true){
        aux = (elemento_t*)lista_ultimo(pila); //Mi pila al desapilar no devuelve el elemento :D
        lista_desapilar(pila);
        printf("%i", aux->cosa);
        visitados[aux->cosa] = true;
        apilador_de_siguientes(g->vector[aux->cosa]->sig, apilados, elementos, pila, visitados);
    }
    lista_destruir(pila);
    liberar_elementos(elementos, g->cantidad);
}
//////////////////////////////////////////////////////////////////////////////////////////
void acomodar_vector_grafo(grafo_t* g){
    nodo_t* aux;
    int indice;
    for(int i = 0; i<g->cantidad; i++){
        if(g->vector[i]->identidad != i){
            indice = g->vector[i]->identidad;
            aux = g->vector[i];
            g->vector[i] = g->vector[indice];
            g->vector[indice] = aux;
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
void recorrer_hasta_el_final(nodo_t* nodo){
    if(nodo->sig)
        recorrer_hasta_el_final(nodo->sig);

    free(nodo);
}

void destruir_grafo(grafo_t* g){
    for(int i = 0; i<g->cantidad; i++){
        recorrer_hasta_el_final(g->vector[i]->sig);
        free(g->vector[i]);
    }
    free(g->vector);
    free(g);
}
//////////////////////////////////////////////////////////////////////////////////////////
typedef struct matriz{
    int* adyacencias;
    int cantidad;
}matriz_t;

void dejar_matriz_para_greedys(matriz_t* m){
    for(int i = 0; i < m->cantidad; i++){
        for(int j = 0; j < m->cantidad; j++){
            m->adyacencias[j*m->cantidad + i] = INFINITO;
            if(i == j)
                m->adyacencias[j*m->cantidad + i] = 0;
        }
    }
}

void poner_relaciones_en_matriz(nodo_t* n, matriz_t* m, int v0){
    if(!n) return;

    int v1;
    v1 = n->identidad;
    m->adyacencias[(v0 * m->cantidad) + v1] = n->peso;
    poner_relaciones_en_matriz(n->sig, m, v0);
}

void rellenar_matriz_con_elementos_en_lista(grafo_t* g, matriz_t* m){
    int v0;
    
    for(int i = 0; i<g->cantidad; i++){
        v0 = g->vector[i]->identidad;
        poner_relaciones_en_matriz(g->vector[i]->sig, m, v0);
    }
}

matriz_t* transformar_listaad_matrizad(grafo_t* g){
    matriz_t* m = malloc(sizeof(matriz_t));
    if(!m) return NULL;

    m->cantidad = g->cantidad;
    m->adyacencias = calloc(m->cantidad*m->cantidad, sizeof(int));
    if(!(m->adyacencias)){
        free(m);
        return NULL;
    }
    //dejar_matriz_para_greedys(m);
    rellenar_matriz_con_elementos_en_lista(g, m);

    return m;
}

void mostrar_matriz(int* matriz, int n){
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
/////////////////////////////////////////////////////////////////////////////////////////////////
int main(){
    grafo_t* g = crear_grafo(8);
    grafo_agregar_arista(g, ENTRADA, SALA, 1);
    grafo_agregar_arista(g, SALA, COCINA, 2);
    grafo_agregar_arista(g, SALA, BANIO, 4);
    grafo_agregar_arista(g, SALA, JARDIN, 4);
    grafo_agregar_arista(g, JARDIN, CALABOZO, 7);
    grafo_agregar_arista(g, JARDIN, TERRAZA, 2);
    grafo_agregar_arista(g, CALABOZO, TORTUTA, 3);
    grafo_agregar_arista(g, TERRAZA, BANIO, 3);

    acomodar_vector_grafo(g);
    mostrar_grafo(g);
    printf("\n");
    grafo_dfs(g, 0);
    printf("-->DFS");
    printf("\n");
    grafo_bfs(g, 0);
    printf("-->BFS");
    printf("\n");

    matriz_t* matriz;
    matriz = transformar_listaad_matrizad(g);
    printf("\n");
    printf("Lista-->Matriz");
    printf("\n");
    mostrar_matriz(matriz->adyacencias, matriz->cantidad);
    destruir_grafo(g);
    matriz_liberar(matriz);
    return 0;
}