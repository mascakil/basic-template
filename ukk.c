#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Deklarasi Array Data Variabel Global
typedef struct Variabel_Global{
    char produk[20];
    int harga;
    int jumlah;
    int TotalHarga;
    int diskon;
}GVariabel;

// Fungsi Urutan Data Produk Berdasarkan Jumlah
void UrutkanProduk(GVariabel data[]) {
    GVariabel temp; // Deklarasi Variabel temp

    // Fungsi Perulangan Pengurutan
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4 - i; j++) {
            if(data[j].jumlah < data[j+1].jumlah) { // Kondisi Cek Pengurutan Produk, Jika Produk pertama lebih kecil jumlahnya dari produk selanjutnya
                temp = data[j];
                data[j] = data[j+1];
                data[j+1] = temp;
            }// End Kondisi Checking
        }
    } // End Fungsi Perulangan Pengurutan
}

// Fungsi Menentukan Jumlah Diskon
int JumlahDiskon(int jumlah) {
    // Kondisi untuk menentukan jumlah diskon sesuai dengan yang ditetapkan aturan
    if(jumlah > 5) {
        return 15;// Berikan diskon 15% jika jumlah items yang dipilih lebih dari 5
    } else if(jumlah > 3 && jumlah <= 5) {
        return 10; // Berikan diskon 10% jika jumlah items yang dipilih lebih dari 3 dan kurang atau = 5
    } else {
        return 0;// Berikan diskon 0% untuk kondisi diluar itu
    }
    // Akhir Kondisi untuk menentukan jumlah diskon sesuai dengan yang ditetapkan aturan
}

// Fungsi Tampilan Menu Awal
void tampilkanMenuAwal(GVariabel data[]) {
    printf("                                SELAMAT DATANG DI                                 \n");
    printf("                                   TOKO SKENSA                                    \n");
    printf("==================================================================================\n");
    printf("                    Silahkan Pilih Barang yang Anda Inginkan :                    \n");
    printf("==================================================================================\n\n");
    printf("\|No|Barang \t\t|Harga      |\n");
    printf("-------------------------------------\n");
    for(int i=0;i<5;i++){
        printf("|%i.|%s|\t\t|%d|\n",i+1,data[i].produk,data[i].harga);
    }// End Funsi Looping untuk menampilkan data array barang dalam tampilan
    printf("==================================================================================\n\n");
    printf("99. Struk Pembayaran\n");
    printf("55. Reset Pilihan\n");
    printf("00. Keluar Aplikasi\n\n");
}

// Fungsi Rekap Pesanan / Struk Pesanan
void TampilkanStruk(GVariabel data[]) {
    printf("\n\n");
    printf("\n\n                              REKAP PESANAN BARANG                                    \n");
    printf("==================================================================================\n");
    printf("|No|Jumlah  |Nama Barang        |Harga       |Total Harga\t|Diskon         |                  \n");
    printf("==================================================================================\n\n");
    for (int i = 0; i < 5; i++) {
        if (data[i].jumlah != 0) { // Periksa apakah jumlah barang tidak nol
            printf("|%i.|%i\t    |%s\t\t|%i\t     |%i\t\t|%i\t\t|\n", i + 1, data[i].jumlah, data[i].produk, data[i].harga, data[i].TotalHarga, data[i].diskon);
        }
    }// End Funsi Looping untuk menampilkan data array barang dalam tampilan
    printf("==================================================================================\n\n");
}

