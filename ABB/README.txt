------------------------------------README------------------------------------------------
------------------------------------------------------------------------------------------
El trabajo es basicamente un TDA o tipo de dato abstracto elaborado con nodos en formal de 
"arbol", que permite almacenar varios elementos (el limite es la cantidad de memoria 
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


------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------