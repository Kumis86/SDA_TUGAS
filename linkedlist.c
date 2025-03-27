/*
 * Program: ADT Kasus 5
 * Pembuat: Naculz
 * Tanggal: 27 Maret 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

NamaNode* buatNodeNama(char *nama) {
    NamaNode *baru = (NamaNode*)malloc(sizeof(NamaNode));
    strcpy(baru->nama, nama);
    baru->next = NULL;
    return baru;
}

void tambahNama(NamaNode **head, char *nama) {
    NamaNode *baru = buatNodeNama(nama);
    if (*head == NULL) {
        *head = baru;
    } else {
        NamaNode *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = baru;
    }
}

void tampilkanNama(NamaNode *head) {
    NamaNode *temp = head;
    while (temp != NULL) {
        printf("%s", temp->nama);
        if (temp->next != NULL) printf(" -> ");
        temp = temp->next;
    }
}

int hitungNama(NamaNode *head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

void hapusSemuaNama(NamaNode **head) {
    NamaNode *temp = *head;
    while (temp != NULL) {
        NamaNode *hapus = temp;
        temp = temp->next;
        free(hapus);
    }
    *head = NULL;
}

