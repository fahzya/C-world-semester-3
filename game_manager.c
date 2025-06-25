#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Game {
    char id[10];
    char nama[50];
    char deskripsi[100];
    char developer[50];
    int harga;
    struct Game* next;
} Game;

Game* head = NULL;

// Login
int login() {
    char user[20], pass[20];
    int attempts = 3;

    while (attempts--) {
        printf("Username: ");
        scanf("%s", user);
        printf("Password: ");
        scanf("%s", pass);

        if (strcmp(user, "admin") == 0 && strcmp(pass, "123") == 0) {
            printf("Login berhasil!\n");
            return 1;
        } else {
            printf("Login gagal. Sisa percobaan: %d\n", attempts);
        }
    }

    printf("Anda telah gagal login sebanyak 3 kali. Program berhenti.\n");
    return 0;
}

// Tambah game
void tambahGame() {
    Game* newGame = (Game*) malloc(sizeof(Game));
    printf("Masukkan ID game: "); scanf("%s", newGame->id);
    printf("Masukkan Nama game: "); scanf(" %[^\n]", newGame->nama);
    printf("Masukkan Deskripsi game: "); scanf(" %[^\n]", newGame->deskripsi);
    printf("Masukkan Developer: "); scanf(" %[^\n]", newGame->developer);
    printf("Masukkan Harga: "); scanf("%d", &newGame->harga);
    newGame->next = head;
    head = newGame;
    printf("Game berhasil ditambahkan!\n");
}

// Tampilkan semua game
void tampilkanGame() {
    Game* temp = head;
    if (!temp) {
        printf("Belum ada game.\n");
        return;
    }

    while (temp) {
        printf("\nID: %s\nNama: %s\nDeskripsi: %s\nDeveloper: %s\nHarga: %d\n",
            temp->id, temp->nama, temp->deskripsi, temp->developer, temp->harga);
        temp = temp->next;
    }
}

// Update game
void updateGame() {
    char id[10];
    printf("Masukkan ID game yang ingin diubah: ");
    scanf("%s", id);

    Game* temp = head;
    while (temp) {
        if (strcmp(temp->id, id) == 0) {
            printf("Masukkan Nama game baru: "); scanf(" %[^\n]", temp->nama);
            printf("Masukkan Deskripsi baru: "); scanf(" %[^\n]", temp->deskripsi);
            printf("Masukkan Developer baru: "); scanf(" %[^\n]", temp->developer);
            printf("Masukkan Harga baru: "); scanf("%d", &temp->harga);
            printf("Game berhasil diperbarui!\n");
            return;
        }
        temp = temp->next;
    }
    printf("Game tidak ditemukan.\n");
}

// Hapus game
void hapusGame() {
    char id[10];
    printf("Masukkan ID game yang ingin dihapus: ");
    scanf("%s", id);

    Game *temp = head, *prev = NULL;

    while (temp && strcmp(temp->id, id) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) {
        printf("Game tidak ditemukan.\n");
        return;
    }

    if (!prev) head = temp->next;
    else prev->next = temp->next;

    free(temp);
    printf("Game berhasil dihapus.\n");
}

// Cari game
void cariGame() {
    char nama[50];
    printf("Masukkan nama game yang dicari: ");
    scanf(" %[^\n]", nama);

    Game* temp = head;
    while (temp) {
        if (strcmp(temp->nama, nama) == 0) {
            printf("Game ditemukan:\nID: %s\nNama: %s\nDeskripsi: %s\nDeveloper: %s\nHarga: %d\n",
                temp->id, temp->nama, temp->deskripsi, temp->developer, temp->harga);
            return;
        }
        temp = temp->next;
    }
    printf("Game tidak ditemukan.\n");
}

// Sorting (Bubble sort by harga)
void bubbleSortHarga() {
    if (!head || !head->next) return;

    int swapped;
    Game *ptr1, *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->harga > ptr1->next->harga) {
                // swap isi node
                char idTmp[10], namaTmp[50], descTmp[100], devTmp[50];
                int hargaTmp;

                strcpy(idTmp, ptr1->id);
                strcpy(namaTmp, ptr1->nama);
                strcpy(descTmp, ptr1->deskripsi);
                strcpy(devTmp, ptr1->developer);
                hargaTmp = ptr1->harga;

                strcpy(ptr1->id, ptr1->next->id);
                strcpy(ptr1->nama, ptr1->next->nama);
                strcpy(ptr1->deskripsi, ptr1->next->deskripsi);
                strcpy(ptr1->developer, ptr1->next->developer);
                ptr1->harga = ptr1->next->harga;

                strcpy(ptr1->next->id, idTmp);
                strcpy(ptr1->next->nama, namaTmp);
                strcpy(ptr1->next->deskripsi, descTmp);
                strcpy(ptr1->next->developer, devTmp);
                ptr1->next->harga = hargaTmp;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
    printf("Game berhasil diurutkan berdasarkan harga.\n");
}

// Simpan ke file
void simpanKeFile() {
    FILE* file = fopen("data_game.txt", "w");
    Game* temp = head;
    while (temp) {
        fprintf(file, "%s;%s;%s;%s;%d\n", temp->id, temp->nama, temp->deskripsi, temp->developer, temp->harga);
        temp = temp->next;
    }
    fclose(file);
    printf("Data berhasil disimpan ke data_game.txt\n");
}

// Menu utama
void menu() {
    int pilihan;
    do {
        printf("\n===== MENU GAME =====\n");
        printf("1. Tambah Game\n2. Tampilkan Semua Game\n3. Update Game\n4. Hapus Game\n");
        printf("5. Cari Game\n6. Urutkan Harga\n7. Simpan ke File\n8. Keluar\n");
        printf("Pilih: ");
        scanf("%d", &pilihan);
        switch (pilihan) {
            case 1: tambahGame(); break;
            case 2: tampilkanGame(); break;
            case 3: updateGame(); break;
            case 4: hapusGame(); break;
            case 5: cariGame(); break;
            case 6: bubbleSortHarga(); break;
            case 7: simpanKeFile(); break;
        }
    } while (pilihan != 8);
}

// Main function
int main() {
    if (login()) {
        menu();
    }
    return 0;
}
