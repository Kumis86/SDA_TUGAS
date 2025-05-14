#include <stdio.h>
#include <stdbool.h>
#include "nbtrees.h"


void Create_tree(Isi_Tree X, int Jml_Node) {
   
    X[1] = (nbtree){'A', 2, 0, 0};
    X[2] = (nbtree){'B', 4, 3, 1};
    X[3] = (nbtree){'C', 6, 0, 1};
    X[4] = (nbtree){'D', 0, 5, 2};
    X[5] = (nbtree){'E', 0, 0, 2};
    X[6] = (nbtree){'F', 0, 7, 3};
    X[7] = (nbtree){'G', 0, 8, 3};
    X[8] = (nbtree){'H', 0, 0, 3};

    for (int i = 9; i <= jml_maks; i++) {
        X[i] = (nbtree){' ', 0, 0, 0};
    }
}

boolean IsEmpty(Isi_Tree P) {
    if (P[1].info == ' ') {
        return true;
    } else {
        return false;
    }
}

int nbElmt(Isi_Tree P) {
    int count = 0;
    for (int i = 1; i <= jml_maks; i++) {
        if (P[i].info != ' ') {
            count++;
        }
    }
    return count;
}

/***** Traversal *****/

void PreOrderNode(Isi_Tree P, int idx) {
    if (idx == 0 || P[idx].info == ' ') return;

    printf("%c ", P[idx].info);                 
    PreOrderNode(P, P[idx].ps_fs);               
    PreOrderNode(P, P[idx].ps_nb);              
}

void PreOrder(Isi_Tree P) {
    PreOrderNode(P, 1);  
}

void InOrderNode(Isi_Tree P, int idx) {
    if (idx == 0 || P[idx].info == ' ') return;

    if (P[idx].ps_fs != 0)
        InOrderNode(P, P[idx].ps_fs);         

    printf("%c ", P[idx].info);               

    if (P[idx].ps_fs != 0)
        InOrderNode(P, P[P[idx].ps_fs].ps_nb); 
}

void InOrder(Isi_Tree P) {
    InOrderNode(P, 1);
}

void PostOrderNode(Isi_Tree P, int idx) {
    if (idx == 0 || P[idx].info == ' ') return;

    PostOrderNode(P, P[idx].ps_fs);     
    PostOrderNode(P, P[idx].ps_nb);    
    printf("%c ", P[idx].info);         
}

void PostOrder(Isi_Tree P) {
    PostOrderNode(P, 1);
}

void Level_order(Isi_Tree P, int Maks_node) {
    for (int i = 1; i <= Maks_node; i++) {
        if (P[i].info != ' ')
            printf("%c ", P[i].info);
    }
}

void PrintTree(Isi_Tree P) {
    for (int i = 1; i <= jml_maks; i++) {
        if (P[i].info != ' ') {
            printf("Index %d: %c (fs: %d, nb: %d, pr: %d)\n",
                   i, P[i].info, P[i].ps_fs, P[i].ps_nb, P[i].ps_pr);
        }
    }
}

boolean Search(Isi_Tree P, infotype X) {
    for (int i = 1; i <= jml_maks; i++) {
        if (P[i].info == X) return true;
    }
    return false;
}

int nbDaun(Isi_Tree P) {
    int count = 0;
    for (int i = 1; i <= jml_maks; i++) {
        if (P[i].info != ' ' && P[i].ps_fs == 0) {
            count++;
        }
    }
    return count;
}

int Level(Isi_Tree P, infotype X) {
    for (int i = 1; i <= jml_maks; i++) {
        if (P[i].info == X) {
            int level = 0;
            int parent = P[i].ps_pr;
            while (parent != 0) {
                level++;
                parent = P[parent].ps_pr;
            }
            return level;
        }
    }
    return -1;  
}

int DepthNode(Isi_Tree P, int idx) {
    if (idx == 0 || P[idx].info == ' ') return -1;

    int maxChildDepth = -1;
    int child = P[idx].ps_fs;
    while (child != 0) {
        int d = DepthNode(P, child);
        if (d > maxChildDepth) maxChildDepth = d;
        child = P[child].ps_nb;
    }

    return maxChildDepth + 1;
}

int Depth(Isi_Tree P) {
    if (IsEmpty(P)) return 0;
    return DepthNode(P, 1); 
}

int Max(infotype Data1, infotype Data2) {
    return (Data1 > Data2) ? Data1 : Data2;
}