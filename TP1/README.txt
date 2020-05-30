A. 

El trabajo recibira un archivo con un formato parecido a esto...
"Ash;Pikachu;40;90;70;Charizard;76;60;90;Snorlax;200;10;10
Giovanni;Nidoqueen;100;40;90;Nidoking;160;62;76;Rhydon;180;77;42" 
(adjunte un archivo ej junto al codigo :D, puede ser agregados entrenadores sin limite, siempre y cuando se respete el formato)
Lo leera y reservara memoria para cada entrenador y sus pokemones.
Una ves que termine de leer, cerrara el archivo y se pondra "jugar rondas"
que no es otra cosa que elegir entre 6 posibles clases de rondas, en cada
rondas se eliminara la mitad de participantes, antes y despues de las rondas se 
listara a los participantes todavia  activos en el torneo, este ciclo se repetira 
hasta que solo quede un entrenador, una ves pase eso a este se lo denominara como 
ganador y se liberara lo que quede de la memoria reservada para el torneo.

B. 

Podra ser compilado con esta linea (siempre y cuando sea descomprimido en una carpeta que no contenga archivos.c ajenos a los del zip):
gcc *.c -o torneo_pokemon
y ejecutado con:
./torneo_pokemon

C.

1. Punteros: Un puntero es un tipo de variable que guarda una direccion de memoria.

Ej: al principio del main (c:40) creo un puntero a torneo_t llamado carmin y lo apunto a  NULL
para que unas lineas mas tarde (c:46) le asigno la direccion del torneo creado en memoria
reservada con los datos del archivo.

2. Aritmetica de punteros: Esto se refiere a las distintas formas de acceder a un espacio de
memoria, ya que en C un arreglo es un tipo de dato estructurado donde los elementos
estan uno detras del otro en la memoria de la computadora, el nombre de un arreglo es 
un puntero al primer elemento del mismo.

Ej: De esto no hay ejemplos en el codigo porque hice a todos de una misma forma, pero un ejemplo sencillo seria
que teniendo un:
entrenador_t* entrenadores;
entrenadores[1] estaria accediendo al entrenador n°2
y el equivalente en la otra forma seria:
*(entrenadores+1) donde tambien estaria accediendo al mismo entrenador, 
esto es asi por lo dicho anteriormente, que en C los arreglos tienen sus elementos uno detars del otro.

3. Punteros a funciones: Un puntero a una funcion es una variable que guarda la direcciona  uan funcion.
Esto tiene muchos usos porque permite luego llamar a la funcion atraves del puntero.

Ej: main(c:42 y c:43) donde creo dos punteros a funcion que apunto en un principio a NULL, para luego mediante
definir_parametros_ronda les asigno una direccion de funcion al azar para generar que cada ronda sea diferente
pero el listar tenga la misma tematica que la ejecucion de la ronda.

4. Malloc y Realloc:
Malloc se encarga de reservar la cantidad de bytes pedida y devolver un puntero a la memoria reservada,
esta no estara inicializada.
Realloc modifica el tamaño del bloque del memoria apuntado por el puntero que le pasemos, en caso
de que no haya problemas, el contenido permanecera sin cambios y la memoria extra no estara inciailizada.
Si el puntero que le pasamos es NULL realloc funcionara como un malloc, y en el caso que el nuevo tamaño sea 0
funcionara como un free.

Ej Malloc: En batallas.c (c:47) hago un malloc para reservar espacio para el torneo, luego verifico
que la direccion del puntero a la cual le habia la direccion de la memoria reservada no sea NULL
para asegurarme que no hubo problemas en la asignacion.

Ej Realloc: En batallas.c (c:59) el puntero torneo mencionado anteriormente que apuntaba a memoria reservada,
tiene en sus campos otro puntero, en este caso de tipo entrenadores_t que lo debere hacer crecer cada ves que
se lea un nuevo entrenador, y que luego en batallas.c (c:193) debere reducir a medida que los entrenadores vayan
siendo eliminados del torneo, para no tener memoria reservada sin usar.
