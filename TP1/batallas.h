#ifndef _BATALLAS_H_
#define _BATALLAS_H_
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define MAX_NOMBRE  80
#define ERROR -1
#define EXITO 0
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct pokemon {
	char nombre[MAX_NOMBRE];
	int fuerza;
	int agilidad;
	int inteligencia;
} pokemon_t;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct entrenador {
	char nombre[MAX_NOMBRE];
	pokemon_t* pokemones;
} entrenador_t;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct torneo {
	entrenador_t *entrenadores;
	int cantidad_entrenadores;
	int ronda;
} torneo_t;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Creará la estructura torneo_t, reservando la memoria necesaria para el mismo.
 * Devolverá un puntero a un torneo, en el cual los participantes ya estarán cargados.
 * En caso de no poder crearlo, o que la ruta del archivo no sea válida, devolverá NULL.
 */
torneo_t* torneo_crear(char *ruta_archivo);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Hará competir a los entrenadores, dejando en la siguiente ronda al ganador de la batalla.
 * El entrenador de la posición 0, lucha contra el de la posición 1, el de la 2 contra el de
 * la 3, etc.
 * Cuando un entrenador no tiene con quien luchar (cantidad impar de entrenadores en esa ronda) 
 * pasa directamente a la siguiente.
 * El vector de entrenadores quedará solo con aquellos que ganaron la batalla (su tamaño se 
 * ajustará luego de cada ronda).
 * Devolverá 0 si se jugó exitosamente, o -1 en caso contrario.
 * Si en el torneo hay sólo un entrenador, no se puede jugar y la funcion devuelve -1.
 */
int torneo_jugar_ronda(torneo_t* torneo, int (*ganador_batalla)(entrenador_t* ,entrenador_t*)); 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Mostrará por pantalla el nombre de cada entrenador, junto a sus pokémones.
 * Dependiendo de la función enviada por parametros (la cual refiere a una batalla), mostrará 
 * distintas caracteristicas de dichos pokémones. 
 */
void torneo_listar(torneo_t* torneo, void (*formatear_entrenador)(entrenador_t*)); 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Destruirá la estructura del torneo, liberando la memoria reservada para él y los entrenadores.
 */
void torneo_destruir(torneo_t* torneo);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif /* _BATALLAS_H_ */
