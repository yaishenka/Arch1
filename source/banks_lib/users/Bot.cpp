//
// Created by wasd on 10.12.2021.
//

#include "Bot.hpp"

#include <iostream>
#include <string>

using namespace banks;

Bot::Bot(const UserInfo& user_info,
         const std::vector<std::shared_ptr<Bank>>& banks)
    : IUser(std::move(user_info)),
      input_(std::cin),
      output_(std::cout),
      banks_(banks) {
}

void Bot::Step() {
  while (true) {
    std::string token;
    input_ >> token;

    if (token == "stop") {
      break;
    } else if (token == "create") {
      ProcessCreate();
    } else if (token == "balance") {
      ProcessBalance();
    } else if (token == "list") {
      ProcessList();
    } else if (token == "operate") {
      ProcessOperation();
    }
  }
}

void Bot::CreateAccount(BankId bank_id, eAccountType account_type) {
  if (!bank_users_mapping_.contains(bank_id)) {
    bank_users_mapping_[bank_id] = banks_[bank_id]->CreateBankUser(user_info_);
    banks_users_.emplace_back(bank_id);
  }

  bank_users_mapping_[bank_id]->CreateAccount(account_type);
}

Money Bot::GetBalance(BankId bank_id, AccountId account_id) {
  return bank_users_mapping_[bank_id]->GetBalance(account_id);
}

std::vector<BankId> Bot::ListBankUsers() {
  return banks_users_;
}

std::vector<AccountId> Bot::ListAccounts(BankId bank_id) {
  return bank_users_mapping_[bank_id]->ListAccounts();
}

void Bot::Withdraw(BankId bank_id, AccountId account_id, Money delta) {
  bank_users_mapping_[bank_id]->Withdraw(account_id, delta);
}

void Bot::Refill(BankId bank_id, AccountId account_id, Money delta) {
  bank_users_mapping_[bank_id]->Refill(account_id, delta);
}

void Bot::ProcessCreate() {
  output_ << "enter bank id and account type(debit/credit/deposit)\n";

  BankId bank_id;
  std::string type;
  input_ >> bank_id >> type;

  eAccountType account_type;
  if (type == "debit") {
    account_type = eAccountType::eDebit;
  } else if (type == "credit") {
    account_type = eAccountType::eCredit;
  } else if (type == "deposit") {
    account_type = eAccountType::eDeposit;
  } else {
    return;
  }

  CreateAccount(bank_id, account_type);
}

void Bot::ProcessBalance() {
  output_ << "enter bank id and account id\n";

  BankId bank_id;
  AccountId account_id;
  input_ >> bank_id >> account_id;

  Money money = GetBalance(bank_id, account_id);
  output_ << "[balance] " << money << "\n";
}

void Bot::ProcessList() {
  std::string token;
  input_ >> token;

  if (token == "banks") {
    auto banks = ListBankUsers();
    for (BankId id : banks) {
      output_ << id << " ";
    }
    output_ << "\n";
  } else if (token == "accounts") {
    output_ << "enter bank id\n";

    BankId bank_id;
    input_ >> bank_id;

    auto accounts = ListAccounts(bank_id);
    for (BankId id : accounts) {
      output_ << id << " ";
    }
    output_ << "\n";
  }
}

void Bot::ProcessOperation() {
  std::string token;
  input_ >> token;

  if (token == "withdraw") {
    BankId bank_id;
    AccountId account_id;
    Money delta;

    output_ << "enter bank id, account id and amount of money\n";
    input_ >> bank_id >> account_id >> delta;

    Withdraw(bank_id, account_id, delta);
  } else if (token == "refill") {
    BankId bank_id;
    AccountId account_id;
    Money delta;

    output_ << "enter bank id, account id and amount of money\n";
    input_ >> bank_id >> account_id >> delta;

    Refill(bank_id, account_id, delta);
  }
}
