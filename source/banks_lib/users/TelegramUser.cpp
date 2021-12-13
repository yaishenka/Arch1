//
// Created by wasd on 10.12.2021.
//

#include "TelegramUser.hpp"

using namespace banks;

TelegramUser::TelegramUser(UserInfo user_info) : IUser(user_info) {
}

void TelegramUser::Step() {
}

void TelegramUser::CreateAccount(BankId bank_id, eAccountType account_type) {
}

Money TelegramUser::GetBalance(BankId bank_id, AccountId account_id) {
  return 0;
}

std::vector<BankId> TelegramUser::ListBankUsers() {
  return {};
}

std::vector<AccountId> TelegramUser::ListAccounts(BankId bank_id) {
  return {};
}

void TelegramUser::Withdraw(BankId bank_id, AccountId account_id, Money delta) {
}

void TelegramUser::Refill(BankId bank_id, AccountId account_id, Money delta) {
}
