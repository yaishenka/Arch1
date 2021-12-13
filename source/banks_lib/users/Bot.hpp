//
// Created by wasd on 10.12.2021.
//

#pragma once

#include "IUser.hpp"
#include "UserInfo.hpp"

#include <unordered_map>

namespace banks {

class Bot : public IUser {
 public:
  explicit Bot(const UserInfo& user_info,
               const std::vector<std::shared_ptr<Bank>>& banks);

  void Step() override;

 protected:
  void CreateAccount(BankId bank_id, eAccountType account_type) override;
  Money GetBalance(BankId bank_id, AccountId account_id) override;
  std::vector<BankId> ListBankUsers() override;
  std::vector<AccountId> ListAccounts(BankId bank_id) override;
  void Withdraw(BankId bank_id, AccountId account_id, Money delta) override;
  void Refill(BankId bank_id, AccountId account_id, Money delta) override;

  std::unordered_map<BankId, BankUser::Ptr> bank_users_mapping_;
  std::vector<BankId> banks_users_;

 private:
  void ProcessCreate();
  void ProcessBalance();
  void ProcessList();
  void ProcessOperation();

  std::ostream& output_;
  std::istream& input_;

  const std::vector<std::shared_ptr<Bank>>& banks_;
};

}  // namespace banks
