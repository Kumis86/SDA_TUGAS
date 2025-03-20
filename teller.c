/**
 * File: teller.c
 * Implementasi sistem antrian teller bank
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "teller.h"

/**
 * Membuat sistem teller baru dengan jumlah teller tertentu
 * @param ts - pointer ke TellerSystem yang akan dibuat
 * @param n - jumlah teller yang akan dibuat
 */
void BuatSistemTeller(TellerSystem *ts, int n) {
    ts->numTellers = n;
    ts->tellers = (Teller *)malloc(n * sizeof(Teller));
    
    for (int i = 0; i < n; i++) {
        ts->tellers[i].currentNumber = 0;
        ts->tellers[i].customersServed = 0;
        BuatQueue(&(ts->tellers[i].queue));
    }
}

/**
 * Menambahkan teller baru ke dalam sistem
 * @param ts - pointer ke TellerSystem
 * @param name - nama teller yang akan ditambahkan
 * @param index - indeks posisi teller
 * @return true jika berhasil ditambahkan, false jika gagal
 */
boolean TambahTeller(TellerSystem *ts, char *name, int index) {
    if (index < 0 || index >= ts->numTellers) {
        return false;
    }
    
    // Periksa apakah nama sudah ada
    if (CekNamaTeller(*ts, name)) {
        return false;
    }
    
    strcpy(ts->tellers[index].name, name);
    return true;
}

/**
 * Memeriksa apakah nama teller sudah ada dalam sistem
 * @param ts - TellerSystem yang akan diperiksa
 * @param name - nama teller yang akan dicek
 * @return true jika nama sudah ada, false jika belum
 */
boolean CekNamaTeller(TellerSystem ts, char *name) {
    for (int i = 0; i < ts.numTellers; i++) {
        if (strcmp(ts.tellers[i].name, name) == 0) {
            return true;
        }
    }
    return false;
}

/**
 * Mencari indeks teller berdasarkan nama
 * @param ts - TellerSystem yang akan dicari
 * @param name - nama teller yang dicari
 * @return indeks teller jika ditemukan, -1 jika tidak ditemukan
 */
int CariTeller(TellerSystem ts, char *name) {
    for (int i = 0; i < ts.numTellers; i++) {
        if (strcmp(ts.tellers[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * Mengambil nomor antrian baru untuk teller tertentu
 * @param ts - pointer ke TellerSystem
 * @param tellerIndex - indeks teller yang dipilih
 * @return nomor antrian yang diambil, -1 jika gagal
 */
int AmbilNomorAntrian(TellerSystem *ts, int tellerIndex) {
    if (tellerIndex < 0 || tellerIndex >= ts->numTellers) {
        return -1;
    }
    
    Teller *t = &(ts->tellers[tellerIndex]);
    t->currentNumber++;
    TambahQueue(&(t->queue), t->currentNumber);
    
    return t->currentNumber;
}

/**
 * Memproses antrian pada teller tertentu
 * @param ts - pointer ke TellerSystem
 * @param tellerIndex - indeks teller yang akan memproses antrian
 * @return true jika berhasil memproses antrian, false jika gagal
 */
boolean ProsesAntrian(TellerSystem *ts, int tellerIndex) {
    if (tellerIndex < 0 || tellerIndex >= ts->numTellers) {
        return false;
    }
    
    Teller *t = &(ts->tellers[tellerIndex]);
    if (QueueKosong(t->queue)) {
        return false;
    }
    
    HapusQueue(&(t->queue));
    t->customersServed++;
    return true;
}

/**
 * Menampilkan informasi status teller tertentu
 * @param t - Teller yang akan ditampilkan informasinya
 */
void TampilTeller(Teller t) {
    printf("\nTeller: %s\n", t.name);
    printf("Jumlah pelanggan dilayani: %d\n", t.customersServed);
    printf("Antrian saat ini: ");
    TampilQueue(t.queue);
    printf("\n");
}

/**
 * Menampilkan informasi status semua teller dalam sistem
 * @param ts - TellerSystem yang akan ditampilkan informasinya
 */
void TampilSemuaTeller(TellerSystem ts) {
    printf("\n=== Status Semua Teller ===\n");
    for (int i = 0; i < ts.numTellers; i++) {
        printf("\n[Teller %d]\n", i + 1);
        TampilTeller(ts.tellers[i]);
    }
}

/**
 * Membersihkan alokasi memori sistem teller
 * @param ts - pointer ke TellerSystem yang akan dibersihkan
 */
void BersihkanSistemTeller(TellerSystem *ts) {
    free(ts->tellers);
    ts->numTellers = 0;
} 