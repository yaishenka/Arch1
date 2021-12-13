/**
 * @file IAccount.hpp
 * @author yaishenka
 * @date 07.11.2021
 */
#pragma once

#include <cctype>
#include <vector>

#include <banks_lib/accounts/IAccountImpl.hpp>
#include <banks_lib/operations/Operations.hpp>
#include <banks_lib/operations/OperationHistory.hpp>
#include <banks_lib/types/types.hpp>

namespace banks {

class IAccount {
 public:
  using Ptr = std::shared_ptr<IAccount>;

  explicit IAccount(AccountId account_id);
  virtual ~IAccount() = default;

  [[nodiscard]] virtual OperationStatus Withdraw(Money delta) = 0;
  [[nodiscard]] virtual OperationStatus Refill(Money delta) = 0;

  virtual void Step() = 0;

  [[nodiscard]] Money GetBalance() const {
    return account_impl_->GetBalance();
  }

  [[nodiscard]] AccountId GetAccountId() const {
    return account_id_;
  }

  void Upgrade();

  [[nodiscard]] std::vector<IOperation::Ptr> AbortOperation(
      OperationId operation_id);

 protected:
  virtual OperationStatus AccruePercents() = 0;

  virtual void AbortOperation(IOperation::Ptr operation) = 0;

  IAccountImpl::Ptr account_impl_;
  OperationHistory operation_history_;

  AccountId account_id_;
  OperationId next_free_op_id_;

  static const Money kHundredPercent = 100;
};
}  // namespace banks