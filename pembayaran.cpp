#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Struktur Buku
struct Buku {
    int id;
    string judul;
    string pengarang;
    double biayaPerHari;  // biaya per hari peminjaman
};

// Struktur Anggota
struct Anggota {
    string nama;
    string idAnggota;
    vector<pair<Buku, int>> bukuDipinjam;  // Daftar buku yang dipinjam anggota beserta jumlah hari peminjaman
};

// Fungsi untuk menghitung total biaya berdasarkan jumlah hari
double hitungBiaya(int jumlahHari, double biayaPerHari, int keterlambatan = 0) {
    double biaya = jumlahHari * biayaPerHari;
    if (keterlambatan > 0) {
        biaya += keterlambatan * 5000;  // Misalnya biaya keterlambatan Rp5000 per hari
    }
    return biaya;
}

// Fungsi untuk menampilkan metode pembayaran dengan total yang sudah dihitung
void metodePembayaran(double totalPembayaran) {
    int pilihanBank;
    string namaBank;
    string cardNumber;
    string cardHolderName;
    string expiryDate;
    int cvv;

    // Menampilkan opsi bank
    cout << "\n========= PEMBAYARAN =========\n";
    cout << "Pilih Bank untuk Pembayaran:\n";
    cout << "1. Bank Mandiri\n";
    cout << "2. Bank BCA\n";
    cout << "3. Bank BRI\n";
    cout << "4. Bank BNI\n";
    cout << "Pilihan: ";
    cin >> pilihanBank;

    // Memilih nama bank berdasarkan input pengguna
    switch (pilihanBank) {
        case 1:
            namaBank = "Bank Mandiri";
            break;
        case 2:
            namaBank = "Bank BCA";
            break;
        case 3:
            namaBank = "Bank BRI";
            break;
        case 4:
            namaBank = "Bank BNI";
            break;
        default:
            cout << "Pilihan tidak valid. Menggunakan Bank Mandiri sebagai default.\n";
            namaBank = "Bank Mandiri";
            break;
    }

    // Input dari pengguna untuk detail kartu kredit
    cin.ignore(); // Mengatasi masalah input getline setelah cin
    cout << "\n--- Masukkan Detail Kartu " << namaBank << " ---\n";
    
    cout << "Nomor Kartu Kredit: ";
    getline(cin, cardNumber);
    
    cout << "Nama Pemegang Kartu: ";
    getline(cin, cardHolderName);
    
    cout << "Tanggal Kedaluwarsa (MM/YY): ";
    getline(cin, expiryDate);
    
    cout << "Masukkan CVV: ";
    cin >> cvv;

    // Simulasi opsi penyimpanan kartu untuk transaksi selanjutnya
    char saveCard;
    cout << "Simpan kartu ini untuk transaksi berikutnya? (y/n): ";
    cin >> saveCard;

    // Menampilkan total pembayaran
    cout << "\nTotal Pembayaran: Rp" << totalPembayaran << endl;
    
    // Konfirmasi pembayaran
    cout << "[Lanjutkan Pembayaran] -> Pembayaran Berhasil!\n";
}

// Fungsi untuk menampilkan daftar harga buku
void cekHargaBuku(vector<Buku> &daftarBuku) {
    cout << "\nDaftar Harga Buku per Hari\n";
    cout << "---------------------------------------\n";
    for (size_t i = 0; i < daftarBuku.size(); ++i) {
        cout << "ID: " << daftarBuku[i].id << " | Judul: " << daftarBuku[i].judul
             << " | Pengarang: " << daftarBuku[i].pengarang 
             << " | Harga: Rp" << daftarBuku[i].biayaPerHari << " per hari" << endl;
    }
    cout << endl;
}

