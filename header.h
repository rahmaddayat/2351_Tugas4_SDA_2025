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