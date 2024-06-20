#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
using namespace std;

const int MAX_SIZE = 10;

struct Mahasiswa {
    string nama;
    string ttl;
    string asek;
    string alamat;
    string agama;
    string hp;
    string prestasi;
};

// Stack untuk pencatatan mahasiswa yang di-blacklist
struct BlacklistStack {
    Mahasiswa items[MAX_SIZE];
    int top;

    BlacklistStack() {
        top = -1;
    }

    bool isEmpty() {
        return (top == -1);
    }

    bool isFull() {
        return (top == MAX_SIZE - 1);
    }

    void push(Mahasiswa item) {
        if (!isFull()) {
            top++;
            items[top] = item;
        } else {
            cout << "Daftar blacklist penuh, tidak dapat menambahkan lagi." << endl;
        }
    }

    Mahasiswa pop() {
        if (!isEmpty()) {
            Mahasiswa poppedItem = items[top];
            top--;
            return poppedItem;
        } else {
            cout << "Daftar blacklist kosong." << endl;
            Mahasiswa emptyItem;
            return emptyItem;
        }
    }
};


struct Antrian {
    Mahasiswa *data;
    int awal, akhir, maba;
    BlacklistStack blacklist; // Stack untuk menyimpan data mahasiswa yang di-blacklist

    Antrian() {
    	data = new Mahasiswa[MAX_SIZE];
        awal = -1;
        akhir = -1;
        maba = -1;
    }
    
    ~Antrian() {
    	delete[] data;
	}
};

Antrian mhs;

// Fungsi untuk menginisialisasi antrian
void init() {
    mhs.awal = -1;
    mhs.akhir = -1;
}

// Fungsi untuk memeriksa apakah antrian penuh
bool full() {
    return (mhs.akhir == MAX_SIZE - 1);
}

// Fungsi untuk memeriksa apakah antrian kosong
bool empty() {
    return (mhs.akhir == -1);
}

// Fungsi untuk mendaftarkan mahasiswa baru
void inQueue() {
    if (!full()) {
    	system("cls");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nama Mahasiswa Baru      : ";
        getline(cin, mhs.data[mhs.akhir + 1].nama);
        cout << "Tempat, Tanggal Lahir    : ";
        getline(cin, mhs.data[mhs.akhir + 1].ttl);
        cout << "Asal Sekolah             : ";
        getline(cin, mhs.data[mhs.akhir + 1].asek);
        cout << "Alamat                   : ";
        getline(cin, mhs.data[mhs.akhir + 1].alamat);
        cout << "No. Hp                   : ";
        getline(cin, mhs.data[mhs.akhir + 1].hp);
        cout << "Agama                    : ";
        getline(cin, mhs.data[mhs.akhir + 1].agama);
        cout << "Masukkan Nilai Akhir     : ";
        getline(cin, mhs.data[mhs.akhir + 1].prestasi);

        mhs.akhir++;
        
        cout << "\nData berhasil ditambahkan\n";
        system("pause"); // Menahan layar sebelum membersihkan layar konsol
        system("cls"); // Membersihkan layar konsol
    } else {
        cout << "\nAntrian penuh\n";
        system("pause");
        system("cls");
    }
}

// Fungsi untuk menampilkan jumlah data mahasiswa
void tampildata() {
	cout << "\n================================================\n";
    cout << "Jumlah Data : " << mhs.akhir-mhs.awal << endl;
    cout << "================================================\n";
    
    system("pause"); // Menahan layar sebelum membersihkan layar konsol
    system("cls"); // Membersihkan layar konsol
}


