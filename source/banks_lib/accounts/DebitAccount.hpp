//
// Created by wasd on 10.12.2021.
//

#pragma once

#include <banks_lib/accounts/IAccount.hpp>

namespace banks {

class DebitAccount : public IAccount {
 public:
  explicit DebitAccount(AccountId account_id, const Percentage& percentage);

  OperationStatus Withdraw(Money delta) override;
  OperationStatus Refill(Money delta) override;

  void Step() override;

 protected:
  OperationStatus AccruePercents() override;

  void AbortOperation(IOperation::Ptr operation) override;

private:
  Percentage percentage_;
};

}  // namespace banks
