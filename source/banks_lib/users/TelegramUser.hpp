//
// Created by wasd on 10.12.2021.
//

#pragma once

#include "IUser.hpp"

namespace banks {

class TelegramUser : public IUser {
 public:
  explicit TelegramUser(UserInfo user_info);

  void Step() override;

 protected:
  void CreateAccount(BankId bank_id, eAccountType account_type) override;
  Money GetBalance(BankId bank_id, AccountId account_id) override;
  std::vector<BankId> ListBankUsers() override;
  std::vector<AccountId> ListAccounts(BankId bank_id) override;
  void Withdraw(BankId bank_id, AccountId account_id, Money delta) override;
  void Refill(BankId bank_id, AccountId account_id, Money delta) override;
};

}  // namespace banks
