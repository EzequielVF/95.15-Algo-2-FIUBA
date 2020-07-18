#include "lista.h"
#include "hash.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct hash{
		size_t cant;
		size_t tam;
		lista_t** tabla;
		hash_destruir_dato_t destructor;
}hash_t;