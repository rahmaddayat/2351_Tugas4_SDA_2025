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

    while(1){
        clearScreen();
        DataKindReturn:
        /* ── menu 1: jenis data ─────────────────────────────── */
        puts("Masukkan jenis data yang akan di-sorting :");
        puts("(1) Data Acak Berupa Angka sebanyak 2.000.000");
        puts("(2) Data Acak Berupa Huruf sebanyak 2.000.000");
        puts("(3) Keluar dari program");
        printf("Masukkan Pilihan : ");
        scanf("%d", (int*)&dataOption);
        clearInputBuffer();  // Bersihkan buffer setelah input
        if(dataOption == 3){
            break;
        }

        clearScreen();
        DataLengthReturn:
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
        clearInputBuffer();  // Bersihkan buffer setelah input
        if(lengthOption == 3){
            goto DataLengthReturn;
        }

        clearScreen();
        /* ── menu 3: metode sorting ─────────────────────────── */
        SortMethodReturn:
        puts("\nPilih metode Sorting :");
        puts("(1) Bubble Sort");
        puts("(2) Selection Sort");
        puts("(3) Insertion Sort");
        puts("(4) Merge Sort");
        puts("(5) Quick Sort");
        puts("(6) Shell Sort");
        puts("(7) Kembali");
        printf("Masukkan Pilihan : ");
        scanf("%d", (int*)&methodOption);
        clearInputBuffer();  // Bersihkan buffer setelah input
        if(methodOption == 3){
            goto SortMethodReturn;
        }

        /* ── cetak rekap pilihan ───────────────────────────── */
        const char *namaData[]   = { "", "Angka", "Huruf" };
        const char *namaLength[] = { "",
            "10.000", "50.000", "100.000", "250.000",
            "500.000", "1.000.000", "1.500.000", "2.000.000"
        };
        const char *namaMetode[] = { "",
            "Bubble Sort", "Selection Sort", "Insertion Sort",
            "Merge Sort", "Quick Sort", "Shell Sort"
        };

        char choice;
        Confirm:
        clearScreen();
        printf("\nRekap pilihan:\n");
        printf("  Jenis data   : %s\n", namaData[dataOption]);
        printf("  Jumlah data  : %s\n", namaLength[lengthOption]);
        printf("  Metode       : %s\n\n", namaMetode[methodOption]);
        printf("Apakah Anda yakin ingin menggunakan sorting tersebut?\n");
        printf("Masukkan Pilihan (Y/N) : ");
        scanf("%c", &choice);
        clearInputBuffer();  // Bersihkan buffer setelah input
        if (choice == 'Y' || choice == 'y') {
            printf("< Memulai Sorting >\n");
        } else if (choice == 'N' || choice == 'n') {
            printf("< Membatalkan Sorting >\n");
            continue;                   
        } else if (dataOption   < DATA_ANGKA || dataOption   > DATA_HURUF ||
                lengthOption < LEN_10K   || lengthOption > LEN_2M      ||
                methodOption < SORT_BUBBLE || methodOption > MENU_BACK) {
            puts("< Terjadi kesalahan: salah satu pilihan menu tidak valid! >");
            continue;                   
        } else {
            puts("< Input konfirmasi tidak valid, Masukkan input Y atau N >");
            Sleep(1600);
            goto Confirm;
        }

        switch (methodOption) {
            case SORT_BUBBLE:
                /* panggil bubbleSort(data, size); */
                break;
            case SORT_SELECTION:
                /* panggil selectionSort(...); */
                break;
            case SORT_INSERTION:
                /* panggil insertionSort(...); */
                break;
            case SORT_MERGE:
                /* panggil mergeSort(...); */
                break;
            case SORT_QUICK:
                /* panggil quickSort(...); */
                break;
            case SORT_SHELL:
                /* panggil shellSort(...); */
                break;
            case MENU_BACK:
                /* kembali ke menu sebelumnya */
                break;
            default:
                puts("< Pilihan tidak valid! >");
        }
    }
    
    clearScreen();
    return 0;
}