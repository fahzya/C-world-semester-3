#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define MAX_LOGIN_ATTEMPT 3

typedef struct Game {
    int id;
    char nama[100];
    char developer[50];
    char deskripsi[200];
    float harga;
    struct Game *next;
} Game;

Game *head = NULL;
char riwayat[1000][200];
int jumlahRiwayat = 0;

// ---------- FUNGSI WINDOWS ----------
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void tampilkanWaktu(int x, int y) {
    time_t now;
    struct tm *local;
    char buffer[50];
    time(&now);
    local = localtime(&now);
    strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %Y", local);
    gotoxy(x, y);
    printf("%s", buffer);
}

void loading() {
    char loadingText[80];
    system("color f0");
    gotoxy((113 - strlen("SELAMAT DATANG DI TUGAS RANCANG KELOMPOK 6"))/2, 7);
    printf("SELAMAT DATANG DI TUGAS RANCANG KELOMPOK 6");
    gotoxy(29, 11);
    putchar(201);
    for (int i = 0; i < 51; i++) {
        putchar(205);
    }
    putchar(187);
    gotoxy(29, 12);
    putchar(186);
    gotoxy(81, 12);
    putchar(186);
    gotoxy(29, 13);
    putchar(200);
    for (int i = 0; i < 51; i++) {
        putchar(205);
    }
    putchar(188);

    for (int i = 0; i <= 100; i++) {
        Sleep(12);

        if (i % 5 == 0) {
            Beep(700, 50);
        }

        snprintf(loadingText, sizeof(loadingText), "Loading : %d%%", i);
        gotoxy((113 - strlen(loadingText))/2, 9);
        printf("%s", loadingText);
        gotoxy(30 + (i / 2), 12);
        putchar(219);
    }

    system("cls");
}

