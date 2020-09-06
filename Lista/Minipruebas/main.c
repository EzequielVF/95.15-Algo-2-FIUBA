#include "lista.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int main(){

lista_t *lista = lista_crear();
int elemento = 4;
int elemento_leido = 0;
int elemento_leido2 = 0;
bool vacia = false;
if(lista_insertar(lista, &elemento) == 0){
    printf("Se inserto correctamente\n");
}
if(lista_insertar(lista, &elemento) == 0){
    printf("Se inserto correctamente\n");
}
if(lista_insertar_en_posicion(lista, &elemento, 0) == 0){
    printf("Se inserto correctamente\n");
}
elemento_leido = *(int*)lista_ultimo(lista);
printf("%d", elemento_leido);

elemento_leido2 = *(int*)lista_elemento_en_posicion(lista, 0);
printf("%d", elemento_leido2);

if(lista_borrar(lista) == 0){
    printf("Se borro correctamente\n");
}
if(lista_borrar(lista) == 0){
    printf("Se borro correctamente\n");
}
if(lista_borrar(lista) == 0){
    printf("Se borro correctamente\n");
}
vacia = lista_vacia(lista);
if(vacia)
    printf("Vacia");

return 0;
}