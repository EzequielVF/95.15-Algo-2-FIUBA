#include <stdio.h>

void mostrar_vector(int* cosas, int cantidad){
  for(int i=0; i<cantidad; i++){
    printf("%i-", cosas[i]);
  }
  printf("\n\n");
}

void swap(int* cosas, int i, int j){
  int aux = cosas[i];
  cosas[i] = cosas[j];
  cosas[j] = aux;
}

int pivotear(int* cosas, int cantidad){
  int pos_pivote = cantidad-1;
  int pos_pivote_final = 0;
  
  for(int i=0; i<pos_pivote; i++){
    if(cosas[i] < cosas[pos_pivote]){
      swap(cosas, i, pos_pivote_final);
      pos_pivote_final++;
    }
  }
  swap(cosas, pos_pivote, pos_pivote_final);
  return pos_pivote_final;
}

void qsorte(int* cosas, int cantidad){
  if(!cosas || cantidad <= 1)
    return;
    
  int pos_pivote = pivotear(cosas, cantidad);
  qsorte(cosas, pos_pivote);
  qsorte(cosas + pos_pivote + 1, cantidad - (pos_pivote+1));
}

int main(){
  
  int cosas[] = {4,2,6,8,2,9,10,22,99,15,42};
  int cantidad = sizeof(cosas)/sizeof(int);
  
  mostrar_vector(cosas, cantidad);
  qsorte(cosas, cantidad);
  mostrar_vector(cosas, cantidad);
  return 0;
}