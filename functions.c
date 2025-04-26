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
    word[length] = '\0';
}

void generate_random_words(const char *filename, int count, int max_word_length){
    FILE *fp = fopen(filename, "w");
    if(!fp){
        perror("cannot open the file..");
        return;
    }

    srand(time(NULL));

    char word[100];
    for(int i = 0; i < count; i++){
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

// Fungsi untuk print header tabel 
void printTableHeader(void) {
    printf("\n+-------------------------------+-----------------------+-----------------------+-------------------------------+\n");
    printf("| Algoritma Sorting    \t\t| Jumlah Data          \t| Waktu Eksekusi   \t| Memori Digunakan          \t|\n");
    printf("+-------------------------------+-----------------------+-----------------------+-------------------------------+\n");
}

// Fungsi untuk print baris tabel 
void printTableRow(const char* algorithm, int count, double time_taken, size_t memory_used) {
    printf("| %-28s \t| %-20d \t| %-19.6f s | %-12zu (%.2f KB) \t|\n", 
           algorithm, count, time_taken, memory_used, memory_used / 1024.0);
}

// Fungsi untuk print footer tabel 
void printTableFooter(void) {
    printf("+-------------------------------+-----------------------+-----------------------+-------------------------------+\n");
}

// Fungsi Sorting
// ============================================================================================================================ //
void bubbleSort(const char *filename, int count, int dataType) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Gagal membuka file");
        return;
    }

    clock_t start, end;
    double time_taken;
    size_t memory_used;
    const char* algorithm = (dataType == 1) ? "Bubble Sort (Angka)" : "Bubble Sort (Huruf)";

    if (dataType == 1) {
        // === SORTING ANGKA ===
        int *data = (int *)malloc(sizeof(int) * count);
        if (!data) {
            perror("Gagal mengalokasikan memori");
            fclose(fp);
            return;
        }

        for (int i = 0; i < count && fscanf(fp, "%d", &data[i]) == 1; i++);
        fclose(fp);

        start = clock();
        // Bubble Sort (Angka)
        for (int step = 0; step < count - 1; ++step) {
            int swapped = 0;
            for (int i = 0; i < count - step - 1; ++i) {
                if (data[i] > data[i + 1]) {
                    int temp = data[i];
                    data[i] = data[i + 1];
                    data[i + 1] = temp;
                    swapped = 1;
                }
            }
            if (!swapped) break;
        }
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        memory_used = count * sizeof(int);

        printTableRow(algorithm, count, time_taken, memory_used);

        free(data);
    } else if (dataType == 2) {
        // === SORTING KATA ===
        char **data = (char **)malloc(sizeof(char *) * count);
        if (!data) {
            perror("Gagal mengalokasikan memori");
            fclose(fp);
            return;
        }

        char buffer[256];
        int index = 0;
        while (fgets(buffer, sizeof(buffer), fp) && index < count) {
            buffer[strcspn(buffer, "\n")] = 0; // Hapus newline
            data[index] = strdup(buffer);      // Salin ke heap
            index++;
        }
        fclose(fp);

        start = clock();
        // Bubble Sort (String)
        for (int step = 0; step < count - 1; ++step) {
            int swapped = 0;
            for (int i = 0; i < count - step - 1; ++i) {
                if (strcmp(data[i], data[i + 1]) > 0) {
                    char *temp = data[i];
                    data[i] = data[i + 1];
                    data[i + 1] = temp;
                    swapped = 1;
                }
            }
            if (!swapped) break;
        }
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        memory_used = count * sizeof(char*) + count * 20; // Estimasi 20 char/kata

        printTableRow(algorithm, count, time_taken, memory_used);

        for (int i = 0; i < count; ++i) free(data[i]);
        free(data);
    }
}

void selectionSort(const char *filename, int count, int dataType) {
    FILE *fp = fopen(filename, "r");
    if (!fp) { 
        perror("Gagal membuka file"); 
        return; 
    }

    clock_t start, end;
    double time_taken;
    size_t memory_used;
    const char* algorithm = (dataType == 1) ? "Selection Sort (Angka)" : "Selection Sort (Huruf)";

    if (dataType == 1) {
        int *data = malloc(sizeof(int) * count);
        if (!data) {
            perror("Gagal mengalokasikan memori");
            fclose(fp);
            return;
        }
        
        for (int i = 0; i < count && fscanf(fp, "%d", &data[i]) == 1; i++);
        fclose(fp);

        start = clock();
        for (int i = 0; i < count - 1; i++) {
            int min_idx = i;
            for (int j = i + 1; j < count; j++)
                if (data[j] < data[min_idx]) min_idx = j;
            int temp = data[min_idx]; data[min_idx] = data[i]; data[i] = temp;
        }
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        memory_used = count * sizeof(int);

        printTableRow(algorithm, count, time_taken, memory_used);

        free(data);
    } else if (dataType == 2) {
        char **data = malloc(sizeof(char *) * count);
        if (!data) {
            perror("Gagal mengalokasikan memori");
            fclose(fp);
            return;
        }
        
        char buffer[256];
        int index = 0;
        while (fgets(buffer, sizeof(buffer), fp) && index < count) {
            buffer[strcspn(buffer, "\n")] = 0;
            data[index++] = strdup(buffer);
        }
        fclose(fp);

        start = clock();
        for (int i = 0; i < count - 1; i++) {
            int min_idx = i;
            for (int j = i + 1; j < count; j++)
                if (strcmp(data[j], data[min_idx]) < 0) min_idx = j;
            char *tmp = data[min_idx]; data[min_idx] = data[i]; data[i] = tmp;
        }
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        memory_used = count * sizeof(char *) + count * 20;

        printTableRow(algorithm, count, time_taken, memory_used);

        for (int i = 0; i < count; ++i) free(data[i]);
        free(data);
    }
}

