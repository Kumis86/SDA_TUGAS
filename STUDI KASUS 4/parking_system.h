/**
 * @file parking_system.h
 * @brief File header untuk Sistem Manajemen Parkir
 * 
 * File ini berisi definisi struktur dan prototipe fungsi
 * untuk Sistem Manajemen Parkir. Sistem ini mengimplementasikan tiga ADT:
 * - Singly Linked List (SLL) untuk tipe tempat parkir
 * - Queue untuk kendaraan yang sedang parkir
 * - Stack untuk riwayat parkir
 * 
 * @author Nasrul Wahid Sulaeman
 * @date Mei 2023
 * @copyright Copyright (c) 2023 Nasrul Wahid Sulaeman
 */

#ifndef PARKING_SYSTEM_H
#define PARKING_SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * @struct SpotType
 * @brief Struktur untuk tipe tempat parkir (Diimplementasikan sebagai SLL)
 */
typedef struct SpotType {
    int id;                  /**< ID unik tipe tempat parkir */
    char name[50];           /**< Nama tipe tempat parkir */
    float hourlyRate;        /**< Tarif per jam */
    int capacity;            /**< Kapasitas total tipe tempat ini */
    struct SpotType* next;   /**< Pointer ke tipe tempat berikutnya */
} SpotType;

/**
 * @struct VehicleRecord
 * @brief Struktur untuk catatan parkir kendaraan
 */
typedef struct VehicleRecord {
    int ticketId;            /**< ID tiket unik */
    int spotTypeId;          /**< ID tipe tempat parkir terkait */
    char licensePlate[20];   /**< Plat nomor kendaraan */
    char ownerName[50];      /**< Nama pemilik kendaraan */
    time_t entryTime;        /**< Waktu masuk */
    struct VehicleRecord* next; /**< Pointer ke catatan berikutnya */
} VehicleRecord;

/** @brief Head dari linked list tipe tempat parkir */
SpotType* spotTypesHead;

/**
 * @struct ParkingQueue
 * @brief Implementasi Queue untuk catatan parkir aktif
 */
typedef struct {
    VehicleRecord* front;    /**< Depan queue */
    VehicleRecord* rear;     /**< Belakang queue */
} ParkingQueue;

/**
 * @struct ParkingHistory
 * @brief Implementasi Stack untuk riwayat parkir
 */
typedef struct {
    VehicleRecord* top;      /**< Puncak stack */
    int count;               /**< Jumlah catatan dalam stack */
} ParkingHistory;

/* Prototipe fungsi */

/**
 * @brief Fungsi-fungsi untuk Linked List Tipe Tempat Parkir
 */
void initializeSpotTypes();
void addSpotType(int id, const char* name, float hourlyRate, int capacity);
void displaySpotTypes();
SpotType* findSpotType(int id);

/**
 * @brief Fungsi-fungsi untuk Queue Parkir
 */
void initializeQueue(ParkingQueue* q);
void enqueueVehicle(ParkingQueue* q, int ticketId, int spotTypeId, const char* licensePlate, const char* ownerName);
VehicleRecord* dequeueVehicle(ParkingQueue* q);
void displayParkedVehicles(ParkingQueue* q);
int isQueueEmpty(ParkingQueue* q);

/**
 * @brief Fungsi-fungsi untuk Stack Riwayat Parkir
 */
void initializeHistory(ParkingHistory* h);
void pushToHistory(ParkingHistory* h, VehicleRecord* record);
VehicleRecord* popFromHistory(ParkingHistory* h);
void displayParkingHistory(ParkingHistory* h);
int isHistoryEmpty(ParkingHistory* h);

#endif /* PARKING_SYSTEM_H */ 