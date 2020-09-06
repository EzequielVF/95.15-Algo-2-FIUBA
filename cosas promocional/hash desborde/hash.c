#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define TAM_INICIAL 101
#define FACTOR_CARGA 0.70
#define INFINITO 99999
/* *****************************************************************
 *                      ESTRUCTURA DEL HASH
 * *****************************************************************/
typedef void (*hash_destruir_dato_t)(void*);

typedef enum estado{
	vacio,
	ocupado,
	borrado
}estado_t;

typedef struct campo{
	char* clave;
	void* dato;
	estado_t estado;
}campo_t;

struct hash{
	size_t tam;
	size_t cant;
	hash_destruir_dato_t destruir_dato;
	campo_t* tabla;
};

typedef struct hash_iter{
	const hash_t* hash;
	int actual;
}hash_iter_t;

bool hash_iter_al_final(const hash_iter_t *iter);
size_t buscar_posicion(const hash_t *hash, const char *clave);
campo_t* crear_campo(size_t tam);
void hash_redimensionar(hash_t* hash, size_t tam_final);
/* *****************************************************************
 *                    PRIMITIVAS DEL HASH
 * *****************************************************************/
hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
	hash_t* hash = malloc(sizeof(hash_t));
	hash->tabla = crear_campo(TAM_INICIAL);
	if (!hash || !hash->tabla){
		return NULL;
	}
	hash->cant = 0;
	hash->tam = TAM_INICIAL;
	hash->destruir_dato = destruir_dato;
	return hash;
}
///////////////////////////////////////////////////////////////////////////////
size_t funcion_hash(const char* s,size_t tam){ 
	size_t hashval; 
	for (hashval = 0; *s != '\0'; s++){
		hashval = *s + 31 * hashval;
	}
	size_t tamanio = tam*0.85;
	return hashval % tamanio;
}
//////////////////////////////////////////////////////////////////////////////
float factor_carga(hash_t* hash){
	float factor = 0;
	float cantidad = (float)hash->cant;
	float tamnio = (float)hash->tam;
	factor = (float)(cantidad/tamnio);
	return factor;
}
//////////////////////////////////////////////////////////////////////////////
char *strdup (const char *s) {
    char *d = malloc (strlen (s) + 1);   
    if (d == NULL) return NULL;          
    strcpy (d,s);                        
    return d;                            
}
///////////////////////////////////////////////////////////////////////////////
campo_t* crear_campo(size_t tam){
	campo_t* campo_nuevo= malloc(sizeof(campo_t)*tam);
	if (!campo_nuevo)return NULL;
	for (int i = 0; i < tam; i++){
		campo_nuevo[i].estado = 0;
	}
	return campo_nuevo;
}
///////////////////////////////////////////////////////////////////////////////
size_t buscar_posicion(const hash_t *hash, const char *clave){
	size_t pos = funcion_hash(clave, hash->tam);
	if (hash->tabla[pos].estado==0 || (hash->tabla[pos].estado == 1 && strcmp(hash->tabla[pos].clave, clave) == 0)){
		return pos;
	}
	pos = (hash->tam)*0.90;

	while(pos < hash->tam){
		if(hash->tabla[pos].estado == 0) return pos;
		if((hash->tabla[pos].estado == 1) && (strcmp(hash->tabla[pos].clave, clave) == 0 )) return pos;

		pos++;
	}
	return INFINITO;
}
///////////////////////////////////////////////////////////////////////////////
bool es_primo_r(size_t n, size_t x){
	if(x == 1)
		return true;

	if(n % x == 0)
		return false;

	return es_primo_r(n, x-1);
}
bool es_primo(size_t n){
	if(n < 2) return false;

	return es_primo_r(n, n-1);
}
size_t nuevo_tamanio_hash(size_t tamanio_viejo){
	size_t nuevo_tamanio = tamanio_viejo*2;
	bool encontrado = false;
	if(es_primo(nuevo_tamanio)){
		encontrado = true;
	}else{
		while(!encontrado){
			nuevo_tamanio++;
			if(es_primo(nuevo_tamanio)){
				encontrado = true;
			}
		}
	}
	return nuevo_tamanio;
}
///////////////////////////////////////////////////////////////////////////////
void hash_redimensionar(hash_t* hash, size_t tam_final){
	size_t nuevo_tam = nuevo_tamanio_hash(tam_final);
	campo_t* campo_nuevo= crear_campo(nuevo_tam);
	campo_t* campo_viejo= hash->tabla;
	size_t tam_in= hash->tam;
	hash->tabla=campo_nuevo;
	hash->tam=nuevo_tam;
	hash->cant=0;
	for(int i=0;i<tam_in;i++){
		if(campo_viejo[i].estado==1){
			hash_guardar(hash,campo_viejo[i].clave,campo_viejo[i].dato);
			free(campo_viejo[i].clave);
		}
	}
	free(campo_viejo);
}
///////////////////////////////////////////////////////////////////////////////
bool hash_guardar(hash_t *hash, const char *clave_nueva, void *dato){
	if(hash==NULL || clave_nueva==NULL)return false;
	size_t pos = buscar_posicion(hash,clave_nueva);
	if(pos == INFINITO){
		hash_redimensionar(hash, hash->tam);
		pos = buscar_posicion(hash, clave_nueva);
	}
	if (hash->tabla[pos].estado == 1){ 
		if(hash->destruir_dato){
			hash->destruir_dato(hash->tabla[pos].dato);
		}
		hash->tabla[pos].dato = dato;
		return true;
	}
	hash->tabla[pos].clave = strdup(clave_nueva);
	hash->tabla[pos].dato = dato;
	hash->tabla[pos].estado = 1;
	hash->cant += 1;
	if(factor_carga(hash) > FACTOR_CARGA){
		hash_redimensionar(hash,hash->tam);
	}
	return true;
}
///////////////////////////////////////////////////////////////////////////////
void *hash_borrar(hash_t *hash, const char *clave){
	if (!hash_pertenece(hash, clave)){
		return NULL;
	}
	size_t pos = buscar_posicion(hash,clave);
	hash->cant -= 1;
	hash->tabla[pos].estado = 2;
	free(hash->tabla[pos].clave);
	void* dato= hash->tabla[pos].dato;
	if(hash->destruir_dato){
				hash->destruir_dato(hash->tabla[pos].dato);
		}
	if (hash->cant *4 <= hash->tam ){
		hash_redimensionar(hash, (hash->tam / 2));
		}
	return dato;
}
///////////////////////////////////////////////////////////////////////////////
void *hash_obtener(const hash_t *hash, const char *clave){
	if (!hash_pertenece(hash, clave)){
		return NULL;
		}
	size_t pos = buscar_posicion(hash,clave); 
	return hash->tabla[pos].dato;
}
///////////////////////////////////////////////////////////////////////////////
bool hash_pertenece(const hash_t *hash, const char *clave){
	size_t pos = buscar_posicion(hash,clave);
	return hash->tabla[pos].estado == 1;
}
///////////////////////////////////////////////////////////////////////////////
size_t hash_cantidad(const hash_t *hash){
	return hash->cant;
}
///////////////////////////////////////////////////////////////////////////////
void hash_destruir(hash_t* hash){
	if(hash_cantidad(hash)!=0){
		for (int i = 0; i != hash->tam; i++){
			if(hash->tabla[i].estado==1){
				if (hash->destruir_dato){
						hash->destruir_dato(hash->tabla[i].dato);
					}
				free(hash->tabla[i].clave);
				}
		}
	}
	free(hash->tabla);
	free(hash);
}
/* *****************************************************************
 *                    PRIMITIVAS DEL ITER
 * *****************************************************************/
