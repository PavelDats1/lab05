#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
public:
    Account(std::string iban, double balance);
    virtual ~Account() = default;
    
    std::string getIban() const;
    virtual double getBalance() const;
    virtual void deposit(double amount);
    virtual bool withdraw(double amount);
    
private:
    std::string iban_;
    double balance_;
};

#endif
