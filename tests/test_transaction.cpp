#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "banking/Account.h"
#include "banking/Transaction.h"

// Mock-класс для Account
class MockAccount : public Account {
public:
    MockAccount(std::string iban, double balance) : Account(iban, balance) {}
    
    MOCK_METHOD(bool, withdraw, (double amount), (override));
    MOCK_METHOD(void, deposit, (double amount), (override));
    MOCK_METHOD(double, getBalance, (), (const, override));
};

TEST(TransactionTest, TransferCallsWithdrawAndDeposit) {
    MockAccount from("DE123", 100.0);
    MockAccount to("DE456", 50.0);
    
    EXPECT_CALL(from, withdraw(30.0))
        .WillOnce(testing::Return(true));
    EXPECT_CALL(to, deposit(30.0))
        .Times(1);
    
    bool result = Transaction::transfer(from, to, 30.0);
    
    EXPECT_TRUE(result);
}

TEST(TransactionTest, TransferFailsWhenWithdrawFails) {
    MockAccount from("DE123", 100.0);
    MockAccount to("DE456", 50.0);
    
    EXPECT_CALL(from, withdraw(30.0))
        .WillOnce(testing::Return(false));
    EXPECT_CALL(to, deposit(30.0))
        .Times(0);
    
    bool result = Transaction::transfer(from, to, 30.0);
    
    EXPECT_FALSE(result);
}
