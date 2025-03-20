/**
 * File: queue.c
 * Implementasi ADT Queue menggunakan Linked List
 */

#include <stdio.h>
#include "queue.h"

/**
 * Membuat Queue baru yang kosong
 * @param q - pointer ke Queue yang akan dibuat
 */
void BuatQueue(Queue *q)
{
    CreateList(&(q->L));
}

/**
 * Memeriksa apakah Queue kosong
 * @param q - Queue yang akan diperiksa
 * @return true jika Queue kosong, false jika tidak
 */
boolean QueueKosong(Queue q)
{
    return ListEmpty(q.L);
}

/**
 * Menghitung panjang/jumlah elemen dalam Queue
 * @param q - Queue yang akan dihitung panjangnya
 * @return jumlah elemen dalam Queue
 */
int PanjangQueue(Queue q)
{
    return NbElmt(q.L);
}

/**
 * Menambahkan elemen baru ke dalam Queue (di belakang)
 * @param q - pointer ke Queue yang akan ditambahkan elemen
 * @param val - nilai yang akan ditambahkan ke Queue
 */
void TambahQueue(Queue *q, int val)
{
    InsVLast(&(q->L), val);
}

/**
 * Menghapus dan mengembalikan elemen pertama dari Queue
 * @param q - pointer ke Queue yang akan dihapus elemennya
 * @return nilai elemen yang dihapus
 * @pre Queue tidak kosong
 */
int HapusQueue(Queue *q)
{
    infotype val;
    DelVFirst(&(q->L), &val);
    return val;
}

/**
 * Mengambil nilai elemen pertama dari Queue tanpa menghapusnya
 * @param q - Queue yang akan diambil nilai pertamanya
 * @return nilai elemen pertama Queue
 * @pre Queue tidak kosong
 */
int DepanQueue(Queue q)
{
    return Info(First(q.L));
}

/**
 * Menampilkan seluruh isi Queue
 * @param q - Queue yang akan ditampilkan isinya
 */
void TampilQueue(Queue q)
{
    if (QueueKosong(q))
    {
        printf("Queue kosong\n");
    }
    else
    {
        printf("Isi Queue: ");
        PrintInfo(q.L);
    }
}