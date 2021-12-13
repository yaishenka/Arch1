//
// Created by wasd on 10.12.2021.
//

#pragma once

#include <banks_lib/accounts/IAccount.hpp>

namespace banks {

class CreditAccount : public IAccount {
 public:
  explicit CreditAccount(AccountId account_id, Money credit_limit,
                         const Percentage& percentage);

  OperationStatus Withdraw(Money delta) override;
  OperationStatus Refill(Money delta) override;

  void Step() override;

 protected:
  OperationStatus AccruePercents() override;

  void AbortOperation(IOperation::Ptr operation) override;

 private:
  Money credit_limit_;
  Percentage percentage_;
};

}  // namespace banks
