// C++ program to implement 
// external sorting using 
// merge sort 
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
using namespace std; 

struct MinHeapNode { 
	// The element to be stored 
	int element; 

	// index of the array from which 
	// the element is taken 
	int i; 
}; 

// Prototype of a utility function 
// to swap two min heap nodes 
void swap(MinHeapNode* x, MinHeapNode* y); 
FILE* openFile(char*, char*);
void externalSort(char*, char*, int, int);
void createInitialRuns(char*, int, int);
void mergeSort(int [], int, int);
void merge(int [], int, int, int);
void mergeFiles(char*, int);

// A class for Min Heap 
class MinHeap { 
	// pointer to array of elements in heap 
	MinHeapNode* harr; 

	// size of min heap 
	int heap_size; 

public: 
	// Constructor: creates a min 
	// heap of given size 
	MinHeap(MinHeapNode a[], int size); 

	// to heapify a subtree with 
	// root at given index 
	void MinHeapify(int); 

	// to get index of left child 
	// of node at index i 
	int left(int i) { return (2 * i + 1); } 

	// to get index of right child 
	// of node at index i 
	int right(int i) { return (2 * i + 2); } 

	// to get the root 
	MinHeapNode getMin() { return harr[0]; } 

	// to replace root with new node 
	// x and heapify() new root 
	void replaceMin(MinHeapNode x) { 
		harr[0] = x; 
		MinHeapify(0); 
	} 
}; 

// Constructor: Builds a heap from 
// a given array a[] of given size 
MinHeap::MinHeap(MinHeapNode a[], int size) { 
	heap_size = size; 
	harr = a; // store address of array 
	int i = (heap_size - 1) / 2; 
	while (i >= 0) { 
		MinHeapify(i); 
		i--; 
	} 
} 

// A recursive method to heapify 
// a subtree with root 
// at given index. This method 
// assumes that the 
// subtrees are already heapified 
void MinHeap::MinHeapify(int i) { 
	int l = left(i); 
	int r = right(i); 
	int smallest = i; 
	if (l < heap_size && harr[l].element < harr[i].element) 
		smallest = l; 
	if (r < heap_size && harr[r].element < harr[smallest].element) 
		smallest = r; 
	if (smallest != i) { 
		swap(&harr[i], &harr[smallest]); 
		MinHeapify(smallest); 
	} 
} 

// Driver program to test above 
int main() { 
	// No. of Partitions of input file. 
	int num_ways = 3; 

	// The size of each partition 
	int run_size = 3; 

	char input_file[] = "input.txt"; 
	char output_file[] = "output.txt"; 

	FILE* in = openFile(input_file, "w"); 

	srand(time(NULL)); 

	// generate input 
	printf("Arquivo Gerado simulando Memoria external(Disco Rigido)\n");
	for (int i = 0; i < num_ways * run_size; i++) {
		int x = rand() %10;
		fprintf(in, "%d ", x);
		printf("%d\n", x);
	} 

	fclose(in); 

	printf("Entrando na funcao External Sort\n");
	externalSort(input_file, output_file, num_ways, 
				run_size); 

	return 0; 
} 

FILE* openFile(char* fileName, char* mode) { 
	FILE* fp = fopen(fileName, mode); 
	if (fp == NULL) { 
		perror("Error while opening the file.\n"); 
		exit(EXIT_FAILURE); 
	} 
	return fp; 
} 

// For sorting data stored on disk 
void externalSort( 
	char* input_file, char* output_file, 
	int num_ways, int run_size) { 
	// read the input file, 
	// create the initial runs, 
	// and assign the runs to 
	// the scratch output files 
	createInitialRuns(input_file, 
					run_size, num_ways); 

	// Merge the runs using 
	// the K-way merging

	printf("\n\nEntrando no MergeFiles!\n\n"); 
	mergeFiles(output_file, num_ways); 
} 

