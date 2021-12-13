//
// Created by wasd on 10.12.2021.
//

#pragma once

#include <memory>

#include <banks_lib/accounts/IAccount.hpp>

namespace banks {

class AccountFabric {
 public:
  explicit AccountFabric();

  std::shared_ptr<IAccount> CreateDebitAccount(const Percentage& debit_percentage);
  std::shared_ptr<IAccount> CreateCreditAccount(Money credit_limit, const Percentage& credit_percentage);
  std::shared_ptr<IAccount> CreateDepositAccount(const Percentage& deposit_percent, Time deadline);

private:
  AccountId next_account_id_ = 0;
};

}  // namespace banks
