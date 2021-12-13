//
// Created by wasd on 10.12.2021.
//

#include "PaymentSystem.hpp"

using namespace banks;

eStatus PaymentSystem::Transfer(AccountId source_account,
                                BankUser::Ptr source_user,
                                AccountId target_account, BankId target_bank_id,
                                Money delta) {
  // TODO check if banks are registered
  BankId source_bank_id = source_user->GetBankId();
  //  if (target_bank_id == source_bank_id) {
  //
  //  } else {
  //
  //  }

  eStatus status =
      id_to_bank_[source_bank_id]->Withdraw(source_account, delta, source_user);
  if (status != eStatus::eOk) {
    return status;
  }

  status = id_to_bank_[target_bank_id]->Refill(target_account, delta);
  if (status != eStatus::eOk) {
    return status;
  }

  // TODO register transaction

  return status;
}

void PaymentSystem::Abort(TransactionId transaction_id) {
  throw std::runtime_error("payment system abort unimplemented");
}