// Using a merge-sort algorithm, 
// create the initial runs 
// and divide them evenly among 
// the output files 
void createInitialRuns( 
	char* input_file, int run_size, 
	int num_ways) { 
	printf("Entrando na funcao createInitialRuns\n");
	// For big input file 
	printf("Lendo Arquivo criado (Disco Rigido)\n");
	FILE* in = openFile(input_file, "r"); 

	// output scratch files 
	printf("Criando Vetor de tamanho %d, representa runs\n", num_ways);
	FILE* out[num_ways]; 
	char fileName[2]; 
	for (int i = 0; i < num_ways; i++) { 
		// convert i to string 
		snprintf(fileName, sizeof(fileName), 
				"%d", i); 

		// Open output files in write mode. 
		printf("Nomeando as runs (Buffers na Memoria) [%s]\n", fileName);
		out[i] = openFile(fileName, "w"); 
	} 

	// allocate a dynamic array large enough 
	// to accommodate runs of size run_size 
	int* arr = (int*)malloc( 
		run_size * sizeof(int)); 

	bool more_input = true; 
	int next_output_file = 0; 

	int i; 
	printf("\nEntrando no while ate more_input = false\n");
	while (more_input) {
		more_input == true ? printf("\n\nmore_input_atual = true\n") : printf("\n\nmore_input_atual = false\n");

		// write run_size elements 
		// into arr from input file 
		for (i = 0; i < run_size; i++) { 
			printf("\ni = %d\n", i);
			printf("run_size = %d\n", run_size);
			printf("Lendo as 3 primeiras posicoes do arquivo in e armazenando-as no array\n", i, arr[i]);
			if (fscanf(in, "%d ", &arr[i]) != 1) { 
				printf("Entrou na condicao i = %d, arr[i] = %d, more_input = false, ou seja foi um arquivo ja lido do ultimo conjunto\n", i, arr[i]);
				more_input = false; 
				break; 
			}
			printf("arr = { %d, %d, %d }\n", arr[0], arr[1], arr[2]);
		} 

		// sort array using merge sort
		printf("\nEntrando no MergeSort\n");
		printf("Parametros : arr, left = %d, right = %d\n", 0, i - 1);
		mergeSort(arr, 0, i - 1); 

		// write the records to the 
		// appropriate scratch output file 
		// can't assume that the loop 
		// runs to run_size 
		// since the last run's length 
		// may be less than run_size
		printf("\n\nSaiu do MergeSort\n");
		printf("Vetor atual\n");
		printf("next_output_file: %d\n", next_output_file);

		printf("Escrevendo nas runs (Buffers da memoria)\n");
		for (int j = 0; j < i; j++) {
			printf("j: %d\n", j);
			printf("i: %d\n", i);	
			printf("Elemento passado: %d\n", arr[j]);
			fprintf(out[next_output_file], 
					"%d ", arr[j]); 

		} 
		next_output_file++; 
	} 

	// close input and output files 
	for (int i = 0; i < num_ways; i++) 
		fclose(out[i]); 

	fclose(in); 
} 

