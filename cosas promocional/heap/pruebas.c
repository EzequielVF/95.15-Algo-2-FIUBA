#include <stdlib.h>
#include <stdio.h>
#include <string.h>
////////////////////////////////////////////////////
/*int cmp_num (const void *a, const void *b){
	if (*(int*)a > *(int*)b){
		return 1;
	}else if (*(int*)a < *(int*)b){
		return -1;
	}
	return 0;
}*/
////////////////////////////////////////////////////////////////////////
void downheap(int* vector, int n, int pos){
	if(n <= pos){
		return;
	}
    int aux;
	int max      = pos;
	int hijo_izq = 2*pos + 1;
	int hijo_der = 2*pos + 2; //hijo_izq + 1
	if((hijo_izq < n) && (vector[hijo_izq] > vector[max])){  /// cambiando los ">" por "<" se pasa de un heap maximal a uno minimal.
		max = hijo_izq;
	}
	if((hijo_der < n) && (vector[hijo_der] > vector[max])){
		max = hijo_der;
	}
	if(max != pos){
        //--------SWAP---------//
        aux = vector[max];
        vector[max] = vector[pos];
        vector[pos] = aux;
        //----------------------//
		downheap(vector, n, max);
	}
}
//////////////////////////////////////////////////////////////////////////
void heapify(int* vector, int n){
	for(int i = (n-1)/2; i >= 0; i--){
		downheap(vector, n, i);
	}		
}
//////////////////////////////////////////////////////////////////////////
void heap_sort(int* vector, int cant){
	heapify(vector,cant);
	int n = cant-1;
    int aux;
	for(int i = n; i > 0; i--){
        //--------SWAP---------//
        aux = vector[0];
        vector[0] = vector[i];
        vector[i] = aux;
        //----------------------//
		downheap(vector, i, 0);
	}
}
//////////////////////////////////////////////////////////////////////////
int main(){

    int arreglo[15] = {32, 30, 70, 45, 1, 25, 3, 2, 9, 11, 6, 45, 4};
    int cantidad = sizeof(arreglo)/sizeof(int);
    int *vector = malloc(sizeof(int)*cantidad);
    for(int i = 0; i< cantidad; i++){
        vector[i] = arreglo[i];
    }
    printf("Vector original------>");
    for(int i = 0; i<cantidad; i++){
        printf("%i-", vector[i]);
    }
    printf("\n");

    heapify(vector, cantidad);

    printf("Vector post-heapify-->");
    for(int i = 0; i<cantidad; i++){
        printf("%i-", vector[i]);
    }
    printf("\n");

    heap_sort(vector, cantidad);

    printf("Vector post-heapsort->");
    for(int i = 0; i<cantidad; i++){
        printf("%i-", vector[i]);
    }
    printf("\n");

    return 0;
}