// Fungsi untuk meminjam buku berdasarkan ID dan jumlah hari peminjaman
void pinjamBuku(vector<Buku> &daftarBuku, Anggota &anggota) {
    int idBuku, jumlahHari;
    cout << "\nMasukkan ID buku yang ingin dipinjam: ";
    cin >> idBuku;
    
    bool bukuDitemukan = false;
    for (auto &buku : daftarBuku) {
        if (buku.id == idBuku) {
            cout << "Masukkan jumlah hari peminjaman: ";
            cin >> jumlahHari;
            anggota.bukuDipinjam.push_back(make_pair(buku, jumlahHari));
            cout << "Buku '" << buku.judul << "' berhasil dipinjam untuk " << jumlahHari << " hari!\n";
            bukuDitemukan = true;
            break;
        }
    }
    
    if (!bukuDitemukan) {
        cout << "Buku dengan ID tersebut tidak ditemukan.\n";
    }
}

// Fungsi untuk menampilkan total biaya
double totalPembayaran(Anggota &anggota, int keterlambatan) {
    double totalBiaya = 0;
    cout << "\nBuku yang dipinjam oleh " << anggota.nama << ":\n";
    cout << "---------------------------------\n";
    for (auto &bukuInfo : anggota.bukuDipinjam) {
        Buku buku = bukuInfo.first;
        int jumlahHari = bukuInfo.second;
        double biaya = hitungBiaya(jumlahHari, buku.biayaPerHari, keterlambatan);
        totalBiaya += biaya;
        cout << buku.judul << " - Jumlah hari: " << jumlahHari << " - Total biaya: Rp" << biaya << endl;
    }
    cout << "---------------------------------\n";
    cout << "Total biaya yang harus dibayar: Rp" << totalBiaya << endl;

    return totalBiaya;
}

// Fungsi untuk cek total biaya dan proses pembayaran
void cekBiayaDanBayar(Anggota &anggota, int keterlambatan) {
    double total = totalPembayaran(anggota, keterlambatan);
    metodePembayaran(total);  // Kirim total pembayaran ke metode pembayaran
}

int main() {
    // Data buku
    vector<Buku> daftarBuku = {
        {1, "Pemrograman C", "Dennis Ritchie", 10000},
        {2, "Algoritma dan Struktur Data", "Donald Knuth", 12000},
        {3, "Sistem Operasi", "Andrew Tanenbaum", 11000},
        {4, "Jaringan Komputer", "William Stallings", 14000},
        {5, "Pemrograman C++", "Bjarne Stroustrup", 15000},
        {6, "Dasar-Dasar Pemrograman", "Tony Gaddis", 10500},
        {7, "Pengantar Basis Data", "Ramez Elmasri", 12500},
        {8, "Desain dan Analisis Algoritma", "Thomas H. Cormen", 13500},
        {9, "Rekayasa Perangkat Lunak", "Roger Pressman", 14500},
        {10, "Artificial Intelligence", "Stuart Russell", 16000}
    };

    // Data anggota
    Anggota anggota;

    // Meminta nama peminjam di awal program
    cout << "Selamat datang di perpustakaan!\n";
    cout << "Masukkan nama peminjam: ";
    getline(cin, anggota.nama);  // Menerima nama peminjam
    
    // Variabel untuk keterlambatan
    int keterlambatan = 2;  // Misalnya ada keterlambatan 2 hari

    // Menu interaktif
    int pilihan;
    do {
        cout << "\n=== Menu Perpustakaan ===\n";
        cout << "1. Cek harga buku\n";
        cout << "2. Pinjam buku\n";
        cout << "3. Total Pembayaran\n";
        cout << "4. Pembayaran\n";
        cout << "5. Exit\n";
        cout << "Pilih opsi (1-5): ";
        cin >> pilihan;
        cin.ignore();  // Untuk mengatasi masalah input getline setelah cin

        switch (pilihan) {
            case 1:
                cekHargaBuku(daftarBuku);
                break;
            case 2:
                pinjamBuku(daftarBuku, anggota);
                break;
            case 3:
                totalPembayaran(anggota, keterlambatan);
                break;
            case 4:
                cekBiayaDanBayar(anggota, keterlambatan);
                break;
            case 5:
                cout << "Terima kasih, " << anggota.nama << "! Keluar dari program...\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
                break;
        }
    } while (pilihan != 5);

    return 0;
}
