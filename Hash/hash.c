#include "lista.h"
#include "hash.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CANT_INICIAL 0
#define TAM_INICIAL 3
#define FACTOR_CARGA 0.75
#define ERROR -1
#define EXITO 0
#define ORIGEN 0
#define VACIO 0
/////////////////////////////////////////////////////////////////STRUCTS///////////////////////////////////////////////////////////////////
struct hash{
		size_t cantidad;
		size_t tamanio;
		lista_t** indice;
		hash_destruir_dato_t destructor;
};

typedef struct cosa{
	char* clave;
	void* elemento;
}cosa_t;
////////////////////////////////////////////////////////////////AUXILIARES////////////////////////////////////////////////////////////////
char* str_dup_c99(const char* s){
  if(!s)
    return NULL;
  
  char* p = malloc(strlen(s)+1);
  strcpy(p,s);
  return p;
}

cosa_t* crear_cosa(void* elemento, const char* clave){
	cosa_t* aux = malloc(sizeof(cosa_t));
	if(!aux) return NULL;

	aux->clave = str_dup_c99(clave);
	aux->elemento = elemento;
	return aux;
}

size_t hashing(size_t tamanio, cosa_t* cosa){
	size_t posicion = strlen(cosa->clave);
	size_t suma = 0;
	for(size_t i = 0; i< posicion; i++){
		suma += (size_t)(cosa->clave[i]);
	}
	suma*=suma;
	posicion = suma%(tamanio+1);
	return posicion;
}

void destruir_cosa(cosa_t* cosa, hash_destruir_dato_t destructor){
	if(!destructor) return;

	destructor(cosa->elemento);
	free(cosa);
}
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
	for(size_t i = 0; i < tamanio; i++){
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

int hash_insertar(hash_t* hash, const char* clave, void* elemento){
	if(!hash) return ERROR;
	
	size_t posicion;
	int estado = ERROR;
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
//////////////////////////////////////////////////////////////////HASH QUITAR//////////////////////////////////////////////////////////////////
int hash_quitar(hash_t* hash, const char* clave){
	if(!hash) return ERROR;

	size_t posicion;
	size_t cantidad_elementos;
	cosa_t* cosa_del_hash = NULL;
	cosa_t aux = {"", NULL};
	int estado = ERROR;

	strcpy(aux.clave, clave);
	posicion = hashing(hash->tamanio, &aux);
	cantidad_elementos = lista_elementos(hash->indice[posicion]);
	for(size_t i = 0; i < cantidad_elementos; i++){
		cosa_del_hash = (cosa_t*)lista_elemento_en_posicion(hash->indice[posicion], i);
		if(strcmp(cosa_del_hash->clave, aux.clave) == 0){
			lista_borrar_de_posicion(hash->indice[posicion], i);
			destruir_cosa(cosa_del_hash, hash->destructor);
			estado = EXITO;
		}
	}
	return estado;
}
/////////////////////////////////////////////////////////////////HASH CONTIENE/////////////////////////////////////////////////////////////////
bool hash_contiene(hash_t* hash, const char* clave){
	size_t posicion;
	size_t cantidad_elementos;
	bool encontre = false;
	cosa_t* cosa_del_hash = NULL;
	cosa_t aux = {"", NULL};

	if(!hash) return encontre;

	strcpy(aux.clave, clave);
	posicion = hashing(hash->tamanio, &aux);
	cantidad_elementos = lista_elementos(hash->indice[posicion]);
	for(size_t i = 0; i < cantidad_elementos; i++){
		cosa_del_hash = (cosa_t*)lista_elemento_en_posicion(hash->indice[posicion], i);
		if(strcmp(cosa_del_hash->clave, aux.clave) == 0){
			encontre = true;
		}
	}
	return encontre;
}
/////////////////////////////////////////////////////////////////HASH OBTENER/////////////////////////////////////////////////////////////////
void* hash_obtener(hash_t* hash, const char* clave){
	if(!hash) return NULL;

	size_t posicion;
	size_t cantidad_elementos;
	cosa_t* cosa_del_hash = NULL;
	cosa_t aux = {"", NULL};

	strcpy(aux.clave, clave);
	posicion = hashing(hash->tamanio, &aux);
	cantidad_elementos = lista_elementos(hash->indice[posicion]);
	for(size_t i = 0; i < cantidad_elementos; i++){
		cosa_del_hash = (cosa_t*)lista_elemento_en_posicion(hash->indice[posicion], i);
		if(strcmp(cosa_del_hash->clave, aux.clave) == 0){
			return cosa_del_hash->elemento;
		}
	}
	return NULL;
}
/////////////////////////////////////////////////////////////////HASH CANTIDAD/////////////////////////////////////////////////////////////////
size_t hash_cantidad(hash_t* hash){
	return hash->cantidad;
}
/////////////////////////////////////////////////////////////////HASH DESTRUIR/////////////////////////////////////////////////////////////////
void hash_destruir(hash_t* hash){
	size_t tamanio = hash->tamanio;
	cosa_t* aux = NULL;

	for(size_t i = 0; i < tamanio; i++){
		if(hash->indice[i]){
			while(!lista_vacia(hash->indice[i])){
				aux = (cosa_t*)lista_elemento_en_posicion(hash->indice[i], ORIGEN);
				lista_borrar_de_posicion(hash->indice[i], ORIGEN);
				destruir_cosa(aux, hash->destructor);
			}
			lista_destruir(hash->indice[i]);
		}
	}
	free(hash->indice);
	free(hash);
}
/////////////////////////////////////////////////////////////////HASH CON CADA CLAVE/////////////////////////////////////////////////////////////////
size_t hash_con_cada_clave(hash_t* hash, bool (*funcion)(hash_t* hash, const char* clave, void* aux), void* aux){
	if(!hash || !funcion) return 0;
	
	size_t tamanio = hash->tamanio;
	size_t cantidad = 0;
	size_t contador = 0;
	bool estado = false;
	cosa_t* cosa_en_hash = NULL;

	for(size_t i = 0; i < tamanio; i++){
		if(hash->indice[i]){
			cantidad = lista_elementos(hash->indice[i]);
			for(size_t j = 0; j < cantidad; j++){
				cosa_en_hash = (cosa_t*)lista_elemento_en_posicion(hash->indice[i], j);
				estado = funcion(hash, cosa_en_hash->clave, aux);
				contador++;
				if(estado) break;
			}
		}
		if(estado) break;
	}
	return contador;
}