#include <iostream>
#include <limits>
using namespace std;

// Struktur Node Pesanan
struct Order {
    int orderID;
    string foodName;
    int quantity;
    double pricePerItem;
    double totalPrice;
    Order* next;

    // Constructor
    Order(int id, string name, int qty, double price) {
        orderID = id;
        foodName = name;
        quantity = qty;
        pricePerItem = price;
        totalPrice = qty * price;
        next = nullptr;
    }
};

// Fungsi untuk validasi input angka
int getValidInt(string prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (!(cin >> value) || value <= 0) {
            cout << "? Pilihan tidak valid! Harap masukkan angka positif.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore();
            return value;
        }
    }
}

// Fungsi untuk validasi input angka desimal
double getValidDouble(string prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (!(cin >> value) || value <= 0) {
            cout << "? Pilihan tidak valid! Harap masukkan angka positif.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore();
            return value;
        }
    }
}

// Fungsi untuk validasi input string (tidak boleh kosong)
string getValidString(string prompt) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        if (!value.empty()) {
            return value;
        }
        cout << "? Input tidak boleh kosong! Silakan coba lagi.\n";
    }
}

// Fungsi menambahkan pesanan ke antrian
void addOrder(Order*& head, int& orderCounter) {
    string foodName = getValidString("?? Masukkan nama makanan: ");
    int quantity = getValidInt("?? Masukkan jumlah: ");
    double price = getValidDouble("?? Masukkan harga per item: ");

    Order* newOrder = new Order(orderCounter++, foodName, quantity, price);

    if (head == nullptr) {
        head = newOrder;
    } else {
        Order* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newOrder;
    }
    cout << "? Pesanan berhasil ditambahkan!\n";
}

// Fungsi menampilkan semua pesanan
void displayOrders(Order* head) {
    if (head == nullptr) {
        cout << "? Tidak ada pesanan dalam antrian.\n";
        return;
    }
    cout << "\n=== ?? DAFTAR PESANAN ?? ===\n";
    Order* temp = head;
    while (temp != nullptr) {
        cout << "----------------------------------\n";
        cout << "?? Order ID: " << temp->orderID << "\n";
        cout << "?? Nama Makanan: " << temp->foodName << "\n";
        cout << "?? Jumlah: " << temp->quantity << "\n";
        cout << "?? Harga per Item: Rp" << temp->pricePerItem << "\n";
        cout << "?? Total Harga: Rp" << temp->totalPrice << "\n";
        temp = temp->next;
    }
}

// Fungsi menghapus setiap node ke-K
void removeEveryKthNode(Order*& head, int K) {
    if (head == nullptr || K <= 0) return;

    Order* temp = head;
    Order* prev = nullptr;
    int count = 1;

    while (temp != nullptr) {
        if (count % K == 0) {  // Jika node ke-K ditemukan
            cout << "? Menghapus Order ID " << temp->orderID << " (" << temp->foodName << ")\n";
            
            if (prev != nullptr) {
                prev->next = temp->next;
                delete temp;
                temp = prev->next;
            } else {  // Jika node yang dihapus adalah head
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

// Fungsi mencari pesanan berdasarkan order ID
Order* findOrder(Order* head, int orderID) {
    Order* temp = head;
    while (temp != nullptr) {
        if (temp->orderID == orderID)
            return temp;
        temp = temp->next;
    }
    return nullptr;
}

// Fungsi membatalkan pesanan berdasarkan Order ID
void cancelOrder(Order*& head, int orderID) {
    if (head == nullptr) {
        cout << "? Tidak ada pesanan yang bisa dibatalkan.\n";
        return;
    }

    Order* temp = head;
    Order* prev = nullptr;

    // Jika pesanan yang ingin dihapus adalah head
    if (temp != nullptr && temp->orderID == orderID) {
        head = temp->next;
        delete temp;
        cout << "? Pesanan dengan Order ID " << orderID << " berhasil dibatalkan!\n";
        return;
    }

    // Mencari pesanan yang ingin dihapus
    while (temp != nullptr && temp->orderID != orderID) {
        prev = temp;
        temp = temp->next;
    }

    // Jika pesanan tidak ditemukan
    if (temp == nullptr) {
        cout << "? Pesanan tidak ditemukan.\n";
        return;
    }

    prev->next = temp->next;
    delete temp;
    cout << "? Pesanan dengan Order ID " << orderID << " berhasil dibatalkan!\n";
}

int main() {
    Order* head = nullptr;
    int orderCounter = 1;
    int choice;

    while (true) {
        cout << "\n=== ?? MENU SISTEM PESANAN ?? ===\n";
        cout << "1?? Tambah Pesanan\n";
        cout << "2?? Lihat Semua Pesanan\n";
        cout << "3?? Batalkan Pesanan\n";
        cout << "4?? Hapus Setiap K-th Pesanan\n";
        cout << "5?? Keluar\n";

        choice = getValidInt("?? Pilih menu: ");

        if (choice == 1) {
            addOrder(head, orderCounter);
        } else if (choice == 2) {
            displayOrders(head);
        } else if (choice == 3) {
            int orderID = getValidInt("?? Masukkan Order ID yang ingin dibatalkan: ");
            cancelOrder(head, orderID);
        } else if (choice == 4) {
            int K = getValidInt("?? Masukkan nilai K (hapus setiap K-th pesanan): ");
            removeEveryKthNode(head, K);
            cout << "? Proses penghapusan selesai.\n";
        } else if (choice == 5) {
            cout << "?? Terima kasih telah menggunakan sistem ini!\n";
            break;
        } else {
            cout << "? Pilihan tidak valid!\n";
        }
    }

    // Hapus semua node untuk menghindari memory leak
    while (head != nullptr) {
        Order* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
