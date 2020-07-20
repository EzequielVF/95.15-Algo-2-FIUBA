------------------------------------README------------------------------------------------
------------------------------------------------------------------------------------------
El trabajo entregado consiste basicamente en la implementacion del tda hash abierto mas facilmente
llamado diccionario.
Esta estructura permite guardar datos y tener un rapido acceso a ellos, gracias a la forma
en la que funciona. Esto es asi, ya que a cada clave"" se le asigna un lugar que se matendra 
durante toda la ejecucion del hash (bueno, cuando se reacomoda el tamaño del hash este cambia
de lugar pero la funcion tambien se adaptara para saber donde se a movido esa clave.).
El hash en su interior cuenta con un vector a punteros a tda listas que le permite guardar elementos
con el unico limitante de la memoria que se disponga.
------------------------------------------------------------------------------------------
--------------------------------LINEA DE COMPILACION--------------------------------------
Para utilizar esta implementacion sera igual al uso de bibliotecas de la libreria estandar
de C.

Includes necesarios:

#include "hash.h"
#include "hash_iterador.h"

tuprograma.c es el programa en que que vas a utilizar la implementacion de hash.

Linea de compilacion:
gcc tuprograma.c hash.c lista.c  -o tuprograma

Linea de ejecucion:
./tuprograma


En el caso de querer usar el archivo pruebas.c la linea de compilacion cambiara a:
gcc pruebas.c hash.c lista.c pa2m.c -o tuprograma

la linea de ejecucion se matendra sin cambios.
------------------------------------------------------------------------------------------
---------------------------------------------TEORIA---------------------------------------
Existen 2 tipos de hashes, abiertos y cerrados y su principal diferencia consiste en la forma
en que resuelven las colisiones, siendo los cerrados los que lo resuelven en su interior y los
abiertos ubicandolos dentro de una lista por cada posicion del hash correspondiente a una clave.

Los cerrados tienen 2 metodos:

Zona de desborde: Se reserva una area extra dentro del hash para guardar los elementos en los
que se presentaron colisiones.

Exploracion de posicion: Si se presenta una colicion el hash buscara alojar el elemento en el proximo
espacio disponible.

El Rehash es cuando el hash para cierto margen de carga, entonces se procede a agrandarlo
volviendoa pasar por las funcion de hash todos los elementos dentro de este para asignarles 
una posicion en de acuerdo al nuevo tamaño disponible.
Es importante ya que permite bajar la tasa de colisiones dentro del hash, y quela tasa de colisiones
se matenga baja permite mantener los buenos tiempoes de busqueda y insercion que se buscan tenercon 
la implementacion de un hash.

