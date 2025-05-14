#include <stdio.h>
#include <stdbool.h>
#include "nbtrees.h"

int main() {
    Isi_Tree T;
    Create_tree(T, 8);

    int pilihan;
    char cari;
    
    do {
        printf("\n===== MENU OPERASI NON BINARY TREE =====\n");
        printf("1. Tampilkan PreOrder\n");
        printf("2. Tampilkan InOrder\n");
        printf("3. Tampilkan PostOrder\n");
        printf("4. Tampilkan Level Order\n");
        printf("5. Tampilkan jumlah node\n");
        printf("6. Tampilkan jumlah daun\n");
        printf("7. Tampilkan level dari simpul tertentu\n");
        printf("8. Tampilkan depth/tinggi tree\n");
        printf("9. Cari simpul\n");
        printf("10. Tampilkan isi tree (detail)\n");
        printf("0. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                printf("PreOrder: ");
                PreOrder(T);
                printf("\n");
                break;
            case 2:
                printf("InOrder: ");
                InOrder(T);
                printf("\n");
                break;
            case 3:
                printf("PostOrder: ");
                PostOrder(T);
                printf("\n");
                break;
            case 4:
                printf("Level Order: ");
                Level_order(T, nbElmt(T));
                printf("\n");
                break;
            case 5:
                printf("Jumlah node: %d\n", nbElmt(T));
                break;
            case 6:
                printf("Jumlah daun: %d\n", nbDaun(T));
                break;
            case 7:
                printf("Masukkan simpul: ");
                scanf(" %c", &cari);
                printf("Level simpul '%c' adalah %d\n", cari, Level(T, cari));
                break;
            case 8:
                printf("Depth/tinggi tree: %d\n", Depth(T));
                break;
            case 9:
                printf("Masukkan simpul yang dicari: ");
                scanf(" %c", &cari);
                if (Search(T, cari))
                    printf("Simpul '%c' ditemukan.\n", cari);
                else
                    printf("Simpul '%c' tidak ditemukan.\n", cari);
                break;
            case 10:
                PrintTree(T);
                break;
            case 0:
                printf("Terima kasih!\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }

    } while (pilihan != 0);

    return 0;
}