// Fungsi untuk menampilkan seluruh data mahasiswa yang telah didaftarkan
void displayAllData() {
    int pilihanMenu, pilihanOrder;
    if (empty()) {
        cout << "\nAntrian kosong" << endl;
        system("pause");
        system("cls");
    } else {
        cout << "\n==========================================" << endl;
        cout << "Data Mahasiswa Baru yang Telah Didaftar:" << endl;
        cout << "==========================================\n";

        cout << "Pilihan Menu: " << endl;
        cout << "1. Urutkan berdasarkan Nama" << endl;
        cout << "2. Urutkan berdasarkan Nilai Prestasi" << endl;
        cout << "3. Cari Mahasiswa berdasarkan Nama" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihanMenu;

        if (pilihanMenu == 1 || pilihanMenu == 2 || pilihanMenu == 3) {
            if (pilihanMenu == 1 || pilihanMenu == 2) {
                cout << "Pilihan urutan: " << endl;
                cout << "1. Ascending (Kecil->Besar)" << endl;
                cout << "2. Descending (Besar->Kecil)" << endl;
                cout << "Masukkan pilihan urutan: ";
                cin >> pilihanOrder;
            }

            bool sort = (pilihanOrder == 1);
            if (pilihanMenu == 1) {  // Urutkan berdasarkan nama
                for (int i = 0; i <= mhs.akhir; ++i) {
                    for (int j = 0; j <= mhs.akhir - i - 1; ++j) {
                        if (sort ? mhs.data[j].nama > mhs.data[j + 1].nama : mhs.data[j].nama < mhs.data[j + 1].nama) {
                            swap(mhs.data[j], mhs.data[j + 1]);
                        }
                    }
                }
            } else if (pilihanMenu == 2) {  // Urutkan berdasarkan nilai prestasi
                for (int i = 0; i <= mhs.akhir; ++i) {
                    for (int j = 0; j <= mhs.akhir - i - 1; ++j) {
                        if (sort ? mhs.data[j].prestasi > mhs.data[j + 1].prestasi : mhs.data[j].prestasi < mhs.data[j + 1].prestasi) {
                            swap(mhs.data[j], mhs.data[j + 1]);
                        }
                    }
                }
            } else if (pilihanMenu == 3) {  // Cari mahasiswa berdasarkan nama
                string namaToSearch;
                cout << "Masukkan nama mahasiswa yang ingin dicari: ";
                cin.ignore();
                getline(cin, namaToSearch);

                bool found = false;
                cout << "========================================================================================================================================================" << endl;
                cout << setw(2) << "No." << setw(20) << "Nama" << setw(25) << "Tempat, Tanggal Lahir" << setw(25) << "Asal Sekolah" << setw(25) << "Alamat" << setw(15) << "No. Hp" << setw(15) << "Agama" << setw(20) << "Nilai Prestasi" << endl;
                cout << "========================================================================================================================================================" << endl;

                for (int i = 0; i <= mhs.akhir; ++i) {
                    if (mhs.data[i].nama.find(namaToSearch) != string::npos) {
                        cout << setw(2) << i + 1 << setw(20) << mhs.data[i].nama << setw(25) << mhs.data[i].ttl << setw(25) << mhs.data[i].asek << setw(25) << mhs.data[i].alamat << setw(15) << mhs.data[i].hp << setw(15) << mhs.data[i].agama << setw(20) << mhs.data[i].prestasi << endl;
                        found = true;
                    }
                }

                if (!found) {
                    cout << "Data tidak ditemukan." << endl;
                }

                cout << "========================================================================================================================================================" << endl;

                system("pause"); // Menahan layar sebelum membersihkan layar konsol
                system("cls"); // Membersihkan layar konsol
                return;
            }
        } else {
            cout << "Pilihan tidak valid" << endl;
            system("pause"); // Menahan layar sebelum membersihkan layar konsol
            system("cls"); // Membersihkan layar konsol
            return;
        }

        cout << "========================================================================================================================================================" << endl;
        cout << setw(2) << "No." << setw(20) << "Nama" << setw(25) << "Tempat, Tanggal Lahir" << setw(25) << "Asal Sekolah" << setw(25) << "Alamat" << setw(15) << "No. Hp" << setw(15) << "Agama" << setw(20) << "Nilai Prestasi" << endl;
        cout << "========================================================================================================================================================" << endl;

        for (int i = 0; i <= mhs.akhir; ++i) {
            cout << setw(2) << i + 1 << setw(20) << mhs.data[i].nama << setw(25) << mhs.data[i].ttl << setw(25) << mhs.data[i].asek << setw(25) << mhs.data[i].alamat << setw(15) << mhs.data[i].hp << setw(15) << mhs.data[i].agama << setw(20) << mhs.data[i].prestasi << endl;
        }

        cout << "=========================================================================================================================================================" << endl;

        system("pause"); // Menahan layar sebelum membersihkan layar konsol
        system("cls"); // Membersihkan layar konsol
    }
}

