#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>

using namespace std;

struct StackIPK {
    float nilai;
    StackIPK* next;
};

struct Mahasiswa {
    char nim[20];
    char nama[50];
    char jurusan[50];
    int thn_masuk;
    float ipk;
    StackIPK* riwayatIPK = nullptr;
};

int jumlahMhs;

struct Node {
    Mahasiswa data;
    Node* next;
};

Node* depan = nullptr;
Node* belakang = nullptr;

bool login() {
    string inputUser, inputPass;
    string username[2] = {"luna", "amel"};
    string password[2] = {"080806", "020206"};

    cout << "=== Sistem Login ===" << endl;
    cout << "Masukkan Username : ";
    cin >> inputUser;
    cout << "Masukkan Password : ";
    cin >> inputPass;

    for (int i = 0; i < 2; i++) {
        if (inputUser == username[i] && inputPass == password[i]) {
            cout << "Login berhasil. Selamat datang, " << username[i] << "!\n";
            return true;
        }
    }
    cout << "Login gagal. Username atau password salah.\n";
    return false;
}

//Menyimpan data ke file
void simpanFile() {
    FILE* file = fopen("data.txt", "w"); // pakai "w" supaya file ditimpa
    if (file == nullptr) {
        cout << "Gagal menyimpan data ke file.\n";
        return;
    }

    Node* bantu = depan;
    while (bantu != nullptr) {
        fprintf(file, "%s;%s;%s;%d;%.2f\n",
            bantu->data.nim,
            bantu->data.nama,
            bantu->data.jurusan,
            bantu->data.thn_masuk,
            bantu->data.ipk);
        bantu = bantu->next;
    }
    fclose(file);
}

//Memuat data dari file ke linked list
void muatDariFile() {
    FILE* file = fopen("data.txt", "r");
    if (file == nullptr) return;

    Mahasiswa mhs;
    while (fscanf(file, "%[^;];%[^;];%[^;];%d;%f\n", 
                  mhs.nim, mhs.nama, mhs.jurusan, &mhs.thn_masuk, &mhs.ipk) != EOF) {
        
        Node* baru = new Node{mhs, nullptr};
        if (depan == nullptr) {
            depan = belakang = baru;
        } else {
            belakang->next = baru;
            belakang = baru;
        }
    }
    fclose(file);
}

//Input data mahasiswa
void inputMahasiswa() {
    Mahasiswa mhs;
    
    cout << "\n=== Input Data Mahasiswa ===\n";
    cout << "Masukkan banyak data mahasiswa = ";
    cin >> jumlahMhs;
    cin.ignore();

    for(int i=0; i<jumlahMhs; i++){
        cout << "\nData Mahasiswa ke-" << (i+1) << ":\n";
        cout << "NIM         : "; cin.getline(mhs.nim, 20);
        cout << "Nama        : "; cin.getline(mhs.nama, 50);
        cout << "Jurusan     : "; cin.getline(mhs.jurusan, 50);
        cout << "Tahun Masuk : "; cin >> mhs.thn_masuk;
        cout << "IPK         : "; cin >> mhs.ipk;
        cin.ignore();  

        //Sisip di belakang Linked list
        Node* baru = new Node{mhs, nullptr};
    if (depan == nullptr) {
        depan = belakang = baru;
    } else {
        belakang->next = baru;
        belakang = baru;
    }

    }
    simpanFile();
    cout << "Data mahasiswa berhasil ditambahkan.\n";
}

//Menampilkan data mahasiswa
void tampilkanMahasiswa() { 
    if (depan == nullptr) {
        cout << "Data kosong.\n";
        return;
    }

    cout << "\n=== Daftar Mahasiswa ===\n";
    cout << setfill('=') << setw(90) << "=" << endl;
    cout << setfill(' ') << left
         << setw(5) << "No"
         << setw(15) << "Nim"
         << setw(15) << "Nama"
         << setw(15) << "Jurusan"
         << setw(15) << "Tahun Masuk"
         << setw(5) << "IPK" << endl;

    cout << setfill('=') << setw(90) << "=" << endl;     

    Node* bantu = depan;
    int no = 1;
    while (bantu != nullptr) {
    cout << setfill(' ') << left
          << setw(5) << no++
          << setw(15) << bantu->data.nim
          << setw(15) << bantu->data.nama
          << setw(15) << bantu->data.jurusan
          << setw(15) << bantu->data.thn_masuk
          << setw(5) << bantu->data.ipk << endl;
          bantu = bantu->next;
        }
    cout << setfill('=') << setw(90) << "=" << endl;
}

