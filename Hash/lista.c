#include "lista.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int ERROR = -1;
const int EXITO = 0;
const int ORIGEN = 0;
const int VACIO = 0;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct nodo{
    void* elemento;
    struct nodo* siguiente;
}nodo_t;

struct lista{
    int cantidad;
    nodo_t* inicio;
    nodo_t* ultimo;
};

struct lista_iterador{
    nodo_t* actual;
    struct lista* lista;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
lista_t* lista_crear(){
    return calloc(1, sizeof(lista_t));
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int lista_insertar(lista_t* lista, void* elemento){
    if(!lista)
        return ERROR;

    nodo_t* nodito = malloc(sizeof(nodo_t));
    if(!nodito)
        return ERROR;

    nodito->elemento = elemento;
    nodito->siguiente = NULL;
    if(lista_vacia(lista)){ 
        lista->inicio = nodito;
        lista->ultimo = nodito;
    }else{
        lista->ultimo->siguiente = nodito;
        lista->ultimo = nodito;
    }
    lista->cantidad++;
    return EXITO;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Inserta un elemento al principio de la lista.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
int lista_insertar_principio(lista_t* lista, void* elemento){
    if(!lista)
        return ERROR;
    
    nodo_t* nuevo_nodo = malloc(sizeof(nodo_t));
    if(!nuevo_nodo)
        return ERROR;
    
    nuevo_nodo->siguiente = lista->inicio;
    nuevo_nodo->elemento = elemento;
    lista->inicio = nuevo_nodo;
    lista->cantidad++;
    return EXITO;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){
    if(!lista)
        return ERROR;

    if(posicion >= lista_elementos(lista))   
        return lista_insertar(lista,  elemento);

    if(lista_vacia(lista))
        return lista_insertar(lista,  elemento);

    if(posicion == ORIGEN)
        return lista_insertar_principio(lista, elemento);

    nodo_t* actual;
    nodo_t* nuevo_nodo = malloc(sizeof(nodo_t));
    if(!nuevo_nodo)
        return ERROR;

    actual = lista->inicio;
    for(int i = 1; i < posicion; i++){
        actual = actual->siguiente;
    }
    nuevo_nodo->siguiente = actual->siguiente;
    nuevo_nodo->elemento = elemento;
    actual->siguiente = nuevo_nodo;
    lista->cantidad++;
    return EXITO;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int lista_borrar(lista_t* lista){
    if(!lista)
        return ERROR;
    if(lista_vacia(lista))     
        return ERROR;

    nodo_t* actual;
    actual = lista->inicio;
    bool llego_alfinal = false;
    
    if(lista_elementos(lista) > 2){   
        while(!llego_alfinal){
            actual = actual->siguiente;
            if(actual->siguiente->siguiente == NULL){
                free(actual->siguiente);
                actual->siguiente = NULL;
                lista->ultimo = actual;
                lista->cantidad--;
                llego_alfinal = true;
            }
        }
    }else if(lista_elementos(lista) == 2){   
        free(actual->siguiente);
        actual->siguiente = NULL;
        lista->ultimo = actual;
        lista->cantidad--;
    }else{
        free(actual);
        lista->inicio = NULL;
        lista->ultimo = NULL;
        lista->cantidad--;
    }
    return EXITO;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Quita de la lista el elemento que se encuentra en la primera posición.
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */
int lista_borrar_principio(lista_t* lista){
    if(!lista)
        return ERROR;

    if(lista_vacia(lista)) 
        return ERROR;

    if(lista_elementos(lista) == 1){  
        free(lista->inicio);
        lista->inicio = NULL;
        lista->ultimo = NULL;
        lista->cantidad--;
    }else{
        nodo_t* nodo_aux;
        nodo_aux = lista->inicio;
        lista->inicio = lista->inicio->siguiente;
        free(nodo_aux);
        lista->cantidad--;
    }
    return EXITO;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
    if(!lista)
        return ERROR;

    if(lista_vacia(lista)) 
        return ERROR;

    if(posicion >= lista_elementos(lista)-1)   
        return lista_borrar(lista);

    if(posicion == ORIGEN)
        return lista_borrar_principio(lista);

    nodo_t* actual;
    nodo_t* nodo_aux;
    actual = lista->inicio;

    for(int i = 1; i < posicion; i++){
        actual = actual->siguiente;
    }
        nodo_aux = actual->siguiente;
        actual->siguiente = actual->siguiente->siguiente;
        free(nodo_aux);
        lista->cantidad--;
        return EXITO;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
    if(!lista)
        return NULL;

    if(lista_vacia(lista))
        return NULL;

    if(posicion >= lista_elementos(lista))
        return NULL;
    
    nodo_t* actual;
    actual = lista->inicio;
    for(int i = 0; i < posicion; i++){
        actual = actual->siguiente;
    }
    return actual->elemento;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void* lista_ultimo(lista_t* lista){
    if(!lista)
        return NULL;

    if(lista_vacia(lista))
        return NULL;
    
    return lista->ultimo->elemento;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool lista_vacia(lista_t* lista){
    if(!lista)
        return ERROR;
    
    bool estado = false;
    if((lista->inicio == NULL) && (lista->ultimo == NULL)){
        estado = true;
    }
    return estado;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
size_t lista_elementos(lista_t* lista){
    if(!lista)
        return 0;

    if(lista_vacia(lista))
        return 0;
    
    nodo_t* actual;
    actual = lista->inicio;
    size_t contador = 1;
    while (actual->siguiente != NULL){
        actual = actual->siguiente;
        contador++;
    }
    return contador;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int lista_apilar(lista_t* lista, void* elemento){
    return lista_insertar(lista,  elemento);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int lista_desapilar(lista_t* lista){
    return lista_borrar(lista);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void* lista_tope(lista_t* lista){
    return lista_ultimo(lista);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int lista_encolar(lista_t* lista, void* elemento){
    return lista_insertar(lista,  elemento);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int lista_desencolar(lista_t* lista){
    return lista_borrar_principio(lista);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void* lista_primero(lista_t* lista){
    if(!lista)
        return NULL;

    if(lista_vacia(lista)) 
        return NULL;

    return lista->inicio->elemento;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void lista_destruir(lista_t* lista){
    if(!lista)
        return;
    
    size_t contador = lista_elementos(lista);
    if(contador == VACIO){
        free(lista);
    }else{
        while(lista_elementos(lista) != VACIO){
            nodo_t* nodo_aux;
            if(lista_elementos(lista) == 1){
                nodo_aux = lista->inicio;
                lista->inicio = NULL;
                lista->ultimo = NULL;
                free(nodo_aux);
            }else{
                if(lista->inicio->siguiente != NULL){
                    nodo_aux = lista->inicio;
                    lista->inicio = lista->inicio->siguiente;
                    free(nodo_aux);
                }
            }
            lista->cantidad--;
        }
        free(lista);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
lista_iterador_t* lista_iterador_crear(lista_t* lista){
    if(!lista)
        return NULL;
    
    lista_iterador_t* it = calloc(1, sizeof(lista_iterador_t));
    if(!it)
        return NULL;
    
    it->lista = lista;
    it->actual = NULL;
    return it;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
    if(!iterador || lista_vacia(iterador->lista))
        return false;
    
    bool tiene_siguiente = false;

    if((iterador->actual == NULL)&&(iterador->lista->inicio != NULL)){
        tiene_siguiente = true;
    }else if(iterador->actual->siguiente != NULL){
        tiene_siguiente = true;
    }
    return tiene_siguiente;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void* lista_iterador_siguiente(lista_iterador_t* iterador){
    if(!iterador || lista_vacia(iterador->lista))
        return NULL;

    void* elemento;

    if((iterador->actual == NULL)&&(iterador->lista->inicio != NULL)){
        iterador->actual = iterador->lista->inicio;
        elemento = iterador->actual->elemento;
    }else if(lista_iterador_tiene_siguiente(iterador)){
        iterador->actual = iterador->actual->siguiente;
        elemento = iterador->actual->elemento;
    }else{
        elemento = NULL;
    }
    return elemento;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void lista_iterador_destruir(lista_iterador_t* iterador){
    free(iterador);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void lista_con_cada_elemento(lista_t* lista, void (*funcion)(void*, void*), void *contexto){
    if(!lista)
        return;
    
    lista_iterador_t* it = lista_iterador_crear(lista);
    if(!it)
        return;

    while(lista_iterador_tiene_siguiente(it)){
        funcion(lista_iterador_siguiente(it), contexto);
    }
    lista_iterador_destruir(it);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////