void insertionSort(const char *filename, int count, int dataType) {
    FILE *fp = fopen(filename, "r");
    if (!fp) { 
        perror("Gagal membuka file"); 
        return; 
    }

    clock_t start, end;
    double time_taken;
    size_t memory_used;
    const char* algorithm = (dataType == 1) ? "Insertion Sort (Angka)" : "Insertion Sort (Huruf)";

    if (dataType == 1) {
        int *data = malloc(sizeof(int) * count);
        if (!data) {
            perror("Gagal mengalokasikan memori");
            fclose(fp);
            return;
        }
        
        for (int i = 0; i < count && fscanf(fp, "%d", &data[i]) == 1; i++);
        fclose(fp);

        start = clock();
        for (int i = 1; i < count; i++) {
            int key = data[i], j = i - 1;
            while (j >= 0 && data[j] > key) {
                data[j + 1] = data[j];
                j--;
            }
            data[j + 1] = key;
        }
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        memory_used = count * sizeof(int);

        printTableRow(algorithm, count, time_taken, memory_used);

        free(data);
    } else if (dataType == 2) {
        char **data = malloc(sizeof(char *) * count);
        if (!data) {
            perror("Gagal mengalokasikan memori");
            fclose(fp);
            return;
        }
        
        char buffer[256];
        int index = 0;
        while (fgets(buffer, sizeof(buffer), fp) && index < count) {
            buffer[strcspn(buffer, "\n")] = 0;
            data[index++] = strdup(buffer);
        }
        fclose(fp);

        start = clock();
        for (int i = 1; i < count; i++) {
            char *key = data[i];
            int j = i - 1;
            while (j >= 0 && strcmp(data[j], key) > 0) {
                data[j + 1] = data[j];
                j--;
            }
            data[j + 1] = key;
        }
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        memory_used = count * sizeof(char *) + count * 20;

        printTableRow(algorithm, count, time_taken, memory_used);

        for (int i = 0; i < count; i++) free(data[i]);
        free(data);
    }
}

void mergeSortInt(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortInt(arr, l, m);
        mergeSortInt(arr, m + 1, r);
        mergeInt(arr, l, m, r);
    }
}

