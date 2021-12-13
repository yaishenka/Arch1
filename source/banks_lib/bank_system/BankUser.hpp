//
// Created by wasd on 10.12.2021.
//

#pragma once

#include <string>
#include <optional>

#include <banks_lib/types/types.hpp>
#include <banks_lib/bank_system/Bank.hpp>

namespace banks {

class BankUser : public std::enable_shared_from_this<BankUser> {
 public:
  using Ptr = std::shared_ptr<BankUser>;

  explicit BankUser(UserId user_id, std::shared_ptr<Bank> bank,
                    const UserInfo& user_info);

  void SetAddress(std::string address);
  void SetPassport(std::string passport);

  void Withdraw(AccountId account_id, Money delta) {
    bank_->Withdraw(account_id, delta, shared_from_this());
  }
  void Refill(AccountId account_id, Money delta) {
    bank_->Refill(account_id, delta);
  }

  Money GetBalance(AccountId account_id);

  UserId GetUserId() const {
    return user_id_;
  }

  BankId GetBankId() const {
    return bank_->GetBankId();
  }

  std::vector<AccountId> ListAccounts() {
    return bank_->ListAccounts(shared_from_this());
  }

  AccountId CreateAccount(eAccountType type) {
    return bank_->CreateAccount(type, shared_from_this());
  }

 private:
  void UpgradeAccounts();

  UserId user_id_;
  std::shared_ptr<Bank> bank_;

  UserInfo user_info_;
};

}  // namespace banks
