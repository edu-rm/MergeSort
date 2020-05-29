#include <stdio.h>
#include <stdlib.h>

void mergesort(int[]);
void display(int[]);


int main() {

    int array [] = {  1, 4, 2, 6 ,8 ,5, 3, 7 };

    printf("Array Original\n");
    display(array);

    printf("Array ordenado\n");
    display(array);

}

//dividir o vetor em 2 vetores
void mergeSort(int array[]) {
    
    //encontrar quantidade de elementos
    int n = (sizeof(array) / sizeof(array[0])); //8 
    
    if(n < 2) {
        return;
    }
    
    int middle = n / 2;
    int left [middle];
    int right [n - middle];
    int i, j;

    //0..3
    for(i = 0; i < (middle - 1); i++) {
        left[i] = array[i];
    }

    //4..7
    for(j = middle; j < (n -1); j++) {
        right[j - middle] = array[j];
    }

    mergeSort(left);
    mergeSort(right);
    merge(left, right, array);

} 

void merge(int left[], int right[], int array[]) {
    //quantidade de elemento no array left
    int nLeft = (sizeof(left) / sizeof(left[0])); //1
    //quantidade de elemento no array right
    int nRight = (sizeof(right) / sizeof(right[0])); //1
    //indices
    //i: left
    //j: right
    //k: array
    int i, j, k;
    i = j = k = 0;

    //ordenar vetores
    do{
        if(left[i] <= right[j]) {
            array[k] = left[i];
            i++;
        } else {
            array[k] = right[j];
            j++;
        }
        k++;
    }while((i < nLeft || j < nRight));
    
    if (i >= nLeft) {
        while(j < nRight) {
            array[k] = right[j];
            j++;
            k++;
        }
    } else if (j >= nRight) {
        while(i < nLeft) {
            array[k] = left[i];
            i++;
            k++;
        }
    }   
}

void display(int array []) {
    int i;
    for(i = 0; i < 8; i++) {
        printf("array[%i]: %i\n", i, array[i]);
    }
}