#include <iostream>
#include <limits>
#include <string>
using namespace std;

// Struktur Node Pesanan
struct Order {
    int orderID;
    string foodName;
    int quantity;
    double pricePerItem;
    double totalPrice;
    Order* next;

    Order(int id, string name, int qty, double price) {
        orderID = id;
        foodName = name;
        quantity = qty;
        pricePerItem = price;
        totalPrice = qty * price;
        next = nullptr;
    }
};

// Fungsi untuk validasi input integer
int getValidInt(string prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (!(cin >> value) || value <= 0) {
            cout << "Input tidak valid! Harap masukkan angka positif.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore();
            return value;
        }
    }
}

// Fungsi untuk validasi input double
double getValidDouble(string prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (!(cin >> value) || value <= 0) {
            cout << "Input tidak valid! Harap masukkan angka positif.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore();
            return value;
        }
    }
}

// Fungsi untuk validasi input string
string getValidString(string prompt) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        if (!value.empty()) {
            return value;
        }
        cout << "Input tidak boleh kosong!\n";
    }
}

// Fungsi menambahkan pesanan ke linked list
void addOrder(Order*& head, int& orderCounter) {
    string foodName = getValidString("Masukkan nama makanan: ");
    int quantity = getValidInt("Masukkan jumlah: ");
    double price = getValidDouble("Masukkan harga per item: ");
    
    Order* newOrder = new Order(orderCounter++, foodName, quantity, price);
    
    if (!head) {
        head = newOrder;
    } else {
        Order* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newOrder;
    }
    cout << "Pesanan berhasil ditambahkan!\n";
}

// Fungsi menampilkan semua pesanan
void displayOrders(Order* head) {
    if (!head) {
        cout << "Tidak ada pesanan dalam antrian.\n";
        return;
    }
    
    cout << "\n=== DAFTAR PESANAN ===\n";
    Order* temp = head;
    while (temp) {
        cout << "----------------------------------\n";
        cout << "Order ID: " << temp->orderID << "\n";
        cout << "Nama Makanan: " << temp->foodName << "\n";
        cout << "Jumlah: " << temp->quantity << "\n";
        cout << "Harga per Item: Rp" << temp->pricePerItem << "\n";
        cout << "Total Harga: Rp" << temp->totalPrice << "\n";
        temp = temp->next;
    }
}

// Fungsi menghapus setiap node ke-K Remove every K-th node from a linked list
void removeEveryKthNode(Order*& head, int K) {
    if (!head || K <= 0) {
        cout << "Nilai K tidak valid atau daftar kosong!\n";
        return;
    }
    
    Order* temp = head;
    Order* prev = nullptr;
    int count = 1;
    
    while (temp) {
        if (count % K == 0) {
            cout << "Menghapus Order ID " << temp->orderID << " (" << temp->foodName << ")\n";
            if (prev) {
                prev->next = temp->next;
                delete temp;
                temp = prev->next;
            } else {
                head = temp->next;
                delete temp;
                temp = head;
            }
        } else {
            prev = temp;
            temp = temp->next;
        }
        count++;
    }
}

// Fungsi membatalkan pesanan berdasarkan ID delete a node without a head pointer
void cancelOrder(Order*& head, int orderID) {
    if (!head) {
        cout << "Tidak ada pesanan yang bisa dibatalkan.\n";
        return;
    }
    
    Order* temp = head;
    Order* prev = nullptr;
    
    if (temp && temp->orderID == orderID) {
        head = temp->next;
        delete temp;
        cout << "Pesanan dengan Order ID " << orderID << " berhasil dibatalkan!\n";
        return;
    }
    
    while (temp && temp->orderID != orderID) {
        prev = temp;
        temp = temp->next;
    }
    
    if (!temp) {
        cout << "Pesanan tidak ditemukan.\n";
        return;
    }
    
    prev->next = temp->next;
    delete temp;
    cout << "Pesanan dengan Order ID " << orderID << " berhasil dibatalkan!\n";
}

int main() {
    Order* head = nullptr;
    int orderCounter = 1;
    int choice;

    while (true) {
        cout << "\n=== MENU SISTEM PESANAN ===\n";
        cout << "\n| By: Ahmad Wildan Fawwaz |\n";
        cout << "\n|                         |\n";
        cout << "\n===========================\n";
        cout << "1. Tambahkan Pesanan\n";
        cout << "2. Lihat Semua Pesanan\n";
        cout << "3. Batalkan Pesanan\n"; //delete a node without a head pointer
        cout << "4. Hapus Setiap K-th Pesanan\n"; //Remove every K-th node from a linked list
        cout << "5. Keluar\n";

        choice = getValidInt("Pilih menu: ");

        if (choice == 1) {
            addOrder(head, orderCounter);
        } else if (choice == 2) {
            displayOrders(head);
        } else if (choice == 3) {
            int orderID = getValidInt("Masukkan Order ID yang ingin dibatalkan: ");
            cancelOrder(head, orderID);
        } else if (choice == 4) {
            int K = getValidInt("Masukkan nilai K (hapus setiap K-th pesanan): ");
            removeEveryKthNode(head, K);
        } else if (choice == 5) {
            cout << "Terima kasih telah menggunakan sistem ini!\n";
            break;
        } else {
            cout << "Pilihan tidak valid!\n";
        }
    }
    return 0;
}
