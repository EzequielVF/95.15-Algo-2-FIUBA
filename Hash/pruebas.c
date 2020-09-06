#include "pa2m.h"
#include "hash.h"
#include "hash_iterador.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char* duplicar_string(const char* s){
  if(!s)
    return NULL;
  
  char* p = malloc(strlen(s)+1);
  strcpy(p,s);
  return p;
}

void destruir_string(void* elemento){
  if(elemento){
    free(elemento);
  }
}

bool mostrar_patente(hash_t* hash, const char* clave, void* aux){
  if(!clave)
    return true;

  aux=aux;
  hash=hash;
  
  printf("Patente en el hash: %s\n", clave);

  return false;
}

int guardar_vehiculo(hash_t* garage, const char* patente, const char* descripcion){
  int retorno = hash_insertar(garage, patente, duplicar_string(descripcion));
  return retorno;
}

void quitar_vehiculo(hash_t* garage, const char* patente){
  int retorno = hash_quitar(garage, patente);
  printf("Retirando vehiculo patente %s: ", patente);
  printf("%s\n", retorno==0?"OK":"ERROR");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pruebas_hash_null(pa2m_t* probador){
    hash_t* garage = NULL;
    printf("*********************************************\n");
    pa2m_avisar("Pruebas con HASH NULL");
    printf("*********************************************\n");
    pa2m_asegurar(probador, "Error al insertar en hash NULL:", hash_insertar(garage, "AC123BD", "Auto de Mariano") == -1);
    pa2m_asegurar(probador, "Error al quitar en hash NULL:", hash_quitar(garage, "AC123BD") == -1);
    pa2m_asegurar(probador, "NULL al obtener en hash NULL:", hash_obtener(garage, "AC123BD") ==   NULL);
    pa2m_asegurar(probador, "False al ver si contiene en hash NULL:", hash_contiene(garage, "AC123BD") ==  false);
    pa2m_asegurar(probador, "Devuelve que tiene 0 elementos un hash NULL:", hash_cantidad(garage) == 0);
    pa2m_asegurar(probador, "Error al usar iterador interno con hash NULL:", hash_con_cada_clave(garage, mostrar_patente, NULL) == 0);
    pa2m_asegurar(probador, "Error al crear el iterador externo:", hash_iterador_crear(garage) == NULL);
    hash_destruir(garage);
    printf("*********************************************\n");
    pa2m_mostrar_estadisticas(probador);
    printf("*********************************************\n");
}
void pruebas_hash_vacio(pa2m_t* probador){
    hash_t* garage = hash_crear(destruir_string, 3);
    printf("*********************************************\n");
    pa2m_avisar("Pruebas con HASH VACIO");
    printf("*********************************************\n");
    pa2m_asegurar(probador, "Error al quitar en hash VACIO:", hash_quitar(garage, "AC123BD") == -1);
    pa2m_asegurar(probador, "Exito al insertar en hash vacio:", guardar_vehiculo(garage, "AC123BD", "Auto de Mariano") == 0);
    pa2m_asegurar(probador, "True al ver si contiene en hash el elemento recien ingresado:", hash_contiene(garage, "AC123BD") ==  true);
    pa2m_asegurar(probador, "Hash obtener devuelve diferente a NULL:", hash_obtener(garage, "AC123BD") != NULL);
    pa2m_asegurar(probador, "Hash cantidad devuelve que tiene un elemento:", hash_cantidad(garage) == 1);
    pa2m_asegurar(probador, "Exito al quitar en hash:", hash_quitar(garage, "AC123BD") == 0);
    pa2m_asegurar(probador, "False al ver si contiene en hash el elemento eliminado:", hash_contiene(garage, "AC123BD") ==  false);
    pa2m_asegurar(probador, "NULL al obtener en hash VACIO:", hash_obtener(garage, "AC123BD") ==   NULL);
    pa2m_asegurar(probador, "Hash cantidad devuelve que tiene 0 elementos:", hash_cantidad(garage) == 0);
    pa2m_asegurar(probador, "Exito al insertar en hash:", guardar_vehiculo(garage, "AC123BD", "Auto de Mariano") == 0);
    pa2m_asegurar(probador, "Exito al insertar en hash:", guardar_vehiculo(garage, "A421ACB", "Moto de Manu") == 0);
    pa2m_asegurar(probador, "Exito al insertar en hash:", guardar_vehiculo(garage, "OPQ976", "Auto de Lucas") == 0);
    printf("Uso el iterador interno:\n");
    size_t impresas = hash_con_cada_clave(garage, mostrar_patente, NULL);
    pa2m_asegurar(probador, "Se mostraron los 3 elementos con el iterador interno:", impresas == 3);
    printf("Uso el iterador externo:\n");
    hash_iterador_t* iterador = hash_iterador_crear(garage);
    size_t listados = 0;

    while(hash_iterador_tiene_siguiente(iterador)){
        const char* clave = hash_iterador_siguiente(iterador);
        if(clave){
        listados++;
        printf("Patente: %s -- Vehiculo: %s\n", clave, (char*)hash_obtener(garage, clave));
        }
    }
    pa2m_asegurar(probador, "Se mostraron los 3 elementos con el iterador interno:", listados == hash_cantidad(garage));
    hash_iterador_destruir(iterador);
    pa2m_asegurar(probador, "Exito al quitar en hash:", hash_quitar(garage, "AC123BD") == 0);
    pa2m_asegurar(probador, "Exito al quitar en hash:", hash_quitar(garage, "A421ACB") == 0);
    pa2m_asegurar(probador, "Exito al quitar en hash:", hash_quitar(garage, "OPQ976") == 0);
    printf("*********************************************\n");
    pa2m_mostrar_estadisticas(probador);
    printf("*********************************************\n");
    hash_destruir(garage);
}
void pruebas_hash_gran_cantidad_elementos(pa2m_t* probador){
    hash_t* garage = hash_crear(destruir_string, 3);
    printf("*********************************************\n");
    pa2m_avisar("Pruebas con gran cantidad de elementos");
    printf("*********************************************\n");
    guardar_vehiculo(garage, "AC123BD", "Auto de Mariano");
    guardar_vehiculo(garage, "OPQ976", "Auto de Lucas");
    guardar_vehiculo(garage, "A421ACB", "Moto de Manu");
    guardar_vehiculo(garage, "AA442CD", "Auto de Guido");
    guardar_vehiculo(garage, "AC152AD", "Auto de Agustina");
    guardar_vehiculo(garage, "DZE443", "Auto de Jonathan");
    guardar_vehiculo(garage, "AA436BA", "Auto de Gonzalo");
    guardar_vehiculo(garage, "QDM443", "Auto de Daniela");
    guardar_vehiculo(garage, "BD123AC", "Auto de Pablo");
    guardar_vehiculo(garage, "CD442AA", "Auto de Micaela");
    guardar_vehiculo(garage, "PQO697", "Auto de Juan");
    guardar_vehiculo(garage, "DZE443", "Auto de Jonathan otra vez");
    guardar_vehiculo(garage, "AC152AD", "Auto de Agustina otra vez");
    guardar_vehiculo(garage, "AC123BDA", "Auto de Mariano");
    guardar_vehiculo(garage, "OPQ976A", "Auto de Lucas");
    guardar_vehiculo(garage, "A421ACBA", "Moto de Manu");
    guardar_vehiculo(garage, "AA442CDA", "Auto de Guido");
    guardar_vehiculo(garage, "AC152ADA", "Auto de Agustina");
    guardar_vehiculo(garage, "DZE443A", "Auto de Jonathan");
    guardar_vehiculo(garage, "AA436BAA", "Auto de Gonzalo");
    guardar_vehiculo(garage, "QDM443A", "Auto de Daniela");
    guardar_vehiculo(garage, "BD123ACA", "Auto de Pablo");
    guardar_vehiculo(garage, "CD442AAA", "Auto de Micaela");
    guardar_vehiculo(garage, "PQO697A", "Auto de Juan");
    guardar_vehiculo(garage, "DZE443A", "Auto de Jonathan otra vez");
    guardar_vehiculo(garage, "AC152ADA", "Auto de Agustina otra vez");
    guardar_vehiculo(garage, "AC123BDB", "Auto de Mariano");
    guardar_vehiculo(garage, "OPQ976B", "Auto de Lucas");
    guardar_vehiculo(garage, "A421ACBB", "Moto de Manu");
    guardar_vehiculo(garage, "AA442CDB", "Auto de Guido");
    guardar_vehiculo(garage, "AC152ADB", "3Auto de Agustina");
    guardar_vehiculo(garage, "DZE443B", "Auto de Jonathan");
    guardar_vehiculo(garage, "AA436BAB", "Auto de Gonzalo");
    guardar_vehiculo(garage, "QDM443B", "Auto de Daniela");
    guardar_vehiculo(garage, "BD123ACB", "Auto de Pablo");
    guardar_vehiculo(garage, "CD442AAB", "Auto de Micaela");
    guardar_vehiculo(garage, "PQO697B", "Auto de Juan");
    guardar_vehiculo(garage, "DZE443B", "Auto de Jonathan otra vez");
    guardar_vehiculo(garage, "AC152ADB", "Auto de Agustina otra vez");
    guardar_vehiculo(garage, "AC123BDAB", "Auto de Mariano");
    guardar_vehiculo(garage, "OPQ976AB", "Auto de Lucas");
    guardar_vehiculo(garage, "A421ACBAB", "Moto de Manu");
    guardar_vehiculo(garage, "AA442CDAB", "Auto de Guido");
    guardar_vehiculo(garage, "AC152ADAB", "Auto de Agustina");
    guardar_vehiculo(garage, "DZE443AB", "Auto de Jonathan");
    guardar_vehiculo(garage, "AA436BAAB", "Auto de Gonzalo");
    guardar_vehiculo(garage, "QDM443AB", "Auto de Daniela");
    guardar_vehiculo(garage, "BD123ACAB", "Auto de Pablo");
    guardar_vehiculo(garage, "CD442AAAB", "Auto de Micaela");
    guardar_vehiculo(garage, "PQO697AB", "Auto de Juan");
    guardar_vehiculo(garage, "DZE443AB", "Auto de Jonathan otra vez");
    guardar_vehiculo(garage, "AC152ADAB", "Auto de Agustina otra vez");
    guardar_vehiculo(garage, "AC123BDC", "Auto de Mariano");
    guardar_vehiculo(garage, "OPQ976C", "Auto de Lucas");
    guardar_vehiculo(garage, "A421ACBC", "Moto de Manu");
    guardar_vehiculo(garage, "AA442CDC", "Auto de Guido");
    guardar_vehiculo(garage, "AC152ADC", "Auto de Agustina");
    guardar_vehiculo(garage, "DZE443C", "Auto de Jonathan");
    guardar_vehiculo(garage, "AA436BAC", "Auto de Gonzalo");
    guardar_vehiculo(garage, "QDM443C", "Auto de Daniela");
    guardar_vehiculo(garage, "BD123ACC", "Auto de Pablo");
    guardar_vehiculo(garage, "CD442AAC", "Auto de Micaela");
    guardar_vehiculo(garage, "PQO697C", "Auto de Juan");
    guardar_vehiculo(garage, "DZE443C", "Auto de Jonathan otra vez");
    guardar_vehiculo(garage, "AC152ADC", "Auto de Agustina otra vez");
    guardar_vehiculo(garage, "AC123BDAC", "Auto de Mariano");
    guardar_vehiculo(garage, "OPQ976AC", "Auto de Lucas");
    guardar_vehiculo(garage, "A421ACBAC", "Moto de Manu");
    guardar_vehiculo(garage, "AA442CDAC", "Auto de Guido");
    guardar_vehiculo(garage, "AC152ADAC", "Auto de Agustina");
    guardar_vehiculo(garage, "DZE443AC", "Auto de Jonathan");
    guardar_vehiculo(garage, "AA436BAAC", "Auto de Gonzalo");
    guardar_vehiculo(garage, "QDM443AC", "Auto de Daniela");
    guardar_vehiculo(garage, "BD123ACAC", "Auto de Pablo");
    guardar_vehiculo(garage, "CD442AAAC", "Auto de Micaela");
    guardar_vehiculo(garage, "PQO697AC", "Auto de Juan");
    guardar_vehiculo(garage, "DZE443AC", "Auto de Jonathan otra vez");
    guardar_vehiculo(garage, "AC152ADAC", "Auto de Agustina otra vez");
    guardar_vehiculo(garage, "AC123BDBC", "Auto de Mariano");
    guardar_vehiculo(garage, "OPQ976BC", "Auto de Lucas");
    guardar_vehiculo(garage, "A421ACBBC", "Moto de Manu");
    guardar_vehiculo(garage, "AA442CDBC", "Auto de Guido");
    guardar_vehiculo(garage, "AC152ADBC", "Auto de Agustina");
    guardar_vehiculo(garage, "DZE443BC", "Auto de Jonathan");
    guardar_vehiculo(garage, "AA436BABC", "Auto de Gonzalo");
    guardar_vehiculo(garage, "QDM443BC", "Auto de Daniela");
    guardar_vehiculo(garage, "BD123ACBC", "Auto de Pablo");
    guardar_vehiculo(garage, "CD442AABC", "Auto de Micaela");
    guardar_vehiculo(garage, "PQO697BC", "Auto de Juan");
    guardar_vehiculo(garage, "DZE443BC", "Auto de Jonathan otra vez");
    guardar_vehiculo(garage, "AC152ADBC", "Auto de Agustina otra vez");
    guardar_vehiculo(garage, "AC123BDABC", "Auto de Mariano");
    guardar_vehiculo(garage, "OPQ976ABC", "Auto de Lucas");
    guardar_vehiculo(garage, "A421ACBABC", "Moto de Manu");
    guardar_vehiculo(garage, "AA442CDABC", "Auto de Guido");
    guardar_vehiculo(garage, "AC152ADABC", "Auto de Agustina");
    guardar_vehiculo(garage, "DZE443ABC", "Auto de Jonathan");
    guardar_vehiculo(garage, "AA436BAABC", "Auto de Gonzalo");
    guardar_vehiculo(garage, "QDM443ABC", "Auto de Daniela");
    guardar_vehiculo(garage, "BD123ACABC", "Auto de Pablo");
    guardar_vehiculo(garage, "CD442AAABC", "Auto de Micaela");
    guardar_vehiculo(garage, "PQO697ABC", "Auto de Juan");
    guardar_vehiculo(garage, "DZE443ABC", "Auto de Jonathan otra vez");
    guardar_vehiculo(garage, "AC152ADABC", "Auto de Agustina otra vez");
    pa2m_asegurar(probador, "Hash contiene los 88 elementos ingresados:", hash_cantidad(garage) == 88);
    
    printf("Uso el iterador interno:\n");
    size_t impresas = hash_con_cada_clave(garage, mostrar_patente, NULL);
    pa2m_asegurar(probador, "Se mostraron los 88 elementos con el iterador interno:", impresas == 88);
    printf("Uso el iterador externo:\n");
    hash_iterador_t* iterador = hash_iterador_crear(garage);
    size_t listados = 0;

    while(hash_iterador_tiene_siguiente(iterador)){
        const char* clave = hash_iterador_siguiente(iterador);
        if(clave){
        listados++;
        printf("Patente: %s -- Vehiculo: %s\n", clave, (char*)hash_obtener(garage, clave));
        }
    }
    pa2m_asegurar(probador, "Se mostraron los 88 elementos con el iterador interno:", listados == hash_cantidad(garage));
    hash_iterador_destruir(iterador);
    printf("*********************************************\n");
    pa2m_mostrar_estadisticas(probador);
    printf("*********************************************\n");
    hash_destruir(garage);
}
void pruebas_insertado_borrado_remplazado(pa2m_t* probador){
    hash_t* garage = hash_crear(destruir_string, 3);
    printf("*********************************************\n");
    pa2m_avisar("Pruebas de insercion/borrado/remplazar");
    printf("*********************************************\n");
    pa2m_asegurar(probador, "Exito al insertar en hash:", guardar_vehiculo(garage, "AC123BD", "Auto de Mariano") == 0);
    pa2m_asegurar(probador, "Exito al remplazar en hash:", guardar_vehiculo(garage, "AC123BD", "Auto de Ezequiel") == 0);
    pa2m_asegurar(probador, "Exito al insertar en hash:", guardar_vehiculo(garage, "OPQ976", "Auto de Lucas") == 0);
    pa2m_asegurar(probador, "Exito al remplazar en hash:", guardar_vehiculo(garage, "OPQ976", "Auto de Gabriel") == 0);
    pa2m_asegurar(probador, "Exito al insertar en hash:", guardar_vehiculo(garage, "A421ACB", "Moto de Manu") == 0);
    pa2m_asegurar(probador, "Exito al remplazar en hash:", guardar_vehiculo(garage, "A421ACB", "Moto de Rodrigo") == 0);
    hash_iterador_t* iterador = hash_iterador_crear(garage);
    size_t listados = 0;

    while(hash_iterador_tiene_siguiente(iterador)){
        const char* clave = hash_iterador_siguiente(iterador);
        if(clave){
        listados++;
        printf("Patente: %s -- Vehiculo: %s\n", clave, (char*)hash_obtener(garage, clave));
        }
    }
    pa2m_asegurar(probador, "Se mostraron los 3 elementos con el iterador interno, con las descripciones actualizadas:", listados == hash_cantidad(garage));
    hash_iterador_destruir(iterador);
    pa2m_asegurar(probador, "Exito al elimnar en hash:", hash_quitar(garage, "AC123BD") == 0);
    pa2m_asegurar(probador, "Exito al eliminar en hash:", hash_quitar(garage, "OPQ976") == 0);
    pa2m_asegurar(probador, "Exito al elimnar en hash:", hash_quitar(garage, "A421ACB") == 0);
    pa2m_asegurar(probador, "Hash cantidad devuelve que tiene 0 elementos:", hash_cantidad(garage) == 0);
    printf("*********************************************\n");
    pa2m_mostrar_estadisticas(probador);
    printf("*********************************************\n");
    hash_destruir(garage);
}
void pruebas_elemento_y_clave_vacia(pa2m_t* probador){
    hash_t* garage = hash_crear(destruir_string, 3);
    printf("*********************************************\n");
    pa2m_avisar("Pruebas con clave y elemento VACIO");
    printf("*********************************************\n");
    pa2m_asegurar(probador, "Exito al insertar en hash:", guardar_vehiculo(garage, "", "") == 0);
    pa2m_asegurar(probador, "Hash obtener devuelve un elemento diferente a NULL:", hash_obtener(garage, "") != NULL);
    pa2m_asegurar(probador, "Hash cantidad devuelve que tiene un elemento:", hash_cantidad(garage) == 1);
    pa2m_asegurar(probador, "True al ver si contiene un elemento asociado a la clave vacia:", hash_contiene(garage, "") ==  true);
    pa2m_asegurar(probador, "Exito al quitar el elemento asociado a clave vacia:", hash_quitar(garage, "") == 0);
    pa2m_asegurar(probador, "Hash cantidad devuelve que tiene 0 elementos:", hash_cantidad(garage) == 0);
    printf("*********************************************\n");
    pa2m_mostrar_estadisticas(probador);
    printf("*********************************************\n");
    hash_destruir(garage);
}
void pruebas_elemento_null(pa2m_t* probador){
    hash_t* garage = hash_crear(destruir_string, 3);
    printf("*********************************************\n");
    pa2m_avisar("Pruebas con clave VACIA y elemento NULL");
    printf("*********************************************\n");
    pa2m_asegurar(probador, "Exito al insertar en hash:", guardar_vehiculo(garage, "", NULL) == 0);
    pa2m_asegurar(probador, "Hash obtener devuelve un elemento NULL:", hash_obtener(garage, "") == NULL);
    pa2m_asegurar(probador, "Hash cantidad devuelve que tiene un elemento:", hash_cantidad(garage) == 1);
    pa2m_asegurar(probador, "True al ver si contiene un elemento asociado a la clave vacia:", hash_contiene(garage, "") ==  true);
    pa2m_asegurar(probador, "Exito al quitar el elemento asociado a clave vacia:", hash_quitar(garage, "") == 0);
    pa2m_asegurar(probador, "Hash cantidad devuelve que tiene 0 elementos:", hash_cantidad(garage) == 0);
    printf("*********************************************\n");
    pa2m_mostrar_estadisticas(probador);
    printf("*********************************************\n");
    hash_destruir(garage);
}
void pruebas_clave_null(pa2m_t* probador){
    hash_t* garage = hash_crear(destruir_string, 3);
    printf("*********************************************\n");
    pa2m_avisar("Pruebas con clave VACIA y elemento NULL");
    printf("*********************************************\n");
    char* descripcion = duplicar_string("");
    pa2m_asegurar(probador, "Error al insertar clave NULL en hash:", hash_insertar(garage, NULL, descripcion) == -1);
    destruir_string(descripcion);
    pa2m_asegurar(probador, "Hash obtener devuelve un elemento NULL:", hash_obtener(garage, NULL) == NULL);
    pa2m_asegurar(probador, "Hash cantidad devuelve que tiene 0 elementos:", hash_cantidad(garage) == 0);
    pa2m_asegurar(probador, "Hash contiene devuelve false:", hash_contiene(garage, NULL) ==  false);
    pa2m_asegurar(probador, "Error al querer quitar elemento asociado a clave NULL:", hash_quitar(garage, NULL) == -1);
    printf("*********************************************\n");
    pa2m_mostrar_estadisticas(probador);
    printf("*********************************************\n");
    hash_destruir(garage);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(){
    pa2m_t* probador = pa2m_crear();
    pruebas_hash_null(probador);
    pruebas_hash_vacio(probador);
    pruebas_hash_gran_cantidad_elementos(probador);
    pruebas_insertado_borrado_remplazado(probador);
    pruebas_elemento_y_clave_vacia(probador);
    pruebas_elemento_null(probador);
    pruebas_clave_null(probador);
    pa2m_destruir(probador);
    return 0;
}