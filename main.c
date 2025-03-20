/**
 * File: main.c
 * Program utama sistem antrian bank
 * Program ini mengimplementasikan sistem antrian bank sederhana
 * dengan multiple teller menggunakan ADT Queue
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "teller.h"

/**
 * Menampilkan menu pilihan yang tersedia dalam sistem
 */
void TampilMenu()
{
    printf("\nSistem Antrian Bank\n");
    printf("1. Ambil Nomor Antrian\n");
    printf("2. Proses Antrian\n");
    printf("3. Tampilkan Status Semua Teller\n");
    printf("4. Keluar\n");
    printf("Pilih opsi (1-4): ");
}

/**
 * Program utama
 * Mengimplementasikan sistem antrian bank dengan fitur:
 * - Inisialisasi sistem dengan jumlah teller yang diinginkan
 * - Pengambilan nomor antrian
 * - Pemrosesan antrian
 * - Menampilkan status teller
 */
int main()
{
    TellerSystem ts;
    int numTellers;
    int choice;
    char tellerName[50];
    
    // Input jumlah teller dan inisialisasi sistem
    printf("Masukkan jumlah teller: ");
    scanf("%d", &numTellers);
    
    // Buat sistem teller dengan jumlah yang ditentukan
    BuatSistemTeller(&ts, numTellers);
    
    // Input nama untuk setiap teller
    // Memastikan tidak ada nama teller yang duplikat
    for (int i = 0; i < numTellers; i++) {
        do {
            printf("Masukkan nama untuk teller ke-%d: ", i + 1);
            scanf(" %[^\n]s", tellerName);
            
            if (CekNamaTeller(ts, tellerName)) {
                printf("Nama teller sudah ada! Gunakan nama lain.\n");
            }
        } while (!TambahTeller(&ts, tellerName, i));
    }
    
    // Loop utama program
    do {
        TampilMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: { // Ambil nomor antrian
                printf("\nDaftar Teller:\n");
                TampilSemuaTeller(ts);
                printf("\nPilih teller (masukkan nama): ");
                scanf(" %[^\n]s", tellerName);
                
                int tellerIndex = CariTeller(ts, tellerName);
                if (tellerIndex == -1) {
                    printf("Teller tidak ditemukan!\n");
                } else {
                    int queueNumber = AmbilNomorAntrian(&ts, tellerIndex);
                    printf("\nNomor antrian Anda: %d\n", queueNumber);
                    TampilTeller(ts.tellers[tellerIndex]);
                }
                break;
            }
            
            case 2: { // Proses antrian
                printf("\nDaftar Teller:\n");
                TampilSemuaTeller(ts);
                printf("\nPilih teller untuk memproses antrian (masukkan nama): ");
                scanf(" %[^\n]s", tellerName);
                
                int tellerIndex = CariTeller(ts, tellerName);
                if (tellerIndex == -1) {
                    printf("Teller tidak ditemukan!\n");
                } else {
                    if (ProsesAntrian(&ts, tellerIndex)) {
                        printf("\nBerhasil memproses antrian\n");
                    } else {
                        printf("\nTidak ada antrian untuk diproses!\n");
                    }
                    TampilTeller(ts.tellers[tellerIndex]);
                }
                break;
            }
            
            case 3: { // Tampilkan status semua teller
                TampilSemuaTeller(ts);
                break;
            }
            
            case 4: { // Keluar dari program
                printf("\nTerima kasih telah menggunakan Sistem Antrian Bank!\n");
                break;
            }
            
            default: { // Pilihan tidak valid
                printf("\nOpsi tidak valid! Silakan pilih 1-4\n");
                break;
            }
        }
    } while (choice != 4);
    
    // Bersihkan alokasi memori sebelum keluar
    BersihkanSistemTeller(&ts);
    return 0;
}
