#include "Authentication.h"
#include "Bank.h"
#include "Utility.h"
#include <iostream>
#include <limits>
#include <memory>

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string getSecureInput() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

void showMainMenu() {
    Utility::clearScreen();
    Utility::showColoredText("\n==== Selamat Datang di Bank Anfika! ====\n", 2);
    std::cout << "1. Register\n"
              << "2. Login sebagai admin\n"
              << "3. Login sebagai nasabah\n"
              << "4. Keluar\n"
              << "=========================================\n"
              << "Pilihan Anda: ";
}

void handleClientRegistration(Authentication& auth) {
    Utility::clearScreen();
    Utility::showColoredText("\n=== REGISTRASI NASABAH ===\n", 2);
    
    clearInputBuffer();
    
    std::cout << "Nama: ";
    std::string name = getSecureInput();
    
    std::cout << "Email: ";
    std::string email = getSecureInput();
    
    std::cout << "No. Telepon: ";
    std::string phone = getSecureInput();
    
    std::cout << "Password: ";
    std::string password = getSecureInput();
    
    std::cout << "PIN (4 digit): ";
    std::string pin = getSecureInput();
    
    std::string accountNumber = Utility::generateAccountNumber();
    Client newClient(name, password, email, phone, pin, accountNumber, 0.0);
    
    if (auth.registerClient(newClient)) {
        Utility::showSuccessMessage("\nRegistrasi berhasil!");
        std::cout << "Nomor rekening Anda: " << accountNumber << "\n";
    } else {
        Utility::showErrorMessage("\nRegistrasi gagal!");
    }
    
    std::cout << "\nTekan Enter untuk kembali...";
    std::cin.get();
}

void handleClientTransactions(Client* client, Bank& bank) {
    Utility::clearScreen();
    Utility::showColoredText("\n=== TRANSAKSI ===\n", 2);
    
    std::cout << "1. Setor Tunai\n"
              << "2. Tarik Tunai\n"
              << "3. Transfer\n"
              << "Pilihan (0 untuk kembali): ";
    
    int choice;
    std::cin >> choice;
    clearInputBuffer();
    
    double amount;
    std::string pin;
    
    switch(choice) {
        case 1: {
            std::cout << "Jumlah setoran: ";
            std::cin >> amount;
            std::cout << "PIN: ";
            clearInputBuffer();
            pin = getSecureInput();
            
            if (bank.deposit(*client, amount, pin)) {
                Utility::showSuccessMessage("Setor tunai berhasil!");
                std::cout << "Saldo baru: " << Utility::formatCurrency(client->getBalance()) << "\n";
            } else {
                Utility::showErrorMessage("Setor tunai gagal!");
            }
            break;
        }
        case 2: {
            std::cout << "Jumlah penarikan: ";
            std::cin >> amount;
            std::cout << "PIN: ";
            clearInputBuffer();
            pin = getSecureInput();
            
            if (bank.withdraw(*client, amount, pin)) {
                Utility::showSuccessMessage("Penarikan berhasil!");
                std::cout << "Saldo baru: " << Utility::formatCurrency(client->getBalance()) << "\n";
            } else {
                Utility::showErrorMessage("Penarikan gagal!");
            }
            break;
        }
        case 3: {
            std::cout << "Nomor rekening tujuan: ";
            std::string targetAccount = getSecureInput();
            std::cout << "Jumlah transfer: ";
            std::cin >> amount;
            std::cout << "PIN: ";
            clearInputBuffer();
            pin = getSecureInput();
            
            if (bank.transfer(*client, targetAccount, amount, pin)) {
                Utility::showSuccessMessage("Transfer berhasil!");
                std::cout << "Saldo baru: " << Utility::formatCurrency(client->getBalance()) << "\n";
            } else {
                Utility::showErrorMessage("Transfer gagal!");
            }
            break;
        }
    }
    
    std::cout << "\nTekan Enter untuk kembali...";
    std::cin.get();
}

