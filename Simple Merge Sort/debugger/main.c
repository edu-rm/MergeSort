#include <stdio.h>
#include <stdlib.h>

void mergeSort(int [], int, int);
void merge(int [], int ,int, int);
void printArray(int [], int);

int main() {
    int arr [] = { 12, 4 ,7 , 6};
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    printf("Given array is \n"); 
    printArray(arr, arr_size); 
  
    mergeSort(arr, 0, arr_size - 1); 
  
    printf("\nSorted array is \n"); 
    printArray(arr, arr_size); 
}

void mergeSort(int arr[], int left, int right) {
    printf("\n\n.........................................\n\n");
    printf("\nNova Pilha\n");
    if (left < right) 
    {  
        int middle = left + (right - left) / 2; 

        // Sort first and second halves 
        printf("Entranda Pilha: arr{ %i, %i, %i, %i } left = %i, right = %i\n", arr[0], arr[1], arr[2], arr[3], left, right);
        printf("middle: left(%i) + (right(%i) - left(%i)) / 2 = %i\n",left, right, left, middle);
        printf("arr : { %i, %i, %i, %i }\n", arr[0], arr[1], arr[2], arr[3]);
        printf("Dados: \n");
        printf("left: %i\n", left);
        printf("right: %i\n", right);
        printf("middle: %i\n", middle);
        printf("Entrando Primeiro MergeSort: mergeSort(arr, left, middle)\n");
        mergeSort(arr, left, middle);

        printf("Entranda Pilha: arr{ %i, %i, %i, %i } left = %i, right = %i\n", arr[0], arr[1], arr[2], arr[3], left, right);
        printf("middle: left(%i) + (right(%i) - left(%i)) / 2 = %i\n",left, right, left, middle);
        printf("Dados: \n");
        printf("left: %i\n", left);
        printf("right: %i\n", right);
        printf("middle: %i\n", middle);
        printf("Entrando Segundo MergeSort: (arr, middle + 1, right)\n");
        mergeSort(arr, middle + 1, right);

        
        printf("Entranda Pilha: arr{ %i, %i, %i, %i } left = %i, right = %i\n", arr[0], arr[1], arr[2], arr[3], left, right);
        printf("middle: left(%i) + (right(%i) - left(%i)) / 2 = %i\n",left, right, left, middle);
        printf("Dados: \n");
        printf("left: %i\n", left);
        printf("right: %i\n", right);
        printf("middle: %i\n", middle);
        printf("Entrando No Merge: merge(arr, left, middle, right) \n");
        merge(arr, left, middle, right); 
    } else {
        printf("NAO ENTROU EM NENHUM MERGE, POIS %i < %i\n", left, right);
        printf("\n\n.........................................\n\n");
        printf("\nPilha Anterior!\n");
    }
}

void merge(int arr[], int left, int middle, int right) {
    printf("\n\n.........................................\n\n");
    printf("\nNova Pilha - Funcao Merge\n");
    printf("Dados: \n");
    printf("arr : { %i, %i, %i, %i }\n", arr[0], arr[1], arr[2], arr[3]);
    printf("left: %i\n", left);
    printf("right: %i\n", right);
    printf("middle: %i\n", middle);
    int i, j, k;

    printf("\nDistribuindo os valores do vetor em 2 outros vetores\n");
    printf("nLeft = middle(%i) - left(%i) + 1 = %i\n", middle, left, middle - left + 1); 
    printf("nLeft = right(%i) - left(%i) = %i\n", right, middle, right - middle); 
    int nLeft = middle - left + 1; 
    int nRight =  right - middle; 
  
    /* create temp arrays */
    int L[nLeft], R[nRight];
    printf("L[nLeft = %i], R[nRight = %i]\n", nLeft, nRight); 
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < nLeft; i++) {
        printf("L[%i] = arr[%i](%i)\n", i, left + i, arr[left + i]); 
        L[i] = arr[left + i]; 
    } 
    
    for (j = 0; j < nRight; j++) {
        printf("R[%i] = arr[%i](%i)\n", j, middle + 1 + j, arr[middle + 1 + j]); 
        R[j] = arr[middle + 1 + j]; 
    }
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = left; // Initial index of merged subarray

    printf("\nORDENANDO\n");
    printf("k: left(%i) -> indice arr\n", left);
    printf("i: %i -> indice L\n", i);
    printf("j: %i -> indice R\n", j);
    
    while (i < nLeft && j < nRight) {
        printf("\nwhile(i(%i) < nLeft(%i) && j(%i) < nRight(%i))\n", i, nLeft, j, nRight); 
        printf("\tif(L[%i](%i) <= R [%i](%i)) { \n", i, L[i], j, R[j]);
        printf("\t\tarr[%i] = L[%i](%i); \n", k, i, L[i]);
        printf("\t\ti++\n");
        printf("\t} else { \n");
        printf("\t\tarr[%i] = R[%i](%i); \n\n",k , j, R[j]);
        printf("\t\tj++\n");
        printf("\t}\n\n");
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            printf("executou esse arr[%i] = L[%i](%i); \ni++\nk++\n", k, i, L[i]);
            i++; 
        } else { 
            arr[k] = R[j]; 
            printf("executou esse arr[%i] = R[%i](%i); \nj++\nk++\n", k, j, R[j]);
            j++; 
        } 
        k++; 
    }
    printf("\nFim do while !\n");
    printf("\nk: %i\n", k);
    printf("i: %i\n", i);
    printf("j: %i\n", j);
  
    /* Copy the remaining elements of L[], if there 
       are any */

    while (i < nLeft) {
        printf("\nwhile(i(%i) < nLeft(%i))\n", i, nLeft);
        printf("\tarr[%i] = L[%i](%i)", k, i, L[i]);
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */

    while (j < nRight) {
        printf("\nwhile(j(%i) < nRight(%i))\n", j, nRight);
        printf("\tarr[%i] = R[%i](%i)", k, j, R[j]);
        arr[k] = R[j]; 
        j++; 
        k++; 
    }
    printf("\nFim do while !\n");
    printf("a[0](%i), a[1](%i), a[2](%i), a[3](%i)\n", arr[0], arr[1], arr[2], arr[3]);
    printf("k: %i\n", k);
    printf("i: %i\n", i);
    printf("j: %i\n", j);
    printf("\n\n.........................................\n\n");
    printf("\nPilha Anterior !\n");
} 

void printArray(int A[], int size) { 
    int i; 
    for (i=0; i < size; i++) 
        printf("%d ", A[i]); 
    printf("\n"); 
} 