//
// Created by wasd on 10.12.2021.
//

#pragma once

#include <unordered_map>
#include <string>

#include "banks_lib/users/UserInfo.hpp"
#include <banks_lib/accounts/AccountFabric.hpp>
#include <banks_lib/logger/ILogger.hpp>
#include <banks_lib/bank_system/AccountConditions.hpp>

namespace banks {

class BankUser;
class PaymentSystem;

class Bank : public std::enable_shared_from_this<Bank> {
 public:
  using Ptr = std::shared_ptr<Bank>;

  explicit Bank(BankId bank_id);

  BankId GetBankId() const {
    return bank_id_;
  }

  void SetLogger(ILogger::Ptr logger);
  void SetAccountConditions(AccountConditions conditions);
  void ConnectToPaymentSystem(
      const std::shared_ptr<PaymentSystem>& payment_system);

  std::shared_ptr<BankUser> CreateBankUser(const UserInfo& user_info);

  AccountId CreateAccount(eAccountType type,
                          std::shared_ptr<BankUser> bank_user);
  std::vector<AccountId> ListAccounts(std::shared_ptr<BankUser> bank_user);
  eStatus GiveAccess(AccountId account_id, std::shared_ptr<BankUser> owner,
                     std::shared_ptr<BankUser> coowner);

  Money GetBalance(AccountId account_id, std::shared_ptr<BankUser> bank_user);

  eStatus Transfer(AccountId source_id, std::shared_ptr<BankUser> source,
                   AccountId target_id, Money delta);

  eStatus Withdraw(AccountId account_id, Money delta,
                   std::shared_ptr<BankUser> bank_user);
  eStatus Refill(AccountId account_id, Money delta);

  void Upgrade(AccountId account_id, std::shared_ptr<BankUser> bank_user);

  void Abort(TransactionId transaction_id);

  void Step();

 private:
  bool CheckAccess(AccountId account_id, std::shared_ptr<BankUser> bank_user);

  BankId bank_id_;
  std::weak_ptr<PaymentSystem> payment_system_;

  ILogger::Ptr logger_;  // TODO logging

  AccountFabric account_fabric_;
  std::optional<AccountConditions> conditions_;
  std::unordered_map<AccountId, IAccount::Ptr> accounts_;
  std::unordered_map<AccountId, std::vector<UserId>> account_to_users_;

  std::unordered_set<UserId> users_;
  UserId next_free_user_id_;
  std::unordered_map<UserId, std::vector<AccountId>> user_to_accounts_;

  std::unordered_map<OperationId, TransactionId> operation_to_transaction_;
  std::unordered_map<TransactionId, std::vector<OperationId>>
      transaction_to_operation_;
  TransactionId next_transaction_id_;
};

}  // namespace banks
