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
void prueba_borrado(pa2m_t* probador){
	abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
	cosa_t* c1= crear_cosa(1);
	cosa_t* c2= crear_cosa(2);
	cosa_t* c3= crear_cosa(3);
	cosa_t* c4= crear_cosa(4);
	printf("*********************************************\n");
    pa2m_avisar("Pruebas de borrado");
    printf("*********************************************\n");
	pa2m_asegurar(probador, "Puedo insertar 2:", arbol_insertar(arbol, c2) == 0);
	pa2m_asegurar(probador, "Puedo insertar 1:", arbol_insertar(arbol, c1) == 0);
	pa2m_asegurar(probador, "Puedo insertar 3:", arbol_insertar(arbol, c3) == 0);
	pa2m_asegurar(probador, "Borrado fallido, el elemento no existe:(C4)", arbol_borrar(arbol,c4) == -1);
	pa2m_asegurar(probador, "Borrado exitoso:(C2)", arbol_borrar(arbol,c2) == 0);
	c2= crear_cosa(2);
	pa2m_asegurar(probador, "Borrado fallido, el elemento ya no esta en el arbol:(C2)", arbol_borrar(arbol,c2) == -1);
	arbol_destruir(arbol);
	destructor_de_cosas(c4);
	destructor_de_cosas(c2);
    printf("*********************************************\n");
    pa2m_mostrar_estadisticas(probador);
    printf("*********************************************\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void probar_inicializacion(pa2m_t* probador){
    abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
	cosa_t* c4= crear_cosa(4);

    printf("*********************************************\n");
    pa2m_avisar("Pruebas inicializacion ARBOL");
    printf("*********************************************\n");
    pa2m_asegurar(probador, "Arbol creado exitosamente", arbol != NULL);
    pa2m_asegurar(probador, "Arbol vacio devuelve raiz NULL:", arbol_raiz(arbol) == NULL);
    pa2m_asegurar(probador, "Arbol vacio devuelve true:", arbol_vacio(arbol) == true);
    pa2m_asegurar(probador, "Puedo insertar:", arbol_insertar(arbol, c4) == 0);
    pa2m_asegurar(probador, "Arbol NO vacio devuelve false:", arbol_vacio(arbol) == false);
    pa2m_asegurar(probador, "La raiz es la adecuada:", ((cosa_t*)arbol_raiz(arbol))->clave==4);
	pa2m_asegurar(probador, "Borrado exitoso:", arbol_borrar(arbol,c4) == 0);
	pa2m_asegurar(probador, "Arbol vacio devuelve true:", arbol_vacio(arbol) == true);
	pa2m_asegurar(probador, "Arbol vacio devuelve raiz NULL:", arbol_raiz(arbol) == NULL);
    arbol_destruir(arbol);
    printf("*********************************************\n");
    pa2m_mostrar_estadisticas(probador);
    printf("*********************************************\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void probar_uso_arbol(pa2m_t* probador){
	abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
    cosa_t* c1= crear_cosa(1);
	cosa_t* c2= crear_cosa(2);
	cosa_t* c3= crear_cosa(3);
	cosa_t* c4= crear_cosa(4);
	cosa_t* c5= crear_cosa(5);
	cosa_t* c6= crear_cosa(6);
	cosa_t* c7= crear_cosa(7);

	printf("*********************************************\n");
    pa2m_avisar("Pruebas agregar elementos Arbol");
    printf("*********************************************\n");
	pa2m_asegurar(probador, "Puedo insertar 4:", arbol_insertar(arbol, c4) == 0);
	pa2m_asegurar(probador, "Puedo insertar 2:", arbol_insertar(arbol, c2) == 0);
	pa2m_asegurar(probador, "Puedo insertar 6:", arbol_insertar(arbol, c6) == 0);
	pa2m_asegurar(probador, "Puedo insertar 1:", arbol_insertar(arbol, c1) == 0);
	pa2m_asegurar(probador, "Puedo insertar 3:", arbol_insertar(arbol, c3) == 0);
	pa2m_asegurar(probador, "Puedo insertar 5:", arbol_insertar(arbol, c5) == 0);
	pa2m_asegurar(probador, "Puedo insertar 7:", arbol_insertar(arbol, c7) == 0);
	pa2m_asegurar(probador, "Elemento encontrado!", ((cosa_t*)arbol_buscar(arbol, c4))->clave==4);
	pa2m_asegurar(probador, "Elemento encontrado!", ((cosa_t*)arbol_buscar(arbol, c2))->clave==2);
	pa2m_asegurar(probador, "Elemento encontrado!", ((cosa_t*)arbol_buscar(arbol, c6))->clave==6);
	pa2m_asegurar(probador, "Elemento encontrado!", ((cosa_t*)arbol_buscar(arbol, c1))->clave==1);
	pa2m_asegurar(probador, "Elemento encontrado!", ((cosa_t*)arbol_buscar(arbol, c3))->clave==3);
	pa2m_asegurar(probador, "Elemento encontrado!", ((cosa_t*)arbol_buscar(arbol, c5))->clave==5);
	pa2m_asegurar(probador, "Elemento encontrado!", ((cosa_t*)arbol_buscar(arbol, c7))->clave==7);
	printf("*********************************************\n");
    pa2m_mostrar_estadisticas(probador);
    printf("*********************************************\n");
	printf("*********************************************\n");
    pa2m_avisar("Pruebas de reacomodacion");
    printf("*********************************************\n");
	pa2m_asegurar(probador, "Borrado exitoso(C4):", arbol_borrar(arbol,c4) == 0);
	pa2m_asegurar(probador, "La raiz es la adecuada:", ((cosa_t*)arbol_raiz(arbol))->clave==3);
	pa2m_asegurar(probador, "Borrado exitoso(C3):", arbol_borrar(arbol,c3) == 0);
	pa2m_asegurar(probador, "La raiz es la adecuada:", ((cosa_t*)arbol_raiz(arbol))->clave==2);
	pa2m_asegurar(probador, "Borrado exitoso(C6):", arbol_borrar(arbol,c6) == 0);
	pa2m_asegurar(probador, "Borrado exitoso:(C2)", arbol_borrar(arbol,c2) == 0);
	pa2m_asegurar(probador, "La raiz es la adecuada:", ((cosa_t*)arbol_raiz(arbol))->clave==1);
	pa2m_asegurar(probador, "Borrado exitoso(C1):", arbol_borrar(arbol,c1) == 0);
	pa2m_asegurar(probador, "La raiz es la adecuada:", ((cosa_t*)arbol_raiz(arbol))->clave==5);
	pa2m_asegurar(probador, "Borrado exitoso(C5):", arbol_borrar(arbol,c5) == 0);
	pa2m_asegurar(probador, "La raiz es la adecuada:", ((cosa_t*)arbol_raiz(arbol))->clave==7);
	pa2m_asegurar(probador, "Borrado exitoso(C7):", arbol_borrar(arbol,c7) == 0);
	pa2m_asegurar(probador, "Arbol vacio devuelve true:", arbol_vacio(arbol) == true);
	pa2m_asegurar(probador, "Arbol vacio devuelve raiz NULL:", arbol_raiz(arbol) == NULL);
	pa2m_asegurar(probador, "Borrado fallido, no hay elementos que borrar(C7):", arbol_borrar(arbol,c7) == -1);
	arbol_destruir(arbol);
    printf("*********************************************\n");
    pa2m_mostrar_estadisticas(probador);
    printf("*********************************************\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pruebas_recorrido(pa2m_t* probador){
	abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
    cosa_t* c1= crear_cosa(1);
	cosa_t* c2= crear_cosa(2);
	cosa_t* c3= crear_cosa(3);
	cosa_t* c4= crear_cosa(4);
	cosa_t* c5= crear_cosa(5);
	cosa_t* c6= crear_cosa(6);
	cosa_t* c7= crear_cosa(7);
	cosa_t* elementos_inorden[10];
	cosa_t* elementos_preorden[10];
	cosa_t* elementos_postorden[10];
	cosa_t* elementos_inorden2[5];
	cosa_t* elementos_preorden2[5];
	cosa_t* elementos_postorden2[5];
	int cantidad = 0;
	printf("*********************************************\n");
    pa2m_avisar("Pruebas de recorrido");
    printf("*********************************************\n");
	printf("*********************************************\n");
    pa2m_avisar("Inserto los elementos");
    printf("*********************************************\n");
	pa2m_asegurar(probador, "Inserto 4:", arbol_insertar(arbol, c4) == 0);
	pa2m_asegurar(probador, "Inserto 2:", arbol_insertar(arbol, c2) == 0);
	pa2m_asegurar(probador, "Inserto 6:", arbol_insertar(arbol, c6) == 0);
	pa2m_asegurar(probador, "Inserto 1:", arbol_insertar(arbol, c1) == 0);
	pa2m_asegurar(probador, "Inserto 3:", arbol_insertar(arbol, c3) == 0);
	pa2m_asegurar(probador, "Inserto 5:", arbol_insertar(arbol, c5) == 0);
	pa2m_asegurar(probador, "Inserto 7:", arbol_insertar(arbol, c7) == 0);
	printf("*********************************************\n");
    pa2m_mostrar_estadisticas(probador);
    printf("*********************************************\n");
	printf("*********************************************\n");
    pa2m_avisar("Pruebas de recorrido vector suficiente");
    printf("*********************************************\n");
	pa2m_avisar("Recorrido inorden:");
	cantidad = arbol_recorrido_inorden(arbol, (void**)elementos_inorden, 10);
	for(int i=0; i<cantidad; i++)
		printf("%i ", elementos_inorden[i]->clave);
	printf("\n");
	pa2m_avisar("Recorrido preorden:");
	cantidad = arbol_recorrido_preorden(arbol, (void**)elementos_preorden, 10);
	for(int i=0;i<cantidad;i++)
		printf("%i ", elementos_preorden[i]->clave);
	printf("\n");
	pa2m_avisar("Recorrido postorden:");
	cantidad = arbol_recorrido_postorden(arbol, (void**)elementos_postorden, 10);
	for(int i=0;i<cantidad;i++)
		printf("%i ", elementos_postorden[i]->clave);
	printf("\n");
	printf("*********************************************\n");
    pa2m_avisar("Pruebas de recorrido vector insuficiente");
    printf("*********************************************\n");
	pa2m_avisar("Recorrido inorden:");
	cantidad = arbol_recorrido_inorden(arbol, (void**)elementos_inorden2, 5);
	for(int i=0; i<cantidad; i++)
		printf("%i ", elementos_inorden2[i]->clave);
	printf("\n");
	pa2m_avisar("Recorrido preorden:");
	cantidad = arbol_recorrido_preorden(arbol, (void**)elementos_preorden2, 5);
	for(int i=0;i<cantidad;i++)
		printf("%i ", elementos_preorden2[i]->clave);
	printf("\n");
	pa2m_avisar("Recorrido postorden:");
	cantidad = arbol_recorrido_postorden(arbol, (void**)elementos_postorden2, 5);
	for(int i=0;i<cantidad;i++)
		printf("%i ", elementos_postorden2[i]->clave);
	printf("\n");
	arbol_destruir(arbol);
    printf("*********************************************\n");
    pa2m_mostrar_estadisticas(probador);
    printf("*********************************************\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pruebas_arbol_lleno_elementos_iguales(pa2m_t* probador){
	abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
	cosa_t* c1= crear_cosa(5);
	cosa_t* c2= crear_cosa(5);
	cosa_t* c3= crear_cosa(5);
	cosa_t* c4= crear_cosa(5);
	cosa_t* c5= crear_cosa(5);
	cosa_t* c6= crear_cosa(5);
	cosa_t* c7= crear_cosa(5);
	cosa_t* elementos_inorden[10];
	cosa_t* elementos_preorden[10];
	cosa_t* elementos_postorden[10];
	int cantidad = 0;
	printf("*********************************************\n");
    pa2m_avisar("Pruebas con arbol con elementos iguales");
    printf("*********************************************\n");
	pa2m_asegurar(probador, "Puedo insertar 4:", arbol_insertar(arbol, c4) == 0);
	pa2m_asegurar(probador, "Puedo insertar 2:", arbol_insertar(arbol, c2) == 0);
	pa2m_asegurar(probador, "Puedo insertar 6:", arbol_insertar(arbol, c6) == 0);
	pa2m_asegurar(probador, "Puedo insertar 1:", arbol_insertar(arbol, c1) == 0);
	pa2m_asegurar(probador, "Puedo insertar 3:", arbol_insertar(arbol, c3) == 0);
	pa2m_asegurar(probador, "Puedo insertar 5:", arbol_insertar(arbol, c5) == 0);
	pa2m_asegurar(probador, "Puedo insertar 7:", arbol_insertar(arbol, c7) == 0);
	pa2m_asegurar(probador, "Elemento encontrado!(C4)", ((cosa_t*)arbol_buscar(arbol, c4))->clave==5);
	pa2m_asegurar(probador, "Elemento encontrado!(C2)", ((cosa_t*)arbol_buscar(arbol, c2))->clave==5);
	pa2m_asegurar(probador, "Elemento encontrado!(C6)", ((cosa_t*)arbol_buscar(arbol, c6))->clave==5);
	pa2m_asegurar(probador, "Elemento encontrado!(C1)", ((cosa_t*)arbol_buscar(arbol, c1))->clave==5);
	pa2m_asegurar(probador, "Elemento encontrado!(C3)", ((cosa_t*)arbol_buscar(arbol, c3))->clave==5);
	pa2m_asegurar(probador, "Elemento encontrado!(C5)", ((cosa_t*)arbol_buscar(arbol, c5))->clave==5);
	pa2m_asegurar(probador, "Elemento encontrado!(C7)", ((cosa_t*)arbol_buscar(arbol, c7))->clave==5);
	pa2m_avisar("Recorrido inorden:");
	cantidad = arbol_recorrido_inorden(arbol, (void**)elementos_inorden, 10);
	for(int i=0; i<cantidad; i++)
		printf("%i ", elementos_inorden[i]->clave);
	printf("\n");
	pa2m_avisar("Recorrido preorden:");
	cantidad = arbol_recorrido_preorden(arbol, (void**)elementos_preorden, 10);
	for(int i=0;i<cantidad;i++)
		printf("%i ", elementos_preorden[i]->clave);
	printf("\n");
	pa2m_avisar("Recorrido postorden:");
	cantidad = arbol_recorrido_postorden(arbol, (void**)elementos_postorden, 10);
	for(int i=0;i<cantidad;i++)
		printf("%i ", elementos_postorden[i]->clave);
	printf("\n");
	pa2m_asegurar(probador, "Borrado exitoso:(C4)", arbol_borrar(arbol,c4) == 0);
	pa2m_asegurar(probador, "Borrado exitoso:(C2)", arbol_borrar(arbol,c2) == 0);
	pa2m_asegurar(probador, "Borrado exitoso:(C6)", arbol_borrar(arbol,c6) == 0);
	pa2m_asegurar(probador, "Borrado exitoso:(C1)", arbol_borrar(arbol,c1) == 0);
	pa2m_asegurar(probador, "Borrado exitoso:(C3)", arbol_borrar(arbol,c3) == 0);
	pa2m_asegurar(probador, "Borrado exitoso:(C5)", arbol_borrar(arbol,c5) == 0);
	pa2m_asegurar(probador, "Borrado exitoso:(C7)", arbol_borrar(arbol,c7) == 0);
	arbol_destruir(arbol);
    printf("*********************************************\n");
    pa2m_mostrar_estadisticas(probador);
    printf("*********************************************\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pruebas_con_arbol_null(pa2m_t* probador){
	abb_t* arbol = NULL;
	cosa_t* c4= crear_cosa(4);
	cosa_t* elementos_inorden[10];
	cosa_t* elementos_preorden[10];
	cosa_t* elementos_postorden[10];
	int cantidad = 0;
	printf("*********************************************\n");
    pa2m_avisar("Pruebas con arbol NULL");
    printf("*********************************************\n");
    pa2m_asegurar(probador, "Arbol NULL devuelve raiz NULL:", arbol_raiz(arbol) == NULL);
    pa2m_asegurar(probador, "Arbol NULL es vacio:", arbol_vacio(arbol) == true);
    pa2m_asegurar(probador, "Arbol NULL no puede insertar:", arbol_insertar(arbol, c4) == -1);
	pa2m_asegurar(probador, "Arbol NULL no puede borrar:", arbol_borrar(arbol,c4) == -1);
	pa2m_asegurar(probador, "Arbol NULL al buscar devuelve NULL:", arbol_buscar(arbol, c4)==NULL);
	pa2m_avisar("Recorrido inorden:");
	cantidad = arbol_recorrido_inorden(arbol, (void**)elementos_inorden, 10);
	pa2m_asegurar(probador, "Arbol NULL al querer recorrer inorden devuelve cantidad 0:", cantidad == 0);
	for(int i=0; i<cantidad; i++)
		printf("%i ", elementos_inorden[i]->clave);
	printf("\n");
	pa2m_avisar("Recorrido preorden:");
	cantidad = arbol_recorrido_preorden(arbol, (void**)elementos_preorden, 10);
	pa2m_asegurar(probador, "Arbol NULL al querer recorrer preorden devuelve cantidad 0:", cantidad == 0);
	for(int i=0;i<cantidad;i++)
		printf("%i ", elementos_preorden[i]->clave);
	printf("\n");
	pa2m_avisar("Recorrido postorden:");
	cantidad = arbol_recorrido_postorden(arbol, (void**)elementos_postorden, 10);
	pa2m_asegurar(probador, "Arbol NULL al querer recorrer postorden devuelve cantidad 0:", cantidad == 0);
	for(int i=0;i<cantidad;i++)
		printf("%i ", elementos_postorden[i]->clave);
	printf("\n");
	destructor_de_cosas(c4);
	printf("*********************************************\n");
    pa2m_mostrar_estadisticas(probador);
    printf("*********************************************\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pruebas_comparador_null(pa2m_t* probador){
	abb_t* arbol = arbol_crear(NULL, destructor_de_cosas);
	printf("*********************************************\n");
    pa2m_avisar("Pruebas con comparador NULL");
    printf("*********************************************\n");
	pa2m_asegurar(probador, "Arbol sin comparador es NULL", arbol == NULL);
	printf("*********************************************\n");
    pa2m_mostrar_estadisticas(probador);
    printf("*********************************************\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pruebas_destructor_null(pa2m_t* probador){
	abb_t* arbol = arbol_crear(comparar_cosas, NULL);
	int c4= 4;
	int c5= 5;
	
	printf("*********************************************\n");
    pa2m_avisar("Pruebas con destructor NULL");
    printf("*********************************************\n");
	pa2m_asegurar(probador, "Arbol inserta correctamente:", arbol_insertar(arbol, &c4) == 0);
	pa2m_asegurar(probador, "Arbol inserta correctamente:", arbol_insertar(arbol, &c5) == 0);
	pa2m_asegurar(probador, "Borra el nodo aunque no haya destructor:", arbol_borrar(arbol, &c4) == 0);
	pa2m_asegurar(probador, "Borra el nodo aunque no haya destructor:", arbol_borrar(arbol, &c5) == 0);
	arbol_destruir(arbol);
	printf("*********************************************\n");
    pa2m_mostrar_estadisticas(probador);
    printf("*********************************************\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool mostrar_elemento(void* elemento, void* extra){
	extra=extra;
	
	if(elemento)
		printf("%i ", ((cosa_t*)elemento)->clave);
	
	return false;
}

bool cantidad_elementos(void* elemento, void* extra){
	if(elemento && extra)
		*(int*)extra+= 1;

	return false;
}


void pruebas_iterador(pa2m_t* probador){
	abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
	cosa_t* c1= crear_cosa(1);
	cosa_t* c2= crear_cosa(2);
	cosa_t* c3= crear_cosa(3);
	cosa_t* c4= crear_cosa(4);
	cosa_t* c5= crear_cosa(5);
	cosa_t* c6= crear_cosa(6);
	cosa_t* c7= crear_cosa(7);
	int contador = 0;
	printf("*********************************************\n");
    pa2m_avisar("Pruebas con iterador");
    printf("*********************************************\n");
	pa2m_asegurar(probador, "Inserto 4:", arbol_insertar(arbol, c4) == 0);
	pa2m_asegurar(probador, "Inserto 2:", arbol_insertar(arbol, c2) == 0);
	pa2m_asegurar(probador, "Inserto 6:", arbol_insertar(arbol, c6) == 0);
	pa2m_asegurar(probador, "Inserto 1:", arbol_insertar(arbol, c1) == 0);
	pa2m_asegurar(probador, "Inserto 3:", arbol_insertar(arbol, c3) == 0);
	pa2m_asegurar(probador, "Inserto 5:", arbol_insertar(arbol, c5) == 0);
	pa2m_asegurar(probador, "Inserto 7:", arbol_insertar(arbol, c7) == 0);
	printf("Recorrido inorden iterador interno: ");    
	abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_elemento, NULL);
	printf("\n");

	printf("Recorrido preorden iterador interno: ");    
	abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_elemento, NULL);
	printf("\n");

	printf("Recorrido postorden iterador interno: ");    
	abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_elemento, NULL);
	printf("\n");

	printf("Cuento elementos INORDEN: ");    
	abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, cantidad_elementos, &contador);
	printf("%d \n", contador);
	contador = 0;
	printf("Cuento elementos PREORDEN: ");    
	abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, cantidad_elementos, &contador);
	printf("%d \n", contador);
	contador = 0;
	printf("Cuento elementos POSTORDEN: ");    
	abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, cantidad_elementos, &contador);
	printf("%d \n", contador);
	contador = 0;
	arbol_destruir(arbol);
	printf("*********************************************\n");
    pa2m_mostrar_estadisticas(probador);
    printf("*********************************************\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(){
    pa2m_t* probador = pa2m_crear();
    probar_inicializacion(probador);
	probar_uso_arbol(probador);
	prueba_borrado(probador);
	pruebas_recorrido(probador);
	pruebas_arbol_lleno_elementos_iguales(probador);
	pruebas_con_arbol_null(probador);
	pruebas_comparador_null(probador);
	pruebas_destructor_null(probador);
	pruebas_iterador(probador);
    pa2m_destruir(probador);
    return 0; 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////