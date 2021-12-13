//
// Created by wasd on 10.12.2021.
//

#include <banks_lib/accounts/CreditAccount.hpp>

using namespace banks;

CreditAccount::CreditAccount(AccountId account_id, Money credit_limit, const Percentage& percentage)
: IAccount(account_id), credit_limit_(credit_limit), percentage_(percentage) {
}

OperationStatus CreditAccount::Withdraw(Money delta) {
  eStatus status = account_impl_->DecreaseBalance(delta);
  if (status == eStatus::eOk) {
    operation_history_.Push(
      std::make_shared<WithdrawOperation>(delta, next_free_op_id_));

    return OperationStatus{next_free_op_id_++, status};
  } else {
    return OperationStatus{0, status};
  }
}

OperationStatus CreditAccount::Refill(Money delta) {
  eStatus status = account_impl_->IncreaseBalance(delta);
  if (status == eStatus::eOk) {
    return OperationStatus{next_free_op_id_++, status};
  } else {
    return OperationStatus{0, status};
  }
}

void CreditAccount::Step() {
  AccruePercents(); // TODO proper step
}

OperationStatus CreditAccount::AccruePercents() {
  if (GetBalance() >= credit_limit_) {
    return {0, eStatus::eDenied};
  }

  Money delta = (credit_limit_ - GetBalance()) * (percentage_.integer * kHundredPercent +
    percentage_.fraction) /
    (kHundredPercent * kHundredPercent);

  eStatus status = account_impl_->DecreaseBalance(delta);
  if (status == eStatus::eOk) {
    return OperationStatus{next_free_op_id_++, status};
  } else {
    return OperationStatus{0, status};
  }
}

void CreditAccount::AbortOperation(IOperation::Ptr operation) {
  throw std::runtime_error("unimplemented");
}
