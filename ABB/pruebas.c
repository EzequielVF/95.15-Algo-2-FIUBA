#include "pa2m.h"
#include "abb.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct cosa {
	int clave;
	char contenido[10];
} cosa_t;

cosa_t* crear_cosa(int clave){
	cosa_t* c = (cosa_t*)malloc(sizeof(cosa_t));
	if(c)
		c->clave = clave;
	return c;
}

void destruir_cosa(cosa_t* c){
	if(c)
		free(c);
}

int comparar_cosas(void* elemento1, void* elemento2){
	if(!elemento1 || !elemento2)
		return 0;

	if(((cosa_t*)elemento1)->clave>((cosa_t*)elemento2)->clave)
		return 1;
	
	if(((cosa_t*)elemento1)->clave<((cosa_t*)elemento2)->clave)
		return -1;
	
	return 0;
}

void destructor_de_cosas(void* elemento){
	if(!elemento)
		return;
	
	destruir_cosa((cosa_t*)elemento);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void probar_inicializacion(pa2m_t* probador){
    abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
    /*cosa_t* c1= crear_cosa(1);
	cosa_t* c2= crear_cosa(2);
	cosa_t* c3= crear_cosa(3);*/
	cosa_t* c4= crear_cosa(4);
	/*cosa_t* c5= crear_cosa(5);
	cosa_t* c6= crear_cosa(6);
	cosa_t* c7= crear_cosa(7);
    */
    printf("*********************************************\n");
    pa2m_avisar("Pruebas ARBOL");
    printf("*********************************************\n");
    pa2m_asegurar(probador, "Arbol creado exitosamente", arbol != NULL);
    pa2m_asegurar(probador, "Arbol vacio devuelve raiz NULL:", arbol_raiz(arbol) == NULL);
    pa2m_asegurar(probador, "Arbol vacio devuelve true:", arbol_vacio(arbol) == true);
    pa2m_asegurar(probador, "Puedo insertar:", arbol_insertar(arbol, c4) == 0);
    pa2m_asegurar(probador, "Arbol NO vacio devuelve false:", arbol_vacio(arbol) == false);
    pa2m_asegurar(probador, "La raiz es la adecuada:", ((cosa_t*)arbol_raiz(arbol))->clave==4);
    arbol_destruir(arbol);
    printf("*********************************************\n");
    pa2m_mostrar_estadisticas(probador);
    printf("*********************************************\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(){

    pa2m_t* probador = pa2m_crear();
    probar_inicializacion(probador);
    pa2m_destruir(probador);
    return 0; 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////