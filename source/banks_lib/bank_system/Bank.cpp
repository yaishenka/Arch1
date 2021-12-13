//
// Created by wasd on 10.12.2021.
//

#include <banks_lib/bank_system/Bank.hpp>
#include <banks_lib/bank_system/BankUser.hpp>

using namespace banks;

Bank::Bank(BankId bank_id, const Percentage& debit_percentage)
    : bank_id_(bank_id),
      account_fabric_(),
      next_free_user_id_(0),
      next_transaction_id_(0) {
}

void Bank::SetLogger(ILogger::Ptr logger) {
  logger_ = std::move(logger);
}

std::shared_ptr<BankUser> Bank::CreateBankUser(const UserInfo& user_info) {
  users_.insert(next_free_user_id_);
  user_to_accounts_[next_free_user_id_] = {};

  return std::make_shared<BankUser>(next_free_user_id_++, shared_from_this(),
                                    user_info);
}

void Bank::SetAccountConditions(AccountConditions conditions) {
  conditions_ = std::move(conditions);
}

AccountId Bank::CreateAccount(eAccountType type,
                              std::shared_ptr<BankUser> bank_user) {
  IAccount::Ptr new_account;
  switch (type) {
    case eAccountType::eDebit:
      new_account =
          account_fabric_.CreateDebitAccount(conditions_.debit_percentage);
      break;
    case eAccountType::eCredit:
      new_account = account_fabric_.CreateCreditAccount(
          conditions_.credit_limit, conditions_.credit_percentage);
      break;
    case eAccountType::eDeposit:
      new_account = account_fabric_.CreateDepositAccount(
          conditions_.deposit_percent,
          conditions_.deadline);  // TODO initial sum percentage
      break;
  }

  AccountId account_id = new_account->GetAccountId();
  accounts_[account_id] = new_account;

  UserId user_id = bank_user->GetUserId();
  account_to_users_[account_id] = {user_id};

  return account_id;
}

std::vector<AccountId> Bank::ListAccounts(std::shared_ptr<BankUser> bank_user) {
  return user_to_accounts_.find(bank_user->GetUserId()) !=
                 user_to_accounts_.end()
             ? user_to_accounts_[bank_user->GetUserId()]
             : std::vector<AccountId>{};
}

eStatus Bank::GiveAccess(AccountId account_id, std::shared_ptr<BankUser> owner,
                         std::shared_ptr<BankUser> coowner) {
  if (!CheckAccess(account_id, owner)) {
    return eStatus::eDenied;
  }
  if (users_.find(coowner->GetUserId()) == users_.end()) {
    return eStatus ::eDenied;
  }

  user_to_accounts_[coowner->GetUserId()].emplace_back(account_id);
  account_to_users_[account_id].emplace_back(coowner->GetUserId());

  return eStatus::eOk;
}

Money Bank::GetBalance(AccountId account_id,
                       std::shared_ptr<BankUser> bank_user) {
  if (!CheckAccess(account_id, bank_user)) {
    return 0;
  }

  return accounts_[account_id]->GetBalance();
}

eStatus Bank::Transfer(AccountId source_id, std::shared_ptr<BankUser> source,
                       AccountId target_id, Money delta) {
  throw std::runtime_error("transfer unimplemented");
  return eStatus::eDenied;  // TODO
}

eStatus Bank::Withdraw(AccountId account_id, Money delta,
                       std::shared_ptr<BankUser> bank_user) {
  if (!CheckAccess(account_id, bank_user)) {
    return eStatus::eDenied;
  }

  OperationStatus status = accounts_[account_id]->Withdraw(delta);

  if (status.status != eStatus::eOk) {
    return status.status;
  }

  operation_to_transaction_[status.operation_id] = next_transaction_id_;
  transaction_to_operation_[next_transaction_id_] = {status.operation_id};
  ++next_transaction_id_;

  return status.status;
}

eStatus Bank::Refill(AccountId account_id, Money delta) {
  OperationStatus status = accounts_[account_id]->Refill(delta);

  if (status.status != eStatus::eOk) {
    return status.status;
  }

  operation_to_transaction_[status.operation_id] = next_transaction_id_;
  transaction_to_operation_[next_transaction_id_] = {status.operation_id};
  ++next_transaction_id_;

  return status.status;
}

void Bank::Upgrade(AccountId account_id, std::shared_ptr<BankUser> bank_user) {
  if (CheckAccess(account_id, bank_user)) {
    accounts_[account_id]->Upgrade();
  }
}

void Bank::Abort(TransactionId transaction_id) {
  throw std::runtime_error("abort error");  // TODO
}

bool Bank::CheckAccess(AccountId account_id,
                       std::shared_ptr<BankUser> bank_user) {
  if (user_to_accounts_.find(account_id) != user_to_accounts_.end()) {
    const auto& accounts = user_to_accounts_[account_id];
    for (AccountId id : accounts) {
      if (account_id == id) {
        return true;
      }
    }
  }

  return false;
}
