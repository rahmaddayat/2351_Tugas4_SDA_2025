#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

// Deklarasi fungsi generate
void generate_random_numbers(const char *filename, int count, int max_value);
void random_word(char *word, int length);
void generate_random_words(const char *filename, int count, int max_word_length); 

// Fungsi tampilan UI
void clearScreen();
void confirmButton();
void clearInputBuffer();
void printTableHeader(void);
void printTableRow(const char* algorithm, int count, double time_taken, size_t memory_used);
void printTableFooter(void);

// Fungsi Sorting
void bubbleSort(const char *filename, int count, int dataType);
void selectionSort(const char *filename, int count, int dataType);
void insertionSort(const char *filename, int count, int dataType);
void mergeSort(const char *filename, int count, int dataType);
void quickSort(const char *filename, int count, int dataType);
void shellSort(const char *filename, int count, int dataType);
void quickSort(const char *filename, int count, int dataType);
int partitionInt(int arr[], int low, int high);
void quickSortInt(int arr[], int low, int high);
void mergeInt(int arr[], int l, int m, int r);
void mergeSortInt(int arr[], int l, int r);
void mergeStr(char **arr, int l, int m, int r);
void mergeSortStr(char **arr, int l, int r);
void mergeSort(const char *filename, int count, int dataType);