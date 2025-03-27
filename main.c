/*
 * Program: ADT Kasus 5
 * Pembuat: Naculz
 * Tanggal: 27 Maret 2025
 */

#include <stdio.h>
#include <string.h>
#include "kota.h"

void menu() {
    printf("\n=== DATA PENDUDUK KOTA ===\n");
    printf("1. Tambah Kota\n");
    printf("2. Tambah Penduduk ke Kota\n");
    printf("3. Tampilkan Data\n");
    printf("4. Hapus Kota\n");
    printf("5. Tampilkan Kota Tertentu\n");
    printf("6. Statistik\n");
    printf("7. Keluar\n");
}

int main() {
    int pilihan;
    char namaKota[50], nama[50];

    while (1) {
        menu();
        printf("Pilih: ");
        scanf("%d", &pilihan);
        getchar();

        switch (pilihan) {
            case 1:
                printf("Masukkan nama kota: ");
                fgets(namaKota, sizeof(namaKota), stdin);
                namaKota[strcspn(namaKota, "\n")] = 0;
                tambahKota(namaKota);
                break;
            
            case 2:
                printf("Masukkan nama kota: ");
                fgets(namaKota, sizeof(namaKota), stdin);
                namaKota[strcspn(namaKota, "\n")] = 0;
                printf("Masukkan nama orang: ");
                fgets(nama, sizeof(nama), stdin);
                nama[strcspn(nama, "\n")] = 0;
                tambahNamaKeKota(namaKota, nama);
                break;
            
            case 3:
                tampilkanData();
                break;

            case 4:
                printf("Masukkan nama kota yang akan dihapus: ");
                fgets(namaKota, sizeof(namaKota), stdin);
                namaKota[strcspn(namaKota, "\n")] = 0;
                hapusKota(namaKota);
                break;

            case 5:
                printf("Masukkan nama kota: ");
                fgets(namaKota, sizeof(namaKota), stdin);
                namaKota[strcspn(namaKota, "\n")] = 0;
                tampilkanKota(namaKota);
                break;

            case 6:
                statistik();
                break;

            case 7:
                return 0;
        }
    }
}

