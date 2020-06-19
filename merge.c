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
void apareo(void* cosas1, int cantidad1, void* cosas2, int cantidad2, size_t size, int (*comparador)(void*, void*)){
    char final[(cantidad1+cantidad2)*size];
    int i=0, j=0, k=0;
    char* ccosas1 = (char*)cosas1;
    char* ccosas2 = (char*)cosas2;

    while(i<cantidad1 && j<cantidad2){
        if(comparador(ccosas1+(i*size), ccosas2+(j*size)) <= 0){
            memcpy(final+(k*size), ccosas1+(i*size), size);
            i++;
        }else{
            memcpy(final+(k*size), ccosas2+(j*size), size);
            j++;
        }
        k++;
    }
    while(i<cantidad1){
        memcpy(final+(k*size), ccosas1+(i*size), size);
        i++;
        k++;
    }
    while(j<cantidad2){
        memcpy(final+(k*size), ccosas2+(j*size), size);
        j++;
        k++;
    }
    for(int i = 0; i<cantidad1+cantidad2; i++){
        memcpy(ccosas1+(i*size), final+(i*size), size);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
void msorte(void* cosas, int cantidad, size_t size, int (*comparador)(void*, void*)){
    if(!cosas || cantidad <= 1)
        return;
    
    char* ccosas = (char*)cosas; 
    int mitad = cantidad/2;
    msorte(ccosas, mitad, size, comparador);
    msorte(ccosas + (mitad*size), cantidad - mitad, size, comparador);
    apareo(ccosas, mitad, ccosas + (mitad*size), cantidad - mitad, size, comparador);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
int main(){
  
  int cosas[] = {4,2,6,8,2,9,10,22,99,15,42};
  int cantidad = sizeof(cosas)/sizeof(int);
  char otras_cosas[] = {'h', 'f', 'A', 'M', 'g', '4', '!', '3'};
  int otra_cantidad = sizeof(otras_cosas)/sizeof(char);
  
  mostrar_vector(cosas, cantidad, sizeof(int), imprimir_int);
  msorte(cosas, cantidad, sizeof(int), comparar_int);
  mostrar_vector(cosas, cantidad, sizeof(int), imprimir_int);

  mostrar_vector(otras_cosas, otra_cantidad, sizeof(char), imprimir_char);
  msorte(otras_cosas, otra_cantidad, sizeof(char), comparar_char);
  mostrar_vector(otras_cosas, otra_cantidad, sizeof(char), imprimir_char);
  return 0;
}

///////////////////////////////////////////////////MERGE IN PLACE NO GENERALIZADO///////////////////////////////////////////////////////////////////////
void aparaeo_inplace(int* cosas1, int cantidad1, int* cosas2, int cantidad2){ 
    int total= cantidad1+cantidad2;

    for(int i = 0, j = cantidad1; i< cantidad1 && j<total;){
        if(cosas1[i] <= cosas1[j]){
            i++;
        }else{
            int aux = cosas1[j];
            for(int k = j; k > i; k--)
                cosas1[k] = cosas1[k-1];

            cosas1[i]= aux;
            cantidad1++;
            i++;
            j++;
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////