#include <gtest/gtest.h>
#include "banking/Account.h"

TEST(AccountTest, ConstructorSetsIbanAndBalance) {
    Account acc("DE12345678", 100.0);
    EXPECT_EQ(acc.getIban(), "DE12345678");
    EXPECT_DOUBLE_EQ(acc.getBalance(), 100.0);
}

TEST(AccountTest, DepositIncreasesBalance) {
    Account acc("DE12345678", 100.0);
    acc.deposit(50.0);
    EXPECT_DOUBLE_EQ(acc.getBalance(), 150.0);
}

TEST(AccountTest, WithdrawDecreasesBalanceWhenSufficient) {
    Account acc("DE12345678", 100.0);
    bool success = acc.withdraw(30.0);
    EXPECT_TRUE(success);
    EXPECT_DOUBLE_EQ(acc.getBalance(), 70.0);
}

TEST(AccountTest, WithdrawFailsWhenInsufficient) {
    Account acc("DE12345678", 100.0);
    bool success = acc.withdraw(150.0);
    EXPECT_FALSE(success);
    EXPECT_DOUBLE_EQ(acc.getBalance(), 100.0);
}
