/**
 * @file IAccount.hpp
 * @author yaishenka
 * @date 07.11.2021
 */
#pragma once
#include <cctype>
#include <vector>
#include "IAccountImpl.hpp"
#include "../Operations.hpp"
#include "../OperationHistory.hpp"
#include "../types.hpp"

namespace banks {

class IAccount {
 public:
  explicit IAccount(AccountId account_id);
  virtual ~IAccount() = default;

  [[nodiscard]] virtual OperationStatus Withdraw(Money delta) = 0;
  [[nodiscard]] virtual OperationStatus Refill(Money delta) = 0;

  virtual void AccruePercents() = 0;

  [[nodiscard]] Money GetBalance() const {return account_impl_->GetBalance(); }

  void Upgrade();

  [[nodiscard]] std::vector<IOperation::Ptr> AbortOperation(OperationId operation_id);

 protected:
  virtual void AbortOperation(IOperation::Ptr operation) = 0;
  IAccountImpl::Ptr account_impl_;
  OperationHistory operation_history_;

 private:
  AccountId account_id_;
};
}