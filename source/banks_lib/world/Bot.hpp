//
// Created by wasd on 10.12.2021.
//

#pragma once

#include <banks_lib/world/IUser.hpp>
#include <banks_lib/world/UserInfo.hpp>

namespace banks {

class Bot : public IUser {
 public:
  explicit Bot(const UserInfo& user_info);

  void Step() override;

protected:
  void CreateAccount(BankId bank_id, eAccountType account_type) override;
  Money GetBalance(AccountId account_id) override;
  std::vector<AccountId> ListAccounts() override;
};

}  // namespace banks
