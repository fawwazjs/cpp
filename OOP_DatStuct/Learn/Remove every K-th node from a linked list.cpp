#include <iostream>
using namespace std;

// Struktur untuk merepresentasikan transaksi dalam linked list
struct Transaction {
    int id;
    int amount;
    bool isFailed; // true jika gagal, false jika berhasil
    Transaction* next;
};

// Fungsi untuk menambahkan transaksi baru ke akhir linked list
void insertTransaction(Transaction*& head, int id, int amount, bool isFailed) {
    Transaction* newNode = new Transaction{id, amount, isFailed, nullptr};
    if (!head) {
        head = newNode;
        return;
    }

    Transaction* temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Fungsi untuk menghapus setiap K-th transaksi yang gagal
void removeKthFailedTransaction(Transaction*& head, int K) {
    if (!head || K <= 0) return;

    Transaction* temp = head;
    Transaction* prev = nullptr;
    int failedCount = 0;

    while (temp) {
        if (temp->isFailed) {
            failedCount++;
            if (failedCount % K == 0) { // Jika ini transaksi gagal ke-K
                // Hapus node ini
                if (prev) {
                    prev->next = temp->next;
                    delete temp;
                    temp = prev->next;
                } else { // Jika yang dihapus adalah head
                    head = temp->next;
                    delete temp;
                    temp = head;
                }
                continue; // Lanjutkan iterasi tanpa mengubah prev
            }
        }
        prev = temp;
        temp = temp->next;
    }
}

// Fungsi untuk mencetak daftar transaksi
void printTransactions(Transaction* head) {
    Transaction* temp = head;
    while (temp) {
        cout << "ID: " << temp->id << ", Amount: " << temp->amount
             << ", Status: " << (temp->isFailed ? "Failed" : "Success") << endl;
        temp = temp->next;
    }
    cout << "------------------------" << endl;
}

// Program utama
int main() {
    Transaction* transactions = nullptr;

    // Menambahkan transaksi
    insertTransaction(transactions, 101, 500, false);
    insertTransaction(transactions, 102, -200, true);
    insertTransaction(transactions, 103, 300, false);
    insertTransaction(transactions, 104, -100, true);
    insertTransaction(transactions, 105, -50, true);
    insertTransaction(transactions, 106, 100, false);
    insertTransaction(transactions, 107, -500, true);
    insertTransaction(transactions, 108, 200, false);

    cout << "Riwayat transaksi sebelum penghapusan:\n";
    printTransactions(transactions);

    int K = 2;
    removeKthFailedTransaction(transactions, K);

    cout << "Riwayat transaksi setelah menghapus setiap " << K << "-th transaksi gagal:\n";
    printTransactions(transactions);

    return 0;
}