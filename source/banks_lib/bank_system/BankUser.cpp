//
// Created by wasd on 10.12.2021.
//

#include <banks_lib/bank_system/BankUser.hpp>

using namespace banks;

BankUser::BankUser(UserId user_id, std::shared_ptr<Bank> bank,
                   const UserInfo& user_info)
    : user_id_(user_id), bank_(std::move(bank)), user_info_(user_info) {
}

void BankUser::SetAddress(std::string address) {
  user_info_.address_ = std::move(address);

  if (user_info_.passport_.has_value()) {
    UpgradeAccounts();
  }
}

void BankUser::SetPassport(std::string passport) {
  user_info_.passport_ = std::move(passport);

  if (user_info_.address_.has_value()) {
    UpgradeAccounts();
  }
}
// TODO upgrade when account created
Money BankUser::GetBalance(AccountId account_id) {
  return bank_->GetBalance(account_id, shared_from_this());
}

void BankUser::UpgradeAccounts() {
  const auto& accounts = ListAccounts();
  for (AccountId account_id : accounts) {
    bank_->Upgrade(account_id, shared_from_this());
  }
}
