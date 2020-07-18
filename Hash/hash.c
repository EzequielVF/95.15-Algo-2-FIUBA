#include "lista.h"
#include "hash.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CANT_INICIAL 0
#define TAM_INICIAL 3
#define FACTOR_CARGA 0.75
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int ERROR = -1;
const int EXITO = 0;
const int ORIGEN = 0;
const int VACIO = 0;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct hash{
		size_t cantidad;
		size_t tamanio;
		lista_t** indice;
		hash_destruir_dato_t destructor;
}hash_t;

typedef struct cosa{
	char* clave;
	void* elemento;
}cosa_t;
////////////////////////////////////////////////////////////////HASH CREAR/////////////////////////////////////////////////////////////////
hash_t* hash_crear(hash_destruir_dato_t destruir_elemento, size_t capacidad){
	size_t tamanio;
	if(capacidad > TAM_INICIAL){
		tamanio = capacidad;
	}else{
		tamanio = TAM_INICIAL;
	}
	
	hash_t* aux = malloc(sizeof(hash_t));
	if(!aux) return NULL;

	lista_t** lista_aux = malloc(sizeof(lista_t*)*tamanio);
	if(!lista_aux){
		free(aux);
		return NULL;
	}
	aux->indice = lista_aux;
	for(size i = 0; i < tamanio; i++){
		aux->indice[i] = lista_crear();
	}
	aux->cantidad = CANT_INICIAL;
	aux->destructor = destruir_elemento;
	aux->tamanio = tamanio;
	return aux;
}
//////////////////////////////////////////////////////////////////HASH INSERTAR////////////////////////////////////////////////////////////////////
float factor_carga(hash_t* hash){
	float factor = (float)(hash->cantidad/hash->tamanio);
	return factor;
}

int redimensionar_vector_listas(hash_t* hash){
	size_t nuevo_tamanio = hash->tamanio*2;
	size_t cantidad = hash->cantidad;
	lista_t** nuevo_indice = malloc(sizeof(lista_t*)*nuevo_tamanio);
	if(!nuevo_indice) return ERROR;

	for(size_t i = 0; i < nuevo_tamanio; i++){
		nuevo_indice[i] = lista_crear();
	}
	for(size_t j = 0; j < hash->tamanio; j++){
		if(hash->indice[j]){
			while(!lista_vacia(hash->indice[j])){
				cosa_t* aux = lista_elemento_en_posicion(hash->indice[j], ORIGEN);
				lista_borrar_de_posicion(hash->indice[j], ORIGEN);
				size_t posicion = hashing(nuevo_tamanio, aux);
				lista_insertar(nuevo_indice[posicion], aux);
			}
			lista_destruir(hash->indice[j]);
		}
	}
	free(hash->indice);
	hash->indice = nuevo_indice;
	hash->tamanio = nuevo_tamanio;
	hash->cantidad = cantidad;
	return EXITO;
}

cosa_t* crear_cosa(void* elemento, char* clave){
	cosa_t* aux = malloc(sizeof(cosa_t));
	if(!aux) return NULL;

	strcpy(aux->clave, clave);
	aux->elemento = elemento;
	return aux;
}

size_t hashing(size_t tamanio, cosa_t* cosa){
	size_t posicion = strlen(cosa->clave);
	int suma = 0;
	for(size_t i = 0; i< posicion; i++){
		suma += (cosa->clave[i]);
	}
	suma*=suma;
	posicion = suma%(tamanio+1);
	return posicion;
}

int hash_insertar(hash_t* hash, const char* clave, void* elemento){
	size_t posicion;
	int estado = 0;
	cosa_t* cosa;

	if(factor_carga(hash) >= FACTOR_CARGA){
		estado = redimensionar_vector_listas(hash);
		if(estado == ERROR){
			return estado;
		}
	}
	cosa = crear_cosa(elemento, clave);
	if(cosa){
		posicion = hashing(hash->tamanio, cosa);
		lista_insertar(hash->indice[posicion], cosa);
		hash->cantidad++;
		estado = EXITO;
	}else{
		estado = ERROR;
	}
	return estado;
}