/**
 * @file parking_system.c
 * @brief File implementasi untuk Sistem Manajemen Parkir
 * 
 * File ini berisi implementasi semua fungsi yang didefinisikan dalam
 * header parking_system.h, termasuk operasi linked list, queue, dan
 * stack untuk mengelola sistem parkir.
 * 
 * @author Nasrul Wahid Sulaeman
 * @date Mei 2023
 * @copyright Copyright (c) 2023 Nasrul Wahid Sulaeman
 */

#include "parking_system.h"

/**
 * @brief Inisialisasi linked list tipe tempat parkir
 */
void initializeSpotTypes()
{
    spotTypesHead = NULL;
}

/**
 * @brief Menambahkan tipe tempat parkir baru ke linked list
 * 
 * @param id Pengenal unik untuk tipe tempat parkir
 * @param name Nama tipe tempat parkir
 * @param hourlyRate Tarif per jam untuk tipe tempat parkir
 * @param capacity Jumlah total tempat dari tipe ini
 */
void addSpotType(int id, const char *name, float hourlyRate, int capacity)
{
    SpotType *newType = (SpotType *)malloc(sizeof(SpotType));
    newType->id = id;
    strcpy(newType->name, name);
    newType->hourlyRate = hourlyRate;
    newType->capacity = capacity;
    newType->next = NULL;

    if (spotTypesHead == NULL)
    {
        spotTypesHead = newType;
    }
    else
    {
        SpotType *current = spotTypesHead;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newType;
    }
}

/**
 * @brief Menampilkan semua tipe tempat parkir yang tersedia
 */
void displaySpotTypes()
{
    SpotType *current = spotTypesHead;
    printf("\n=== TIPE TEMPAT PARKIR ===\n");
    while (current != NULL)
    {
        printf("[%d] %s - Rp%.2f/jam (Kapasitas: %d)\n",
               current->id, current->name,
               current->hourlyRate, current->capacity);
        current = current->next;
    }
    printf("=========================\n");
}

/**
 * @brief Mencari tipe tempat parkir berdasarkan ID-nya
 * 
 * @param id ID yang dicari
 * @return SpotType* Pointer ke tipe tempat parkir jika ditemukan, NULL jika tidak
 */
SpotType *findSpotType(int id)
{
    SpotType *current = spotTypesHead;
    while (current != NULL)
    {
        if (current->id == id)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

/**
 * @brief Inisialisasi queue parkir
 * 
 * @param q Pointer ke queue yang akan diinisialisasi
 */
void initializeQueue(ParkingQueue *q)
{
    q->front = q->rear = NULL;
}

/**
 * @brief Menambahkan kendaraan ke queue parkir
 * 
 * @param q Pointer ke queue parkir
 * @param ticketId ID tiket unik
 * @param spotTypeId ID tipe tempat parkir
 * @param licensePlate Plat nomor kendaraan
 * @param ownerName Nama pemilik kendaraan
 */
void enqueueVehicle(ParkingQueue *q, int ticketId, int spotTypeId,
                    const char *licensePlate, const char *ownerName)
{
    VehicleRecord *newRecord = (VehicleRecord *)malloc(sizeof(VehicleRecord));
    newRecord->ticketId = ticketId;
    newRecord->spotTypeId = spotTypeId;
    strcpy(newRecord->licensePlate, licensePlate);
    strcpy(newRecord->ownerName, ownerName);
    newRecord->entryTime = time(NULL);
    newRecord->next = NULL;

    if (q->rear == NULL)
    {
        q->front = q->rear = newRecord;
    }
    else
    {
        q->rear->next = newRecord;
        q->rear = newRecord;
    }
}

/**
 * @brief Mengeluarkan kendaraan dari depan queue parkir
 * 
 * @param q Pointer ke queue parkir
 * @return VehicleRecord* Pointer ke catatan kendaraan yang dikeluarkan, NULL jika queue kosong
 */
VehicleRecord *dequeueVehicle(ParkingQueue *q)
{
    if (q->front == NULL)
    {
        return NULL;
    }

    VehicleRecord *temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL)
    {
        q->rear = NULL;
    }

    return temp;
}

/**
 * @brief Menampilkan semua kendaraan yang sedang parkir
 * 
 * @param q Pointer ke queue parkir
 */
void displayParkedVehicles(ParkingQueue *q)
{
    VehicleRecord *current = q->front;
    printf("\n=== KENDARAAN YANG SEDANG PARKIR ===\n");
    if (current == NULL) {
        printf("Tidak ada kendaraan yang sedang parkir.\n");
    } else {
        while (current != NULL)
        {
            SpotType *spot = findSpotType(current->spotTypeId);
            printf("Tiket #%d - %s (%s) - Tipe Tempat: %s - Waktu Masuk: %s",
                   current->ticketId, current->ownerName,
                   current->licensePlate, spot->name, 
                   ctime(&current->entryTime));
            current = current->next;
        }
    }
    printf("================================\n");
}

/**
 * @brief Memeriksa apakah queue parkir kosong
 * 
 * @param q Pointer ke queue parkir
 * @return int 1 jika kosong, 0 jika tidak
 */
int isQueueEmpty(ParkingQueue *q)
{
    return q->front == NULL;
}

/**
 * @brief Inisialisasi stack riwayat parkir
 * 
 * @param h Pointer ke stack riwayat
 */
void initializeHistory(ParkingHistory *h)
{
    h->top = NULL;
    h->count = 0;
}

/**
 * @brief Menambahkan catatan kendaraan ke stack riwayat
 * 
 * @param h Pointer ke stack riwayat
 * @param record Pointer ke catatan kendaraan yang akan ditambahkan
 */
void pushToHistory(ParkingHistory *h, VehicleRecord *record)
{
    record->next = h->top;
    h->top = record;
    h->count++;
}

/**
 * @brief Mengambil catatan kendaraan dari stack riwayat
 * 
 * @param h Pointer ke stack riwayat
 * @return VehicleRecord* Pointer ke catatan yang diambil, NULL jika stack kosong
 */
VehicleRecord *popFromHistory(ParkingHistory *h)
{
    if (h->top == NULL)
    {
        return NULL;
    }

    VehicleRecord *temp = h->top;
    h->top = h->top->next;
    h->count--;
    return temp;
}

/**
 * @brief Menampilkan riwayat parkir
 * 
 * @param h Pointer ke stack riwayat
 */
void displayParkingHistory(ParkingHistory *h)
{
    VehicleRecord *current = h->top;
    printf("\n=== RIWAYAT PARKIR ===\n");
    if (current == NULL) {
        printf("Tidak ada riwayat parkir yang tersedia.\n");
    } else {
        printf("Keluar terbaru lebih dulu:\n");
        while (current != NULL)
        {
            SpotType *spot = findSpotType(current->spotTypeId);
            printf("Tiket #%d - %s (%s) - Tipe Tempat: %s - Waktu Masuk: %s",
                   current->ticketId, current->ownerName,
                   current->licensePlate, spot->name,
                   ctime(&current->entryTime));
            current = current->next;
        }
    }
    printf("=====================\n");
}

/**
 * @brief Memeriksa apakah stack riwayat kosong
 * 
 * @param h Pointer ke stack riwayat
 * @return int 1 jika kosong, 0 jika tidak
 */
int isHistoryEmpty(ParkingHistory *h)
{
    return h->top == NULL;
} 
