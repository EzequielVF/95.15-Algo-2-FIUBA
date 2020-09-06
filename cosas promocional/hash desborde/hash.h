#ifndef __HASH_H__
#define __HASH_H__

#include <stdbool.h>
#include <stddef.h>

typedef struct hash hash_t;
typedef void (*hash_destruir_dato_t)(void*);

hash_t *hash_crear(hash_destruir_dato_t destruir_dato);

bool hash_guardar(hash_t *hash, const char *clave_nueva, void *dato);

void *hash_borrar(hash_t *hash, const char *clave);

void *hash_obtener(const hash_t *hash, const char *clave);

bool hash_pertenece(const hash_t *hash, const char *clave);

size_t hash_cantidad(const hash_t *hash);

void hash_destruir(hash_t* hash);

#endif /* __HASH_H__ */
