/**
 * @file main_app.c
 * @brief Aplikasi utama untuk Sistem Manajemen Parkir Cerdas
 * 
 * File ini berisi logika program utama untuk sistem manajemen parkir,
 * termasuk menu interaktif, penanganan input pengguna, dan logika bisnis inti.
 * 
 * @author Nasrul Wahid Sulaeman
 * @date Mei 2023
 * @copyright Copyright (c) 2023 Nasrul Wahid Sulaeman
 */

#include "parking_system.h"

/**
 * @brief Inisialisasi tipe tempat parkir default
 * 
 * Fungsi ini menambahkan tipe-tipe tempat parkir yang telah ditentukan ke sistem
 */
void initializeDefaultSpotTypes()
{
    addSpotType(1, "Reguler", 2000.00, 100);
    addSpotType(2, "Premium", 4000.00, 50);
    addSpotType(3, "VIP", 6000.00, 20);
    addSpotType(4, "Difabel", 1500.00, 15);
    addSpotType(5, "Motor", 1000.00, 30);
}

/**
 * @brief Menampilkan pilihan menu utama
 */
void displayOptions()
{
    printf("\n=== SISTEM MANAJEMEN PARKIR  ===\n");
    printf("1. Kendaraan Masuk\n");
    printf("2. Kendaraan Keluar\n");
    printf("3. Lihat Kendaraan Parkir\n");
    printf("4. Lihat Riwayat Parkir\n");
    printf("5. Keluar Program\n");
    printf("Pilihan Anda: ");
}

/**
 * @brief Menghitung biaya parkir untuk sebuah kendaraan
 * 
 * @param entryTime Waktu ketika kendaraan masuk
 * @param hourlyRate Tarif per jam untuk tempat parkir
 * @return float Biaya parkir yang dihitung
 */
float calculateParkingFee(time_t entryTime, float hourlyRate)
{
    time_t currentTime = time(NULL);
    double hours = difftime(currentTime, entryTime) / 3600.0; // Konversi detik ke jam
    if (hours < 0.5) // Biaya minimum setengah jam
        hours = 0.5;
    
    return hourlyRate * hours;
}

/**
 * @brief Fungsi utama
 * 
 * @return int Status keluar
 */
int main()
{
    ParkingQueue parkingLot;
    ParkingHistory history;
    int choice, ticketId = 1001;
    char licensePlate[20], ownerName[50];
    int spotTypeId;

    // Inisialisasi semua struktur data
    initializeSpotTypes();
    initializeQueue(&parkingLot);
    initializeHistory(&history);

    // Tambahkan tipe tempat parkir
    initializeDefaultSpotTypes();

    printf("Selamat Datang di Sistem Manajemen Parkir\n");
    printf("----------------------------------------\n");

    while (1)
    {
        displayOptions();
        scanf("%d", &choice);
        getchar(); // Bersihkan buffer input

        switch (choice)
        {
        case 1: // Kendaraan Masuk
            displaySpotTypes();
            printf("\nMasukkan nama pemilik kendaraan: ");
            fgets(ownerName, 50, stdin);
            ownerName[strcspn(ownerName, "\n")] = 0; // Hapus newline

            printf("Masukkan plat nomor: ");
            fgets(licensePlate, 20, stdin);
            licensePlate[strcspn(licensePlate, "\n")] = 0; // Hapus newline

            printf("Masukkan ID tipe tempat: ");
            scanf("%d", &spotTypeId);

            SpotType *spotType = findSpotType(spotTypeId);
            if (spotType == NULL)
            {
                printf("Tipe tempat tidak ditemukan!\n");
                break;
            }

            enqueueVehicle(&parkingLot, ticketId++, spotTypeId, licensePlate, ownerName);
            printf("Kendaraan berhasil diparkir! Tiket #%d dikeluarkan.\n", ticketId-1);
            break;

        case 2: // Kendaraan Keluar
            if (isQueueEmpty(&parkingLot))
            {
                printf("Tidak ada kendaraan di area parkir!\n");
            }
            else
            {
                int exitTicketId;
                printf("Masukkan ID tiket untuk kendaraan keluar: ");
                scanf("%d", &exitTicketId);
                
                // Cari kendaraan dalam queue
                VehicleRecord *current = parkingLot.front;
                VehicleRecord *prev = NULL;
                
                while (current != NULL && current->ticketId != exitTicketId) {
                    prev = current;
                    current = current->next;
                }
                
                if (current == NULL) {
                    printf("Tiket tidak ditemukan!\n");
                    break;
                }
                
                // Keluarkan kendaraan dari queue
                if (prev == NULL) {
                    // Kendaraan ada di depan
                    parkingLot.front = current->next;
                    if (parkingLot.front == NULL) {
                        parkingLot.rear = NULL;
                    }
                } else {
                    // Kendaraan ada di tengah atau akhir
                    prev->next = current->next;
                    if (current->next == NULL) {
                        parkingLot.rear = prev;
                    }
                }
                
                // Hitung biaya parkir
                SpotType *spot = findSpotType(current->spotTypeId);
                float fee = calculateParkingFee(current->entryTime, spot->hourlyRate);
                
                printf("Kendaraan dengan tiket #%d sedang keluar.\n", current->ticketId);
                printf("Pemilik: %s, Plat Nomor: %s\n", current->ownerName, current->licensePlate);
                printf("Durasi parkir: %.2f jam\n", difftime(time(NULL), current->entryTime) / 3600.0);
                printf("Biaya parkir: Rp%.2f\n", fee);
                
                // Tambahkan ke riwayat
                pushToHistory(&history, current);
                printf("Terima kasih telah menggunakan fasilitas parkir kami!\n");
            }
            break;

        case 3: // Lihat Kendaraan Parkir
            displayParkedVehicles(&parkingLot);
            break;

        case 4: // Lihat Riwayat
            displayParkingHistory(&history);
            break;

        case 5: // Keluar Program
            printf("Terima kasih telah menggunakan Sistem Manajemen Parkir Cerdas!\n");
            return 0;

        default:
            printf("Pilihan tidak valid! Silakan coba lagi.\n");
        }
    }

    return 0;
} 
