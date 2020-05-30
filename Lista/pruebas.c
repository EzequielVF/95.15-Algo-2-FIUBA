#include "pa2m.h"
#include "lista.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void probar_inicializacion_lista(pa2m_t* probador){
    lista_t* lista = lista_crear();
    printf("*********************************************\n");
    pa2m_avisar("Pruebas con lista vacia:");
    printf("*********************************************\n");
    pa2m_asegurar(probador, "Lista creada exitosamente:", lista != NULL);
    pa2m_asegurar(probador, "Lista vacia es una lista vacia:", lista_vacia(lista) == true);
    pa2m_asegurar(probador, "Lista vacia tiene 0 elementos:", lista_elementos(lista) == 0);
    pa2m_asegurar(probador, "Lista vacia no puede borrar ultimo:", lista_borrar(lista) == -1);
    pa2m_asegurar(probador, "Lista vacia no puede borrar en posicion:", lista_borrar_de_posicion(lista, 4) == -1);
    pa2m_asegurar(probador, "Lista vacia no puede listar el ultimo:", lista_ultimo(lista) == NULL);
    pa2m_asegurar(probador, "Lista vacia no puede listar en posicion 0:", lista_elemento_en_posicion(lista, 0) == NULL);
    pa2m_asegurar(probador, "Lista vacia no puede listar en posicion 2:", lista_elemento_en_posicion(lista, 2) == NULL);
    pa2m_asegurar(probador, "Lista vacia no puede listar en inicio:", lista_primero(lista) == NULL);
    lista_destruir(lista);
    printf("*********************************************\n");
    pa2m_mostrar_estadisticas(probador);
    printf("*********************************************\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void probar_inicializacion_cola(pa2m_t* probador){
    lista_t* lista = lista_crear();
    printf("*********************************************\n");
    pa2m_avisar("Pruebas con cola vacia:");
    printf("*********************************************\n");
    pa2m_asegurar(probador, "La cola vacia no puede desencolar:", lista_desencolar(lista) == -1);
    pa2m_asegurar(probador, "Cola vacia no puede listar en inicio:", lista_primero(lista) == NULL);
    pa2m_asegurar(probador, "Cola vacia esta vacia:", lista_vacia(lista) == true);
    pa2m_asegurar(probador, "Cola vacia tiene 0 elementos:", lista_elementos(lista) == 0);
    lista_destruir(lista);
    printf("*********************************************\n");
    pa2m_mostrar_estadisticas(probador);
    printf("*********************************************\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void probar_inicializacion_pila(pa2m_t* probador){
    lista_t* lista = lista_crear();
    printf("*********************************************\n");
    pa2m_avisar("Pruebas con pila vacia:");
    printf("*********************************************\n");
    pa2m_asegurar(probador, "La pila vacia no puede desapilar:", lista_desapilar(lista) == -1);
    pa2m_asegurar(probador, "Pila vacia no puede listar el ultimo elemento:", lista_ultimo(lista) == NULL);
    pa2m_asegurar(probador, "Pila vacia esta vacia:", lista_vacia(lista) == true);
    pa2m_asegurar(probador, "Pila vacia tiene 0 elementos:", lista_elementos(lista) == 0);
    lista_destruir(lista);
    printf("*********************************************\n");
    pa2m_mostrar_estadisticas(probador);
    printf("*********************************************\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pruebas_lista_nula(pa2m_t* probador){
    lista_t* lista = NULL;
    int elemento = 4;
    printf("*********************************************\n");
    pa2m_avisar("Pruebas con lista NULL:");
    printf("*********************************************\n");
    pa2m_asegurar(probador, "Lista NULL es una lista VACIA:", lista_vacia(lista) == true);
    pa2m_asegurar(probador, "Lista NULL tiene 0 elementos:", lista_elementos(lista) == 0);
    pa2m_asegurar(probador, "Lista NULL no puede borrar ultimo:", lista_borrar(lista) == -1);
    pa2m_asegurar(probador, "Lista NULL no puede borrar en posicion:", lista_borrar_de_posicion(lista, 4) == -1);
    pa2m_asegurar(probador, "Lista NULL no puede listar el ultimo:", lista_ultimo(lista) == NULL);
    pa2m_asegurar(probador, "Lista NULL no puede listar en posicion 0:", lista_elemento_en_posicion(lista, 0) == NULL);
    pa2m_asegurar(probador, "Lista NULL no puede listar en posicion 2:", lista_elemento_en_posicion(lista, 2) == NULL);
    pa2m_asegurar(probador, "Lista NULL no puede listar en inicio:", lista_primero(lista) == NULL);
    pa2m_asegurar(probador, "Lista NULL no puede insertar en el final:", lista_insertar(lista, &elemento) == -1);
    pa2m_asegurar(probador, "Lista NULL no puede insertar en principio:", lista_insertar_en_posicion(lista, &elemento, 0) == -1);
    pa2m_asegurar(probador, "Lista NULL no puede insertar en posicion:", lista_insertar_en_posicion(lista, &elemento, 2) == -1);
    pa2m_asegurar(probador, "Lista NULL no se puede crear iterador:", lista_iterador_crear(lista) == NULL);
    printf("*********************************************\n");
    pa2m_mostrar_estadisticas(probador);
    printf("*********************************************\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pruebas_cola_nula(pa2m_t* probador){
    lista_t* lista = NULL;
    int elemento = 4;
    printf("*********************************************\n");
    pa2m_avisar("Pruebas con Cola NULL:");
    printf("*********************************************\n");
    pa2m_asegurar(probador, "Cola NULL no puede desencolar:", lista_desencolar(lista) == -1);
    pa2m_asegurar(probador, "Cola NULL no puede encolar:", lista_encolar(lista, &elemento) == -1);
    pa2m_asegurar(probador, "Cola NULL no puede listar primer elemento:", lista_primero(lista) == NULL);
    pa2m_asegurar(probador, "Cola NULL es una Cola VACIA:", lista_vacia(lista) == true);
    pa2m_asegurar(probador, "Cola NULL tiene 0 elementos:", lista_elementos(lista) == 0);
    printf("*********************************************\n");
    pa2m_mostrar_estadisticas(probador);
    printf("*********************************************\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pruebas_pila_nula(pa2m_t* probador){
    lista_t* lista = NULL;
    int elemento = 4;
    printf("*********************************************\n");
    pa2m_avisar("Pruebas con Pila NULL:");
    printf("*********************************************\n");
    pa2m_asegurar(probador, "Pila NULL no puede desapilar:", lista_desapilar(lista) == -1);
    pa2m_asegurar(probador, "Pila NULL no puede apilar:", lista_apilar(lista, &elemento) == -1);
    pa2m_asegurar(probador, "Pila NULL no puede listar ultimo elemento:", lista_ultimo(lista) == NULL);
    pa2m_asegurar(probador, "Pila NULL es una Pila VACIA:", lista_vacia(lista) == true);
    pa2m_asegurar(probador, "Pila NULL tiene 0 elementos:", lista_elementos(lista) == 0);
    printf("*********************************************\n");
    pa2m_mostrar_estadisticas(probador);
    printf("*********************************************\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pruebas_lista_uso_intensivo(pa2m_t* probador){
    lista_t* lista = lista_crear();
    int elemento1 = 4;
    int elemento2 = 10;
    printf("*********************************************\n");
    pa2m_avisar("Pruebas intensivas con lista valida:");
    printf("*********************************************\n");
    pa2m_asegurar(probador, "Insertar exitosamente en lista valida:", lista_insertar(lista, &elemento1) == 0);
    pa2m_asegurar(probador, "La lista con un elemento no es vacia:", lista_vacia(lista) == false);
    pa2m_asegurar(probador, "Lista con un elemento tiene un elemento:", lista_elementos(lista) == 1);
    pa2m_asegurar(probador, "El elemento insertado en la lista es el mismo que se inserto:", (elemento1 = *(int*)lista_ultimo(lista)));
    pa2m_asegurar(probador, "Inserto al principio de la lista con insertar en posicion", lista_insertar_en_posicion(lista, &elemento2, 0) == 0);
    pa2m_asegurar(probador, "Inserto en la posicion 2 de la lista con insertar en posicion", lista_insertar_en_posicion(lista, &elemento2, 2) == 0);
    pa2m_asegurar(probador, "El elemento insertado en el inicio de la lista es el mismo que se inserto:", (elemento2 == *(int*)lista_primero(lista)));
    pa2m_asegurar(probador, "El elemento en posicion invalida es NULL:", (NULL == lista_elemento_en_posicion(lista, 3)));
    pa2m_asegurar(probador, "El elemento insertado en la posicion 2 de la lista es el correcto:", (elemento2 == *(int*)lista_elemento_en_posicion(lista, 2)));
    pa2m_asegurar(probador, "El elemento insertado al final de la lista es el que debe ser:", (elemento2 == *(int*)lista_ultimo(lista)));
    pa2m_asegurar(probador, "Lista con 3 elementos tiene 3 elementos:", lista_elementos(lista) == 3);
    pa2m_asegurar(probador, "Lista borrar funciona", lista_borrar(lista) == 0);
    pa2m_asegurar(probador, "El elemento insertado en el inicio es el correcto:", (elemento2 == *(int*)lista_primero(lista)));
    pa2m_asegurar(probador, "Lista con 2 elementos tiene 2 elementos:", lista_elementos(lista) == 2);
    pa2m_asegurar(probador, "Lista vacia no puede borrar en posicion:", lista_borrar_de_posicion(lista, 4) == 0);
    pa2m_asegurar(probador, "El elemento insertado alfinal de la lista es correcto:", (elemento1 = *(int*)lista_ultimo(lista)));
    pa2m_asegurar(probador, "Lista borrar en posicion 0 funciona", lista_borrar_de_posicion(lista, 0) == 0);
    pa2m_asegurar(probador, "La lista sin elementos es lista vacia", lista_vacia(lista) == true);
    pa2m_asegurar(probador, "Lista sin elementos no tiene elementos:", lista_elementos(lista) == 0);
    pa2m_asegurar(probador, "Lista vacia no puede borrar ultimo:", lista_borrar(lista) == -1);
    pa2m_asegurar(probador, "Lista vacia no puede borrar en posicion:", lista_borrar_de_posicion(lista, 4) == -1);
    pa2m_asegurar(probador, "Lista vacia no puede listar el ultimo:", lista_ultimo(lista) == NULL);
    pa2m_asegurar(probador, "Lista vacia no puede listar en posicion 0:", lista_elemento_en_posicion(lista, 0) == NULL);
    pa2m_asegurar(probador, "Lista vacia no puede listar en posicion 2:", lista_elemento_en_posicion(lista, 2) == NULL);
    pa2m_asegurar(probador, "Lista vacia no puede listar en inicio:", lista_primero(lista) == NULL);
    lista_destruir(lista);
    printf("*********************************************\n");
    pa2m_mostrar_estadisticas(probador);
    printf("*********************************************\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pruebas_cola_uso_intensivo(pa2m_t* probador){
    lista_t* lista = lista_crear();
    int elemento1 = 4;
    int elemento2 = 10;
    printf("*********************************************\n");
    pa2m_avisar("Pruebas intensivas con cola valida:");
    printf("*********************************************\n");
    pa2m_asegurar(probador, "Cola puede encolar:", lista_encolar(lista, &elemento1) == 0);
    pa2m_asegurar(probador, "El elemento encolado es el que tiene que ser:", (elemento1 == *(int*)lista_primero(lista)));
    pa2m_asegurar(probador, "Cola puede volver a encolar:", lista_encolar(lista, &elemento2) == 0);
    pa2m_asegurar(probador, "El elemento en el inicio es el correcto:", (elemento1 == *(int*)lista_primero(lista)));
    pa2m_asegurar(probador, "Cola con 2 elementos tiene 2 elementos:", lista_elementos(lista) == 2);
    pa2m_asegurar(probador, "Desencolar funciona", lista_desencolar(lista) == 0);
    pa2m_asegurar(probador, "Cola con 2 elementos al desencolar tiene 1 elemento:", lista_elementos(lista) == 1);
    pa2m_asegurar(probador, "Desencolar funciona nuevamente", lista_desencolar(lista) == 0);
    pa2m_asegurar(probador, "Cola ya no puede desencolar:", lista_desencolar(lista) == -1);
    pa2m_asegurar(probador, "Cola sin elementos deberia ser vacia:", lista_vacia(lista) == true);
    lista_destruir(lista);
    printf("*********************************************\n");
    pa2m_mostrar_estadisticas(probador);
    printf("*********************************************\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pruebas_pila_uso_intensivo(pa2m_t* probador){
    lista_t* lista = lista_crear();
    int elemento1 = 4;
    int elemento2 = 10;
    printf("*********************************************\n");
    pa2m_avisar("Pruebas intensivas con pila valida:");
    printf("*********************************************\n");
    pa2m_asegurar(probador, "Pila puede apilar:", lista_apilar(lista, &elemento1) == 0);
    pa2m_asegurar(probador, "El elemento apilado es el que tiene que ser:", (elemento1 == *(int*)lista_ultimo(lista)));
    pa2m_asegurar(probador, "Pila puede volver a apilar:", lista_apilar(lista, &elemento2) == 0);
    pa2m_asegurar(probador, "El elemento en el final es el correcto:", (elemento2 == *(int*)lista_ultimo(lista)));
    pa2m_asegurar(probador, "Pila con 2 elementos tiene 2 elementos:", lista_elementos(lista) == 2);
    pa2m_asegurar(probador, "Pila puede desapilar:", lista_desapilar(lista) == 0);
    pa2m_asegurar(probador, "Pila puede desapilar:", lista_desapilar(lista) == 0);
    pa2m_asegurar(probador, "Pila ya no puede desapilar:", lista_desapilar(lista) == -1);
    pa2m_asegurar(probador, "Pila sin elementos deberia ser vacia:", lista_vacia(lista) == true);
    lista_destruir(lista);
    printf("*********************************************\n");
    pa2m_mostrar_estadisticas(probador);
    printf("*********************************************\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pruebas_iterador(pa2m_t* probador){
    printf("*********************************************\n");
    pa2m_avisar("Pruebas del iterador en una lista con 3 elementos:");
    printf("*********************************************\n");
    lista_t* lista = lista_crear();
    int elemento1 = 4;
    int elemento2 = 10;
    lista_iterador_t* iterador;
    lista_insertar(lista, &elemento1);
    lista_insertar_en_posicion(lista, &elemento2, 0);
    lista_insertar_en_posicion(lista, &elemento2, 2);
    iterador = lista_iterador_crear(lista);
    pa2m_asegurar(probador, "Creacion iterador exitosa:", iterador != NULL);
    pa2m_asegurar(probador, "Iterador muestra primer elemento:", *(int*)lista_iterador_siguiente(iterador) == elemento2);
    pa2m_asegurar(probador, "Iterador muestra segundo elemento:", *(int*)lista_iterador_siguiente(iterador) == elemento1);
    pa2m_asegurar(probador, "Iterador muestra tercer elemento:", *(int*)lista_iterador_siguiente(iterador) == elemento2);
    pa2m_asegurar(probador, "Iterador muestra NULL, ya que no hay mas elementos:", lista_iterador_siguiente(iterador) == NULL);
    lista_iterador_destruir(iterador);
    lista_destruir(lista);
    printf("*********************************************\n");
    pa2m_mostrar_estadisticas(probador);
    printf("*********************************************\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(){

    pa2m_t* probador = pa2m_crear();

    probar_inicializacion_lista(probador);
    probar_inicializacion_cola(probador);
    probar_inicializacion_pila(probador);
    pruebas_lista_nula(probador);
    pruebas_cola_nula(probador);
    pruebas_pila_nula(probador);
    pruebas_lista_uso_intensivo(probador);
    pruebas_cola_uso_intensivo(probador);
    pruebas_pila_uso_intensivo(probador);
    pruebas_iterador(probador);
    pa2m_destruir(probador);
    return 0; 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////