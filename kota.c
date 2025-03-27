/*
 * Program: ADT Kasus 5
 * Pembuat: Naculz
 * Tanggal: 27 Maret 2025
 */

#include <stdio.h>
#include <string.h>
#include "kota.h"

Kota daftarKota[MAX_KOTA];
int totalKota = 0;

void tambahKota(char *namaKota) {
    if (totalKota < MAX_KOTA) {
        strcpy(daftarKota[totalKota].namaKota, namaKota);
        daftarKota[totalKota].head = NULL;
        totalKota++;
    } else {
        printf("Maksimum kota telah tercapai!\n");
    }
}

void tambahNamaKeKota(char *namaKota, char *nama) {
    for (int i = 0; i < totalKota; i++) {
        if (strcmp(daftarKota[i].namaKota, namaKota) == 0) {
            tambahNama(&daftarKota[i].head, nama);
            return;
        }
    }
    printf("Kota tidak ditemukan!\n");
}

void tampilkanData() {
    printf("\n=== Daftar Kota dan Nama ===\n");
    for (int i = 0; i < totalKota; i++) {
        printf("%s: ", daftarKota[i].namaKota);
        tampilkanNama(daftarKota[i].head);
        printf("\n");
    }
}

void hapusKota(char *namaKota) {
    for (int i = 0; i < totalKota; i++) {
        if (strcmp(daftarKota[i].namaKota, namaKota) == 0) {
            printf("Menghapus Kota %s beserta datanya...\n", daftarKota[i].namaKota);
            hapusSemuaNama(&daftarKota[i].head);

            for (int j = i; j < totalKota - 1; j++) {
                daftarKota[j] = daftarKota[j + 1];
            }
            totalKota--;
            return;
        }
    }
    printf("Kota tidak ditemukan!\n");
}

void tampilkanKota(char *namaKota) {
    for (int i = 0; i < totalKota; i++) {
        if (strcmp(daftarKota[i].namaKota, namaKota) == 0) {
            printf("Kota %s: ", daftarKota[i].namaKota);
            tampilkanNama(daftarKota[i].head);
            printf("\n");
            return;
        }
    }
    printf("Kota tidak ditemukan!\n");
}

void statistik() {
    printf("\n=== Statistik ===\n");
    printf("Total Kota: %d\n", totalKota);
    int totalNama = 0;
    for (int i = 0; i < totalKota; i++) {
        int jumlahNama = hitungNama(daftarKota[i].head);
        printf("- %s: %d nama\n", daftarKota[i].namaKota, jumlahNama);
        totalNama += jumlahNama;
    }
    printf("Total Nama: %d\n", totalNama);
}

