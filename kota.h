/*
 * Program: ADT Kasus 5
 * Pembuat: Naculz
 * Tanggal: 27 Maret 2025
 */

#ifndef KOTA_H
#define KOTA_H

#include "linkedlist.h"

#define MAX_KOTA 10

typedef struct Kota {
    char namaKota[50];
    NamaNode *head;
} Kota;

extern Kota daftarKota[MAX_KOTA];

void tambahKota(char *namaKota);
void tambahNamaKeKota(char *namaKota, char *nama);
void tampilkanData();
void hapusKota(char *namaKota);
void tampilkanKota(char *namaKota);
void statistik();

#endif

