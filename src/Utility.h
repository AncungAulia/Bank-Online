#ifndef UTILITY_H
#define UTILITY_H

#include <string>

// Inti dari class ini hanya untuk memberikan method-method tambahan untuk mempermudah 
class Utility {
public:
    // Method - method class Utility
    // (Semua mehthod dibentuk static agar tidak perlu membentuk objek dan langsung diakses dengan namespace saja)

    static std::string generateAccountNumber(); 
    //membentuk nomor rekening berjumlah 8 digit secara acak

    static std::string formatCurrency(double amount); 
    //membuat format rupiah pada amount dan balance

    static std::string getCurrentDateTime(); 
    //untuk memberikan waktu transaksi pada file transaction 
    
    static void clearScreen(); 
    //membersihkan terminal agar terlihat lebih simple 
    
    static void showColoredText(const std::string& text, int color); 
    //menampilkan warna pada teks notifikasi dan lainnya menggunakan ANSI Escape Code
    
    static void showSuccessMessage(const std::string& message); 
    //menampilkan message dengan memanggil fungsi showColoredText untuk membuat warna hijau
    
    static void showErrorMessage(const std::string& message); 
    //memberikan message dengan memanggil fungsi showColoredText untuk membuat warna hijau
};

#endif 