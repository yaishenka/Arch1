//
// Created by wasd on 10.12.2021.
//

#pragma once

#include <banks_lib/world/IUser.hpp>

namespace banks {

class TelegramUser : public IUser {
public:
  explicit TelegramUser(UserInfo user_info);

  void Step() override;

protected:
  void CreateAccount(BankId bank_id, eAccountType account_type) override;
  Money GetBalance(AccountId account_id) override;
  std::vector<AccountId> ListAccounts() override;
};

}  // namespace banks
