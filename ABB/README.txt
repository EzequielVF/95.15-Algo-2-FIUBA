------------------------------------README------------------------------------------------
------------------------------------------------------------------------------------------
El trabajo es basicamente un TDA o tipo de dato abstracto elaborado con nodos en forma de 
"arbol binario (nodos con hijos a derecha y izquierda)", 
que permite almacenar varios elementos (el limite es la cantidad de memoria 
disponible) ademas de facil acceso a los mismos una ves guardados.
------------------------------------------------------------------------------------------
--------------------------------LINEA DE COMPILACION--------------------------------------
Para utilizar esta implementacion sera igual al uso de bibliotecas de la libreria estandar
de C.
#include "abb.h"
Ademas de agregar en la linea de compilacion:
gcc tuprograma.c -- y agregar -- abb.c
Linea de ejecucion: ./a.out o el nombre elegido usando en la linea de compilacion -o nombre
------------------------------------------------------------------------------------------
----------------------------------TEORIA--------------------------------------------------
Un ABB es un Arbol de Busqueda Binario, es una estructura de nodos en la que de cada nodo 
puede colgar 2, 1 o ningun hijo, cada uno de estos nodos puede contener cualquier tipo de
elementos y a diferencia de un Arbol Binario normal en el ABB se sigue un patron al insertar
que lo vuelve util a la hora de manejar varios elementos a la vez.

Una funcion de destruccion en el TDA permitiria que el mismo arbol pudiera ir eliminando los
elementos almacenados en su interior a medida que el usuario lo requiera, sin un destructor
llos tipos de datos complejos solo serian eliminados d ela estructura del arbol pero no de 
la memoria produciendo perdidas de esta en la implementacion del usuario del arbol.

//Complejidades//

arbol_crear es O(1), ya que son solo asignaciones y un malloc.

arbol_raiz es O(1), ya que lo unico que hace es un return.

arbol_vacio es O(1), al igual que el anterior solo tiene un return dentro de un if.

arbol_recorrido_inorden/postorden/preorden son O(N), ya que basicamente recorren todo el arbol, 
si recorren todos los elementos significa que recorren los n espacios del arbol, por eso O(N).

arbol_destruir es O(N + M), al igual que los recorridos, esta funcion recorrera todos los elementos
prsententes y los eliminara, el O(N) es por recorrer, y el O(M) es la complejidad de la funcion destructor
que nos pase el usuario.

abb_con_cada elemento es O(N) al igual que los recorridos, recorre todo el arbol en el peor de los casos.

arbol_buscar es O(N) en el caso de un arbol "degenerado", donde todos sus elementos estan siempre hacia al
mismo lado, seria O(N) ya que para llegar al ultimo elemento deberia recorrer todos los elementos
presentes anets que el. En el caso de que el arbol estuviese equilibrado, por teorema maestro
diria que su complejidad es O(log n).

arbol_insertar es O(N) al igual que el buscar en un arbol degenerado, para lograr insertar un elemento
en la ultima posicion debera recorrer todos los elementos anteriores hasta llegar a la ultima posicion.

arbol_borrar es O(N + K), porque dentro tiene varias partes que hay que tener en cuenta,
la parte del buscar_nodo es O(N) en el caso de un arbol degenerado en lista (serie el peor caso),
luego tiene la parte del borrado, la cual mas compleja algoritmicamente es cuando se da el caso de
2 hijos, donde debera recorrer para encontrar a un remplazante para borrar esto seria O(M)
(aunque si seguimos pensando el caso de un arbol degenerado esta seria casi O(N)),
y luego solo faltaria la complejidad de destruir_nodo que depende de la complejidad del destructor
suministrado por el usuario O(K).
------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------