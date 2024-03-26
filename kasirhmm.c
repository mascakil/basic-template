#include <stdio.h>
#include <string.h>

// Struktur untuk menyimpan informasi barang
struct Barang {
    int kode;
    char nama[50];
    float harga;
};

int main() {
    // Menyiapkan data barang
    struct Barang barang[] = {
        {1, "Sabun", 5000},
        {2, "Shampoo", 10000},
        {3, "Odol", 7000},
        {4, "Sandal", 3000},
        {5, "Toys", 80000},
        // Tambahkan barang lain di sini
    };

    int jumlah_barang[sizeof(barang)/sizeof(barang[0])]; // array untuk menyimpan jumlah barang yang dibeli
    int total_barang = sizeof(barang)/sizeof(barang[0]); // total barang yang tersedia
    float total_belanja = 0; // total harga belanja
    int i;

    // Inisialisasi jumlah barang menjadi 0
    for (i = 0; i < total_barang; i++) {
        jumlah_barang[i] = 0;
    }

    char nama_pembeli[100]; // menyimpan nama pembeli

    // Meminta nama pembeli
    printf("Masukkan nama pembeli: ");
    fgets(nama_pembeli, sizeof(nama_pembeli), stdin);
    strtok(nama_pembeli, "\n"); // menghapus karakter newline dari nama pembeli

    // Menampilkan daftar barang yang tersedia
    printf("\nDaftar Barang yang Tersedia:\n");
    printf("Kode\tNama\t\tHarga\n");
    for (i = 0; i < total_barang; i++) {
        printf("%d\t%s\t\t%.2f\n", barang[i].kode, barang[i].nama, barang[i].harga);
    }

    // Memasukkan jumlah barang yang akan dibeli
    printf("\nMasukkan kode barang yang ingin dibeli (99 untuk struk, 55 untuk reset, 00 untuk keluar):\n");
    do {
        int kode;
        printf("Kode barang: ");
        scanf("%d", &kode);
        if (kode == 0) {
            break;
        } else if (kode == 55) {
            // Reset jumlah barang yang dibeli dan barang yang dipilih sebelumnya
            for (i = 0; i < total_barang; i++) {
                jumlah_barang[i] = 0;
            }
            total_belanja = 0;
            printf("Semua barang telah direset.\n");
            continue; // Melanjutkan iterasi tanpa memproses input selanjutnya
        } else if (kode == 99) {
            // Menampilkan struk belanja
            printf("\n================= Struk Belanja =================\n");
            printf("Nama Pembeli   : %s\n", nama_pembeli);
            printf("Nama Produk    | Harga Satuan  | Jumlah     | Total Harga | Diskon    \n");
            printf("-------------------------------------------------\n");
            float total_diskon = 0;
            for (i = 0; i < total_barang; i++) {
                if (jumlah_barang[i] > 0) {
                    float subtotal = barang[i].harga * jumlah_barang[i];
                    float diskon = 0;
                    if (jumlah_barang[i] > 3) {
                        diskon = subtotal * 0.10; // Diskon 10% jika jumlah produk melebihi 3
                    }
                    if (jumlah_barang[i] > 5) {
                        diskon = subtotal * 0.15; // Diskon 15% jika jumlah produk melebihi 5
                    }
                    total_diskon += diskon;
                    printf("%-15s | %-13.2f | %-10d | %-11.2f | %-10.2f\n", barang[i].nama, barang[i].harga, jumlah_barang[i], subtotal, diskon);
                }
            }
            printf("-------------------------------------------------\n");
            float total_harga = total_belanja - total_diskon;
            printf("Total Harga   : %.2f\n", total_harga);
            printf("Total diskon  : %.2f\n", total_diskon);

            float uang_dibayarkan;
            do {
                printf("\nMasukkan uang yang dibayarkan: ");
                scanf("%f", &uang_dibayarkan);
                if (uang_dibayarkan < total_harga) {
                    printf("Uang yang dibayarkan kurang dari total harga. Mohon masukkan kembali.\n");
                }
            } while (uang_dibayarkan < total_harga);

            float kembalian = uang_dibayarkan - total_harga;
            printf("Uang kembalian          : %.2f\n", kembalian);
            printf("\n-------------------------------------------------\n");

            // Simpan struk belanja ke dalam file teks
            char filename[50];
            sprintf(filename, "struk_%s.txt", nama_pembeli);
            FILE *file;
            file = fopen(filename, "w");
            if (file != NULL) {
                fprintf(file, "================= Struk Belanja =================\n");
                fprintf(file, "Nama Pembeli   : %s\n", nama_pembeli);
                fprintf(file, "Nama Produk    | Harga Satuan  | Jumlah     | Total Harga | Diskon    \n");
                fprintf(file, "-------------------------------------------------\n");
                for (i = 0; i < total_barang; i++) {
                    if (jumlah_barang[i] > 0) {
                        float subtotal = barang[i].harga * jumlah_barang[i];
                        float diskon = 0;
                        if (jumlah_barang[i] > 3) {
                            diskon = subtotal * 0.10; // Diskon 10% jika jumlah produk melebihi 3
                        }
                        if (jumlah_barang[i] > 5) {
                            diskon = subtotal * 0.15; // Diskon 15% jika jumlah produk melebihi 5
                        }
                        fprintf(file, "%-15s | %-13.2f | %-10d | %-11.2f | %-10.2f\n", barang[i].nama, barang[i].harga, jumlah_barang[i], subtotal, diskon);
                    }
                }
                fprintf(file, "-------------------------------------------------\n");
                fprintf(file, "Total Harga   : %.2f\n", total_harga);
                fprintf(file, "Total diskon  : %.2f\n", total_diskon);
                fprintf(file, "Uang yang dibayarkan    : %.2f\n", uang_dibayarkan);
                fprintf(file, "Uang kembalian          : %.2f\n", kembalian);
                fprintf(file, "\n-------------------------------------------------\n");
                fclose(file);
                printf("\nStruk telah berhasil dicetak dalam file '%s'.\n", filename);

            } else {
                printf("Gagal menyimpan struk belanja ke dalam file.\n");
            }
            break;
        }
        int jumlah;
        printf("Jumlah barang: ");
        scanf("%d", &jumlah);
        // Mencari barang sesuai dengan kode yang dimasukkan
        for (i = 0; i < total_barang; i++) {
            if (barang[i].kode == kode) {
                jumlah_barang[i] += jumlah;
                total_belanja += barang[i].harga * jumlah;
                break;
            }
        }
        if (i == total_barang) {
            printf("Kode barang tidak valid.\n");
        }
    } while (1);

    return 0;
}
