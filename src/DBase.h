#ifndef DBASE_H
#define DBASE_H

#include "Client.h"
#include <vector>

class DBase {
private:
    //atribut berupa file txt
    const std::string CLIENT_FILE = "clients.txt";
    const std::string TRANSACTION_PREFIX = "transactions_";
    
public:
    //method-method dari class DBase: 

    bool saveClient(const Client& client); 
    //membentuk file bertipe txt yang menyimpan akun yang dibuat saat registrasi Client
    
    bool updateClient(const Client& client); 
    //mengupdate data Client ketika terjadi transaksi atau perubahan profil
    
    bool deleteClient(const std::string& accountNumber); 
    //menghapus akun Client (hanya dapat dilakukan oleh Admin)
    
    std::vector<Client> getAllClients(); 
    // mengambil akun-akun Client yang tersedia beserta datanya
    
    Client getClientByAccountNumber(const std::string& accountNumber); 
    //mengambil 1 akun Client saja berdasarkan nomor rekening
    
    void saveTransaction(const std::string& accountNumber,
                         const std::string& type, 
                         double amount, 
                         const std::string& targetAccount);
    //menyimpan data transaksi tiap Client dengan file bertipe txt

    std::vector<std::string> getTransactionHistory(const std::string& accountNumber); 
    //mengambil data transaksi dari file yang dbentuk oleh method  saveTransaction                                                                             
};

#endif