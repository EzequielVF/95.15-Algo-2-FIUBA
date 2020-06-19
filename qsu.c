#include <stdio.h>
#include <string.h>
/////////////////////////////////////////////////////////////////////////////////////////////////////
void imprimir_int(void* entero){
  if(!entero)
    return;

  printf("%i-", *((int*)entero));
}

void imprimir_char(void* caracter){
  if(!caracter)
    return;

  printf("%c-", *((char*)caracter));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
void mostrar_vector(void* cosas, int cantidad, size_t size, void (*imprimir)(void*)){
  for(int i=0; i<cantidad; i++){
    imprimir((char*)cosas+(i*size));
  }
  printf("\n\n");
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
int comparar_int(void* entero1, void* entero2){
  return *((int*)entero1) - *((int*)entero2);
}

int comparar_char(void* char1, void* char2){
  return *((char*)char1) - *((char*)char2);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
void swap(char* cosas, int i, int j, size_t size){
  char aux[size];
  memcpy(aux, cosas+(i*size), size);
  memcpy(cosas+(i*size), cosas+(j*size), size);
  memcpy(cosas+(j*size), aux, size);
}

int pivotear(void* cosas, int cantidad, size_t size, int (*comparador)(void*, void*)){
  int pos_pivote = cantidad-1;
  int pos_pivote_final = 0;
  char* ccosas = (char*)cosas;
  
  for(int i=0; i<pos_pivote; i++){
    if(comparador(ccosas+(i*size), ccosas+(pos_pivote*size)) < 0){
      swap(ccosas, i, pos_pivote_final, size);
      pos_pivote_final++;
    }
  }
  swap(ccosas, pos_pivote, pos_pivote_final, size);
  return pos_pivote_final;
}

void qsorte(void* cosas, int cantidad, size_t size, int (*comparador)(void*, void*)){
  if(!cosas || cantidad <= 1)
    return;

  char* ccosas = (char*)cosas; 
  int pos_pivote = pivotear(ccosas, cantidad, size, comparador);
  qsorte(ccosas, pos_pivote, size, comparador);
  qsorte(ccosas + ((pos_pivote+1)*size), cantidad - (pos_pivote+1), size, comparador);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
int main(){
  
  int cosas[] = {4,2,6,8,2,9,10,22,99,15,42};
  int cantidad = sizeof(cosas)/sizeof(int);
  char otras_cosas[] = {'h', 'f', 'A', 'M', 'g', '4', '!', '3'};
  int otra_cantidad = sizeof(otras_cosas)/sizeof(char);

  mostrar_vector(cosas, cantidad, sizeof(int), imprimir_int);
  qsorte(cosas, cantidad, sizeof(int), comparar_int);
  mostrar_vector(cosas, cantidad, sizeof(int), imprimir_int);
  
  mostrar_vector(otras_cosas, otra_cantidad, sizeof(char), imprimir_char);
  qsorte(otras_cosas, otra_cantidad, sizeof(char), comparar_char);
  mostrar_vector(otras_cosas, otra_cantidad, sizeof(char), imprimir_char);
  return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
