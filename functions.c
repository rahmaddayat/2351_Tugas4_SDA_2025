#include "header.h"


// Fungsi generate
// ============================================================================================================================ //
void generate_random_numbers(const char *filename, int count, int max_value){
    FILE *fp = fopen (filename, "w");
    if(!fp){
        perror("Cannot open the file..");
        return;
    }

    srand(time(NULL)); // Inisialisasi seed
    for(int i = 0; i < count; i++){
        int num = rand() % max_value;
        fprintf(fp, "%d\n", num);
    }

    fclose(fp);
}

void random_word( char *word, int length){
    static const char charset[] = "abcdefghijklmnopqrstuvwxyz";

    for(int i = 0; i < length; i++){
        int key = rand() % (int)(sizeof(charset) - 1);
        word[i] = charset[key];
    }
}

void generate_random_words(const char *filename, int count, int max_word_length){
    FILE *fp = fopen(filename, "w");
    if(!fp){
        perror("cannot open the file..");
        return;
    }

    srand(time(NULL));

    char word[100];
    for(int i = 0; i < max_word_length; i++){
        int length = (rand() % (max_word_length - 3)) + 3; // panjang kata minimal 3
        random_word(word, length);
        fprintf(fp, "%s\n", word);        
    }

    fclose(fp);
}
// ============================================================================================================================ //


// Fungsi UI
// ============================================================================================================================ //

// Fungsi untuk membersihkan layar
void clearScreen() {
#ifdef _WIN32
    if (system(NULL)) {
        system("cls");  // jika system() tersedia
    } else {
        printf("\033[H\033[J"); // fallback
        fflush(stdout);
    }
#else
    printf("\033[H\033[J");
    fflush(stdout);
#endif
}

// Fungsi untuk membersihkan buffer input
void clearInputBuffer() {
    while (getchar() != '\n'); // Mengkonsumsi karakter hingga baris baru
}

// Fungsi konfirmasi
void confirmButton() {
    printf("\n\nTekan ENTER untuk melanjutkan...\n");
    getchar();  // Tunggu input ENTER
}