hash_iter_t *hash_iter_crear(const hash_t *hash){
	hash_iter_t* iter = malloc(sizeof(hash_iter_t));
	if (!iter) return NULL;
	iter->hash=hash;
	iter->actual=0;
	if (iter->hash->cant == 0) iter->actual = (int)iter->hash->tam;
	else{
		while (iter->hash->tabla[iter->actual].estado != 1){
			iter->actual++;
		}
	}
	return iter;
}
///////////////////////////////////////////////////////////////////////////////
const char *hash_iter_ver_actual(const hash_iter_t *iter){
	if (hash_iter_al_final(iter))return NULL;
	return iter->hash->tabla[iter->actual].clave;
}
///////////////////////////////////////////////////////////////////////////////
bool hash_iter_al_final(const hash_iter_t *iter){
	return iter->actual == (int) iter->hash->tam;
}         
///////////////////////////////////////////////////////////////////////////////		
bool hash_iter_avanzar(hash_iter_t *iter){
	if (hash_iter_al_final(iter))return false;
	iter->actual++;
	while ( !hash_iter_al_final(iter) && iter->hash->tabla[iter->actual].estado != 1){
		iter->actual++;
	}
	if (hash_iter_al_final(iter))return false;
	return true;
}
///////////////////////////////////////////////////////////////////////////////
void hash_iter_destruir(hash_iter_t* iter){
	free(iter);
}
///////////////////////////////////////////////////////////////////////////////