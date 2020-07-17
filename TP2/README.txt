------------------------------------README------------------------------------------------
------------------------------------------------------------------------------------------
El trabajo realizado consiste en una especie de "pokedex", proveniente del famoso universo
Pokemon, y en su implementacion son usadas algunas estructuras basicas de almacenaje de datos
basicas como arbol de busqueda binaria y lista (junto a sus variantes como pila y cola).

La pokedex cuenta con 4 campos, el nombre del dueño de la misma, una cola y una pila donde 
en una se guardaran los pokemones vistos y en otra solo los capturados y como ultimo campo 
cuenta con un abb donde se almacenaran las diferentes especies de pokemones, sin repetir
y ordenadas en el orden en que se van descubriendo(el arbol decide izqueirda o derecha de acuerdo
al numero de la especie, siendo mas pequeña izquierda y mas grande derecha).
Dentro de estas "especies" se contara con una lista simplemente enlazada donde se guardaran los 
pokemones vistos y capturados, cada uno en su interior tendra la informacion obtenida de cada uno.

La cola y pila descriptas anteriormente tienen una particularidad, al ser revisadas estas luego
se reinician y pierden toda la informacion en su interior.

Para el funcionamiento del mismo debera contar con los 3 archivos que acompañan esta implementacion
avistamientos.txt, evoluciones.txt y pokedex.txt, estos podran ser modificados siempre y cuando se
respeten su formato basico.
------------------------------------------------------------------------------------------
--------------------------------LINEA DE COMPILACION--------------------------------------
En el caso que desee utilizar el menu que viene junto a la implementacion (main.c)
debera compilarlo con la siguiente linea:
gcc main.c pokedex.c lista.c abb.c -o menu

Si no desea usar el menu con el que viene podra usar uno creado por usted cambiando
el "main.c" de la linea anterior por el nombre de su .c.

La linea de ejecucion no variara a menos que cambie lo que se encuentra en la linea de compilacion
luego del -o. Si no realiza cambios el programa se ejecutara con ./menu, si realizo cambios
se ejecutara con ./loqueustedescribio