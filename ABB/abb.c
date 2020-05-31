#include "abb.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define ERROR -1
#define EXITO 0
#define IZQUIERDA 2
#define DERECHA 1
#define COINCIDENCIA 0
#define VACIO 0
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){
    abb_t* arbol = malloc(sizeof(abb_t));
    if(!arbol)
        return NULL;

    arbol->nodo_raiz = NULL;
    arbol->destructor = destructor;
    arbol->comparador = comparador;
    return arbol;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
nodo_abb_t* crear_nodo(void* elemento){
    nodo_abb_t* nodito = malloc(sizeof(nodo_abb_t));
    if(!nodito)
        return NULL;

    nodito->derecha = NULL;
    nodito->izquierda = NULL;
    nodito->elemento = elemento;
    return nodito;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int insertar_nodo(abb_t* arbol, nodo_abb_t* raiz, void* elemento, int posicion){
    nodo_abb_t* nodo = crear_nodo(elemento);
    if(!nodo)
        return ERROR;

    if(posicion == DERECHA){
        raiz->derecha = nodo;
    }
    if(posicion == IZQUIERDA){
        raiz->izquierda = nodo;
    }
    return EXITO;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int arbol_insertar_recursivo(abb_t* arbol, nodo_abb_t* raiz, void* elemento){
    if(!arbol->comparador) /* PENDIENTE DE VERIFICAR*/
        return ERROR;

    int comparador = arbol->comparador(elemento, raiz->elemento);
    if(comparador >= COINCIDENCIA){
        if(!raiz->derecha){
            return insertar_nodo(arbol, raiz, elemento, DERECHA);
        }
        return arbol_insertar_recursivo(arbol, raiz->derecha, elemento);
    }
    if(comparador < COINCIDENCIA){
        if(!raiz->izquierda){
            return insertar_nodo(arbol, raiz, elemento, IZQUIERDA);
        }
        return arbol_insertar_recursivo(arbol, raiz->izquierda, elemento);
    }
    return ERROR;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int arbol_insertar(abb_t* arbol, void* elemento){
    if(!arbol)
        return ERROR;

    if(arbol_vacio(arbol)){  
        nodo_abb_t* nodo = crear_nodo(elemento);
        arbol->nodo_raiz = nodo;
        return EXITO;
    }
    return arbol_insertar_recursivo(arbol, arbol->nodo_raiz, elemento);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool arbol_vacio(abb_t* arbol){
    if(!arbol)
        return true;
    
    if(!arbol->nodo_raiz)
        return true;
    
    return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void* arbol_raiz(abb_t* arbol){
    if(arbol_vacio(arbol))
        return NULL;
    
    return arbol->nodo_raiz->elemento;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void* buscar_recursivo(abb_t* arbol, nodo_abb_t* raiz, void* elemento){
    if(!arbol->comparador) /* PENDIENTE DE VERIFICAR*/
        return NULL;
    
    int comparador = arbol->comparador(elemento, raiz->elemento);
    if(comparador == COINCIDENCIA)
        return raiz->elemento;
    
    if(comparador > COINCIDENCIA){
        if(!raiz->derecha)
            return NULL;

        return buscar_recursivo(arbol, raiz->derecha, elemento);
    }
    if(comparador < COINCIDENCIA){
        if(!raiz->izquierda)
            return NULL;

        return buscar_recursivo(arbol, raiz->izquierda, elemento);
    }
    return NULL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void* arbol_buscar(abb_t* arbol, void* elemento){
    if(arbol_vacio(arbol))
        return NULL;

    return buscar_recursivo(arbol, arbol->nodo_raiz, elemento);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void inorden_recursivo(nodo_abb_t* nodo, void** array, int* llenados, int tope){
    if(!nodo)
        return;
    
    if(nodo->izquierda && (*llenados)>=tope){
        inorden_recursivo(nodo->izquierda, array, llenados, tope);
    }
    if((*llenados) >= tope)
        return;

    array[(*llenados)] = nodo->elemento;
    (*llenados)++;
    if(nodo->derecha && (*llenados)>=tope){
        inorden_recursivo(nodo->derecha, array, llenados, tope);
    }
    return;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int arbol_recorrido_inorden(abb_t* arbol, void** array, int tamanio_array){
    if(arbol_vacio(arbol))
        return VACIO;
    
    int llenados = VACIO;
    array = malloc((size_t)tamanio_array*sizeof(void*));
    inorden_recursivo(arbol->nodo_raiz, array, &llenados, tamanio_array);
    return llenados;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void preorden_recursivo(nodo_abb_t* nodo, void** array, int* llenados, int tope){
    if(!nodo)
        return;
    
    if((*llenados) >= tope)
        return;

    array[*llenados] = nodo->elemento;
    (*llenados)++;
    if(nodo->izquierda && (*llenados)>=tope){
        preorden_recursivo(nodo->izquierda, array, llenados, tope);
    }
    if(nodo->derecha && (*llenados)>=tope){
        preorden_recursivo(nodo->derecha, array, llenados, tope);
    }
    return;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int arbol_recorrido_preorden(abb_t* arbol, void** array, int tamanio_array){
    if(arbol_vacio(arbol))
        return VACIO;
    
    int llenados = VACIO;
    array = malloc((size_t)tamanio_array*sizeof(void*));
    preorden_recursivo(arbol->nodo_raiz, array, &llenados, tamanio_array);
    return llenados;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void postorden_recursivo(nodo_abb_t* nodo, void** array, int* llenados, int tope){
    if(!nodo)
        return;
    
    if(nodo->izquierda && (*llenados)>=tope){
        postorden_recursivo(nodo->izquierda, array, llenados, tope);
    }
    if(nodo->derecha && (*llenados)>=tope){
        postorden_recursivo(nodo->derecha, array, llenados, tope);
    }
    if((*llenados) >= tope)
        return;

    array[*llenados] = nodo->elemento;
    (*llenados)++;
    return;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int arbol_recorrido_postorden(abb_t* arbol, void** array, int tamanio_array){
    if(arbol_vacio(arbol))
        return VACIO;
    
    int llenados = VACIO;
    array = malloc((size_t)tamanio_array*sizeof(void*));
    postorden_recursivo(arbol->nodo_raiz, array, &llenados, tamanio_array);
    return llenados;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void destruir_nodo(nodo_abb_t* nodo, abb_liberar_elemento destructor){
    if(destructor)
        destructor(nodo->elemento);
    
    free(nodo);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int borrar_recursivo(nodo_abb_t** puntero_a_nodo, abb_liberar_elemento destructor){
    nodo_abb_t* nodo = *puntero_a_nodo;
    nodo_abb_t* auxiliar;
    if(!nodo->izquierda && !nodo->derecha){
        auxiliar = NULL;
    }else if(nodo->izquierda && !nodo->derecha){
        auxiliar = nodo->izquierda;
    }else if(!nodo->izquierda && nodo->derecha){
        auxiliar = nodo->derecha;
    }else{
        auxiliar = nodo->izquierda;
        if(!auxiliar->derecha){
            borrar_recursivo(&nodo->izquierda, NULL);
        }else{
            while((auxiliar->derecha)->derecha != NULL){
                auxiliar = auxiliar->derecha;
            }
            nodo_abb_t* nodo_obj = auxiliar->derecha;
            borrar_recursivo(&auxiliar->derecha, NULL);
            auxiliar = nodo_obj;
        }
        auxiliar->derecha = nodo->derecha;
        auxiliar->izquierda = nodo->izquierda;
    }
    if(destructor)
        destruir_nodo(nodo, destructor);

    *puntero_a_nodo = auxiliar;
    return EXITO;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
nodo_abb_t** buscar_nodo(nodo_abb_t** puntero_a_nodo, void* elemento, abb_comparador comparador){
    nodo_abb_t* nodo = *puntero_a_nodo;
    int comparar = comparador(elemento, nodo->elemento);
    if(!nodo || comparar == COINCIDENCIA){ /*En caso que nodo no exista, devolvera NULL*/
        return puntero_a_nodo;
    }else if(comparar > COINCIDENCIA){
        return buscar_nodo(&nodo->derecha, elemento, comparador);
    }else{
        return buscar_nodo(&nodo->izquierda, elemento, comparador);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int arbol_borrar(abb_t* arbol, void* elemento){
    if(arbol_vacio(arbol))
        return ERROR;

    nodo_abb_t** puntero_a_nodo = buscar_nodo(&arbol->nodo_raiz, elemento,arbol->comparador);
    if(!puntero_a_nodo)
        return ERROR;

    return borrar_recursivo(puntero_a_nodo, arbol->destructor);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void arbol_destruir(abb_t* arbol){
    free(arbol);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