void go(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void centerText(const char *text, int row) {
    int len = strlen(text);
    int pos = (113 - len) / 2;
    gotoxy(pos, row);
    printf("%s", text);
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Data dummy 10 game untuk memenuhi instruksi soal
void inisialisasiGameDummy() {
    Game *dataDummy[] = {
        (Game*)malloc(sizeof(Game)),
        (Game*)malloc(sizeof(Game)),
        (Game*)malloc(sizeof(Game)),
        (Game*)malloc(sizeof(Game)),
        (Game*)malloc(sizeof(Game)),
        (Game*)malloc(sizeof(Game)),
        (Game*)malloc(sizeof(Game)),
        (Game*)malloc(sizeof(Game)),
        (Game*)malloc(sizeof(Game)),
        (Game*)malloc(sizeof(Game))
    };

    // Initialize dummy data
    dataDummy[0]->id = 101; strcpy(dataDummy[0]->nama, "Valorant"); strcpy(dataDummy[0]->developer, "Riot Games"); strcpy(dataDummy[0]->deskripsi, "FPS 5v5 berbasis agent"); dataDummy[0]->harga = 0; dataDummy[0]->next = NULL;
    dataDummy[1]->id = 102; strcpy(dataDummy[1]->nama, "Genshin Impact"); strcpy(dataDummy[1]->developer, "miHoYo"); strcpy(dataDummy[1]->deskripsi, "Game RPG petualangan anime"); dataDummy[1]->harga = 0; dataDummy[1]->next = NULL;
    dataDummy[2]->id = 103; strcpy(dataDummy[2]->nama, "FIFA 23"); strcpy(dataDummy[2]->developer, "EA Sports"); strcpy(dataDummy[2]->deskripsi, "Game sepak bola dunia nyata"); dataDummy[2]->harga = 699000; dataDummy[2]->next = NULL;
    dataDummy[3]->id = 104; strcpy(dataDummy[3]->nama, "Call of Duty"); strcpy(dataDummy[3]->developer, "Activision"); strcpy(dataDummy[3]->deskripsi, "FPS perang modern"); dataDummy[3]->harga = 799000; dataDummy[3]->next = NULL;
    dataDummy[4]->id = 105; strcpy(dataDummy[4]->nama, "PUBG"); strcpy(dataDummy[4]->developer, "Krafton"); strcpy(dataDummy[4]->deskripsi, "Battle royale realistis"); dataDummy[4]->harga = 149000; dataDummy[4]->next = NULL;
    dataDummy[5]->id = 106; strcpy(dataDummy[5]->nama, "Mobile Legends"); strcpy(dataDummy[5]->developer, "Moonton"); strcpy(dataDummy[5]->deskripsi, "MOBA mobile 5v5"); dataDummy[5]->harga = 0; dataDummy[5]->next = NULL;
    dataDummy[6]->id = 107; strcpy(dataDummy[6]->nama, "Minecraft"); strcpy(dataDummy[6]->developer, "Mojang"); strcpy(dataDummy[6]->deskripsi, "Game sandbox dan kreatif"); dataDummy[6]->harga = 399000; dataDummy[6]->next = NULL;
    dataDummy[7]->id = 108; strcpy(dataDummy[7]->nama, "Roblox"); strcpy(dataDummy[7]->developer, "Roblox Corp"); strcpy(dataDummy[7]->deskripsi, "Game user-generated"); dataDummy[7]->harga = 0; dataDummy[7]->next = NULL;
    dataDummy[8]->id = 109; strcpy(dataDummy[8]->nama, "Among Us"); strcpy(dataDummy[8]->developer, "Innersloth"); strcpy(dataDummy[8]->deskripsi, "Social deception game"); dataDummy[8]->harga = 50000; dataDummy[8]->next = NULL;
    dataDummy[9]->id = 110; strcpy(dataDummy[9]->nama, "Apex Legends"); strcpy(dataDummy[9]->developer, "Respawn"); strcpy(dataDummy[9]->deskripsi, "Battle royale futuristik"); dataDummy[9]->harga = 0; dataDummy[9]->next = NULL;

    for (int i = 0; i < 10; i++) {
        if (!head) {
            head = dataDummy[i];
        } else {
            Game *tail = head;
            while (tail->next) tail = tail->next;
            tail->next = dataDummy[i];
        }
    }
}

void login() {
    char username[20];
    char password[20];
    char input;
    int i, attempt = 0;

    while (1) {
        system("cls");

        gotoxy(33, 3);
        printf("====================================================");
        gotoxy(40, 5);
        printf("              MENU LOGIN              ");
        gotoxy(33, 7);
        printf("====================================================");
        gotoxy(33, 8);
        printf("><><><><><><><><><><><><><><><><><><><><><><><><><><");
        gotoxy(33, 9);
        printf("====================================================");

        gotoxy(40, 12);
        printf("USERNAME : ");
        gotoxy(40, 13);
        printf("PASSWORD : ");

        gotoxy(33, 16);
        printf("====================================================");
        gotoxy(34, 17);
        printf("GAME STORE KELOMPOK 6");
        tampilkanWaktu(60, 17);
        gotoxy(33, 18);
        printf("====================================================");

        // Input Username
        gotoxy(51, 12);
        scanf("%s", username);
        clearInputBuffer();

        // Input Password (disamarkan)
        gotoxy(51, 13);
        i = 0;
        while (1) {
            input = getch();
            if (input == 13) break;
            else if (input == 8 && i > 0) {
                i--;
                printf("\b \b");
            } else if (i < (int)sizeof(password) - 1 && input >= 32 && input <= 126) {
                password[i++] = input;
                printf("*");
            }
        }
        password[i] = '\0';

        const char* allowed_users[] = {
            "672024241", "672024243", "672024249",
            "672024201", "672024217", "672024227"
        };

        const char* user_names[] = {
            "Raphael", "Jeremy", "Enrico",
            "Wilson", "Ajeng", "Fahzya"
        };

        int valid = 0;
        int index = -1;
        for (int j = 0; j < sizeof(allowed_users)/sizeof(allowed_users[0]); j++) {
            if (strcmp(username, allowed_users[j]) == 0 && strcmp(password, allowed_users[j]) == 0) {
                valid = 1; // true
                index = j; //5
                break;
            }
        }

        if (valid) {
            system("cls");
            char message[100];
            snprintf(message, sizeof(message), "Selamat datang, %s!", user_names[index]);
            centerText(message, 10);
            Sleep(3000);
            break;
        } else {
            attempt++; //3
            gotoxy(45, 19);
            printf("Username atau password salah.");
            Sleep(1500);
            if (attempt >= MAX_LOGIN_ATTEMPT) {
                gotoxy(40, 21);
                printf("Terlalu banyak percobaan login. Program keluar.\n");
                exit(1);
            }
        }
    }
}

// ---------- FITUR GAME STORE LINKED LIST ----------
Game* buatGameBaru(int id, char *nama, char *developer, char *deskripsi, float harga) {
    Game* g = (Game*) malloc(sizeof(Game));
    g->id = id;
    strcpy(g->nama, nama);
    strcpy(g->developer, developer);
    strcpy(g->deskripsi, deskripsi);
    g->harga = harga;
    g->next = NULL;
    return g;
}

void tambahGame() {
    system("cls");
    int id;
    char nama[100], developer[50], deskripsi[200];
    float harga;

    printf("\nMasukkan ID Game       : ");
    scanf("%d", &id); clearInputBuffer();
    printf("Masukkan Nama Game     : ");
    fgets(nama, sizeof(nama), stdin); nama[strcspn(nama, "\n")] = 0;
    printf("Developer              : ");
    fgets(developer, sizeof(developer), stdin); developer[strcspn(developer, "\n")] = 0;
    printf("Deskripsi Game         : ");
    fgets(deskripsi, sizeof(deskripsi), stdin); deskripsi[strcspn(deskripsi, "\n")] = 0;
    printf("Harga Game (Rp)        : ");
    scanf("%f", &harga); clearInputBuffer();

    // Cek apakah ID sudah ada
    Game *curr = head;
    while (curr) {
        if (curr->id == id) {
            printf("ID Game sudah terdaftar!\n");
            return;
        }
        curr = curr->next;
    }

    Game *baru = buatGameBaru(id, nama, developer, deskripsi, harga);
    if (!head) head = baru;
    else {
        Game *tail = head;
        while (tail->next) tail = tail->next;
        tail->next = baru;
    }
    sprintf(riwayat[jumlahRiwayat++], "Game \"%s\" ditambahkan.", nama);
    printf("Game berhasil ditambahkan!\n");
}

void tampilkanGame() {
    system("cls");
    if (!head) {
        printf("Belum ada game yang dijual.\n");
    } else {
        printf("\nDaftar Game yang Dijual:\n");
        Game *curr = head;
        int i = 1;
        while (curr) {
            printf("\n--- Game ke-%d ---\n", i++);
            printf("ID        : %d\n", curr->id);
            printf("Nama      : %s\n", curr->nama);
            printf("Developer : %s\n", curr->developer);
            printf("Deskripsi : %s\n", curr->deskripsi);
            printf("Harga     : Rp %.2f\n", curr->harga);
            curr = curr->next;
        }
    }
}

void cariGame() {
    system("cls");
    if (!head) {
        printf("Belum ada game yang tersedia.\n");
        return;
    }

    int pilihan;
    printf("Cari berdasarkan:\n");
    printf("1. ID\n2. Nama\n3. Developer\n4. Harga\n");
    printf("Pilihan: ");
    scanf("%d", &pilihan); clearInputBuffer();

    char keyword[100];
    printf("Masukkan kata kunci pencarian: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = 0;

    Game *curr = head;
    int ditemukan = 0;
    while (curr) {
        int cocok = 0;
        switch (pilihan) {
            case 1:
                if (curr->id == atoi(keyword)) cocok = 1;
                break;
            case 2:
                if (strstr(curr->nama, keyword)) cocok = 1;
                break;
            case 3:
                if (strstr(curr->developer, keyword)) cocok = 1;
                break;
            case 4:
                if (curr->harga == atof(keyword)) cocok = 1;
                break;
            default:
                printf("Pilihan tidak valid!\n");
                return;
        }

        if (cocok) {
            if (!ditemukan) {
                printf("\nHasil Pencarian:\n");
            }
            ditemukan = 1;
            printf("\nID        : %d\n", curr->id);
            printf("Nama      : %s\n", curr->nama);
            printf("Developer : %s\n", curr->developer);
            printf("Deskripsi : %s\n", curr->deskripsi);
            printf("Harga     : Rp %.2f\n", curr->harga);
        }
        curr = curr->next;
    }

    if (!ditemukan) {
        printf("\nData tidak ditemukan.\n");
    }
}

void ubahGame() {
    system("cls");
    int id;
    char nama[100], developer[50], deskripsi[200];
    float harga;
    printf("Masukkan ID Game yang ingin diubah: ");
    scanf("%d", &id); clearInputBuffer();
    Game *curr = head;
    while (curr) {
        if (curr->id == id) {
            printf("Nama Game Baru       : ");
            fgets(nama, sizeof(nama), stdin); nama[strcspn(nama, "\n")] = 0;
            printf("Developer Baru       : ");
            fgets(developer, sizeof(developer), stdin); developer[strcspn(developer, "\n")] = 0;
            printf("Deskripsi Baru       : ");
            fgets(deskripsi, sizeof(deskripsi), stdin); deskripsi[strcspn(deskripsi, "\n")] = 0;
            printf("Harga Baru (Rp)      : ");
            scanf("%f", &harga); clearInputBuffer();
            strcpy(curr->nama, nama);
            strcpy(curr->developer, developer);
            strcpy(curr->deskripsi, deskripsi);
            curr->harga = harga;
            sprintf(riwayat[jumlahRiwayat++], "Game ID %d diubah.", id);
            printf("Data berhasil diubah.\n");
            return;
        }
        curr = curr->next;
    }
    printf("Game tidak ditemukan.\n");
}

void hapusGame() {
    system("cls");
    int id;
    printf("Masukkan ID Game yang ingin dihapus: ");
    scanf("%d", &id); clearInputBuffer();
    Game *curr = head, *prev = NULL;
    while (curr) {
        if (curr->id == id) {
            if (prev) prev->next = curr->next;
            else head = curr->next;
            sprintf(riwayat[jumlahRiwayat++], "Game \"%s\" dihapus.", curr->nama);
            free(curr);
            printf("Game berhasil dihapus.\n");
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("Game tidak ditemukan.\n");
}

// ---------- SORTING & SEARCHING ----------
void urutkanGame() {
    system("cls");
    if (!head || !head->next) {
        printf("Data kurang dari 2, tidak perlu diurutkan.\n");
        return;
    }

    int pilihan, arah;
    printf("\nUrutkan berdasarkan:\n");
    printf("1. ID\n2. Nama\n3. Developer\n4. Harga\nPilihan: ");
    scanf("%d", &pilihan); clearInputBuffer();
    printf("1. Ascending\n2. Descending\nPilihan: ");
    scanf("%d", &arah); clearInputBuffer();

    // BUBBLE SORT
    int swapped;
    do {
        swapped = 0;
        Game **ptr = &head;
        while ((*ptr) && (*ptr)->next) {
            Game *a = *ptr;
            Game *b = a->next;
            int compare = 0;

            switch (pilihan) {
                case 1: compare = (a->id > b->id); break;
                case 2: compare = (strcmp(a->nama, b->nama) > 0); break;
                case 3: compare = (strcmp(a->developer, b->developer) > 0); break;
                case 4: compare = (a->harga > b->harga); break;
            }

            if ((arah == 1 && compare) || (arah == 2 && !compare)) {
                // Tukar data (bukan pointer)
                int tempId = a->id; a->id = b->id; b->id = tempId;
                float tempHarga = a->harga; a->harga = b->harga; b->harga = tempHarga;

                char tempNama[100], tempDev[50], tempDesc[200];
                strcpy(tempNama, a->nama); strcpy(a->nama, b->nama); strcpy(b->nama, tempNama);
                strcpy(tempDev, a->developer); strcpy(a->developer, b->developer); strcpy(b->developer, tempDev);
                strcpy(tempDesc, a->deskripsi); strcpy(a->deskripsi, b->deskripsi); strcpy(b->deskripsi, tempDesc);

                swapped = 1;
            }
            ptr = &((*ptr)->next);
        }
    } while (swapped);

    printf("\nData berhasil diurutkan secara Bubble Sort.\n");

    // Tampilkan hasil pengurutan
    Game *curr = head;
    int i = 1;
    while (curr) {
        printf("\n--- Game ke-%d ---\n", i++);
        printf("ID        : %d\n", curr->id);
        printf("Nama      : %s\n", curr->nama);
        printf("Developer : %s\n", curr->developer);
        printf("Deskripsi : %s\n", curr->deskripsi);
        printf("Harga     : Rp %.2f\n", curr->harga);
        curr = curr->next;
    }
}

// ---------- RIWAYAT ----------
void tampilRiwayat() {
    system("cls");
    printf("\nRiwayat Aktivitas:\n");
    for (int i = 0; i < jumlahRiwayat; i++) {
        printf("- %s\n", riwayat[i]);
    }
}

// ---------- FILE HANDLING ----------
void cetakKeFile() {
    system("cls");
    FILE *f = fopen("daftar_game_store.txt", "w");
    if (!f) {
        printf("Gagal membuka file untuk menulis!\n");
        return;
    }
    Game *curr = head;
    fprintf(f, "===== DATA GAME STORE KELOMPOK 6 =====\n\n");
    int i = 1;
    while (curr) {
        fprintf(f, "--- Game ke-%d ---\n", i++);
        fprintf(f, "ID        : %d\n", curr->id);
        fprintf(f, "Nama      : %s\n", curr->nama);
        fprintf(f, "Developer : %s\n", curr->developer);
        fprintf(f, "Deskripsi : %s\n", curr->deskripsi);
        fprintf(f, "Harga     : Rp %.2f\n\n", curr->harga);
        curr = curr->next;
    }
    fclose(f);
    printf("Data berhasil dicetak ke file: daftar_game_store.txt\n");
}

void Author() {
    const char *baris[] = {
        "||                           CREATOR                             ||",
        "||===============================================================||",
        "||            NAMA                          |        NIM         ||",
        "||---------------------------------------------------------------||",
        "|| Wilson Ratu Dalberth                     | 672024201          ||",
        "|| Ajeng Natali Desmonda                    | 672024217          ||",
        "|| Fahzya Ubung Irang                       | 672024227          ||",
        "|| Raphael Mathew Pendong                   | 672024241          ||",
        "|| Jeremy Thimotius Ratungalo               | 672024243          ||",
        "|| Enrico Samuel Sebastian Sugianto         | 672024249          ||",
        "||===============================================================||",
        "||              Algoritma dan Struktur Data - B                  ||",
        "||          Tekan Enter untuk kembali ke menu utama              ||",
        "||===============================================================||"
    };

    int barisJumlah = sizeof(baris) / sizeof(baris[0]);
    for (int i = 0; i < barisJumlah; i++) {
        int len = strlen(baris[i]);
        int x = (113 - len) / 2;  // pos tengah dari layar 113 kolom
        gotoxy(x, 5 + i);         // baris mulai dari 5 ke bawah

        for (int j = 0; j < len; j++) {
            putchar(baris[i][j]);
            Sleep(1);  // animasi karakter
        }
    }
    getchar();
}

void keluarProgram() {
    char *colors[6] = {
        "\033[31m", // Merah
        "\033[32m", // Hijau
        "\033[33m", // Kuning
        "\033[34m", // Biru
        "\033[35m", // Ungu
        "\033[36m"  // Cyan
    };

    const char *resetColor = "\033[0m";

    char spinner[] = {'|', '/', '-', '\\'};
    int spinnerSize = sizeof(spinner) / sizeof(spinner[0]);

    int countdown = 5;
    int i = 0, colorIndex = 0;

    while (countdown > 0) {
        system("cls");
        for (int j = 0; j < 10; j++) {
            printf("\n");
        }

        printf("\t\t\t\tTerima kasih telah menggunakan program kami\n");
        printf("\n");
        printf("\t\t\t\t\tProgram akan berhenti dalam\n \t\t\t\t\t\t%s%d%s detik\n\t\t\t\t\t\t    %s%c%s\n",
               colors[colorIndex], countdown, resetColor, colors[colorIndex], spinner[i], resetColor);

        fflush(stdout);

        i = (i + 1) % spinnerSize;
        colorIndex = (colorIndex + 1) % 6;

        Sleep(200);

        if (i == 0) {
            countdown--;
        }
    }
    system("cls");
    printf("\t\t\t\t\033[32mProgram selesai! Sampai jumpa lagi!\033[0m\n");
}

// ---------- MENU GAME STORE ----------
void menuGameStore() {
    centerText("||===============================================================||", 3);
    centerText("||                    GAME STORE - KELOMPOK 6                    ||", 4);
    centerText("||===============================================================||", 5);
    centerText("||                                                               ||", 6);
    centerText("||   1. Tambah Game Baru                                         ||", 7);
    centerText("||   2. Tampilkan Game Dijual                                    ||", 8);
    centerText("||   3. Cari Game                                                ||", 9);
    centerText("||   4. Ubah Data Game                                           ||", 10);
    centerText("||   5. Hapus Game                                               ||", 11);
    centerText("||   6. Urutkan Data Game                                        ||", 12);
    centerText("||   7. Riwayat Aktivitas                                        ||", 13);
    centerText("||   8. Cetak ke File                                            ||", 14);
    centerText("||   9. Author                                                   ||", 15);
    centerText("||  10. Keluar                                                   ||", 16);
    centerText("||===============================================================||", 17);
    centerText("||   Masukkan Pilihan :                                          ||", 18);
    centerText("||===============================================================||", 19);

    // Pindahkan kursor ke posisi input setelah teks "Masukkan Pilihan :"
    // "||   Masukkan Pilihan : " = 24 karakter dari kiri margin menu
    // panjang menu = 63 karakter (di centerText)
    int menuWidth = 63;
    int startX = (113 - menuWidth) / 2;  // titik awal garis menu
    gotoxy(startX + 24, 18); // posisikan setelah "Masukkan Pilihan :"
}

int main() {
    loading();
    login();
    inisialisasiGameDummy(); // Memuat 10 game otomatis

    int pilihan;
    do {
        system("cls");
        menuGameStore();
        scanf("%d", &pilihan); clearInputBuffer();
        switch (pilihan) {
            case 1: tambahGame(); break;
            case 2: tampilkanGame(); break;
            case 3: cariGame(); break;
            case 4: ubahGame(); break;
            case 5: hapusGame(); break;
            case 6: urutkanGame(); break;
            case 7: tampilRiwayat(); break;
            case 8: cetakKeFile(); break;
            case 9: Author(); break;
            case 10: keluarProgram(); break;
            default: printf("Pilihan tidak valid!\n");
        }
        if (pilihan != 9) {
            printf("\nTekan ENTER untuk kembali ke menu...");
            getchar();
        }
    } while (pilihan != 10);

    // Bebaskan memori sebelum keluar (bonus, biar rapi)
    Game *curr = head;
    while (curr) {
        Game *hapus = curr;
        curr = curr->next;
        free(hapus);
    }
    return 0;
}