void mergeInt(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int *L = malloc(sizeof(int) * n1);
    int *R = malloc(sizeof(int) * n2);

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeStr(char *arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    char **L = malloc(n1 * sizeof(char *));
    char **R = malloc(n2 * sizeof(char *));

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (strcmp(L[i], R[j]) <= 0) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSortStr(char *arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortStr(arr, l, m);
        mergeSortStr(arr, m + 1, r);
        mergeStr(arr, l, m, r);
    }
}

void mergeSort(const char *filename, int count, int dataType) {
    FILE *fp = fopen(filename, "r");
    if (!fp) { 
        perror("Gagal membuka file"); 
        return; 
    }

    clock_t start, end;
    double time_taken;
    size_t memory_used;
    const char* algorithm = (dataType == 1) ? "Merge Sort (Angka)" : "Merge Sort (Huruf)";

    if (dataType == 1) {
        int *data = malloc(sizeof(int) * count);
        if (!data) {
            perror("Gagal mengalokasikan memori");
            fclose(fp);
            return;
        }
        
        for (int i = 0; i < count && fscanf(fp, "%d", &data[i]) == 1; i++);
        fclose(fp);

        start = clock();
        mergeSortInt(data, 0, count - 1);
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        memory_used = count * sizeof(int);

        printTableRow(algorithm, count, time_taken, memory_used);

        free(data);
    } else if (dataType == 2) {
        char **data = malloc(sizeof(char *) * count);
        if (!data) {
            perror("Gagal mengalokasikan memori");
            fclose(fp);
            return;
        }
        
        char buffer[256];
        int index = 0;
        while (fgets(buffer, sizeof(buffer), fp) && index < count) {
            buffer[strcspn(buffer, "\n")] = 0;
            data[index++] = strdup(buffer);
        }
        fclose(fp);

        start = clock();
        mergeSortStr(data, 0, count - 1);
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        memory_used = count * sizeof(char *) + count * 20;

        printTableRow(algorithm, count, time_taken, memory_used);

        for (int i = 0; i < count; i++) free(data[i]);
        free(data);
    }
}

void quickSortInt(int arr[], int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                int tmp = arr[++i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
        int tmp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = tmp;

        int pi = i + 1;
        quickSortInt(arr, low, pi - 1);
        quickSortInt(arr, pi + 1, high);
    }
}

void quickSortStr(char **arr, int low, int high) {
    if (low < high) {
        char *pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (strcmp(arr[j], pivot) <= 0) {
                char *tmp = arr[++i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
        char *tmp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = tmp;

        int pi = i + 1;
        quickSortStr(arr, low, pi - 1);
        quickSortStr(arr, pi + 1, high);
    }
}

void quickSort(const char *filename, int count, int dataType) {
    FILE *fp = fopen(filename, "r");
    if (!fp) { 
        perror("Gagal membuka file"); 
        return; 
    }

    clock_t start, end;
    double time_taken;
    size_t memory_used;
    const char* algorithm = (dataType == 1) ? "Quick Sort (Angka)" : "Quick Sort (Huruf)";

    if (dataType == 1) {
        int *data = malloc(sizeof(int) * count);
        if (!data) {
            perror("Gagal mengalokasikan memori");
            fclose(fp);
            return;
        }
        
        for (int i = 0; i < count && fscanf(fp, "%d", &data[i]) == 1; i++);
        fclose(fp);

        start = clock();
        quickSortInt(data, 0, count - 1);
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        memory_used = count * sizeof(int);

        printTableRow(algorithm, count, time_taken, memory_used);

        free(data);
    } else if (dataType == 2) {
        char **data = malloc(sizeof(char *) * count);
        if (!data) {
            perror("Gagal mengalokasikan memori");
            fclose(fp);
            return;
        }
        
        char buffer[256];
        int index = 0;
        while (fgets(buffer, sizeof(buffer), fp) && index < count) {
            buffer[strcspn(buffer, "\n")] = 0;
            data[index++] = strdup(buffer);
        }
        fclose(fp);

        start = clock();
        quickSortStr(data, 0, count - 1);
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        memory_used = count * sizeof(char *) + count * 20;

        printTableRow(algorithm, count, time_taken, memory_used);

        for (int i = 0; i < count; i++) free(data[i]);
        free(data);
    }
}

void shellSortInt(int arr[], int count) {
    // Shell sort for integers
    for (int gap = count / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < count; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void shellSortStr(char **arr, int count) {
    // Shell sort for strings
    for (int gap = count / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < count; i++) {
            char *temp = arr[i];
            int j;
            for (j = i; j >= gap && strcmp(arr[j - gap], temp) > 0; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void shellSort(const char *filename, int count, int dataType) {
    FILE *fp = fopen(filename, "r");
    if (!fp) { 
        perror("Gagal membuka file"); 
        return; 
    }

    clock_t start, end;
    double time_taken;
    size_t memory_used;
    const char* algorithm = (dataType == 1) ? "Shell Sort (Angka)" : "Shell Sort (Huruf)";

    if (dataType == 1) {
        // === SORTING ANGKA ===
        int *data = malloc(sizeof(int) * count);
        if (!data) {
            perror("Gagal mengalokasikan memori");
            fclose(fp);
            return;
        }

        for (int i = 0; i < count && fscanf(fp, "%d", &data[i]) == 1; i++);
        fclose(fp);

        start = clock();
        shellSortInt(data, count);
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        memory_used = count * sizeof(int);
        
        printTableRow(algorithm, count, time_taken, memory_used);
        
        free(data);
    } else if (dataType == 2) {
        // === SORTING KATA ===
        char **data = malloc(sizeof(char *) * count);
        if (!data) {
            perror("Gagal mengalokasikan memori");
            fclose(fp);
            return;
        }

        char buffer[256];
        int index = 0;
        while (fgets(buffer, sizeof(buffer), fp) && index < count) {
            buffer[strcspn(buffer, "\n")] = 0; 
            data[index] = strdup(buffer);      
            index++;
        }
        fclose(fp);

        start = clock();
        shellSortStr(data, count);
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        memory_used = count * sizeof(char *) + count * 20; // Estimasi 20 char per kata
        
        printTableRow(algorithm, count, time_taken, memory_used);
        
        for (int i = 0; i < count; i++) free(data[i]);
        free(data);
    }
}

// ============================================================================================================================ //