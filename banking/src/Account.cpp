#include "banking/Account.h"

Account::Account(std::string iban, double balance) 
    : iban_(iban), balance_(balance) {}

std::string Account::getIban() const {
    return iban_;
}

double Account::getBalance() const {
    return balance_;
}

void Account::deposit(double amount) {
    balance_ += amount;
}

bool Account::withdraw(double amount) {
    if (amount <= balance_) {
        balance_ -= amount;
        return true;
    }
    return false;
}
