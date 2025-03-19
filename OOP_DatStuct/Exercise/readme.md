# Problem: Sistem Manajemen Pesanan Makanan dengan Pembatalan Tanpa Akses ke Head Pointer
Deskripsi Masalah:  
Sebuah restoran cepat saji menggunakan sistem pemesanan digital untuk mengelola daftar pesanan pelanggan. Pelanggan dapat memesan berbagai jenis makanan, dan setiap pesanan akan masuk ke dalam sistem sebagai antrian berbasis linked list. Setiap pesanan direpresentasikan sebagai node dalam linked list, dengan informasi:  
Nomor Pesanan (orderID)  
Pointer ke pesanan berikutnya (next)  

Namun, restoran menghadapi beberapa tantangan dalam mengelola daftar pesanan:  
1. Menghapus Pesanan Tertentu (Delete a Node Without a Head Pointer)
Terkadang, pelanggan berubah pikiran dan ingin membatalkan salah satu pesanan mereka. Sayangnya, sistem restoran hanya memiliki akses ke node pesanan tertentu (misalnya, pesanan ke-3 dalam antrian) tanpa mengetahui node kepala (head pointer). Manajemen restoran perlu solusi untuk menghapus pesanan secara efisien tanpa merusak struktur data.
2. Menghapus Setiap Pesanan ke-K (Remove Every K-th Node from a Linked List)
Setiap akhir jam operasional, restoran perlu melakukan audit pesanan untuk menghapus pesanan tertentu dalam pola tertentu. Misalnya:
Jika restoran ingin menghapus setiap pesanan ke-2, maka pesanan ke-2, ke-4, ke-6, dan seterusnya akan dihapus.
Jika restoran ingin menghapus setiap pesanan ke-3, maka pesanan ke-3, ke-6, ke-9, dan seterusnya akan dihapus.
Jika pelanggan memasukkan nilai K = 1, berarti restoran akan menghapus semua pesanan ganjil (1, 3, 5, ...).

Masalah utama yang dihadapi restoran adalah menjaga keteraturan daftar pesanan tanpa kehilangan informasi penting atau menyebabkan error dalam sistem. 
