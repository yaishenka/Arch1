//
// Created by wasd on 10.12.2021.
//

#include <banks_lib/accounts/DebitAccount.hpp>
#include <banks_lib/operations/Operations.hpp>

using namespace banks;

DebitAccount::DebitAccount(AccountId account_id, const Percentage& percentage)
    : IAccount(account_id), percentage_(percentage) {
}

OperationStatus DebitAccount::Withdraw(Money delta) {
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

OperationStatus DebitAccount::Refill(Money delta) {
  eStatus status = account_impl_->IncreaseBalance(delta);
  if (status == eStatus::eOk) {
    return OperationStatus{next_free_op_id_++, status};
  } else {
    return OperationStatus{0, status};
  }
}

void DebitAccount::Step() {
  AccruePercents();  // TODO proper step
}

OperationStatus DebitAccount::AccruePercents() {
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

void DebitAccount::AbortOperation(IOperation::Ptr operation) {
  throw std::runtime_error("unimplemented");
}
