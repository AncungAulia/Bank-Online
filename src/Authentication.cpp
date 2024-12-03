#include "Authentication.h"
#include "DBase.h"

Authentication::Authentication() : admin("Admin", "1234") {}

bool Authentication::registerClient(const Client& client) {
    DBase db;
    return db.saveClient(client);
}

Client* Authentication::loginClient(const std::string& name, const std::string& password) {
    DBase db;
    std::vector<Client> clients = db.getAllClients();
    
    for (auto& client : clients) {
        if (client.getName() == name && client.getPassword() == password) {
            // Create a new Client object with the found client's data
            return new Client(client.getName(), 
                            client.getPassword(),
                            client.getEmail(),
                            client.getPhone(),
                            client.getPin(),
                            client.getAccountNumber(),
                            client.getBalance());
        }
    }
    
    return nullptr;
}

Admin* Authentication::loginAdmin(const std::string& name, const std::string& password) {
    if (admin.login(name, password)) {
        return new Admin(admin);
    }
    return nullptr;
}