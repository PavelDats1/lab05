#include "banking/Transaction.h"

bool Transaction::transfer(Account& from, Account& to, double amount) {
    if (from.withdraw(amount)) {
        to.deposit(amount);
        return true;
    }
    return false;
}
