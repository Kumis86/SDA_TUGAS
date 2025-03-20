#ifndef QUEUE_H
#define QUEUE_H

#include "boolean.h"
#include "list1.h"

#define MAX_QUEUE 100
#define IDX_UNDEF -1
#define QUEUE_CAPACITY 100

typedef struct {
    List L;
} Queue;

/* Operasi Queue */

/* membuat queue kosong */
void BuatQueue(Queue *q);

/* return true jika queue kosong */
boolean QueueKosong(Queue q);

/* return jumlah elemen dalam queue */
int PanjangQueue(Queue q);

/* menambah val ke dalam queue */
void TambahQueue(Queue *q, int val);

/* menghapus elemen dari queue */
int HapusQueue(Queue *q);

/* mengirim elemen pertama dari queue */
int DepanQueue(Queue q);

/* menampilkan isi queue */
void TampilQueue(Queue q);

#endif