void showTransactionHistory(const std::string& accountNumber, DBase& db) {
    Utility::clearScreen();
    Utility::showColoredText("\n=== RIWAYAT TRANSAKSI ===\n", 2);
    
    auto history = db.getTransactionHistory(accountNumber);
    if (history.empty()) {
        std::cout << "Belum ada transaksi.\n";
    } else {
        for (const auto& transaction : history) {
            std::cout << transaction << "\n";
        }
    }
    
    std::cout << "\nTekan Enter untuk kembali...";
    std::cin.get();
}

void handleClientMenu(Client* client, Bank& bank, DBase& db) {
    while (true) {
        Utility::clearScreen();
        Utility::showColoredText("\n=== Menu Nasabah ===\n", 2);
        std::cout << "Selamat datang, " << client->getName() << "!\n\n"
                  << "1. Lihat profil\n"
                  << "2. Ubah profil\n"
                  << "3. Transaksi\n"
                  << "4. Lihat riwayat transaksi\n"
                  << "5. Logout\n"
                  << "\nPilihan Anda: ";
        
        int choice;
        std::cin >> choice;
        clearInputBuffer();
        
        switch (choice) {
            case 1: {
                Utility::clearScreen();
                Utility::showColoredText("\n=== PROFIL NASABAH ===\n", 2);
                std::cout << "Nama: " << client->getName() << "\n"
                         << "Email: " << client->getEmail() << "\n"
                         << "No. Telepon: " << client->getPhone() << "\n"
                         << "No. Rekening: " << client->getAccountNumber() << "\n"
                         << "Saldo: " << Utility::formatCurrency(client->getBalance()) << "\n";
                std::cout << "\nTekan Enter untuk kembali...";
                std::cin.get();
                break;
            }
            case 2: {
                Utility::clearScreen();
                Utility::showColoredText("\n=== UBAH PROFIL ===\n", 2);
    
                std::cout << "Profil saat ini:\n"
                        << "Nama: " << client->getName() << "\n"
                        << "Email: " << client->getEmail() << "\n"
                        << "No. Telepon: " << client->getPhone() << "\n\n";
    
                std::cout << "Masukkan PIN untuk verifikasi: ";
                std::string pin = getSecureInput();
    
                if (pin != client->getPin()) {
                    Utility::showErrorMessage("PIN salah!");
                    std::cout << "\nTekan Enter untuk kembali...";
                    std::cin.get();
                    break;
                }
    
                std::cout << "\nMasukkan data baru (kosongkan jika tidak ingin mengubah):\n";
    
                std::cout << "Nama baru: ";
                std::string newName = getSecureInput();
    
                std::cout << "Email baru: ";
                std::string newEmail = getSecureInput();
    
                std::cout << "No. Telepon baru: ";
                std::string newPhone = getSecureInput();
    
                std::cout << "Password baru (kosongkan jika tidak ingin mengubah): ";
                std::string newPassword = getSecureInput();
    
                if (!newName.empty()) client->setName(newName);
                if (!newEmail.empty()) client->setEmail(newEmail);
                if (!newPhone.empty()) client->setPhone(newPhone);
                if (!newPassword.empty()) client->setPassword(newPassword);
    
                if (db.updateClient(*client)) {
                    Utility::showSuccessMessage("Profil berhasil diperbarui!");
                } else {
                    Utility::showErrorMessage("Gagal memperbarui profil!");
                }
    
                std::cout << "\nTekan Enter untuk kembali...";
                std::cin.get();
                break;
            }
            case 3:
                handleClientTransactions(client, bank);
                break;
            case 4:
                showTransactionHistory(client->getAccountNumber(), db);
                break;
            case 5:
                return;
        }
    }
}

