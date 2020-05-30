------------------------------------README------------------------------------------------
------------------------------------------------------------------------------------------
El trabajo es basicamente un TDA o tipo de dato abstracto elaborado con nodos, que permite 
guardar varios tipos de datos y su limite de capacidad esta determinado por la cantidad 
de memoria ram libre en la computadora ejecutante.
------------------------------------------------------------------------------------------
--------------------------------LINEA DE EJECUCION----------------------------------------
Para utilizar esta implementacion sera igual al uso de bibliotecas de la libreria estandar
de C.
#include "lista.h"
Ademas de agregar en la linea de compilacion:
gcc tuprograma.c -- y agregas -- lista.c
------------------------------------------------------------------------------------------
----------------------------------FUNCIONAMIENTO------------------------------------------
Basicamente es una "Lista", que tiene punteros a un nodo inicial y final, ademas de la cantidad
de nodos existentes. Los nodos son otro tipo de dato que contienen un elemento como *void
para permitir que el usuario por usar la lista para el tipo de dato deseado sin tener que adaptarla,
ademas tiene dentro la direccion hacia el nodo siguiente, que permitira recorrer la lista.
Se usan nodos en su implementacion ya que permiten mayor "optimizacion" en el uso de recursos.
Ademas dentro de lista.h se cuenta con un ierador externo y un interno para permitirle al usuario
recorrerla como necesite. 
Dato Importante = No solo cuenta con funciones de lista, sino que ademas si desea utilizarse
como una cola o un pila (que no son mas que tipos especificos de lista), dentro de la implementacion 
cuentan con funciones especificas para esos usos.
------------------------------------------------------------------------------------------
----------------------------------TEORIA--------------------------------------------------
Una lista es un conjunto de elementos uno tras otro, conectados a traves de punteros entre si (en el caso de implementacion
 de nodos) y su asignacion de memoria transcurre durante el periodo de ejecucion. 

La principal diferencia entre una lista simple y doble enlazada, esta que en uns lita simplemente enlazada
solo puede recorrersela hacia adelante, del principio al final, esto gracias a los nodos que cuentan contienenun puntero 
hacia al siguiente, ahora en una doblemente enlazada los nodos cuentan con direccion al siguiente y al anterior
por lo que se podria desplazarse desde el principio al final o desde el final al principio.

Una Pila es un tipo de lista con caracteristicas especificas, en estas los elementos solo entran
por el final y salen por el final (LIFO, Last In First Out).
La Cola tambiene es un tipo de lista con caracteristicas especificas, aca los elementos entran por el final y sale por el principio
(FIFO, First In First Out).

Un iterador es un elemento que le permite al programador o al usuario de laimplementacion recorrer algo,
este este caso una lista.

El iterador interno ya esta definido por el creador, en cambio el iterador interno, gracias a su
implementacion diferente permite al usuario de dicho iterador mas libertades en cuanto a la forma
en que funcionara.
------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------