/* l is for left index and r is right index of the 
sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r) {
	printf("\n\n.........................................\n\n");
    printf("\nNova Pilha\n");
	printf("arr = { %d, %d, %d }\n", arr[0], arr[1], arr[2]);

	printf("%d < %d ?\n", l, r);
	if (l < r) { 
		// Same as (l+r)/2, but avoids overflow for 
		// large l and h 
		int m = l + (r - l) / 2; 
		// Sort first and second halves
		printf("Calculando o meio left = %d, right = %d, meio = %d + %d / 2 = %d\n", l, r, l, r, m);
		printf("Entrando Primeiro Merge\n");
		printf("left = %d\n", l);
		printf("right = %d\n", r);
		printf("middle = %d\n", m);
		printf("Parametros: arr, left, middle\n");
		mergeSort(arr, l, m);
		 

		printf("Entrando Segundo Merge\n");
		printf("left = %d\n", l);
		printf("right = %d\n", r);
		printf("middle = %d\n", m);
		printf("Parametros: arr, middle + 1, right\n");
		mergeSort(arr, m + 1, r);

		printf("Entrando no Merge\n");
		printf("left = %d\n", l);
		printf("right = %d\n", r);
		printf("middle = %d\n", m);
		merge(arr, l, m, r); 
	} else {
		printf("NAO ENTROU EM NENHUM MERGE, POIS %i >= %i\n", l, r);
        printf("\n\n.........................................\n\n");
        printf("\nPilha Anterior!\n");
	}
}

// Merges two subarrays of arr[]. 
// First subarray is arr[l..m] 
// Second subarray is arr[m+1..r] 
void merge(int arr[], int l, int m, int r) { 
	printf("\n\n.........................................\n\n");
    printf("\nNova Pilha - Funcao Merge\n");
	printf("left: %i\n", l);
    printf("right: %i\n", r);
    printf("middle: %i\n", m);
	int i, j, k; 
	int n1 = m - l + 1; 
	int n2 = r - m;
	printf("N1: %d\n", n1);
	printf("N2: %d\n", n2);
	printf("Tamanho de do vetor L = %d, R = %d\n", n1, n2);

	/* create temp arrays */
	int L[n1], R[n2]; 

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++) {
		L[i] = arr[l + i]; 
		printf("L[%d] = %d\n", i, L[i]);
	}
	for (j = 0; j < n2; j++) {
		R[j] = arr[m + 1 + j]; 
		printf("R[%d] = %d\n", j, R[j]);
	}

	/* Merge the temp arrays back into arr[l..r]*/
	// Initial index of first subarray 
	i = 0; 

	// Initial index of second subarray 
	j = 0; 

	// Initial index of merged subarray 
	k = l;
	printf("i: %d (incide do vetor left)\n", i);
	printf("j: %d (indice do vetor right)\n", j);
	printf("k: %d (indice do vetor final)\n", k);
	printf("Entrando no while ate i >= n1 ou j >= n2\n");
	while (i < n1 && j < n2) { 
		printf("i: %d\n", i);
		printf("j: %d\n", j);
		printf("k: %d\n", k);
		printf("%d < %d  && %d < %d ?\n", i, n1, j, n2);

		printf("Se L[i] <= R[j]; %d <= %d ? \n", L[i], R[j]);
		if (L[i] <= R[j]) {
			printf("Entao arr[k] = L[i]; arr[%d] = %d\n", k, L[i]);
			arr[k++] = L[i++]; 
		} else {
			printf("Entao arr[k] = R[j]; arr[%d] = %d\n", k, R[j]);
			arr[k++] = R[j++]; 
		}
	} 

	/* Copy the remaining elements of L[], 
		if there are any */
	printf("Passando Valores restantes se houver algum\n");
	if(i < n1) {
		printf("i < n1; %d < %d\n", i, n1);
	} else {
		printf("j < n2; %d < %d\n", j, n2);
	}

	while (i < n1) {
		printf("i: %d\n", i);
		printf("k: %d\n", k);
		printf("arr[k] = L[i]; arr[%d] = %d\n", k, L[i]);
		arr[k++] = L[i++]; 
		
	}

	/* Copy the remaining elements of R[], 
		if there are any */	
	while (j < n2) {
		printf("j: %d\n", j);
		printf("k: %d\n", k);
		printf("arr[k] = R[j]; arr[%d] = %d\n", k, R[j]);
		arr[k++] = R[j++]; 
	}
	printf("\narr = { %d, %d, %d }\n", arr[0], arr[1], arr[2]);
	printf("Fim do Merge\n\n");
} 


// Merges k sorted files. Names of files are assumed 
// to be 1, 2, 3, ... k 
void mergeFiles(char* output_file, int k) { 
	FILE* in[k]; 
	for (int i = 0; i < k; i++) { 
		char fileName[2]; 

		// convert i to string 
		snprintf(fileName, sizeof(fileName), 
				"%d", i); 

		// Open output files in read mode. 
		in[i] = openFile(fileName, "r"); 
	} 

	// FINAL OUTPUT FILE 
	FILE* out = openFile(output_file, "w"); 

	// Create a min heap with k heap 
	// nodes. Every heap node 
	// has first element of scratch 
	// output file 
	MinHeapNode* harr = new MinHeapNode[k]; 
	int i; 
	for (i = 0; i < k; i++) { 
		// break if no output file is empty and 
		// index i will be no. of input files 
		if (fscanf(in[i], "%d ", &harr[i].element) != 1) 
			break; 

		// Index of scratch output file 
		harr[i].i = i; 
	} 
	// Create the heap 
	MinHeap hp(harr, i); 

	int count = 0; 

	// Now one by one get the 
	// minimum element from min 
	// heap and replace it with 
	// next element. 
	// run till all filled input 
	// files reach EOF 
	while (count != i) { 
		// Get the minimum element 
		// and store it in output file 
		MinHeapNode root = hp.getMin(); 
		fprintf(out, "%d ", root.element); 

		// Find the next element that 
		// will replace current 
		// root of heap. The next element 
		// belongs to same 
		// input file as the current min element. 
		if (fscanf(in[root.i], "%d ", 
				&root.element) 
			!= 1) { 
			root.element = INT_MAX; 
			count++; 
		} 

		// Replace root with next 
		// element of input file 
		hp.replaceMin(root); 
	} 

	// close input and output files 
	for (int i = 0; i < k; i++) 
		fclose(in[i]); 

	fclose(out); 
} 

// A utility function to swap two elements 
void swap(MinHeapNode* x, MinHeapNode* y) { 
	MinHeapNode temp = *x; 
	*x = *y; 
	*y = temp; 
} 




