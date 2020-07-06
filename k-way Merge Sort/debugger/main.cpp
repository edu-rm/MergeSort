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
	MinHeapNode getMin() {
		printf("retorna a primeira posicao do harr\n"); 
		return harr[0]; 
	} 

	// to replace root with new node 
	// x and heapify() new root 
	void replaceMin(MinHeapNode x) {
		printf("\nPassa o root para a posicao 0 de harr\n");
		harr[0] = x;
		printf("Entra em MinHeapify passando 0 como parametro\n"); 
		MinHeapify(0); 
	} 
}; 

// Constructor: Builds a heap from 
// a given array a[] of given size 
MinHeap::MinHeap(MinHeapNode a[], int size) { 
	heap_size = size;
	printf("\nConstrutor MinHeap\n");
	harr = a; // store address of array 
	int i = (heap_size - 1) / 2;
	printf("i = (num_ways - 1) / 2\n");
	printf("\nEnquanto i >= 0\n");
	while (i >= 0) {
		printf("\ni: %d\n", i);
		printf("Executa a funcao MinHeapify passando como parametro i\n"); 
		MinHeapify(i); 
		i--;
		printf("\n\nFim do Enquanto do Construtor\n\n");
	} 

	printf("\nFim do Contrutor\n");
} 

// A recursive method to heapify 
// a subtree with root 
// at given index. This method 
// assumes that the 
// subtrees are already heapified 
void MinHeap::MinHeapify(int i) {
	printf("\n\nNova Pilha - Funcao MinHeapify\n\n");
	printf("Chama Funcao Left passando i como parametro que retorna 2 * i + 1 \n");
	int l = left(i); 
	printf("left = %d\n", l);
	printf("Chama Funcao Right passando i como parametro retornando 2 * i + 2\n");
	int r = right(i); 
	printf("right = %d\n", r);
	int smallest = i;
	printf("Passa para variavel smallest o valor de i; smallest = %d", i);
	printf("\nif l (%d) < (%d) num_ways && harr[l].element (%d) < (%d) harr[i].element\n", l, heap_size, harr[l].element, harr[i].element); 
	if (l < heap_size && harr[l].element < harr[i].element) {
		smallest = l; 
		printf("Entao smallest = l; smallest = %d\n", l);
		

	}
	printf("\nif r (%d) <  (%d) num_ways && harr[r].element (%d) < (%d) harr[smallest].element\n", r, heap_size, harr[r].element, harr[smallest].element);
	if (r < heap_size && harr[r].element < harr[smallest].element) {
		smallest = r; 
		printf("Entao smallest = r; smallest = %d\n", r);
	}
	printf("\nif smallest (%d) != (%d) i\n", smallest, i);
	if (smallest != i) { 
		printf("Entao chama funcao swap passando como referencia o harr[i] = %d e harr[smallest] = %d\n", harr[i].element, harr[smallest].element);
		swap(&harr[i], &harr[smallest]);
		printf("Entrando em MinHeapify passando smallest = %d como parametro\n", smallest);
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
		int x = rand() %30;
		fprintf(in, "%d ", x);
		printf("%d\n", x);
	} 

	fclose(in); 

	printf("Entrando na funcao External Sort\n");
	externalSort(input_file, output_file, num_ways, 
				run_size); 


	system("pause");
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
			printf("Lendo as 3 primeiras posicoes do arquivo in e armazenando-as no array\n");
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
	//k == nuwways
	printf("Abre as runs criadas no mode de leitura\n");
	printf("FILE in[%d]\n", k);
	FILE* in[k];
	FILE* aux;
	for (int i = 0; i < k; i++) { 
		char fileName[2]; 

		// convert i to string 
		snprintf(fileName, sizeof(fileName), 
				"%d", i); 
		printf("Abrindo as runs (Buffers na Memoria) [%s]\n", fileName);

		// Open output files in read mode. 
		in[i] = openFile(fileName, "r");

	}

	printf("\n\n");
	
	int* arr = (int*) malloc(3 * sizeof(int));
	for (int i = 0; i < k; i++) { 
		char fileName[2]; 
		// convert i to string 
		snprintf(fileName, sizeof(fileName), 
				"%d", i); 
		// Open output files in read mode. 
		aux = openFile(fileName, "r");
		for (int j = 0; j < 3; j++) {
			if(fscanf(aux, "%d ", &arr[j]) != 1) {
				break;
			} 
		}
		
		printf("run %d = { ", i);
		for(int m = 0; m < 3; m++) {
			printf("%d ", arr[m]);
		}
		printf("}\n");
			
	}  

	printf("\n\n");

	// FINAL OUTPUT FILE 
	printf("\nCria o arquivo final no modo de escrita out\n");
	FILE* out = openFile(output_file, "w");


	// Create a min heap with k heap 
	// nodes. Every heap node 
	// has first element of scratch 
	// output file 
	printf("\nCria um vetor da struct MinHeapNode com o mesmo tamanho de num_ways\n");
	printf("MinHeapNode harr[%d] possui um elemento e um indice\n", k);
	MinHeapNode* harr = new MinHeapNode[k]; 
	int i; 
	printf("\n\n\nEntrando no for de i ate num_ways\n");
	for (i = 0; i < k; i++) {
		printf("\ni = %d\n", i);
		// break if no output file is empty and 
		// index i will be no. of input files 
		printf("Lendos os valores de in[%d] e passando para o elemento de  harr[%d]\n", i, i);
		if (fscanf(in[i], "%d ", &harr[i].element) != 1) {
			printf("Entrou na condicao, ou seja, não existem mais arquivos para serem lidos\n");
			break; 
		}
		
		printf("harr[%d] = %d\n", i, harr[i].element);

		// Index of scratch output file 
		printf("\nConcatenando o mesmo indice i = %d com o indice de harr[i].i = %d\n", i, i);
		harr[i].i = i; 
	} 
	// Create the heap 
	printf("\n\n\n\nnum_ways = %d\n", i);
	printf("Criando a classe MinHeap passando para o construtor harr e num_ways\n");
	MinHeap hp(harr, i);

	int count = 0; 

	// Now one by one get the 
	// minimum element from min 
	// heap and replace it with 
	// next element. 
	// run till all filled input 
	// files reach EOF
	printf("\n\nVoltou a funcao MergeFiles\n");
	printf("count = %d\n", count);
	printf("num_ways = %d\n", i);
	printf("Enquanto %d != %d\n", count, i);
	
	while (count != i) { 
		printf("\n\ncount: %d\n", count);
		// Get the minimum element 
		// and store it in output file
		printf("Cria uma estrutura MinHeapNode root e passa para ela o menor valor da classe MinHeap com a funcao getMin()\n"); 
		MinHeapNode root = hp.getMin();
		printf("root = %d\n", root.element); 

		printf("\nEscreve no arquivo final (out)  o valor de root\n");
		fprintf(out, "%d ", root.element); 
		printf("root = %d\n", root.element);
		printf("root.i = %d\n\n", root.i);

		// Find the next element that 
		// will replace current 
		// root of heap. The next element 
		// belongs to same 
		// input file as the current min element. 
		
		printf("Enquanto houver, pega o proximo elemento no run e passa para root.element; do arquivo in[%d], onde %d = root.i\n", root.i, root.i);
		if (fscanf(in[root.i], "%d ", 
				&root.element) 
			!= 1) {
			
			printf("Entro na condicao, nao existe mais elemento para ser lido, e passa para root.element um valor grande\n");
			root.element = INT_MAX; 
			count++; 
			printf("count++ = %d\n", count);
		}
		
		printf("root.element = %d\n\n", root.element);
		

		// Replace root with next 
		// element of input file
		printf("Aplica a funcao de replaceMin na classe MinHeap passando root como parametro %d\n\n", root.element);
		hp.replaceMin(root);

		printf("\n\nVoltou ao MergeFiles\n");

		printf("Fim do Enquanto Merge Files\n");
	} 

	// close input and output file
	for (int i = 0; i < k; i++) 
		fclose(in[i]); 

	fclose(out); 
} 

// A utility function to swap two elements 
void swap(MinHeapNode* x, MinHeapNode* y) {
	printf("\nfuncao swap\n");
	printf("Inverte os valores de harr[i] e harr[smallest]\n");
	MinHeapNode temp = *x; 
	*x = *y; 
	*y = temp;
	printf("harr[i] = %d, harr[smallest] = %d\n", x->element, y->element);
} 