void handleAdminMenu(Admin* admin, DBase& db) {
    while (true) {
        Utility::clearScreen();
        Utility::showColoredText("\n=== Menu Admin ===\n", 2);
        std::cout << "1. Lihat semua akun\n"
                  << "2. Hapus akun\n"
                  << "3. Lihat riwayat transaksi nasabah\n"
                  << "4. Logout\n"
                  << "\nPilihan Anda: ";
        
        int choice;
        std::cin >> choice;
        clearInputBuffer();
        
        switch (choice) {
            case 1: {
                Utility::clearScreen();
                Utility::showColoredText("\n=== DAFTAR NASABAH ===\n", 2);
                auto clients = db.getAllClients();
                for (const auto& client : clients) {
                    std::cout << "\nNama: " << client.getName()
                             << "\nEmail: " << client.getEmail()
                             << "\nTelepon: " << client.getPhone()
                             << "\nNo. Rekening: " << client.getAccountNumber()
                             << "\nSaldo: " << Utility::formatCurrency(client.getBalance())
                             << "\n" << std::string(30, '=');
                }
                std::cout << "\nTekan Enter untuk kembali...";
                std::cin.get();
                break;
            }
            case 2: {
                std::cout << "Masukkan nomor rekening: ";
                std::string accNumber = getSecureInput();
                if (db.deleteClient(accNumber)) {
                    Utility::showSuccessMessage("Akun berhasil dihapus!");
                } else {
                    Utility::showErrorMessage("Gagal menghapus akun!");
                }
                std::cout << "\nTekan Enter untuk kembali...";
                std::cin.get();
                break;
            }
            case 3: {
                std::cout << "Masukkan nomor rekening: ";
                std::string accNumber = getSecureInput();
                showTransactionHistory(accNumber, db);
                break;
            }
            case 4:
                return;
        }
    }
}

int main() {
    try {
        DBase db;
        Bank bank(db);
        Authentication auth;
        
        while (true) {
            showMainMenu();
            int choice;
            if (!(std::cin >> choice)) {
                clearInputBuffer();
                Utility::showErrorMessage("\nInput tidak valid!");
                continue;
            }
            
            switch (choice) {
                case 1:
                    handleClientRegistration(auth);
                    break;
                    
                case 2: {
                    Utility::clearScreen();
                    clearInputBuffer();
                    
                    std::cout << "Nama Admin: ";
                    std::string name = getSecureInput();
                    std::cout << "Password: ";
                    std::string password = getSecureInput();
                    
                    std::unique_ptr<Admin> admin(auth.loginAdmin(name, password));
                    if (admin) {
                        Utility::showSuccessMessage("\nLogin berhasil!");
                        std::cout << "Tekan Enter untuk melanjutkan...";
                        std::cin.get();
                        handleAdminMenu(admin.get(), db);
                    } else {
                        Utility::showErrorMessage("\nLogin gagal!");
                        std::cout << "Tekan Enter untuk kembali...";
                        std::cin.get();
                    }
                    break;
                }
                    
                case 3: {
                    Utility::clearScreen();
                    clearInputBuffer();
                    
                    std::cout << "Nama: ";
                    std::string name = getSecureInput();
                    std::cout << "Password: ";
                    std::string password = getSecureInput();
                    
                    std::unique_ptr<Client> client(auth.loginClient(name, password));
                    if (client) {
                        Utility::showSuccessMessage("\nLogin berhasil!");
                        std::cout << "Tekan Enter untuk melanjutkan...";
                        std::cin.get();
                        handleClientMenu(client.get(), bank, db);
                    } else {
                        Utility::showErrorMessage("\nLogin gagal!");
                        std::cout << "Tekan Enter untuk kembali...";
                        std::cin.get();
                    }
                    break;
                }
                    
                case 4:
                    Utility::showColoredText("\nTerima kasih telah menggunakan layanan kami!", 2);
                    return 0;
                    
                default:
                    Utility::showErrorMessage("\nPilihan tidak valid!");
                    std::cout << "Tekan Enter untuk kembali...";
                    clearInputBuffer();
                    std::cin.get();
            }
        }
    } catch (const std::exception& e) {
        Utility::showErrorMessage("\nTerjadi kesalahan: " + std::string(e.what()));
        return 1;
    }
    
    return 0;
}