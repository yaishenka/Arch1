//
// Created by wasd on 10.12.2021.
//

#include <banks_lib/accounts/DepositAccount.hpp>

using namespace banks;

DepositAccount::DepositAccount(AccountId account_id,
                               const Percentage& deposit_percent, Time deadline)
    : IAccount(account_id),
      percentage_(deposit_percent),
      deadline_(deadline),
      months_count_(0) {
}

OperationStatus DepositAccount::Withdraw(Money delta) {
  if (months_count_ < deadline_) {
    return OperationStatus{0, eStatus::eDenied};
  }

  if (GetBalance() < delta) {
    return OperationStatus{0, eStatus::eDenied};
  }

  eStatus status = account_impl_->DecreaseBalance(delta);
  if (status == eStatus::eOk) {
    operation_history_.Push(
        std::make_shared<WithdrawOperation>(delta, next_free_op_id_));

    return OperationStatus{next_free_op_id_++, status};
  } else {
    return OperationStatus{0, status};
  }
}

OperationStatus DepositAccount::Refill(Money delta) {
  eStatus status = account_impl_->IncreaseBalance(delta);
  if (status == eStatus::eOk) {
    return OperationStatus{next_free_op_id_++, status};
  } else {
    return OperationStatus{0, status};
  }
}

void DepositAccount::Step() {
  AccruePercents();  // TODO proper step
}

OperationStatus DepositAccount::AccruePercents() {
  ++months_count_;

  Money delta = GetBalance() *
                (percentage_.integer * kHundredPercent + percentage_.fraction) /
                (kHundredPercent * kHundredPercent);

  eStatus status = account_impl_->IncreaseBalance(delta);
  if (status == eStatus::eOk) {
    return OperationStatus{next_free_op_id_++, status};
  } else {
    return OperationStatus{0, status};
  }
}

void DepositAccount::AbortOperation(IOperation::Ptr operation) {
  throw std::runtime_error("unimplemented");
}
