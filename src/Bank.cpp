#include "Bank.h"
#include "Utility.h"

Bank::Bank(DBase& database) : db(database) {}

bool Bank::deposit(Client& client, double amount, const std::string& pin) {
    if (pin != client.getPin()) return false;
    
    client.setBalance(client.getBalance() + amount);
    db.updateClient(client);
    db.saveTransaction(client.getAccountNumber(), "SETOR", amount, client.getAccountNumber());
    
    return true;
}

bool Bank::withdraw(Client& client, double amount, const std::string& pin) {
    if (pin != client.getPin() || client.getBalance() < amount) return false;
    
    client.setBalance(client.getBalance() - amount);
    db.updateClient(client);
    db.saveTransaction(client.getAccountNumber(), "TARIK", amount, client.getAccountNumber());
    
    return true;
}

bool Bank::transfer(Client& sender, const std::string& receiverAccount,
                   double amount, const std::string& pin) {
    if (pin != sender.getPin() || sender.getBalance() < amount) return false;
    
    Client receiver = db.getClientByAccountNumber(receiverAccount);
    if (receiver.getAccountNumber().empty()) return false;
    
    sender.setBalance(sender.getBalance() - amount);
    receiver.setBalance(receiver.getBalance() + amount);
    
    db.updateClient(sender);
    db.updateClient(receiver);
    
    db.saveTransaction(sender.getAccountNumber(), "TRANSFER_KELUAR", amount, receiverAccount);
    db.saveTransaction(receiver.getAccountNumber(), "TRANSFER_MASUK", amount, sender.getAccountNumber());
    
    return true;
}