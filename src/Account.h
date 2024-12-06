#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
protected: //protected agar class turunannya berupa Admin dan Client dapat mengakses
    std::string name;
    std::string password;

public:
    //Constructor 
    Account(std::string name = "", std::string password = ""); 

    //Destructor dengan virtual dan berisi default
    virtual ~Account() = default;  
    
    // getter
    std::string getName() const;
    std::string getPassword() const;

    //setter
    void setName(const std::string& name);
    void setPassword(const std::string& password);
    
    //method login dengan konsep abstraction
    virtual bool login(const std::string& inputName, 
                       const std::string& inputPassword) = 0;
};

#endif