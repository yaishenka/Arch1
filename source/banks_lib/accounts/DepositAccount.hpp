//
// Created by wasd on 10.12.2021.
//

#pragma once

#include <banks_lib/accounts/IAccount.hpp>
#include <banks_lib/types/types.hpp>

namespace banks {

class DepositAccount : public IAccount {
 public:
  explicit DepositAccount(AccountId account_id,
                          const Percentage& deposit_percent, Time deadline);

  OperationStatus Withdraw(Money delta) override;
  OperationStatus Refill(Money delta) override;

  void Step() override;

 protected:
  OperationStatus AccruePercents() override;

  void AbortOperation(IOperation::Ptr operation) override;

 private:
  Percentage percentage_;
  Time deadline_;
  Time months_count_;
};

}  // namespace banks
