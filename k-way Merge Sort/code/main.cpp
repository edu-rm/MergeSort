// C++ program to implement 
// external sorting using 
// merge sort 
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <windows.h>
#include "MinHeap.h" //Classe MinHeap

using namespace std; 

// Prototype of a utility function 
FILE* openFile(char*, char*);
void externalSort(char*, char*, int, int);
void createInitialRuns(char*, int, int);
void mergeSort(int [], int, int);
void merge(int [], int, int, int);
void mergeFiles(char*, int);

// Driver program to test above 
int main() { 
	// No. of Partitions of input file. 
	int num_ways = 10; 

	// The size of each partition 
	int run_size = 1000;
	CreateDirectory("/file", NULL);
	CreateDirectory("/num_ways", NULL);

	char input_file[] = "file/input.txt"; 
	char output_file[] = "file/output.txt"; 

	FILE* in = openFile(input_file, "w"); 

	srand(time(NULL)); 

	// generate input 
	for (int i = 0; i < num_ways * run_size; i++) 
		fprintf(in, "%d ", rand()); 

	fclose(in); 

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
	mergeFiles(output_file, num_ways); 
} 

// Using a merge-sort algorithm, 
// create the initial runs 
// and divide them evenly among 
// the output files 
void createInitialRuns( 
	char* input_file, int run_size, 
	int num_ways) { 
	// For big input file 
	FILE* in = openFile(input_file, "r"); 

	// output scratch files 
	FILE* out[num_ways]; 
	char fileName[2]; 
	for (int i = 0; i < num_ways; i++) { 
		// convert i to string 
		snprintf(fileName, sizeof(fileName), 
				"%d", i);

		//gerando path
		char path[] = "num_ways/"; //pasta onde será armazena as runs 
		strcat(path, fileName); 
		strcat(path, ".txt"); //extensão do arquivo

		// Open output files in write mode. 
		out[i] = openFile(path, "w"); 
	} 

	// allocate a dynamic array large enough 
	// to accommodate runs of size run_size 
	int* arr = (int*)malloc( 
		run_size * sizeof(int)); 

	bool more_input = true; 
	int next_output_file = 0; 

	int i; 
	while (more_input) { 
		// write run_size elements 
		// into arr from input file 
		for (i = 0; i < run_size; i++) { 
			if (fscanf(in, "%d ", &arr[i]) != 1) { 
				more_input = false; 
				break; 
			} 
		} 

		// sort array using merge sort 
		mergeSort(arr, 0, i - 1); 

		// write the records to the 
		// appropriate scratch output file 
		// can't assume that the loop 
		// runs to run_size 
		// since the last run's length 
		// may be less than run_size 
		for (int j = 0; j < i; j++) 
			fprintf(out[next_output_file], 
					"%d ", arr[j]); 

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
	if (l < r) { 
		// Same as (l+r)/2, but avoids overflow for 
		// large l and h 
		int m = l + (r - l) / 2; 

		// Sort first and second halves 
		mergeSort(arr, l, m); 
		mergeSort(arr, m + 1, r); 

		merge(arr, l, m, r); 
	} 
}

// Merges two subarrays of arr[]. 
// First subarray is arr[l..m] 
// Second subarray is arr[m+1..r] 
void merge(int arr[], int l, int m, int r) { 
	int i, j, k; 
	int n1 = m - l + 1; 
	int n2 = r - m; 

	/* create temp arrays */
	int L[n1], R[n2]; 

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++) 
		L[i] = arr[l + i]; 
	for (j = 0; j < n2; j++) 
		R[j] = arr[m + 1 + j]; 

	/* Merge the temp arrays back into arr[l..r]*/
	// Initial index of first subarray 
	i = 0; 

	// Initial index of second subarray 
	j = 0; 

	// Initial index of merged subarray 
	k = l; 
	while (i < n1 && j < n2) { 
		if (L[i] <= R[j]) 
			arr[k++] = L[i++]; 
		else
			arr[k++] = R[j++]; 
	} 

	/* Copy the remaining elements of L[], 
		if there are any */
	while (i < n1) 
		arr[k++] = L[i++]; 

	/* Copy the remaining elements of R[], 
		if there are any */
	while (j < n2) 
		arr[k++] = R[j++]; 
} 


// Merges k sorted files. Names of files are assumed 
// to be 1, 2, 3, ... k 
void mergeFiles(char* output_file, int num_ways) { 
	FILE* run[num_ways]; 
	for (int i = 0; i < num_ways; i++) { 
		char fileName[2]; 

		// convert i to string 
		snprintf(fileName, sizeof(fileName), 
				"%d", i); 
		//gerando path
		char path[] = "num_ways/"; //pasta onde será armazena as runs 
		strcat(path, fileName); 
		strcat(path, ".txt"); //extensão do arquivo
		// Open output files in read mode. 
		run[i] = openFile(path, "r"); 
	} 

	// FINAL OUTPUT FILE 
	FILE* out = openFile(output_file, "w"); 

	// Create a min heap with k heap 
	// nodes. Every heap node 
	// has first element of scratch 
	// output file 
	MinHeapNode* harr = new MinHeapNode[num_ways]; 
	int i; 
	for (i = 0; i < num_ways; i++) { 
		// break if no output file is empty and 
		// index i will be no. of input files 
		if (fscanf(run[i], "%d ", &harr[i].element) != 1) 
			break; 

		// Index of scratch output file 
		harr[i].i = i; 
	} 
	// Create the heap 
	MinHeap hp(harr, i); 

	// Now one by one get the 
	// minimum element from min 
	// heap and replace it with 
	// next element. 
	// run till all filled input 
	// files reach EOF 
	int count = 0; 
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
		if (fscanf(run[root.i], "%d ", 
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
	for (int i = 0; i < num_ways; i++) 
		fclose(run[i]); 

	fclose(out); 
} 





