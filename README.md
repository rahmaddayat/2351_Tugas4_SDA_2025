NAMA : Rahmad Hidayatullah Tsunami
NPM  : 23080107010051


📊 TUGAS 4 MATA KULIAH SDA D
📝 Deskripsi
Program ini merupakan aplikasi berbasis command-line untuk memvisualisasikan dan membandingkan performa dari berbagai algoritma sorting yang populer digunakan. Program ini dikembangkan menggunakan bahasa C dan berfokus pada analisis waktu eksekusi dan penggunaan memori dari tiap algoritma.
✨ Fitur

Pemilihan Jenis Data: Opsi untuk mensortir data numerik atau data string (kata)
Variasi Ukuran Data: Pengujian dengan dataset berbeda mulai dari 10.000 hingga 2.000.000 data
Multiple Sorting Algorithm: Implementasi 6 algoritma sorting populer
Analisis Performa: Pengukuran waktu eksekusi dan penggunaan memori
Tampilan Terstruktur: Hasil ditampilkan dalam bentuk tabel yang mudah dibaca

🧮 Algoritma Yang Diimplementasikan

Bubble Sort: Algoritma sederhana yang bekerja dengan menukar elemen bersebelahan jika tidak berurutan
Selection Sort: Mencari nilai minimum/maksimum dan menukarnya dengan posisi yang sesuai
Insertion Sort: Membangun array terurut satu per satu
Merge Sort: Algoritma divide-and-conquer, membagi array menjadi dua bagian
Quick Sort: Algoritma divide-and-conquer berbasis pivot
Shell Sort: Variasi dari insertion sort yang memproses elemen berjarak tertentu

🚀 Cara Penggunaan

Kompilasi program:
gcc -o main main.c header.h

Jalankan program:
./main

Ikuti instruksi di layar:

Pilih jenis data (angka atau kata)
Pilih ukuran data
Pilih algoritma sorting atau bandingkan semua
Konfirmasi pilihan dan lihat hasil



📋 Struktur Program

header.h: Berisi deklarasi semua fungsi yang digunakan
main.c: Berisi fungsi main yang menampilkan menu dan mengatur alur program

📊 Output
Program menampilkan tabel perbandingan dengan informasi:

Nama algoritma
Jumlah data
Waktu eksekusi (dalam detik)
Memori yang digunakan (dalam byte dan KB)

🔄 Proses Kerja

Program memeriksa keberadaan file data, jika tidak ada maka akan dibuat data baru
User memilih jenis data, ukuran data, dan metode sorting
Program menjalankan sorting sesuai pilihan
Hasil pengukuran waktu dan memori ditampilkan dalam bentuk tabel

📚 Catatan
Program ini dibuat untuk keperluan laporan mata kuliah SDA tentang algoritma sorting dan perbandingan performanya dalam kondisi yang berbeda. Hasil performa dapat bervariasi tergantung pada spesifikasi komputer dan kondisi sistem.