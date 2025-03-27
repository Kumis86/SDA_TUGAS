/*
 * Program: ADT Kasus 5
 * Pembuat: Naculz
 * Tanggal: 27 Maret 2025
 */
 
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct NamaNode {
    char nama[50];
    struct NamaNode *next;
} NamaNode;

// Fungsi ADT Linked List
NamaNode* buatNodeNama(char *nama);
void tambahNama(NamaNode **head, char *nama);
void tampilkanNama(NamaNode *head);
int hitungNama(NamaNode *head);
void hapusSemuaNama(NamaNode **head);

#endif

