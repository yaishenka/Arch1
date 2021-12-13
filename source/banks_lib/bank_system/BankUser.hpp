//
// Created by wasd on 10.12.2021.
//

#pragma once

#include <string>
#include <optional>

#include <banks_lib/types/types.hpp>
#include <banks_lib/bank_system/Bank.hpp>

namespace banks {

class BankUser : std::enable_shared_from_this<BankUser> {
 public:
  using Ptr = std::shared_ptr<BankUser>;

  explicit BankUser(UserId user_id, std::shared_ptr<Bank> bank,
                    const UserInfo& user_info);

  void SetAddress(std::string address);
  void SetPassport(std::string passport);

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

 private:
  void UpgradeAccounts();

  UserId user_id_;
  std::shared_ptr<Bank> bank_;

  UserInfo user_info_;
};

}  // namespace banks