//Mencari mahasiswa berdasarkan NIM, Searching
void cariMahasiswa() {
    string cariNIM;
    cout << "Masukkan NIM yang dicari: ";
    cin >> cariNIM;

    Node* bantu = depan;
    int no = 1;
    bool ditemukan = false;

    while (bantu != nullptr) {
        if (bantu->data.nim == cariNIM) {
            cout << "\n=== Data Mahasiswa Ditemukan ===\n";
            cout << setfill('=') << setw(90) << "=" << endl;
            cout << setfill(' ') << left
                 << setw(5) << "No"
                 << setw(15) << "Nim"
                 << setw(15) << "Nama"
                 << setw(20) << "Jurusan"
                 << setw(15) << "Tahun Masuk"
                 << setw(5) << "IPK" << endl;
            cout << setfill('=') << setw(90) << "=" << endl;

            cout << setfill(' ') << left
                 << setw(5) << no
                 << setw(15) << bantu->data.nim
                 << setw(15) << bantu->data.nama
                 << setw(15) << bantu->data.jurusan
                 << setw(15) << bantu->data.thn_masuk
                 << setw(5) << bantu->data.ipk << endl;
            cout << setfill('=') << setw(90) << "=" << endl;

            ditemukan = true;
            break;
        }
        bantu = bantu->next;
        no++;
    }

    if (!ditemukan) {
        cout << "Mahasiswa dengan NIM " << cariNIM << " tidak ditemukan.\n";
    }
}

//Mengurutkan data mahasiswa berdasarkan NIM (Bubble Sort)
void bubbleSortNim() {
    if (depan == nullptr) return; // Kalau list kosong, langsung keluar

    bool swapped;
    Node* bantu;       // pointer bantu untuk traversal
    Node* batas = nullptr; // penanda batas sudah terurut di akhir

    do {
        swapped = false;
        bantu = depan; // mulai dari depan setiap putaran

        while (bantu->next != batas) {
            if (strcmp(bantu->data.nim, bantu->next->data.nim) > 0) {
                // Tukar data mahasiswa antar node
                Mahasiswa temp = bantu->data;
                bantu->data = bantu->next->data;
                bantu->next->data = temp;
                swapped = true;
            }
            bantu = bantu->next; // maju ke node berikutnya
        }
        batas = bantu; // node terakhir sudah terurut
    } while (swapped);

    cout << "Data berhasil diurutkan berdasarkan NIM (asc).\n";
    tampilkanMahasiswa();
}

//Push nilai IPK ke Stack (Riwayat)
void pushRiwayatIPK(Mahasiswa &mhs, float ipkLama) {
    StackIPK* baru = new StackIPK{ipkLama, nullptr};
    baru->next = mhs.riwayatIPK;
    mhs.riwayatIPK = baru;
}

//Mengubah IPK Mahasiswa dan menyimpan riwayat
void ubahIPK() {
    string cariNIM;
    cout << "Masukkan NIM mahasiswa yang ingin diubah IPK-nya: ";
    cin >> cariNIM;

    Node* bantu = depan;
    while (bantu != nullptr) {
        if (bantu->data.nim == cariNIM) {
            float ipkBaru;
            cout << "IPK lama: " << bantu->data.ipk << endl;
            cout << "Masukkan IPK baru: ";
            cin >> ipkBaru;

            // Simpan ke riwayat sebelum mengubah
            pushRiwayatIPK(bantu->data, bantu->data.ipk);
            bantu->data.ipk = ipkBaru;

            cout << "IPK berhasil diubah.\n";
            simpanFile();
            return;
        }
        bantu = bantu->next;
    }

    cout << "Mahasiswa dengan NIM " << cariNIM << " tidak ditemukan.\n";
}

//Menampilkan riwayat perubahan IPK
void tampilkanRiwayatIPK() {
    string cariNIM;
    cout << "Masukkan NIM mahasiswa yang ingin dilihat riwayat IPK-nya: ";
    cin >> cariNIM;

    Node* bantu = depan;
    while (bantu != nullptr) {
        if (bantu->data.nim == cariNIM) {
            cout << "\nRiwayat Perubahan IPK untuk " << bantu->data.nama << " (NIM: " << bantu->data.nim << "):\n";
            StackIPK* stack = bantu->data.riwayatIPK;
            if (stack == nullptr) {
                cout << "Belum ada riwayat perubahan IPK.\n";
            } else {
                int no = 1;
                while (stack != nullptr) {
                    cout << no++ << ". " << stack->nilai << endl;
                    stack = stack->next;
                }
            }
            return;
        }
        bantu = bantu->next;
    }

    cout << "Mahasiswa dengan NIM " << cariNIM << " tidak ditemukan.\n";
}

void menu() {
    int pilihan;
    do {
        cout << "\n=== MENU UTAMA ===\n";
        cout << "1. Input Data Mahasiswa\n";
        cout << "2. Tampilkan Data Mahasiswa\n";
        cout << "3. Cari Data Mahasiswa\n";
        cout << "4. Urutkan Data Mahasiswa (NIM)\n";
        cout << "5. Ubah IPK Mahasiswa\n";
        cout << "6. Tampilkan Riwayat Perubahan IPK Mahasiswa\n";
        cout << "7. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cout << endl;

        switch (pilihan) {
            case 1: inputMahasiswa(); break;
            case 2: tampilkanMahasiswa(); break;
            case 3: cariMahasiswa(); break;
            case 4: bubbleSortNim(); break;
            case 5: ubahIPK(); break;
            case 6: tampilkanRiwayatIPK(); break;
            case 7: cout << "Keluar dari program.\n"; break;
            default: cout << "Menu tidak valid.\n"; break;
        }
    } while (pilihan != 7);
}

int main() {
    system("cls");
    if (login()) {
    muatDariFile();
    menu(); 
}
    return 0;
}
