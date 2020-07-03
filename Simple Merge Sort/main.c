/* C program for Merge Sort */
#include<stdlib.h> 
#include<stdio.h> 
  

void merge(int arr[], int l, int m, int r) 
{ 
    // K = Índice do novo array

    int i, j, k; 
    
    // Tamanho do vetor L e R (length)
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    /* arrays temporários */
    int L[n1], R[n2]; 
  
    /* copiando dados para o array L[] e R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    /* Juntando os arrays temporários em arr[l..r] */
    i = 0; // índice inicial do primeiro sub array. 
    j = 0; // indíce inicial do secundo sub array 
    k = l; // Indice do array final 

    // Caso dois sub arrays de 3 elementos:
    // 3 1 5 - 4 2 6 

    // i = 1, k = 1 
    // i = 2, k = 2
    // j = 1, k = 3
    // i = 3, k = 4
    // j = 2, k = 5
    // j = 3, k = 6

    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 

        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
  

void mergeSort(int arr[], int l, int r) 
{ 
    /*
    *  só entrará no loop quando o valor do l estar 1 de diferença do valor r,
    *  em outras palavras, o array será dividido até quando os elementos chegarem a um subarray de 1 elemento.
    */

    if (l < r) 
    { 
        // Acha a metade e arredonda pra baixo
        int m = l+(r-l)/2; 
        float m1 = m+1;

        // *contador++;
        // Dividindo novamente até a condição l < r não ser atendida 
        printf("Vou entrar no primeiro mergesort:\nl = %i\nm  = %i\n\n\n", l, m); 
        mergeSort(arr, l, m); 
        printf("Vou entrar no segundo mergesort:\nm+1 = %f\nr = %i\n\n\n", m1, r); 
        mergeSort(arr, m+1, r); 
        printf("Vou entrar no merge:\nl = %i, \nm = %i,\nr = %i\n\n\n ", l, m , r); 

        // Juntando todos em um array
        merge(arr, l, m, r); 
    } 
} 

void printArray(int A[], int size) 
{ 
    int i; 
    for (i=0; i < size; i++) 
        printf("%d ", A[i]); 
    printf("\n"); 
} 

int main() 
{ 
    int arr[] = {12, 11, 13, 5}; 
    int arr_size = sizeof(arr)/sizeof(arr[0]); 

    // int* contador = malloc(sizeof(int));
    // *contador = 0 ;

    printf("Vou entrar na pilha 1 \n"); 
    printArray(arr, arr_size); 
  
    mergeSort(arr, 0, arr_size - 1); 
  
    printf("\nSorted array is \n"); 
    printArray(arr, arr_size); 
    return 0; 
} 
