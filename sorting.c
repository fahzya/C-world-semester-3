#include <stdio.h>
#define MAKS_DATA 30

// Deklarasi array data dan jumlah elemen
int data[MAKS_DATA];
int dataSebelumnya[MAKS_DATA];
int jumlahData = 0;

// Fungsi untuk menyimpan data saat ini ke dalam data sebelumnya
void simpanDataSebelumnya() {
    for (int i = 0; i < jumlahData; i++) {
        dataSebelumnya[i] = data[i];
    }
}

// Fungsi untuk memasukkan data dari pengguna
void masukkanData() {
    printf("Masukkan jumlah elemen data (maks %d): ", MAKS_DATA);
    scanf("%d", &jumlahData);
    if (jumlahData > MAKS_DATA || jumlahData <= 0) {
        printf("Jumlah elemen tidak valid!\n");
        jumlahData = 0;
        return;
    }
    printf("Masukkan %d elemen data:\n", jumlahData);
    for (int i = 0; i < jumlahData; i++) {
        printf("Data[%d]: ", i + 1);
        scanf("%d", &data[i]);
    }
    simpanDataSebelumnya();
}

// Fungsi untuk mengurutkan data menggunakan Bubble Sort
void urutBubble(int ascending) {
    simpanDataSebelumnya();
    for (int i = 0; i < jumlahData - 1; i++) {
        for (int j = 0; j < jumlahData - i - 1; j++) {
            if ((ascending && data[j] > data[j + 1]) || (!ascending && data[j] < data[j + 1])) {
                int sementara = data[j];
                data[j] = data[j + 1];
                data[j + 1] = sementara;
            }
        }
    }
    printf("Data berhasil diurutkan menggunakan Bubble Sort.\n");
}

// Fungsi untuk mengurutkan data menggunakan Exchange Sort
void urutTukar(int ascending) {
    simpanDataSebelumnya();
    for (int i = 0; i < jumlahData - 1; i++) {
        for (int j = i + 1; j < jumlahData; j++) {
            if ((ascending && data[i] > data[j]) || (!ascending && data[i] < data[j])) {
                int sementara = data[i];
                data[i] = data[j];
                data[j] = sementara;
            }
        }
    }
    printf("Data berhasil diurutkan menggunakan Exchange Sort.\n");
}

// Fungsi untuk mengurutkan data menggunakan Selection Sort
void urutPilih(int ascending) {
    simpanDataSebelumnya();
    for (int i = 0; i < jumlahData - 1; i++) {
        int indeksMinAtauMax = i;
        for (int j = i + 1; j < jumlahData; j++) {
            if ((ascending && data[j] < data[indeksMinAtauMax]) || (!ascending && data[j] > data[indeksMinAtauMax])) {
                indeksMinAtauMax = j;
            }
        }
        if (indeksMinAtauMax != i) {
            int sementara = data[i];
            data[i] = data[indeksMinAtauMax];
            data[indeksMinAtauMax] = sementara;
        }
    }
    printf("Data berhasil diurutkan menggunakan Selection Sort.\n");
}

// Fungsi untuk menampilkan data
void tampilkanData() {
    if (jumlahData == 0) {
        printf("Data kosong. Silakan masukkan data terlebih dahulu.\n");
        return;
    }

    printf("Data sebelumnya: ");
    for (int i = 0; i < jumlahData; i++) {
        printf("%d ", dataSebelumnya[i]);
    }
    printf("\n");

    printf("Data saat ini: ");
    for (int i = 0; i < jumlahData; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
}

// Fungsi utama
int main() {
    int pilihan, urutan;
    while (1) {
        printf("\n==========================\n");
        printf("Nama: Fahzya Ubung Irang\n");
        printf("NIM : 672024227\n");
        printf("==========================\n");

        // Tampilkan menu
        printf("\nMenu:\n");
        printf("1. Masukkan Data\n");
        printf("2. Bubble Sort\n");
        printf("3. Exchange Sort\n");
        printf("4. Selection Sort\n");
        printf("5. Tampilkan Data\n");
        printf("6. Keluar\n\n");
        printf("Pilih opsi: ");
        scanf("%d", &pilihan);
        printf("--------------------------\n");

        // Pilih tindakan berdasarkan opsi menu
        switch (pilihan) {
            case 1:
                masukkanData();
                break;
            case 2:
                printf("1: untuk Ascending\n");
                printf("0: untuk Descending\n");
                printf("Pilih Urutan: ");
                scanf("%d", &urutan);
                printf("--------------------------\n");
                urutBubble(urutan);
                break;
            case 3:
                printf("1: untuk Ascending\n");
                printf("0: untuk Descending\n");
                printf("Pilih Urutan: ");
                scanf("%d", &urutan);
                printf("--------------------------\n");
                urutTukar(urutan);
                break;
            case 4:
                printf("1: untuk Ascending\n");
                printf("0: untuk Descending\n");
                printf("Pilih Urutan: ");
                scanf("%d", &urutan);
                printf("--------------------------\n");
                urutPilih(urutan);
                break;
            case 5:
                tampilkanData();
                break;
            case 6:
                printf("Keluar dari program.\n");
                return 0;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    }
    return 0;
}
