//
// Created by wasd on 10.12.2021.
//

#pragma once

#include <unordered_map>

#include <banks_lib/types/types.hpp>
#include <banks_lib/bank_system/BankUser.hpp>

namespace banks {

class PaymentSystem {
 public:
  eStatus Transfer(AccountId source_account, BankUser::Ptr source_user,
                   AccountId target_account, BankId target_bank_id,
                   Money delta);

  void RegisterBank(BankId bank_id, Bank::Ptr bank) {
    id_to_bank_[bank_id] = bank;
  }

  void Abort(TransactionId transaction_id);

 private:
  std::unordered_map<BankId, Bank::Ptr> id_to_bank_;
};

}  // namespace banks