// Fungsi Eksekusi Program
int main() {

    // Deklarasi Data dari Array Global
    GVariabel data[5] = {
        {"Buku Tulis", 5000, 0},
        {"Pensil", 2000, 0},
        {"Penghapus", 1000, 0},
        {"Penggaris", 1000, 0},
        {"Bujur", 500, 0}
    };
    // Akhir Deklarasi Data dari Array Global

    // Deklarasi Variabel Eksekusi

    // Deklarasi Variabel int
    int BarangDipilih;
    int loop = 0;
    int PersentaseDiskon;
    int TotalSemuaTagihan;
    int TotalDiskon;
    int Tagihan;
    int Pembayaran;
    int Kembalian;
    int IDStruk[20];
    // Akhir Deklarasi Variabel int

    // Deklarasi variable Char / String
    char ZonaWaktu[80];
    char namafile[50];
    // Akhir Deklarasi variable Char / String

    // Akhir Deklarasi Variabel Eksekusi

    // Deklarasi Variabel Fungsi Waktu
    time_t sekarang;
    time(&sekarang);
    struct tm *waktu_lokal = localtime(&sekarang);
    strftime(ZonaWaktu, 80, "%a %b %d %H:%M:%S %Y", waktu_lokal); // Deklarasi Set Time untuk Tampilan
    // Akhir Deklarasi Variabel Fungsi Waktu

    // Panggil Fungsi TampilkanMenuAwal
    tampilkanMenuAwal(data);
    // Akhir Panggil Fungsi TampilkanMenuAwal

    // Fungsi Do While untuk Perulangan Pilihan
    do {

        printf("\==================================================================================\n\n");
        printf("\Input Pilihan yang Anda Inginkan : ");
        scanf("%i", &BarangDipilih);

        if(BarangDipilih < 0 || BarangDipilih  > 5 && BarangDipilih != 99 && BarangDipilih != 55 && BarangDipilih != 00) {
            printf("\--------------------------------------\n");
            printf("\Pilihan Tidak Valid\n");
            continue;

        } else if(BarangDipilih == 99 || BarangDipilih == 55 || BarangDipilih == 00) {
            break;
        }

            printf("\--------------------------------------\n");
            printf("\Masukkan Jumlah %s \t : ", data[BarangDipilih - 1].produk);
            int tambahanJumlah;
            scanf("%i", &tambahanJumlah);
            data[BarangDipilih - 1].jumlah += tambahanJumlah; // Menggunakan += untuk menambahkan jumlah baru ke jumlah yang sudah ada
            printf("\n");


            for( int i = 0; i < 5; i++ ) {
                data[i].TotalHarga = data[i].harga * data[i].jumlah;


                PersentaseDiskon = JumlahDiskon(data[i].jumlah);
                data[i].diskon = (data[i].TotalHarga * PersentaseDiskon) / 100;
            }

            loop++;

    }  while(BarangDipilih != 99 || BarangDipilih != 55 || BarangDipilih != 00);
    // Akhir Fungsi Do While untuk Perulangan Pilihan

    // Panggil Fungsi UrutkanProduk
    UrutkanProduk(data);
    // Akhir Panggil Fungsi UrutkanProduk

    if(BarangDipilih == 55) {

        for(int i = 0; i < 5; i++) {
            data[i].jumlah = 0;
            data[i].TotalHarga = 0;
            data[i].diskon = 0;
        }

        loop = 0;

        while(loop == 0) {
            printf("\n----------------------------------------------------------------------------------\n");
            printf("                               Pilihan Telah Direset                              \n");
            printf("                Silahkan Masukkan Ulang Pilihan yang Anda Inginkan                \n");
            printf("----------------------------------------------------------------------------------\n");

            do {

                printf("==================================================================================\n\n");
                printf("Input Pilihan yang Anda Inginkan : ");
                scanf("%i", &BarangDipilih);

                if(BarangDipilih < 0 || BarangDipilih  > 5 && BarangDipilih != 99 && BarangDipilih != 55 && BarangDipilih != 00) {
                    printf("--------------------------------------\n");
                    printf("Pilihan Tidak Valid\n");
                    continue;

                }

                else if(BarangDipilih == 99 || BarangDipilih == 55 || BarangDipilih == 00) {
                    break;
                }

                    printf("--------------------------------------\n");
                    printf("Masukkan Jumlah %s \t : ", data[BarangDipilih - 1].produk);
                    scanf("%i", &data[BarangDipilih - 1].jumlah);
                    printf("\n");

                    for( int i = 0; i < 5; i++ ) {
                        data[i].TotalHarga = data[i].harga * data[i].jumlah;


                        PersentaseDiskon = JumlahDiskon(data[i].jumlah);
                        data[i].diskon = (data[i].TotalHarga * PersentaseDiskon) / 100;
                    }

                    loop++;

            } while(BarangDipilih != 99 || BarangDipilih != 55 || BarangDipilih != 00);

            if(BarangDipilih == 99 || BarangDipilih == 00) {
                break;
            }
        }
    }

    // Fungsi Jika BarangDipilih == 00
    if(BarangDipilih == 00) {
        printf("\n----------------------------------------------------------------------------------\n");
            printf("                               Keluar Dari Program                              \n");
            printf("----------------------------------------------------------------------------------\n");
        return 0;
    }

    // Fungsi Jika BarangDipilih == 99
    if(BarangDipilih == 99) {

        // Menyimpan ID Struk sebelum mencetak struk ke konsol
        char IDStrukConsole[50];
        sprintf(IDStrukConsole, "%ld", sekarang);

        TampilkanStruk(data);

        TotalSemuaTagihan = data[0].TotalHarga +  data[1].TotalHarga +  data[2].TotalHarga +  data[3].TotalHarga +  data[4].TotalHarga;
        printf("Total Harga \t:Rp. %i,-", TotalSemuaTagihan);

        TotalDiskon = data[0].diskon + data[1].diskon + data[2].diskon + data[3].diskon + data[4].diskon;
        printf("\nTotal Diskon \t:Rp. %i,-", TotalDiskon);

        Tagihan = TotalSemuaTagihan - TotalDiskon;
        printf("\nTotal Bayar \t:Rp. %i,-", Tagihan);

        printf("\n==================================================================================\n\n");

        printf("Masukkan Nominal Pembayaran :Rp. ");
        scanf("%i", &Pembayaran);

        do {

            if(Pembayaran < Tagihan) {

                printf("\nNominal Pembayaran Kurang!, Silahkan Masukkan Ulang Nominal Pembayaran");
                printf("\n==================================================================================\n\n");
                printf("\nMasukkan Ulang Nominal Pembayaran :Rp. ");
                scanf("%i", &Pembayaran);

            } else {
                break;
            }

        } while (Pembayaran != Tagihan || Pembayaran < Tagihan);

        if(Pembayaran == Tagihan || Pembayaran > Tagihan) {
            Kembalian = Pembayaran - Tagihan;
            printf("\nKembalian \t\t    :Rp. %i\n", Kembalian);
            printf("\n==================================================================================\n\n");
            printf("\n==================================================================================\n");
            printf("|                                   TOKO SKENSA                                  |\n");
            printf("|                          JALAN HOS COKROAMINOTO NO. 84                         |\n");
            printf("|                                  DENPASAR, BALI                                |\n");
            printf("|                                  TELP. 081628579                               |\n");
            printf("|                                                                                |\n");
            printf("|ID Struk : %s                                                           |\n", IDStrukConsole);
            printf("==================================================================================\n");
            printf("|No|Jumlah  |Nama Barang        |Harga       |Total Harga\t|Diskon         |                  \n");
            printf("==================================================================================\n\n");
             for (int i = 0; i < 5; i++) {
        if (data[i].jumlah != 0) { // Periksa apakah jumlah barang tidak nol
            printf("|%i.|%i\t    |%s\t\t|%i\t     |%i\t\t|%i\t\t|\n", i + 1, data[i].jumlah, data[i].produk, data[i].harga, data[i].TotalHarga, data[i].diskon);
        }
    }
            printf("==================================================================================\n");
            printf("|                                                                                |\n");
            printf("|Total Harga \t:Rp. %i,-                                                     |\n", TotalSemuaTagihan);
            printf("|Total Diskon \t:Rp. %i,-                                                      |\n", TotalDiskon);
            printf("|Total Bayar \t:Rp. %i,-                                                     |\n", Tagihan);
            printf("|Pembayaran \t:Rp. %i,-                                                     |\n", Pembayaran);
            printf("|Kembalian \t:Rp. %i,-                                                      |\n", Kembalian);
            printf("|                                                                                |\n");
            printf("|Waktu / Hari : %s                                         |\n", ZonaWaktu);
            printf("|                                                                                |\n");
            printf("==================================================================================\n");

        }

    }


    FILE *file;
    sprintf(IDStruk, "%ld", sekarang);
    sprintf(namafile, "Struk_%s.txt", IDStruk);
    file = fopen(namafile, "w");

    fprintf(file, "\n\t\t==================================================================================\n");
    fprintf(file, "\t\t|                                   TOKO SKENSA                                  |\n");
    fprintf(file, "\t\t|                          JALAN HOS COKROAMINOTO NO. 84                         |\n");
    fprintf(file, "\t\t|                                  DENPASAR, BALI                                |\n");
    fprintf(file, "\t\t|                                  TELP. 081628579                               |\n");
    fprintf(file, "\t\t|                                                                                |\n");
    fprintf(file, "\t\t|ID Struk : %s                                                           |\n", IDStruk);
    fprintf(file, "\t\t==================================================================================\n");
    fprintf(file, "\t\t|No|Jumlah  |Nama Barang        |Harga       |Total Harga\t|Diskon         |                  \n");
    fprintf(file, "\t\t==================================================================================\n\n");
     for (int i = 0; i < 5; i++) {
        if (data[i].jumlah != 0) { // Periksa apakah jumlah barang tidak nol
            fprintf(file,"|%i.|%i\t    |%s\t\t|%i\t     |%i\t\t|%i\t\t|\n", i + 1, data[i].jumlah, data[i].produk, data[i].harga, data[i].TotalHarga, data[i].diskon);
        }
    }
    fprintf(file, "\t\t==================================================================================\n");
    fprintf(file, "\t\t|                                                                                |\n");
    fprintf(file, "\t\t|Total Harga \t:Rp. %i,-                                                     |", TotalSemuaTagihan);
    fprintf(file, "\n\t\t|Total Diskon \t:Rp. %i,-                                                      |", TotalDiskon);
    fprintf(file, "\n\t\t|Total Bayar \t:Rp. %i,-                                                     |", Tagihan);
    fprintf(file, "\n\t\t|Pembayaran \t:Rp. %i,-                                                     |", Pembayaran);
    fprintf(file, "\n\t\t|Kembalian \t:Rp. %i,-                                                      |\n", Kembalian);
    fprintf(file, "\t\t|                                                                                |\n");
    fprintf(file, "\t\t|                                                                                |\n");
    fprintf(file, "\t\t|Waktu / Hari : %s                                         |\n", ZonaWaktu);
    fprintf(file, "\t\t|                                                                                |\n");
    fprintf(file, "\t\t==================================================================================\n");

    return 0;
}
// Akhir Fungsi Eksekusi Program
