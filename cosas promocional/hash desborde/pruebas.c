#include "pa2m.h"
#include "hash.h"
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

bool guardar_vehiculo(hash_t* garage, const char* patente, const char* descripcion){
  hash_guardar(garage, patente, duplicar_string(descripcion));
  bool retorno = hash_pertenece(garage, patente);
  return retorno;
}

void quitar_vehiculo(hash_t* garage, const char* patente){
  hash_borrar(garage, patente);
  bool retorno = hash_pertenece(garage, patente);
  printf("Retirando vehiculo patente %s: ", patente);
  printf("%s\n", retorno==0?"OK":"ERROR");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pruebas_hash_vacio(pa2m_t* probador){
    hash_t* garage = hash_crear(destruir_string);
    printf("*********************************************\n");
    pa2m_avisar("Pruebas con HASH VACIO");
    printf("*********************************************\n");
    pa2m_asegurar(probador, "Error al quitar en hash VACIO:", hash_pertenece(garage, "AC123BD") == false);
    pa2m_asegurar(probador, "Exito al insertar en hash vacio:", guardar_vehiculo(garage, "AC123BD", "Auto de Mariano") == true);
    pa2m_asegurar(probador, "True al ver si contiene en hash el elemento recien ingresado:", hash_pertenece(garage, "AC123BD") ==  true);
    pa2m_asegurar(probador, "Hash obtener devuelve diferente a NULL:", hash_obtener(garage, "AC123BD") != NULL);
    pa2m_asegurar(probador, "Hash cantidad devuelve que tiene un elemento:", hash_cantidad(garage) == 1);
    hash_borrar(garage, "AC123BD");
    pa2m_asegurar(probador, "Exito al quitar en hash:", hash_pertenece(garage, "AC123BD") == 0);
    pa2m_asegurar(probador, "NULL al obtener en hash VACIO:", hash_obtener(garage, "AC123BD") ==   NULL);
    pa2m_asegurar(probador, "Hash cantidad devuelve que tiene 0 elementos:", hash_cantidad(garage) == 0);
    pa2m_asegurar(probador, "Exito al insertar en hash:", guardar_vehiculo(garage, "AC123BD", "Auto de Mariano") == true);
    pa2m_asegurar(probador, "Exito al insertar en hash:", guardar_vehiculo(garage, "A421ACB", "Moto de Manu") == true);
    pa2m_asegurar(probador, "Exito al insertar en hash:", guardar_vehiculo(garage, "OPQ976", "Auto de Lucas") == true);
    hash_borrar(garage, "AC123BD");
    hash_borrar(garage, "A421ACB");
    hash_borrar(garage, "OPQ976");
    pa2m_asegurar(probador, "Exito al quitar en hash:", hash_pertenece(garage, "AC123BD") == false);
    pa2m_asegurar(probador, "Exito al quitar en hash:", hash_pertenece(garage, "A421ACB") == false);
    pa2m_asegurar(probador, "Exito al quitar en hash:", hash_pertenece(garage, "OPQ976") == false);
    printf("*********************************************\n");
    pa2m_mostrar_estadisticas(probador);
    printf("*********************************************\n");
    hash_destruir(garage);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pruebas_insertado_borrado_remplazado(pa2m_t* probador){
    hash_t* garage = hash_crear(destruir_string);
    printf("*********************************************\n");
    pa2m_avisar("Pruebas de insercion/borrado/remplazar");
    printf("*********************************************\n");
    pa2m_asegurar(probador, "Exito al insertar en hash:", guardar_vehiculo(garage, "AC123BD", "Auto de Mariano") == true);
    pa2m_asegurar(probador, "Exito al remplazar en hash:", guardar_vehiculo(garage, "AC123BD", "Auto de Ezequiel") == true);
    pa2m_asegurar(probador, "Exito al insertar en hash:", guardar_vehiculo(garage, "OPQ976", "Auto de Lucas") == true);
    pa2m_asegurar(probador, "Exito al remplazar en hash:", guardar_vehiculo(garage, "OPQ976", "Auto de Gabriel") == true);
    pa2m_asegurar(probador, "Exito al insertar en hash:", guardar_vehiculo(garage, "A421ACB", "Moto de Manu") == true);
    pa2m_asegurar(probador, "Exito al remplazar en hash:", guardar_vehiculo(garage, "A421ACB", "Moto de Rodrigo") == true);
    printf("Patente: %s -- Vehiculo: %s\n", "AC123BD", (char*)hash_obtener(garage, "AC123BD"));
    printf("Patente: %s -- Vehiculo: %s\n", "OPQ976", (char*)hash_obtener(garage, "OPQ976"));
    printf("Patente: %s -- Vehiculo: %s\n", "A421ACB", (char*)hash_obtener(garage, "A421ACB"));
    hash_borrar(garage, "AC123BD");
    hash_borrar(garage, "OPQ976");
    hash_borrar(garage, "A421ACB");
    pa2m_asegurar(probador, "Exito al elimnar en hash:", hash_pertenece(garage, "AC123BD") == false);
    pa2m_asegurar(probador, "Exito al eliminar en hash:", hash_pertenece(garage, "OPQ976") == false);
    pa2m_asegurar(probador, "Exito al elimnar en hash:", hash_pertenece(garage, "A421ACB") == false);
    pa2m_asegurar(probador, "Hash cantidad devuelve que tiene 0 elementos:", hash_cantidad(garage) == 0);
    printf("*********************************************\n");
    pa2m_mostrar_estadisticas(probador);
    printf("*********************************************\n");
    hash_destruir(garage);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pruebas_hash_gran_cantidad_elementos(pa2m_t* probador){
    hash_t* garage = hash_crear(destruir_string);
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
    guardar_vehiculo(garage, "AC123BDXD", "Auto de Mariano");
    guardar_vehiculo(garage, "OPQ976XD", "Auto de Lucas");
    guardar_vehiculo(garage, "A421ACBXD", "Moto de Manu");
    guardar_vehiculo(garage, "AA442CDXD", "Auto de Guido");
    guardar_vehiculo(garage, "AC152ADXD", "Auto de Agustina");
    guardar_vehiculo(garage, "DZE443XD", "Auto de Jonathan");
    guardar_vehiculo(garage, "AA436BAXD", "Auto de Gonzalo");
    guardar_vehiculo(garage, "QDM443XD", "Auto de Daniela");
    guardar_vehiculo(garage, "BD123ACXD", "Auto de Pablo");
    guardar_vehiculo(garage, "CD442AAXD", "Auto de Micaela");
    guardar_vehiculo(garage, "PQO697XD", "Auto de Juan");
    guardar_vehiculo(garage, "DZE443XD", "Auto de Jonathan otra vez");
    guardar_vehiculo(garage, "AC152ADXD", "Auto de Agustina otra vez");
    guardar_vehiculo(garage, "AC123BDAXD", "Auto de Mariano");
    guardar_vehiculo(garage, "OPQ976AXD", "Auto de Lucas");
    guardar_vehiculo(garage, "A421ACBAXD", "Moto de Manu");
    guardar_vehiculo(garage, "AA442CDAXD", "Auto de Guido");
    guardar_vehiculo(garage, "AC152ADAXD", "Auto de Agustina");
    guardar_vehiculo(garage, "DZE443AXD", "Auto de Jonathan");
    guardar_vehiculo(garage, "AA436BAAXD", "Auto de Gonzalo");
    guardar_vehiculo(garage, "QDM443AXD", "Auto de Daniela");
    guardar_vehiculo(garage, "BD123ACAXD", "Auto de Pablo");
    guardar_vehiculo(garage, "CD442AAAXD", "Auto de Micaela");
    guardar_vehiculo(garage, "PQO697AXD", "Auto de Juan");
    guardar_vehiculo(garage, "DZE443AXD", "Auto de Jonathan otra vez");
    guardar_vehiculo(garage, "AC152ADAXD", "Auto de Agustina otra vez");
    guardar_vehiculo(garage, "AC123BDBXD", "Auto de Mariano");
    guardar_vehiculo(garage, "OPQ976BXD", "Auto de Lucas");
    guardar_vehiculo(garage, "A421ACBBXD", "Moto de Manu");
    guardar_vehiculo(garage, "AA442CDBXD", "Auto de Guido");
    guardar_vehiculo(garage, "AC152ADBXD", "3Auto de Agustina");
    guardar_vehiculo(garage, "DZE443BXD", "Auto de Jonathan");
    guardar_vehiculo(garage, "AA436BABXD", "Auto de Gonzalo");
    guardar_vehiculo(garage, "QDM443BXD", "Auto de Daniela");
    guardar_vehiculo(garage, "BD123ACBXD", "Auto de Pablo");
    guardar_vehiculo(garage, "CD442AABXD", "Auto de Micaela");
    guardar_vehiculo(garage, "PQO697BXD", "Auto de Juan");
    guardar_vehiculo(garage, "DZE443BXD", "Auto de Jonathan otra vez");
    guardar_vehiculo(garage, "AC152ADBXD", "Auto de Agustina otra vez");
    guardar_vehiculo(garage, "AC123BDABXD", "Auto de Mariano");
    guardar_vehiculo(garage, "OPQ976ABXD", "Auto de Lucas");
    guardar_vehiculo(garage, "A421ACBABXD", "Moto de Manu");
    guardar_vehiculo(garage, "AA442CDABXD", "Auto de Guido");
    guardar_vehiculo(garage, "AC152ADABXD", "Auto de Agustina");
    guardar_vehiculo(garage, "DZE443ABXD", "Auto de Jonathan");
    guardar_vehiculo(garage, "AA436BAABXD", "Auto de Gonzalo");
    guardar_vehiculo(garage, "QDM443ABXD", "Auto de Daniela");
    guardar_vehiculo(garage, "BD123ACABXD", "Auto de Pablo");
    guardar_vehiculo(garage, "CD442AAABXD", "Auto de Micaela");
    guardar_vehiculo(garage, "PQO697ABXD", "Auto de Juan");
    guardar_vehiculo(garage, "DZE443ABXD", "Auto de Jonathan otra vez");
    guardar_vehiculo(garage, "AC152ADABXD", "Auto de Agustina otra vez");
    guardar_vehiculo(garage, "AC123BDCXD", "Auto de Mariano");
    guardar_vehiculo(garage, "OPQ976CXD", "Auto de Lucas");
    guardar_vehiculo(garage, "A421ACBCXD", "Moto de Manu");
    guardar_vehiculo(garage, "AA442CDCXD", "Auto de Guido");
    guardar_vehiculo(garage, "AC152ADCXD", "Auto de Agustina");
    guardar_vehiculo(garage, "DZE443CXD", "Auto de Jonathan");
    guardar_vehiculo(garage, "AA436BACXD", "Auto de Gonzalo");
    guardar_vehiculo(garage, "QDM443CXD", "Auto de Daniela");
    guardar_vehiculo(garage, "BD123ACCXD", "Auto de Pablo");
    guardar_vehiculo(garage, "CD442AACXD", "Auto de Micaela");
    guardar_vehiculo(garage, "PQO697CXD", "Auto de Juan");
    guardar_vehiculo(garage, "DZE443CXD", "Auto de Jonathan otra vez");
    guardar_vehiculo(garage, "AC152ADCXD", "Auto de Agustina otra vez");
    guardar_vehiculo(garage, "AC123BDACXD", "Auto de Mariano");
    guardar_vehiculo(garage, "OPQ976ACXD", "Auto de Lucas");
    guardar_vehiculo(garage, "A421ACBACXD", "Moto de Manu");
    guardar_vehiculo(garage, "AA442CDACXD", "Auto de Guido");
    guardar_vehiculo(garage, "AC152ADACXD", "Auto de Agustina");
    guardar_vehiculo(garage, "DZE443ACXD", "Auto de Jonathan");
    guardar_vehiculo(garage, "AA436BAACXD", "Auto de Gonzalo");
    guardar_vehiculo(garage, "QDM443ACXD", "Auto de Daniela");
    guardar_vehiculo(garage, "BD123ACACXD", "Auto de Pablo");
    guardar_vehiculo(garage, "CD442AAACXD", "Auto de Micaela");
    guardar_vehiculo(garage, "PQO697ACXD", "Auto de Juan");
    guardar_vehiculo(garage, "DZE443ACXD", "Auto de Jonathan otra vez");
    guardar_vehiculo(garage, "AC152ADACXD", "Auto de Agustina otra vez");
    guardar_vehiculo(garage, "AC123BDBCXD", "Auto de Mariano");
    guardar_vehiculo(garage, "OPQ976BCXD", "Auto de Lucas");
    guardar_vehiculo(garage, "A421ACBBCXD", "Moto de Manu");
    guardar_vehiculo(garage, "AA442CDBCXD", "Auto de Guido");
    guardar_vehiculo(garage, "AC152ADBCXD", "Auto de Agustina");
    guardar_vehiculo(garage, "DZE443BCXD", "Auto de Jonathan");
    guardar_vehiculo(garage, "AA436BABCXD", "Auto de Gonzalo");
    guardar_vehiculo(garage, "QDM443BCXD", "Auto de Daniela");
    guardar_vehiculo(garage, "BD123ACBCXD", "Auto de Pablo");
    guardar_vehiculo(garage, "CD442AABCXD", "Auto de Micaela");
    guardar_vehiculo(garage, "PQO697BCXD", "Auto de Juan");
    guardar_vehiculo(garage, "DZE443BCXD", "Auto de Jonathan otra vez");
    guardar_vehiculo(garage, "AC152ADBCXD", "Auto de Agustina otra vez");
    guardar_vehiculo(garage, "AC123BDABCXD", "Auto de Mariano");
    guardar_vehiculo(garage, "OPQ976ABCXD", "Auto de Lucas");
    guardar_vehiculo(garage, "A421ACBABCXD", "Moto de Manu");
    guardar_vehiculo(garage, "AA442CDABCXD", "Auto de Guido");
    guardar_vehiculo(garage, "AC152ADABCXD", "Auto de Agustina");
    guardar_vehiculo(garage, "DZE443ABCXD", "Auto de Jonathan");
    guardar_vehiculo(garage, "AA436BAABCXD", "Auto de Gonzalo");
    guardar_vehiculo(garage, "QDM443ABCXD", "Auto de Daniela");
    guardar_vehiculo(garage, "BD123ACABCXD", "Auto de Pablo");
    guardar_vehiculo(garage, "CD442AAABCXD", "Auto de Micaela");
    guardar_vehiculo(garage, "PQO697ABCXD", "Auto de Juan");
    guardar_vehiculo(garage, "DZE443ABCXD", "Auto de Jonathan otra vez");
    guardar_vehiculo(garage, "AC152ADABCXD", "Auto de Agustina otra vez");
    printf("%zu\n", hash_cantidad(garage));
    pa2m_asegurar(probador, "Hash contiene los 88 elementos ingresados:", hash_cantidad(garage) == 176);
    printf("*********************************************\n");
    pa2m_mostrar_estadisticas(probador);
    printf("*********************************************\n");
    hash_destruir(garage);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(){
    pa2m_t* probador = pa2m_crear();
    //pruebas_hash_null(probador);
    pruebas_hash_vacio(probador);
    pruebas_hash_gran_cantidad_elementos(probador);
    pruebas_insertado_borrado_remplazado(probador);
    /*pruebas_elemento_y_clave_vacia(probador);
    pruebas_elemento_null(probador);
    pruebas_clave_null(probador);*/
    pa2m_destruir(probador);
    return 0;
}