void dequeue() {
    if (empty()) {
        cout << "\nAntrian kosong" << endl;
        system("pause");
        system("cls");
    } else {
        cout << "Mahasiswa atas nama : " << mhs.data[0].nama << " telah dikeluarkan dari antrian" << endl;

        // Geser seluruh elemen antrian ke depan
        for (int i = 0; i < mhs.akhir; ++i) {
            mhs.data[i] = mhs.data[i + 1];
        }

        mhs.akhir--; // Kurangi jumlah elemen di antrian

        system("pause");
        system("cls");
    }
}

void blacklistMahasiswa() {
    if (!mhs.blacklist.isFull()) {
        string nama;
        string asalSekolah;
		cout << endl;
		
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Masukkan nama calon mahasiswa yang ingin dimasukkan ke dalam daftar blacklist: ";
        getline(cin, nama);
        cout << "Masukkan asal sekolah calon mahasiswa: ";
        getline(cin, asalSekolah);

        Mahasiswa calonMahasiswa;
        calonMahasiswa.nama = nama;
        calonMahasiswa.asek = asalSekolah;

        mhs.blacklist.push(calonMahasiswa);
        cout << "\n\nCalon mahasiswa " << nama << " dari " << asalSekolah << " telah dimasukkan ke dalam daftar blacklist.\n";
    } else {
        cout << "\n\nDaftar blacklist penuh, tidak dapat menambahkan lagi.\n";
    }

    system("pause");
    system("cls");
}

void displayBlacklisted() {
	int no=1;
	
    if (mhs.blacklist.isEmpty()) {
        cout << "\n\nDaftar blacklist kosong.\n";
    } else {
        cout << "\nDaftar Mahasiswa yang Terdaftar di Blacklist:\n";
        for (int i = mhs.blacklist.top; i >= 0; --i) {
            Mahasiswa calonMahasiswa = mhs.blacklist.items[i];
            cout << no << ". Nama: " << calonMahasiswa.nama << ", Asal Sekolah: " << calonMahasiswa.asek << endl;
            no++;
        }
    }

    system("pause");
    system("cls");
}

Mahasiswa removeFromBlacklist() {
    Mahasiswa removedMahasiswa;
    if (!mhs.blacklist.isEmpty()) {
        removedMahasiswa = mhs.blacklist.pop();
        if (!removedMahasiswa.nama.empty()) {
            cout << "\nMahasiswa " << removedMahasiswa.nama << " telah dihapus dari daftar blacklist.\n";
        }
    } else {
        cout << "\n\nDaftar blacklist kosong\n";
    }
    system("pause");
    system("cls");
    return removedMahasiswa;
}


// Fungsi utama
int main() {
    int pilihan;
    init();

    do {
        cout << "================================================" << endl;
        cout << "SELAMAT DATANG DI UNIVERSITAS AMIKOM YOGYAKARTA" << endl;
        cout << "================================================" << endl;
        cout << "ANTRIAN PENERIMAAN MAHASISWA BARU JALUR REGULER"<<endl;
        cout << "       PROGRAM STUDI S1 SISTEM INFORMASI" << endl;
        cout << "------------------------------------------------" << endl;
    
        cout << "\nSilahkan Pilih Menu Yang Akan Dijalankan : " << endl;
        cout << "1. Pendaftaran Mahasiswa Baru" << endl;
        cout << "2. Jumlah Data" << endl;
        cout << "3. Tampilkan Semua Data" << endl;
        cout << "4. Mengeluarkan Data Dari Antrian" << endl;
        cout << "5. Blacklist Mahasiswa" << endl;
        cout << "6. Tampilkan Mahasiswa di Blacklist" << endl;
        cout << "7. Hapus Mahasiswa dari Blacklist" << endl;
        cout << "0. Keluar" << endl;
        cout << "Masukkan pilihan anda : ";
        cin >> pilihan;
    
        switch (pilihan) {
            case 1:
                inQueue();
                break;
            case 2:
                tampildata();
                break;
            case 3:
                displayAllData();
                break;
            case 4:
                dequeue();
                break;
            case 5:
                blacklistMahasiswa();
                break;
            case 6:
                displayBlacklisted();
                break;
            case 7:
                removeFromBlacklist();
                break;
            case 0:
                cout << "Program berhenti." << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Program berhenti." << endl;
                pilihan = 0; // Set pilihan ke 0 agar keluar dari loop
                break;
        }
    } while (pilihan != 0);

    return 0;
}
