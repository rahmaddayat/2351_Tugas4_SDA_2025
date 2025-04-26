#include "header.h"

/*─ enumerasi ragam menu ─*/
enum DataKind   { DATA_ANGKA = 1, DATA_HURUF };
enum DataLength {
    LEN_10K = 1, LEN_50K, LEN_100K, LEN_250K,
    LEN_500K, LEN_1M, LEN_1_5M, LEN_2M
};
enum SortMethod {
    SORT_BUBBLE = 1, SORT_SELECTION, SORT_INSERTION,
    SORT_MERGE, SORT_QUICK, SORT_SHELL, MENU_BACK
};

int main(void)
{
    enum DataKind dataOption;
    enum DataLength lengthOption;
    enum SortMethod methodOption;

    // cek data, jika tidak ada maka generate ulang
    FILE *fp = fopen("dataNumber.txt", "r");
    if (!fp) {
        puts("< File dataNumber.txt tidak ditemukan, membuat data baru... >");
        Sleep(1200);
        generate_random_numbers("dataNumber.txt", 200000000, 2000000); // contoh: 20 juta angka acak, max 2000000
    } else {
        fclose(fp); // file ditemukan, tutup kembali
    }

    fp = fopen("dataWord.txt", "r");
    if (!fp) {
        puts("< File dataWord.txt tidak ditemukan, membuat data baru... >");
        Sleep(1200);
        generate_random_words("dataWord.txt", 20000000, 20); // contoh: 20 juta kata acak, max panjang 20
    } else {
        fclose(fp);
    }
    const char *fileName[]   = { "", "dataNumber.txt", "dataWord.txt"};

    while(1){
        DataType:
        clearScreen();
        /* ── menu 1: jenis data ─────────────────────────────── */
        puts("Masukkan jenis data yang akan di-sorting :");
        puts("(1) Data Acak Berupa Angka sebanyak 2.000.000 angka");
        puts("(2) Data Acak Berupa Huruf sebanyak 2.000.000 kata");
        puts("(3) Keluar dari program");
        printf("Masukkan Pilihan : ");
        scanf("%d", (int*)&dataOption);
        clearInputBuffer();  
        if(dataOption == 3){
            break;
        }

        DataLength:
        clearScreen();
        /* ── menu 2: ukuran data ────────────────────────────── */
        puts("\nPilih Jumlah data yang ingin diuji :");
        puts("(1) 10.000");
        puts("(2) 50.000");
        puts("(3) 100.000");
        puts("(4) 250.000");
        puts("(5) 500.000");
        puts("(6) 1.000.000");
        puts("(7) 1.500.000");
        puts("(8) 2.000.000");
        puts("(9) Kembali");
        printf("Masukkan Pilihan : ");
        scanf("%d", (int*)&lengthOption);
        clearInputBuffer();  
        if(lengthOption == 9){
            goto DataType;
        }

        /* ── menu 3: metode sorting ─────────────────────────── */
        clearScreen();
        puts("\nPilih Metode Sorting :");
        puts("(1) Bubble Sort");
        puts("(2) Selection Sort");
        puts("(3) Insertion Sort");
        puts("(4) Merge Sort");
        puts("(5) Quick Sort");
        puts("(6) Shell Sort");
        puts("(7) Semua Metode");
        puts("(8) Kembali");
        printf("Masukkan Pilihan : ");
        scanf("%d", (int*)&methodOption);
        clearInputBuffer();  // Bersihkan buffer setelah input
        if(methodOption == 8){
            goto DataLength;
        }

        /* ── cetak rekap pilihan ───────────────────────────── */
        const char *dataValues[]   = { "", "Angka", "Kata" };
        const int lengthValues[] = {
            0, 10000, 50000, 100000, 250000, 
            500000, 1000000, 1500000, 2000000};
        const char *methodName[] = { "",
            "Bubble Sort", "Selection Sort", "Insertion Sort",
            "Merge Sort", "Quick Sort", "Shell Sort", "Semua Metode Sorting"
        };

        char choice;
        Confirm:
        clearScreen();
        printf("\nRekap pilihan:\n");
        printf("  Jenis data   : %s\n", dataValues[dataOption]);
        printf("  Jumlah data  : %d\n", lengthValues[lengthOption]);
        printf("  Metode       : %s\n\n", methodName[methodOption]);
        printf("Apakah Anda yakin ingin menggunakan sorting tersebut?\n");
        printf("Masukkan Pilihan (Y/N) : ");
        scanf("%c", &choice);
        clearInputBuffer();  // Bersihkan buffer setelah input
        if (choice == 'Y' || choice == 'y') {
            printf("< Memulai Sorting >\n");
            Sleep(1600);
        } else if (choice == 'N' || choice == 'n') {
            printf("< Membatalkan Sorting >\n");
            Sleep(1600);
            continue;                   
        } else if ((dataOption   != DATA_ANGKA && dataOption   != DATA_HURUF) ||
            (lengthOption < LEN_10K     || lengthOption > LEN_2M)       ||
            (methodOption < SORT_BUBBLE || methodOption > MENU_BACK)) {
            puts("< Terjadi kesalahan: salah satu pilihan menu tidak valid! >");
            Sleep(1600);
            continue;
        }
        else {
            puts("< Input konfirmasi tidak valid, Masukkan input Y atau N >");
            Sleep(1600);
            goto Confirm;
        }

        switch (methodOption) {
        case SORT_BUBBLE:
            printTableHeader();
            bubbleSort(fileName[dataOption], lengthValues[lengthOption], dataOption);
            printTableFooter();
            puts("\n< Tekan enter untuk lanjut >");
            getchar();
            break;
        case SORT_SELECTION:
            printTableHeader();
            selectionSort(fileName[dataOption], lengthValues[lengthOption], dataOption);
            printTableFooter();
            puts("\n< Tekan enter untuk lanjut >");
            getchar();
            break;
        case SORT_INSERTION:
            printTableHeader();
            insertionSort(fileName[dataOption], lengthValues[lengthOption], dataOption);
            printTableFooter();
            puts("\n< Tekan enter untuk lanjut >");
            getchar();
            break;
        case SORT_MERGE:
            printTableHeader();
            mergeSort(fileName[dataOption], lengthValues[lengthOption], dataOption);
            printTableFooter();
            puts("\n< Tekan enter untuk lanjut >");
            getchar();
            break;
        case SORT_QUICK:
            printTableHeader();
            quickSort(fileName[dataOption], lengthValues[lengthOption], dataOption);
            printTableFooter();
            puts("\n< Tekan enter untuk lanjut >");
            getchar();
            break;
        case SORT_SHELL:
            printTableHeader();
            shellSort(fileName[dataOption], lengthValues[lengthOption], dataOption);
            printTableFooter();
            puts("\n< Tekan enter untuk lanjut >");
            getchar();
            break;
        case 7: 
            printf("\n=== Perbandingan Metode Sorting ===\n");
            
            // Print header tabel
            printTableHeader();
            
            // Panggil semua fungsi sorting methods
            bubbleSort(fileName[dataOption], lengthValues[lengthOption], dataOption);
            selectionSort(fileName[dataOption], lengthValues[lengthOption], dataOption);
            insertionSort(fileName[dataOption], lengthValues[lengthOption], dataOption);
            mergeSort(fileName[dataOption], lengthValues[lengthOption], dataOption);
            quickSort(fileName[dataOption], lengthValues[lengthOption], dataOption);
            shellSort(fileName[dataOption], lengthValues[lengthOption], dataOption);
            
            // Print footer tabel
            printTableFooter();

            puts("\n< Tekan enter untuk lanjut >");
            getchar();
            break;
        default:
            puts("< Pilihan tidak valid! >");
        
        }
    }
    
    clearScreen();
    return 0;
}