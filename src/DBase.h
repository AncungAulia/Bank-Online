#ifndef DBASE_H
#define DBASE_H

#include "Client.h"
#include <vector>

class DBase {
private:
    const std::string CLIENT_FILE = "clients.txt";
    const std::string TRANSACTION_PREFIX = "transactions_";
    
public:
    bool saveClient(const Client& client);
    bool updateClient(const Client& client);
    bool deleteClient(const std::string& accountNumber);
    std::vector<Client> getAllClients();
    Client getClientByAccountNumber(const std::string& accountNumber);
    void saveTransaction(const std::string& accountNumber, const std::string& type,
                        double amount, const std::string& targetAccount);
    std::vector<std::string> getTransactionHistory(const std::string& accountNumber);
};

#endif