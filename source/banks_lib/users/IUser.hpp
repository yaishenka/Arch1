//
// Created by wasd on 10.12.2021.
//

#pragma once

#include <vector>

#include "banks_lib/types/types.hpp"
#include "banks_lib/bank_system/BankUser.hpp"

namespace banks {

class IUser {
 public:
  explicit IUser(const UserInfo& user_info) : user_info_(user_info) {
  }

  virtual void Step() = 0;

 protected:
  virtual void CreateAccount(BankId bank_id, eAccountType account_type) = 0;
  virtual Money GetBalance(BankId bank_id, AccountId account_id) = 0;
  virtual std::vector<BankId> ListBankUsers() = 0;
  virtual std::vector<AccountId> ListAccounts(BankId bank_id) = 0;
  virtual void Withdraw(BankId bank_id, AccountId account_id, Money delta) = 0;
  virtual void Refill(BankId bank_id, AccountId account_id, Money delta) = 0;

  UserInfo user_info_;
};

}  // namespace banks
